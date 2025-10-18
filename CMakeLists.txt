cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES CXX)

# ====================================================
# [R3C] Rust LTS → NASM Full Bootstrap Pipeline
# ====================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ====================================================
# 플랫폼 감지
# ====================================================
if(WIN32)
  message(STATUS "[r3c] Platform: Windows")
  add_definitions(-DPLATFORM_WINDOWS)
  set(ASM_FORMAT win64)
  set(OUT_EXT ".exe")
elseif(APPLE)
  message(STATUS "[r3c] Platform: macOS")
  add_definitions(-DPLATFORM_MACOS)
  set(ASM_FORMAT macho64)
  set(OUT_EXT "")
else()
  message(STATUS "[r3c] Platform: Linux")
  add_definitions(-DPLATFORM_LINUX)
  set(ASM_FORMAT elf64)
  set(OUT_EXT "")
endif()

# ====================================================
# 컴파일러 옵션
# ====================================================
if(MSVC)
  add_compile_options(/O2 /W3 /EHsc)
else()
  add_compile_options(-O2 -Wall -Wextra -Wno-unused-result)
endif()

# ====================================================
# 소스 파일 수집 (.hpp)
# ====================================================
file(GLOB_RECURSE R3C_SOURCES
  src/*.cpp
  src/*.hpp
)

add_executable(r3c ${R3C_SOURCES})
set_target_properties(r3c PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
  OUTPUT_NAME "r3c"
)

# ====================================================
# NASM 감지
# ====================================================
find_program(NASM_EXECUTABLE nasm)
if(NASM_EXECUTABLE)
  message(STATUS "[r3c] NASM found: ${NASM_EXECUTABLE}")
else()
  message(FATAL_ERROR "[r3c] NASM not found! Please install NASM.")
endif()

# ====================================================
# 경로 설정
# ====================================================
set(R3C_ASM "${CMAKE_BINARY_DIR}/out_lts.asm")
set(R3C_OBJ "${CMAKE_BINARY_DIR}/out_lts.obj")
set(R3C_EXE "${CMAKE_BINARY_DIR}/out_lts${OUT_EXT}")

# ====================================================
# 트랜스파일 → 어셈블 → 링크 → 실행 자동화
# ====================================================
add_custom_command(
  OUTPUT ${R3C_ASM}
  COMMAND $<TARGET_FILE:r3c> --emit-asm --emit-asm-from-rust --asm-out ${R3C_ASM}
  DEPENDS r3c
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "[r3c] Transpiling Rust → NASM..."
)

add_custom_command(
  OUTPUT ${R3C_OBJ}
  COMMAND ${NASM_EXECUTABLE} -f ${ASM_FORMAT} ${R3C_ASM} -o ${R3C_OBJ}
  DEPENDS ${R3C_ASM}
  COMMENT "[r3c] Assembling NASM → Object..."
)

add_custom_command(
  OUTPUT ${R3C_EXE}
  COMMAND ${CMAKE_CXX_COMPILER} ${R3C_OBJ} -o ${R3C_EXE}
  DEPENDS ${R3C_OBJ}
  COMMENT "[r3c] Linking Object → Executable..."
)

add_custom_command(
  TARGET r3c POST_BUILD
  COMMAND ${R3C_EXE}
  COMMENT "[r3c] Running final binary..."
)

add_custom_target(pipeline ALL
  DEPENDS ${R3C_EXE}
  COMMENT "[r3c] Full Rust→ASM→OBJ→EXE→RUN pipeline complete."
)

# ====================================================
# 테스트 명령
# ====================================================
enable_testing()
add_test(NAME r3c_test
  COMMAND r3c --emit-asm --test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
