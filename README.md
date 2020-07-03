# BLS
A C++ interface to get data from the US Bureau of Labor Statistics (BLS). **Note** that BLS is still being developed and so the interfaces are not yet stable.

Dependencies
============
* [gcc](https://gcc.gnu.org/)
* [libcurl](https://curl.haxx.se/libcurl/)
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp)

Installation
============
```sh
$ git clone https://github.com/sarrvesh/BLS.git
$ cd BLS
$ mkdir build
$ cmake ../ 
(or)
$ cmake ../ -Djsoncpp_ROOT=<path to jsoncpp>
$ make
$ make install
```

Basic Usage
===========
The series ID for the U.S. city average, All items survey under the category CPI for All Urban Consumers (CPI-U) is CUUR0000SA0. Create a blssurvey object with
```
blssurvey name("CUUR0000SA0");
```
You can get some basic information about this survey with 
```
name.print_info();
```
You can query all available time series data from this survey with 
```
name.query_survey();
```
