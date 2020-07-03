#include<iostream>
#include "blm_survey.h"

int main(void) {
    blmsurvey name("CUUR0000SA0");
    name.print_info();
    /*
    try {
        name.query_survey();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    */
    
    
    return 0;
}
