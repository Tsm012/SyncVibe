cmake_minimum_required(VERSION 3.14)
project(Utilities)

add_library(Utilities "Utilities.cpp" "Utilities.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Utilities PROPERTY CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)
endif()
