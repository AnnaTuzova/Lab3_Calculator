cmake_minimum_required(VERSION 2.8) 

project(main)				

set(SOURCE_EXE main.cpp)			

add_executable(main ${SOURCE_EXE})	

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

target_link_libraries(main Calculator_lib)	