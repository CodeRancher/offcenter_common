# OffcenterCommon

The OffcenterCommon project is a set of C++ libraries of support classes and routines for other offcenter applications and libraries.

## Documentation

[API Reference](https://coderancher.github.io/OffcenterCommon/index.html)

## Installation
This project is hosted on github under user [CodeRancher](https://github.com/CodeRancher).

### Clone
To clone this repository use the git command:
```shell
git clone https://github.com/CodeRancher/OffcenterCommon.git
```
### Build
The most simple build, if dependencies are installed globally.
```shell
cd OffcenterCommon
mkdir build
cd build
cmake ..
make
```

A more complicated build if the libraries are in non-standard locations.
```shell
cd OffcenterCommon
mkdir build
cd build
cmake \
    -DCMAKE_INSTALL_PREFIX=<installation path> \
    -DBUILD_DOC=<ON|OFF> \
    -DCMAKE_PREFIX_PATH="<nlohmann json path>;<cpprestsdk path>" \
    -DBOOST_ROOT=<boost root> \
    -DEASYLOGGINGPP_ROOT=<easyloggingpp root> \
    -DEASYLOGGINGPP_USE_STATIC_LIBS=<ON|OFF> \
    -DAPR_ALTLOCATION=<alt location for apr> \
    -DGTEST_ROOT=<googletest root> \
    ..
make install
```

Important make commands.

| Command | Action |
| ------- | ------ |
| make | Build library. Build documentation if ${BUILD_DOC}=ON |
| make install | Build library and install to ${CMAKE_INSTALL_PREFIX}. Build documentation if ${BUILD_DOC}=ON |
| make doc_doxygen | Build library. Build documentation if ${BUILD_DOC}=ON |


Important cmake build variables.

| Variable | Description | Examples |
| -------- | ----------- | --------------- |
| [CMAKE_INSTALL_PREFIX](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html) | Install directory for `make install`. | e.g. ${HOME}/libs |
| [CMAKE_PREFIX_PATH](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html) | Directories to search during `make`. | ${HOME}/libs/cmake/nlohmann_json;${HOME}/libs/cmake/cpprestsdk |
| BUILD_DOC | Build Doxygen documentation during `make doc_doxygen`. Can be 'ON' or 'OFF'. | ON |
| [BOOST_ROOT](https://cmake.org/cmake/help/latest/module/FindBoost.html) | Boost library location. | e.g. ${HOME}/libs |
| [EASYLOGGINGPP_ROOT](https://github.com/amrayn/easyloggingpp/blob/master/cmake/FindEASYLOGGINGPP.cmake) | Easylogging++ library location. | e.g. ${HOME}/libs |
| [EASYLOGGINGPP_USE_STATIC_LIBS](https://github.com/amrayn/easyloggingpp/blob/master/cmake/FindEASYLOGGINGPP.cmake) | If ${EASYLOGGINGPP_USE_STATIC_LIBS} is ON then static libs are searched. | ON |
| [APR_ALTLOCATION](https://github.com/CodeRancher/OffcenterCommon/blob/main/cmake/FindAPR.cmake) | Alternate location to search for libraries/executables | e.g. ${HOME}/libs |
| [GTEST_ROOT](https://cmake.org/cmake/help/latest/module/FindGTest.html) | The root directory of the Google Test installation. | e.g. ${HOME}/libs |

## Dependencies

| Library | Minimum Version | License |
| ------- | --------------- | ------- |
| [nlohmann json](https://github.com/nlohmann/json) | 3.9.1 | [MIT](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT) |
| [C++ REST SDK](https://github.com/microsoft/cpprestsdk) | 2.10.16 | [MIT](https://github.com/microsoft/cpprestsdk/blob/master/license.txt) |
| [Boost](https://www.boost.org/) | 1.74 | [Boost Software License 1.0](https://www.boost.org/users/license.html) |
| [Easylogging++](https://github.com/amrayn/easyloggingpp) | 9.97.0 | [MIT](https://github.com/amrayn/easyloggingpp/blob/master/LICENSE) |
| [SOCI](https://github.com/SOCI) | v4.0.1 | [GNU LGPL version 2.1](https://github.com/mariadb-corporation/mariadb-connector-cpp/blob/master/COPYING) |
| [GoogleTest](https://github.com/google/googletest) | 1.10.0 | [BSD 3-Clause "New" or "Revised" License (modified)](https://github.com/google/googletest/blob/master/LICENSE) |
| [OpenSSL](https://www.openssl.org) | 1.1.1 | [](https://www.openssl.org/source/license-openssl-ssleay.txt) |

| Tools |
| ----- |
| [Doxygen](https://www.doxygen.nl) |

## Libraries

### amqp

Simplifies connecting to and using an ActiveMQ server. This is a framework to create producers and consumers, automatically receive messages, and simplify configuration of connections to the server.

### amqp_server

Simplified application framework that will create a connection to the ActiveMQ server, accept configuration options from the command line or file, and process messages. The general idea is to create a class inherited from IAmqpServerApp, then override several methods where processing of messages can occur.

### common

Common classes used across other libraries.

### distributed_system

Not implemented

This will be a management system for microservices. It will allow remote nodes to be started, stopped, paused, and resumed. 

### framework

A group of frameworks that simplifies creation of applications. Integrates handling of command line options and config files. 

Pending Development: Remote logging and monitoring of applications.

### program_options

Support for simplifying command line options and config files within applications. Used extensively in the framework.

### rest_server

Simplifies creating a REST server. Has pregenerated command line/config file options for initializing the server.

### schedule

Not implemented

This library will support creation of recurring tasks at intervals. This will be used with heartbeats between different microservices nodes.

### soci

Support for creating SOCI connections to databases.

### threading

Support for application threads, thread pools, and manipulating threads.

## Roadmap
<strong>Missing Functionality</strong>

Add missing functionality.

<strong>Testing</strong>

The library needs testing from end-to-end. There are basic tests and examples for some of the most used calls but the rest of the system needs validation.

<strong>Documentation</strong>
1. Create the missing documenation.
2. Add examples.

## License
[Apache License, Version 2.0](https://github.com/CodeRancher/offcenter_oanda/blob/main/LICENSE)