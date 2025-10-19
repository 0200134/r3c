cmake_minimum_required(VERSION 3.16)
project(r3c LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =====================================================
# [r3c] Cross-Platform Build (v6 Stable)
# =====================================================
message(STATUS "=====================================================")
message(STATUS "[r3c] Cross-Platform Build (v6 Stable)")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "=====================================================")

# =====================================================
# Dependencies
# =====================================================
include(FetchContent)

# ---- nlohmann/json ----
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)
message(STATUS "✅ nlohmann/json included via FetchContent")

# ---- NASM (optional, warn only) ----
find_program(NASM_EXECUTABLE nasm)
if (NASM_EXECUTABLE)
    message(STATUS "✅ NASM found: ${NASM_EXECUTABLE}")
else()
    message(WARNING "⚠️ NASM not found — skipping ASM emit")
endif()

# =====================================================
# Source files
# =====================================================
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

add_executable(r3c ${SRC_FILES} ${HEADER_FILES})

# Include directories
target_include_directories(r3c PRIVATE include)

# Link dependencies
target_link_libraries(r3c PRIVATE nlohmann_json::nlohmann_json)

# =====================================================
# Optional tests
# =====================================================
if (EXISTS "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp")
    add_executable(r3c_tests tests/test_basic.cpp)
    target_link_libraries(r3c_tests PRIVATE nlohmann_json::nlohmann_json)
    message(STATUS "🧪 Test target enabled")
endif()

# =====================================================
# Stub logic (deprecated)
# =====================================================
set(STUB_JSON "${CMAKE_SOURCE_DIR}/include/nlohmann/json.hpp")
if (NOT EXISTS ${STUB_JSON})
    message(STATUS "✅ Real json.hpp managed by FetchContent (no stub needed)")
else()
    message(WARNING "⚠️ Stub json.hpp detected — you can safely delete it.")
endif()

# =====================================================
# Output
# =====================================================
set_target_properties(r3c PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
