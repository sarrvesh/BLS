cmake_minimum_required(VERSION 3.5)
project(BLM)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Set compiler flags
LIST(APPEND CMAKE_CPP_FLAGS "-O2")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Find the libraries
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
find_package(jsoncpp REQUIRED)
include_directories(${jsoncpp_INCLUDE_DIRS})

set(SOURCES 
    ${PROJECT_SOURCE_DIR}/blm_query.cpp
    ${PROJECT_SOURCE_DIR}/blm_survey.cpp)
add_executable(blm_query ${SOURCES})
target_link_libraries(blm_query 
    ${CMAKE_CPP_FLAGS} 
    ${CURL_LIBRARIES} 
    ${jsoncpp_LIBRARIES})
