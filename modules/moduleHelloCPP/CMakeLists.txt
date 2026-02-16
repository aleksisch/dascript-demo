cmake_minimum_required (VERSION 3.16)
project (HelloModule)

find_package(DAS REQUIRED)

# Create CPP-AOT file.
ADD_CUSTOM_COMMAND(
    OUTPUT  "hello_module.aot.cpp"
    DEPENDS DAS::daslang_dyn "hello_module.das"
    COMMENT "AOT compiling file"
    # Linking with library => use aotlib and manually reference generated
    # variable in `hello_module.cpp`.
    COMMAND DAS::daslang_dyn -aotlib "hello_module.das" "hello_module.aot.cpp"
)

add_library(hello_ModuleCPP SHARED hello_module.cpp hello_module.aot.cpp)
target_link_libraries(hello_ModuleCPP PRIVATE DAS::libDaScriptDyn)

# For Release build we should manually set
# all flags from original `libDaScript`.
# Once they are added as a target properties
# in `daScript` repo it will be gone from here.
SET(CMAKE_CXX_FLAGS "-DNDEBUG=0")
target_compile_options(hello_ModuleCPP PRIVATE 
    $<$<CXX_COMPILER_ID:GNU>:-fno-rtti>
    $<$<CXX_COMPILER_ID:Clang>:-fno-rtti>
    $<$<CXX_COMPILER_ID:AppleClang>:-fno-rtti>
    $<$<CXX_COMPILER_ID:MSVC>:/GR->
)
SET_TARGET_PROPERTIES(hello_ModuleCPP PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}"
    SUFFIX ".das_module"
    PREFIX ""
)
