#build-essential has to be installed
cmake_minimum_required(VERSION 3.16)

# set the project name
project(CellCraft)

include(${CMAKE_SOURCE_DIR}/3rdparty/cmake/mbedtls/mbedtls.cmake)
include(${CMAKE_SOURCE_DIR}/3rdparty/cmake/lwjson/lwjson.cmake)
include(${CMAKE_SOURCE_DIR}/3rdparty/cmake/zlib/zlib.cmake)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include(CTest)
option(CELLCRAFT_TCP_TESTS "Run Linux server status/ping tests (requires Python 3)" OFF)
option(CELLCRAFT_SANITIZERS "Enable address and undefined behavior sanitizers" OFF)
option(CELLCRAFT_COVERAGE "Instrument first-party code for LLVM coverage" OFF)

# Share the production configuration and dependency headers with the tests.
add_library(cellcraft_options INTERFACE)
target_include_directories(cellcraft_options INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/3rdparty"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/CellCraft"
    "${CMAKE_CURRENT_SOURCE_DIR}")
if(UNIX)
    target_compile_options(cellcraft_options INTERFACE -Werror -Wall -Wextra -Wno-unused-parameter)
    target_link_libraries(cellcraft_options INTERFACE m)
endif()
if(MbedTLS_FOUND)
    target_link_libraries(cellcraft_options INTERFACE MbedTLS::mbedtls)
else()
    target_link_libraries(cellcraft_options INTERFACE mbedtls)
endif()
target_link_libraries(cellcraft_options INTERFACE lwjson zlib)
if(CELLCRAFT_SANITIZERS)
    if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux" OR NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR "CELLCRAFT_SANITIZERS requires GCC or Clang on Linux")
    endif()
    target_compile_options(cellcraft_options INTERFACE
        -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer)
    target_link_options(cellcraft_options INTERFACE -fsanitize=address,undefined)
endif()

if(CELLCRAFT_COVERAGE)
    if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux" OR NOT CMAKE_C_COMPILER_ID STREQUAL "Clang")
        message(FATAL_ERROR "CELLCRAFT_COVERAGE requires Clang on Linux")
    endif()
    target_compile_options(cellcraft_options INTERFACE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(cellcraft_options INTERFACE -fprofile-instr-generate)
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/profiles")
endif()

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
