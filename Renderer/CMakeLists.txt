cmake_minimum_required(VERSION 3.14)
project(SyncVibe)

# Add the source to this project's executable
add_executable(Renderer "Renderer.cpp" "Renderer.h")

# Set the C++ standard if the CMake version is greater than 3.12
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Renderer PROPERTY CXX_STANDARD 20)
endif()

# Detect the operating system
if (WIN32)
    # Windows-specific configuration
    message(STATUS "Configuring for Windows")
    
    # Include the dependencies directory in the include path
    target_include_directories(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/include)
    target_include_directories(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3/include)
    
    # Link against SDL3 and SDL3_image using all-keyword signatures
    target_link_libraries(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3/SDL3.lib)
    target_link_libraries(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/SDL3_image.lib)
    
    # Add custom command to move the DLL
    add_custom_command(TARGET Renderer POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/SDL3_image.dll $<TARGET_FILE_DIR:Renderer>/SDL3_image.dll 
                       COMMENT "Moving SDL3_image.dll to the output directory")
                       
elseif (UNIX)
    # Linux-specific configuration
    message(STATUS "Configuring for Linux")
    set(CMAKE_PREFIX_PATH "/usr/local/lib")
    
    # Find SDL3 and SDL3_image
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
    
    # Include the dependencies directory in the include path
    target_include_directories(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/include)
    target_include_directories(Renderer PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/SDL3/include)
    
    # Link against SDL3 and SDL3_image using all-keyword signatures
    target_link_libraries(Renderer PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
endif()