cmake_minimum_required(VERSION 3.14)
project(SyncVibe)

# Add the source to this project's executable
add_executable(Network "Network.cpp" "Network.h")

# Set the C++ standard if the CMake version is greater than 3.12
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Renderer PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Network PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/enet)
