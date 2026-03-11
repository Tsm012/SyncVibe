cmake_minimum_required (VERSION 3.14)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SyncVibe")

add_subdirectory (Utilities)
add_subdirectory (Renderer)
add_subdirectory (Network)
add_subdirectory (Engine)
add_subdirectory (CLI)
add_subdirectory (Server)
add_subdirectory (Client)
