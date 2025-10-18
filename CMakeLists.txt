# ================================================
# R3C - Rust→NASM Transpiler + LTS Bootstrap Compiler
# Cross-Platform CMake Build
# ================================================

cmake_minimum_required(VERSION 3.16...3.30)
cmake_policy(VERSION 3.16)

project(r3c
    VERSION 0.3.0
    DESCRIPTION "Rust LTS Transpiler & NASM Bootstrap Compiler"
    LANGUAGES CXX
)

# ----------------------------------------
# Global Build Settings
# ----------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ----------------------------------------
# Platform Detection
# ----------------------------------------
if (WIN32)
    message(STATUS "[r3c] Platform: Windows")
elseif(APPLE)
    message(STATUS "[r3c] Platform: macOS")
elseif(UNIX)
    message(STATUS "[r3c] Platform: Linux")
else()
    message(WARNING "[r3c] Unknown platform detected!")
endif()

# ----------------------------------------
# Git Commit Hash
# ----------------------------------------
find_package(Git QUIET)
if(Git_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(GIT_HASH "unknown")
endif()

# ----------------------------------------
# Build Date & Compiler Info
# ----------------------------------------
string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M:%S")
set(COMPILER_NAME "${CMAKE_CXX_COMPILER_ID}")
set(COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}")

# Platform Name
if (WIN32)
    set(PLATFORM_NAME "Windows")
elseif(APPLE)
    set(PLATFORM_NAME "macOS")
elseif(UNIX)
    set(PLATFORM_NAME "Linux")
else()
    set(PLATFORM_NAME "Unknown")
endif()

# NASM Version (if available)
find_program(NASM_EXE nasm)
if (NOT NASM_EXE)
    message(FATAL_ERROR "NASM not found. Please install nasm.")
else()
    execute_process(
        COMMAND ${NASM_EXE} -v
        OUTPUT_VARIABLE NASM_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS "[r3c] NASM found: ${NASM_EXE}")
endif()

# ----------------------------------------
# Include directories
# ----------------------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/generated
)

# ----------------------------------------
# Generate build info header
# ----------------------------------------
configure_file(
    ${CMAKE_SOURCE_DIR}/include/r3c_build_info.hpp.in
    ${CMAKE_BINARY_DIR}/generated/r3c_build_info.hpp
    @ONLY
)

# ----------------------------------------
# Dependencies (nlohmann_json)
# ----------------------------------------
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# ----------------------------------------
# Source Files
# ----------------------------------------
file(GLOB SRC_FILES
    src/main.cpp
    src/pkgmgr.cpp
    src/formatter.cpp
    src/tester.cpp
    src/docgen.cpp
    src/transpiler.cpp
    src/stdlib_r3c.cpp
    src/r3cpkg.cpp
    src/r3c.cpp
    src/manifest.cpp
)

# ----------------------------------------
# Executable
# ----------------------------------------
add_executable(r3c ${SRC_FILES})
target_link_libraries(r3c PRIVATE nlohmann_json::nlohmann_json)

# Embed build metadata
target_compile_definitions(r3c PRIVATE
    R3C_VERSION="${PROJECT_VERSION}"
    R3C_GIT_HASH="${GIT_HASH}"
    R3C_BUILD_DATE="${BUILD_DATE}"
    R3C_PLATFORM="${PLATFORM_NAME}"
    R3C_COMPILER_NAME="${COMPILER_NAME}"
    R3C_COMPILER_VERSION="${COMPILER_VERSION}"
    R3C_NASM_VERSION="${NASM_VERSION}"
)

# ----------------------------------------
# Installation
# ----------------------------------------
install(TARGETS r3c DESTINATION bin)

# ----------------------------------------
# Custom Target: Test
# ----------------------------------------
add_custom_target(test
    COMMAND r3c --test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "[r3c] Running internal test"
)
