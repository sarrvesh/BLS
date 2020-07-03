# BLS
A C++ interface to get data from the US Bureau of Labor Statistics (BLS).

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
