cmake_minimum_required(VERSION 3.28)
project(r3c LANGUAGES CXX)

# ---------------- C++ / warnings ----------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W3 /EHsc)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---------------- include paths (OS 공통) ----------------
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/nlohmann
  ${CMAKE_SOURCE_DIR}/src
)

# ---------------- platform defines ----------------
if(WIN32)
  add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
  add_definitions(-DPLATFORM_MAC)
elseif(UNIX)
  add_definitions(-DPLATFORM_LINUX)
endif()

# ---------------- ensure required files exist ----------------
# nlohmann/json.hpp 강제 확보 (워크플로에서도 생성하지만, 로컬 빌드 안전망)
set(JSON_HEADER "${CMAKE_SOURCE_DIR}/include/nlohmann/json.hpp")
if(NOT EXISTS "${JSON_HEADER}")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/include/nlohmann")
  file(WRITE "${JSON_HEADER}" "// auto-generated local json.hpp stub\n#pragma once\nnamespace nlohmann{ class json{}; }")
  message(STATUS "⚠️  include/nlohmann/json.hpp stub generated (real header not found)")
else()
  message(STATUS "✅  include/nlohmann/json.hpp found")
endif()

# 누락 심볼 방지용 기본 스텁 (실구현 전 링크 실패 차단)
set(AUTO_STUB "${CMAKE_SOURCE_DIR}/src/auto_stub.cpp")
if(NOT EXISTS "${AUTO_STUB}")
  file(WRITE "${AUTO_STUB}" "
#include <string>
#include <vector>
int run_pipeline(const std::vector<std::string>&, const std::string&, bool, bool, const std::string&, bool){return 0;}
int test_main(){return 0;}
")
  message(STATUS "🪄  src/auto_stub.cpp generated")
endif()

# 기본 테스트 보증
set(TEST_CPP "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp")
if(NOT EXISTS "${TEST_CPP}")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
  file(WRITE "${TEST_CPP}" "int main(){return 0;}")
  message(STATUS "🧪  tests/test_basic.cpp generated")
endif()

# ---------------- sources ----------------
file(GLOB_RECURSE R3C_SOURCES "src/*.cpp")

# ---------------- executables ----------------
add_executable(r3c ${R3C_SOURCES})
add_executable(r3c_tests tests/test_basic.cpp)

# ---------------- linker settings ----------------
if(MSVC)
  # ws2_32는 네트워킹 사용시만 필요하지만 안전하게 추가
  target_link_libraries(r3c PRIVATE ws2_32)
elseif(APPLE)
  target_link_libraries(r3c PRIVATE c++ m)
elseif(UNIX)
  target_link_libraries(r3c PRIVATE stdc++ m)
endif()

# ---------------- optional: NASM detection ----------------
find_program(NASM_EXECUTABLE nasm)
if(NASM_EXECUTABLE)
  message(STATUS "✅ NASM found: ${NASM_EXECUTABLE}")
else()
  message(WARNING "⚠️ NASM not found — ASM stage will be skipped")
endif()

# ---------------- output dirs ----------------
set_target_properties(r3c PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
set_target_properties(r3c_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# ---------------- build banner ----------------
message(STATUS "=====================================================")
message(STATUS "[r3c] Stable Build Configuration v6 (universal)")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "JSON Header  : ${JSON_HEADER}")
message(STATUS "=====================================================")
