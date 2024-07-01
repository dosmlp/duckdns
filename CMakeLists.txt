cmake_minimum_required(VERSION 3.16)

project(duckdns VERSION 1.0 LANGUAGES C CXX)

set(OPENSSL_USE_STATIC_LIBS TRUE)
set(CMAKE_CXX_LINK_LIBRARY_FLAG)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)


add_executable(duckdns main.cpp httplib.h json.hpp)
target_link_libraries(duckdns OpenSSL::Crypto OpenSSL::SSL)


#添加链接选项
#target_link_options(${CMAKE_PROJECT_NAME} PRIVATE /LTCG)
