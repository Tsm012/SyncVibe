cmake_minimum_required(VERSION 3.14)
project(Engine)

add_library(Engine "Engine.cpp" "Engine.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)
endif()

target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Network)
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/Renderer)
    
target_link_libraries(Engine PUBLIC Renderer)
target_link_libraries(Engine PUBLIC Network)

