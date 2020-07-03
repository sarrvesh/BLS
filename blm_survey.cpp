#include<iostream>
#include<memory>
#include<stdexcept>
#include<string>
#include<curl/curl.h>
#include <json/json.h>
#include"blm_survey.h"

void blmsurvey::print_info(void) {
    auto series = get_series_map();
    auto itr = series.find(survey_id);
    // Iterator itr points to the (key, value) pair
    // Print the key name
    std::cout << "Series ID: " << itr->first << std::endl;
    // Print the four strings in the list
    std::cout << "Category: " << *(std::next((itr->second).begin(), 0)) << std::endl;
    std::cout << "Sub category: " << *(std::next((itr->second).begin(), 1)) << std::endl;
    std::cout << "Database: " << *(std::next((itr->second).begin(), 2)) << std::endl;
    std::cout << "Survey: " << *(std::next((itr->second).begin(), 3)) << std::endl;
}

std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out) {
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

void blmsurvey::query_survey(void) {
    // Form the final URL
    const std::string url {"https://api.bls.gov/publicAPI/v2/timeseries/data/" + survey_id};
    
    // Setup curl
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    
    // Get HTTP response and cleanup when done
    long httpCode {0};
    std::unique_ptr<std::string> httpData(new std::string());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);
    
    if(httpCode == 200) {
        // Parse httpData with JSON
        Json::Value jsonData;
        Json::Reader jsonReader;
        if(jsonReader.parse(*httpData.get(), jsonData))
        {
            if(jsonData["status"] == "REQUEST_NOT_PROCESSED") {
                throw std::runtime_error("Error: You have reached your daily download limit.");
            }
            else {
                std::cout << jsonData << std::endl;
                std::cout << jsonData["status"] << std::endl;
                auto nItems = jsonData["Results"]["series"][0]["data"].size();
                for(auto& item:jsonData["Results"]["series"][0]["data"]) {
                    std::cout << item << std::endl;
                    //break;
                }
            }
        }
        else {
            throw std::runtime_error("Error: Unable to parse the json input");
        }
    }
    else {
        throw std::runtime_error("Error: Unable to connect to remote server. HTTP code: " + 
                                std::to_string(httpCode));
    }
}

void blmsurvey::print_survey_data(void) {
    std::cout << "I'll print the time series data" << std::endl;
}

