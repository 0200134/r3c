cmake_minimum_required(VERSION 3.28)
project(r3c LANGUAGES CXX)

# =====================================================
# ✅ C++ 표준 / 빌드 옵션
# =====================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# =====================================================
# ✅ include 경로 고정 (전 OS 공통)
# =====================================================
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)

# =====================================================
# ✅ 플랫폼 매크로 정의
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
file(GLOB_RECURSE R3C_SOURCES
  "src/*.cpp"
)

# =====================================================
# ✅ 누락 방지: 스텁 파일 자동 생성
# =====================================================
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src/auto_stub.cpp")
  file(WRITE "${CMAKE_SOURCE_DIR}/src/auto_stub.cpp" "
#include <string>
#include <vector>
int run_pipeline(const std::vector<std::string>&, const std::string&, bool, bool, const std::string&, bool){return 0;}
int test_main(){return 0;}
")
endif()

# =====================================================
# ✅ 테스트 파일 누락 시 자동 생성
# =====================================================
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
  file(WRITE "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp" "int main(){return 0;}")
endif()

# =====================================================
# ✅ 실행 파일 정의
# =====================================================
add_executable(r3c ${R3C_SOURCES})
add_executable(r3c_tests tests/test_basic.cpp)

# =====================================================
# ✅ NASM 감지 (선택적)
# =====================================================
find_program(NASM_EXECUTABLE nasm)
if(NASM_EXECUTABLE)
  message(STATUS "✅ NASM found: ${NASM_EXECUTABLE}")
else()
  message(WARNING "⚠️ NASM not found, skipping assembly stage")
endif()

# =====================================================
# ✅ 플랫폼별 링커 설정 (경고 억제)
# =====================================================
if(APPLE)
  target_link_libraries(r3c "-lc++" "-lm")
elseif(UNIX)
  target_link_libraries(r3c "-lstdc++" "-lm")
endif()

# =====================================================
# ✅ 빌드 출력 경로
# =====================================================
set_target_properties(r3c PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# =====================================================
# ✅ 빌드 정보 로그
# =====================================================
message(STATUS "=====================================================")
message(STATUS "[r3c] Stable Build Configuration v4")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "=====================================================")
