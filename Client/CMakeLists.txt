cmake_minimum_required(VERSION 3.14)

add_executable (Client "Client.cpp" "Client.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Client PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Client PRIVATE ${CMAKE_SOURCE_DIR}/Engine)

target_link_libraries(Client PRIVATE Engine)

if (WIN32)
    add_custom_command(TARGET Client POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/dependencies/SDL3_image/SDL3_image.dll $<TARGET_FILE_DIR:Client>/SDL3_image.dll 
                       COMMENT "Moving SDL3_image.dll to the output directory")
    add_custom_command(TARGET Client POST_BUILD 
                       COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/dependencies/SDL3/SDL3.dll $<TARGET_FILE_DIR:Client>/SDL3.dll 
                       COMMENT "Moving SDL3.dll to the output directory")
endif()

