add_library(SyncVibe "SyncVibe.cpp" "SyncVibe.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SyncVibe PROPERTY CXX_STANDARD 20)
endif()
