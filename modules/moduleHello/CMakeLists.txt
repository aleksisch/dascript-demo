cmake_minimum_required (VERSION 3.16)
project (HelloModule)

find_package(DAS REQUIRED)

# add_executable(hello_from_das_cpp main.cpp)
# target_link_libraries(hello_from_das_cpp PRIVATE DAS::libDaScript)

add_library(hello_Module SHARED hello_module.cpp)
target_link_libraries(hello_Module PRIVATE DAS::libDaScriptDyn)
SET_TARGET_PROPERTIES(hello_Module PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}"
    SUFFIX ".mod"
    PREFIX ""
)
