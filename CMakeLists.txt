cmake_minimum_required (VERSION 3.16)
project (das-example)

include(FetchContent)

FetchContent_Declare(
  dascript
  GIT_REPOSITORY https://github.com/GaijinEntertainment/daScript.git
  GIT_SUBMODULES ""
  GIT_TAG        5c0c5471fb9b0be03cc01303cc1cb56c9eefd362 # current master
)
FetchContent_MakeAvailable(dascript)

SETUP_COMPILER()
add_executable(hello_from_das main.cpp)
target_link_libraries(hello_from_das PRIVATE libDaScript)