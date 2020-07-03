#include<string>
#include<map>
#include<list>

std::map<std::string, std::list<std::string> > get_series_map(void);

class blmsurvey {
    std::string survey_id;
    
    public:
        // Constructors
        blmsurvey(std::string s): survey_id{s} {}
        
        // Print basic information about a survey ID
        void print_info(void);
        
        // Query information from BLM
        void query_survey(void);
        
        // Print the time series data
        void print_survey_data(void);
};
