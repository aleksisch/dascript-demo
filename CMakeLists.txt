cmake_minimum_required (VERSION 3.16)
project (das-example)

find_package(DAS REQUIRED)

# C++ API is not stable and subject to change.
add_executable(hello_from_das_cpp main.cpp)
target_link_libraries(hello_from_das_cpp PRIVATE DAS::libDaScriptDyn)

# For Release build we should manually set NDEBUG for now. It will be shipped
# with `libDaScript` cmake package soon.
SET(CMAKE_CXX_FLAGS "-DNDEBUG=0")

# Note, there's no static dependencies on submodule.
add_executable(hello_from_das_c main-C.c)
target_link_libraries(hello_from_das_c PRIVATE DAS::libDaScriptDyn)

if(WIN32)
    add_custom_command(TARGET hello_from_das_c POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:hello_from_das_c>
            $<TARGET_FILE_DIR:hello_from_das_c>
        COMMAND_EXPAND_LISTS
        COMMENT "Copying runtime DLLs to output directory"
    )
ENDIF()
