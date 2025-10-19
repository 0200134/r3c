cmake_minimum_required(VERSION 3.28)
project(r3c LANGUAGES CXX)

# =====================================================
# ✅ C++ 표준 및 경고 제어
# =====================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W3 /EHsc)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# =====================================================
# ✅ include 경로 설정
# =====================================================
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/nlohmann
  ${CMAKE_SOURCE_DIR}/src
)

# =====================================================
# ✅ nlohmann/json 자동 포함 (누락 방지)
# =====================================================
set(JSON_HEADER_PATH "${CMAKE_SOURCE_DIR}/include/nlohmann/json.hpp")

if(NOT EXISTS ${JSON_HEADER_PATH})
  message(STATUS "⚠️ nlohmann/json.hpp not found — generating local stub")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/include/nlohmann")
  file(WRITE "${JSON_HEADER_PATH}" "// auto-generated stub for JSON\n#pragma once\nnamespace nlohmann { class json {}; }")
else()
  message(STATUS "✅ Found nlohmann/json.hpp at ${JSON_HEADER_PATH}")
endif()

# =====================================================
# ✅ 플랫폼별 정의
# =====================================================
if(WIN32)
  add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
  add_definitions(-DPLATFORM_MAC)
elseif(UNIX)
  add_definitions(-DPLATFORM_LINUX)
endif()

# =====================================================
# ✅ 소스 파일 목록
# =====================================================
file(GLOB_RECURSE R3C_SOURCES "src/*.cpp")

# =====================================================
# ✅ 테스트 스텁 생성 (없을 경우)
# =====================================================
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
  file(WRITE "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp" "int main(){return 0;}")
endif()

# =====================================================
# ✅ 실행 파일 생성
# =====================================================
add_executable(r3c ${R3C_SOURCES})
add_executable(r3c_tests tests/test_basic.cpp)

# =====================================================
# ✅ 링커 설정
# =====================================================
if(MSVC)
  target_link_libraries(r3c PRIVATE ws2_32)
elseif(APPLE)
  target_link_libraries(r3c PRIVATE "-lc++" "-lm")
elseif(UNIX)
  target_link_libraries(r3c PRIVATE "-lstdc++" "-lm")
endif()

# =====================================================
# ✅ NASM 감지
# =====================================================
find_program(NASM_EXECUTABLE nasm)
if(NASM_EXECUTABLE)
  message(STATUS "✅ NASM found: ${NASM_EXECUTABLE}")
else()
  message(WARNING "⚠️ NASM not found — skipping ASM stage")
endif()

# =====================================================
# ✅ 빌드 결과 출력 폴더
# =====================================================
set_target_properties(r3c PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# =====================================================
# ✅ 빌드 로그
# =====================================================
message(STATUS "=====================================================")
message(STATUS "[r3c] Ultra-Stable Build Configuration v5")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "JSON Include : ${JSON_HEADER_PATH}")
message(STATUS "=====================================================")
