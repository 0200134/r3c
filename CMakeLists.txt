cmake_minimum_required(VERSION 3.20)
project(R3C LANGUAGES CXX)

# =========================================================
# ✅ 기본 설정
# =========================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 빌드 경고 강화
if(MSVC)
    add_compile_options(/W4 /permissive- /EHsc)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 출력 디렉토리 통일
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# =========================================================
# ✅ 헤더 / 소스 경로
# =========================================================
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/*.cpp
)

add_executable(r3c ${SRC_FILES})

# =========================================================
# ✅ NASM 탐지 (Windows/Linux 공용)
# =========================================================
find_program(NASM_EXE nasm
    PATHS
        "C:/Program Files/NASM"
        "C:/Program Files (x86)/NASM"
        /usr/bin
        /usr/local/bin
)
if(NOT NASM_EXE)
    message(FATAL_ERROR "❌ NASM not found! Please install NASM before building.")
else()
    message(STATUS "✅ NASM found: ${NASM_EXE}")
endif()

# =========================================================
# ✅ 테스트 빌드 옵션
# =========================================================
option(R3C_BUILD_TESTS "Build R3C test suite" ON)

if(R3C_BUILD_TESTS)
    enable_testing()
    add_executable(r3c_tests ${CMAKE_SOURCE_DIR}/tests/test_basic.cpp)
    add_test(
        NAME R3C_BasicTest
        COMMAND $<TARGET_FILE:r3c_tests>
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endif()

# =========================================================
# ✅ 설치 / 패키징 (선택)
# =========================================================
install(TARGETS r3c DESTINATION bin)
