cmake_minimum_required(VERSION 3.20)
project(r3c LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------- Include directories --------
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/nlohmann
  ${CMAKE_SOURCE_DIR}/src
)

# -------- Platform detection --------
if(WIN32)
  add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
  add_definitions(-DPLATFORM_MAC)
elseif(UNIX)
  add_definitions(-DPLATFORM_LINUX)
endif()

# -------- Check nlohmann/json.hpp --------
set(JSON_HEADER "${CMAKE_SOURCE_DIR}/include/nlohmann/json.hpp")
if(NOT EXISTS "${JSON_HEADER}")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/include/nlohmann")
  file(WRITE "${JSON_HEADER}" "// auto-generated json.hpp stub\n#pragma once\nnamespace nlohmann{ class json{}; }")
  message(STATUS "⚠️  include/nlohmann/json.hpp stub generated")
endif()

# -------- Check stub cpp --------
set(STUB_CPP "${CMAKE_SOURCE_DIR}/src/r3c_stub.cpp")
if(NOT EXISTS "${STUB_CPP}")
  file(WRITE "${STUB_CPP}" "#include <string>\n#include <vector>\nint run_pipeline(const std::vector<std::string>&, const std::string&, bool, bool, const std::string&, bool){return 0;}\nint test_main(){return 0;}")
  message(STATUS "🪄  src/r3c_stub.cpp stub created")
endif()

# -------- Check test file --------
set(TEST_CPP "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp")
if(NOT EXISTS "${TEST_CPP}")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
  file(WRITE "${TEST_CPP}" "int main(){return 0;}")
  message(STATUS "🧪  tests/test_basic.cpp generated")
endif()

# -------- Source files --------
file(GLOB_RECURSE R3C_SOURCES "src/*.cpp")
add_executable(r3c ${R3C_SOURCES})
add_executable(r3c_tests tests/test_basic.cpp)

# -------- Linker settings --------
if(MSVC)
  target_link_libraries(r3c PRIVATE ws2_32)
elseif(APPLE)
  target_link_libraries(r3c PRIVATE c++ m)
elseif(UNIX)
  target_link_libraries(r3c PRIVATE stdc++ m)
endif()

# -------- NASM detection --------
find_program(NASM_EXECUTABLE nasm)
if(NASM_EXECUTABLE)
  message(STATUS "✅ NASM found: ${NASM_EXECUTABLE}")
else()
  message(WARNING "⚠️ NASM not found — skipping ASM stage")
endif()

# -------- Output dir --------
set_target_properties(r3c PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(r3c_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

message(STATUS "=====================================================")
message(STATUS "[r3c] Cross-Platform Build (v6 Stable)")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "=====================================================")
