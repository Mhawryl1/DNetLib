#DNetLib CMAkeLists.txt

cmake_minimum_required(VERSION 3.20)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set global variables for the project provide a way to access the include directory from the user project
set(DNetLib_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include CACHE PATH "DNetLib include directory path" )
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/out/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(DNetLib_LINK_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CACHE PATH "DNetLib link directory path" )


file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

message("DNEtLib PATH: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ")
add_library(DNetLib STATIC ${SOURCES})
target_precompile_headers(DNetLib PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)
target_include_directories(DNetLib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
if(WIN32)
	target_link_libraries(DNetLib PUBLIC ws2_32)
endif()
