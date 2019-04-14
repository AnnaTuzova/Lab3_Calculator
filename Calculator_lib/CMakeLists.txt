cmake_minimum_required(VERSION 2.8) 

project(Calculator_lib)				

set(SOURCE_LIB Calculator.cpp)	
set(HEADER_LIB Calculator.h)

set(CALCULATOR_LIB_DIR Calculator_lib)

add_library(Calculator_lib STATIC ${SOURCE_LIB} ${HEADER_LIB})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")