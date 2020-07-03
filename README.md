# BLM
A C++ interface to get data from the US Bureau of Labor Statistics (BLM).

Dependencies
============
* [gcc](https://gcc.gnu.org/)
* [libcurl](https://curl.haxx.se/libcurl/)
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp)

Installation
============
```sh
$ git clone https://github.com/sarrvesh/BLM.git
$ cd BLM
$ mkdir build
$ cmake ../ 
(or)
$ cmake ../ -Djsoncpp_ROOT=<path to jsoncpp>
$ make
$ make install
```
