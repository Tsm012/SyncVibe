cmake_minimum_required(VERSION 3.14)
add_executable (Server "Server.cpp" "Server.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Server PROPERTY CXX_STANDARD 20)
endif()
