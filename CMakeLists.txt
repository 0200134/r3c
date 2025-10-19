cmake_minimum_required(VERSION 3.20)
project(r3c LANGUAGES CXX)

# =====================================================
# 🧱 General Config
# =====================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Binary output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# =====================================================
# 🧰 Compiler & Platform Info
# =====================================================
message(STATUS "=====================================================")
message(STATUS "[r3c] Cross-Platform Build (v6 Stable)")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "=====================================================")

# =====================================================
# 📦 Dependencies: nlohmann/json
# =====================================================
include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)
include_directories(${nlohmann_json_SOURCE_DIR}/include)

# =====================================================
# ⚙️ Source Files
# =====================================================
file(GLOB SRC_FILES
    src/main.cpp
    src/pipeline.cpp
    src/transpiler.cpp
    src/pkgmgr.cpp
    src/r3c.cpp
    src/r3cpkg.cpp
    src/manifest.cpp
    src/docgen.cpp
    src/formatter.cpp
    src/tester.cpp
    src/stdlib_r3c.cpp
)

# remove accidental stubs if they exist
list(FILTER SRC_FILES EXCLUDE REGEX "r3c_stub.cpp")

# =====================================================
# 🧩 Target
# =====================================================
add_executable(r3c ${SRC_FILES})
target_include_directories(r3c PRIVATE include)
target_link_libraries(r3c PRIVATE nlohmann_json::nlohmann_json)

# =====================================================
# 🧪 NASM Optional
# =====================================================
find_program(NASM_EXECUTABLE nasm)
if(NASM_EXECUTABLE)
    message(STATUS "✅ NASM found: ${NASM_EXECUTABLE}")
else()
    message(WARNING "⚠️ NASM not found — skipping ASM emit")
endif()

# =====================================================
# 🧩 Build Info Summary
# =====================================================
message(STATUS "✅ Real json.hpp managed by FetchContent (no stub needed)")
message(STATUS "✅ CMake build configured successfully")
