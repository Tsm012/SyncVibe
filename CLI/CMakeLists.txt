add_executable (CLI "CLI.cpp" "CLI.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CLI PROPERTY CXX_STANDARD 20)
endif()