std::map<std::string, std::list<std::string> > get_series_map(void) {
    /* Map the series ID to its category, sub category, database, and survey */
    std::map<std::string, std::list<std::string> > series_map {
        {"CUUR0000SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, All items"}
        },
        {"CUUR0000SA0L1E", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, All items less food and energy"}
        },
        {"CUUR0000SAF1", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, Food"}
        },
        {"CUUR0000SA0E", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, Energy"}
        },
        {"CUUR0000SETB01", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, Gasoline, all types"}
        },
        {"CUUR0000SAM", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, Medical care"}
        },
        {"CUUR0000SEMC01", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, Physicians' services"}
        },
        {"CUUR0000SEMD01", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, Hospital services"}
        },
        {"CUUR0000SEMF01", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, Prescription drugs"}
        },
        {"CUUR0000SAH1", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "U.S. city average, Shelter"}
        },
        {"CUUR0100SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "Northeast region, All items"}
        },
        {"CUURS12ASA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "New York, All items"}
        },
        {"CUURS12BSA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "Philadelphia, All items"}
        },
        {"CUUR0300SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "South region, All items"}
        },
        {"CUURS35CSA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "Atlanta, All items"}
        },
        {"CUURS35ASA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "Washington, All items"}
        },
        {"CUUR0200SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "Midwest region, All items"}
        },
        {"", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              ""}
        },
        {"CUURS23ASA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "Chicago, All items"}
        },
        {"CUUR0400SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "West region, All items"}
        },
        {"CUURS49ASA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "Los Angeles, All items"}
        },
        {"CUURS49BSA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for All Urban Consumers (CPI-U)", 
              "San Francisco, All items"}
        },
        
        {"CWUR0000SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, All items"}
        },
        {"CWUR0000SA0L1E", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, All items less food and energy"}
        },
        {"CWUR0000SAF1", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, Food"}
        },
        {"CWUR0000SA0E", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, Energy"}
        },
        {"CWUR0000SETB01", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, Gasoline, all types"}
        },
        {"CWUR0000SAM", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, Medical care"}
        },
        {"CWUR0000SEMC01", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, Physicians' services"}
        },
        {"CWUR0000SEMD01", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, Hospital services"}
        },
        {"CWUR0000SEMF01", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, Prescription drugs"}
        },
        {"CWUR0000SAH1", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "U.S. city average, Shelter"}
        },
        {"CWUR0100SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "Northeast region, All items"}
        },
        {"CWURS12ASA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "New York, All items"}
        },
        {"CWURS12BSA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "Philadelphia, All items"}
        },
        {"CWUR0300SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "South region, All items"}
        },
        {"CWURS35CSA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "Atlanta, All items"}
        },
        {"CWURS35ASA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "Washington, All items"}
        },
        {"CWUR0200SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "Midwest Region, All items"}
        },
        {"CWURS23ASA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "Chicago, All items"}
        },
        {"CWUR0400SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "West region, All items"}
        },
        {"CWURS49ASA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "Los Angeles, All items"}
        },
        {"CWURS49BSA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI for Urban Wage Earners and Clerical Workers (CPI-W)", 
              "San Francisco, All items"}
        },
        
        {"SUUR0000SA0", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "All items"}
        },
        {"SUUR0000SA0L1E", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "All items less food and energy"}
        },
        {"SUUR0000SAF", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Food and beverages"}
        },
        {"SUUR0000SAH", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Housing"}
        },
        {"SUUR0000SAA", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Apparel"}
        },
        {"SUUR0000SAT", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Transportation"}
        },
        {"SUUR0000SAM", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Medical care"}
        },
        {"SUUR0000SAR", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Recreation"}
        },
        {"SUUR0000SAE", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Education and communication"}
        },
        {"SUUR0000SAG", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Other goods and services"}
        },
        {"SUUR0000SA0E", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Energy"}
        },
        {"SUUR0000SAC", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Commodities"}
        },
        {"SUUR0000SAS", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Services"}
        },
        {"SUUR0000SAD", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Durables"}
        },
        {"SUUR0000SAN", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "Chained CPI for All Urban Consumers, U.S. city average (C-CPI-U)", 
              "Nondurables"}
        },
        
        
        {"APU0000704111", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Bacon, sliced, per lb."}
        },
        {"APU0000711211", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Bananas, per lb."}
        },
        {"APU0000702111", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Bread, white, pan, per lb."}
        },
        {"APU0000706111", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Chicken, fresh, whole, per lb."}
        },
        {"APU0000717311", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Coffee, 100%, ground roast, all sizes, per lb."}
        },
        {"APU0000708111", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Eggs, grade A, large, per doz."}
        },
        {"APU0000701111", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Flour, white, all purpose, per lb."}
        },
        {"APU0000709112", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Milk, fresh, whole, fortified, per gal."}
        },
        {"APU0000711311", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Oranges, navel, per lb."}
        },
        {"APU0000701312", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Rice, white, long grain, uncooked, per lb."}
        },
        {"APU0000712311", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Tomatoes, field grown, per lb."}
        },
        {"APU000072610", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Electricity per KWH"}
        },
        {"APU000072511", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Fuel oil #2 per gallon"}
        },
        {"APU00007471A", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Gasoline, all types, per gallon"}
        },
        {"APU000074714", 
             {"Inflation & Prices", 
              "Prices - Consumer", 
              "CPI Average Price Data, U.S. city average (AP)", 
              "Gasoline, unleaded regular, per gallon"}
        },
        /* PRICES - PRODUCER sub category */
        /* PRICES - INTERNATIONAL subcategory*/
        /* Employment category */
        /* Unemployment category */
        /* Pay & benefits category */
        /* Spending & Time Use category */
        /* Productivity category */
        /* Workplace Injuries category */
        /* Occupational requirements category */
        /* Regional resources category */
        /* International category */
        /*
        {"", 
             {"International", 
              "Prices - International", 
              "Import/Export Price Indexes", 
              ""}
        },
        */
    };
    
    return series_map;
}
