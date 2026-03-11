cmake_minimum_required(VERSION 3.14)
project(Network)

# Add the source to this project's executable
add_library(Network Client.cpp Client.h Message.cpp Message.h NetworkConnection.cpp NetworkConnection.h Server.cpp Server.h ThreadSafeByteChannel.h)

# Set the C++ standard if the CMake version is greater than 3.12
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_target_properties(Network PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)
endif()

target_include_directories(Network PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/enet/includes)
target_include_directories(Network PUBLIC ${CMAKE_SOURCE_DIR}/Utilities)

target_link_libraries(Network PRIVATE Utilities)

if (WIN32)
    target_link_libraries(Network PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/enet/enet.lib)
elseif (UNIX)
    target_link_libraries(Network PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/enet/libenet.a)
endif()
