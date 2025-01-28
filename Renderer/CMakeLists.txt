cmake_minimum_required(VERSION 3.14)
project(Renderer)

# Add the source to this project's executable
add_library(Renderer "Renderer.cpp" "Renderer.h" "Sprite.cpp" "Sprite.h")

# Set the C++ standard if the CMake version is greater than 3.12
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Renderer PROPERTY CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES)
endif()
    
target_include_directories(Renderer PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/include)
target_include_directories(Renderer PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/SDL3/include)

if (WIN32)
    target_link_libraries(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3/SDL3.lib)
    target_link_libraries(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/SDL3_image.lib)
    target_link_libraries(Renderer PRIVATE Setupapi.lib)
    target_link_libraries(Renderer PRIVATE Version.lib)
    target_link_libraries(Renderer PRIVATE Imm32.lib)
    target_link_libraries(Renderer PRIVATE ws2_32.lib)
    target_link_libraries(Renderer PRIVATE winmm.lib)
elseif (UNIX)
    target_link_libraries(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3/libSDL3.so)
    target_link_libraries(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/libSDL3_image.so)
    target_link_libraries(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/libSDL3_image.so.0)
endif()
