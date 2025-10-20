cmake_minimum_required(VERSION 3.5...3.30)
project(r3c LANGUAGES CXX)

# =========================================================
# ⚙️ R3C Cross-Platform Autonomous Build (v7.3 Safe Stub)
# =========================================================
# - Fix: stub generation removes .cpp safely
# - Fix: UTF-8 safe MSVC build
# - Fix: JSON FetchContent isolation
# - Tested: macOS (arm64), Linux (x86_64), Windows (MSVC)
# =========================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# =========================================================
# 🧠 Global Policy & Encoding Fixes
# =========================================================
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.13")
    cmake_policy(SET CMP0077 NEW)
endif()
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.5")
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
endif()

# ✅ Fix MSVC UTF-8 encoding issue
if (MSVC)
    add_compile_options(/utf-8 /EHsc /permissive- /W3)
else()
    add_compile_options(-Wall -Wextra -Wno-unused-parameter)
endif()

# =========================================================
# 📦 Dependencies (FetchContent)
# =========================================================
include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# =========================================================
# 🧱 Source Structure
# =========================================================
file(GLOB R3C_SRC CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE R3C_HDR CONFIGURE_DEPENDS "include/**/*.h" "include/**/*.hpp")

add_executable(r3c ${R3C_SRC} ${R3C_HDR})

target_include_directories(r3c PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${nlohmann_json_SOURCE_DIR}/include
)

target_link_libraries(r3c PRIVATE nlohmann_json::nlohmann_json)

# =========================================================
# ⚙️ Safe Stub Generator (fixed v7.3)
# =========================================================
foreach(f ${R3C_SRC})
    if (NOT EXISTS ${f})
        get_filename_component(fname ${f} NAME_WE)  # "docgen.cpp" -> "docgen"
        string(REGEX REPLACE "[^A-Za-z0-9_]" "_" fname ${fname})
        message(WARNING "⚠️ Missing source file: ${fname}, generating stub...")
        file(WRITE ${f} "// Auto-generated stub\nvoid r3c_stub_${fname}() {}\n")
    endif()
endforeach()

# =========================================================
# 🧪 Optional Test Target
# =========================================================
if (EXISTS "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp")
    add_executable(r3c_tests tests/test_basic.cpp)
    target_link_libraries(r3c_tests PRIVATE nlohmann_json::nlohmann_json)
endif()

# =========================================================
# 🧾 Post-build Summary
# =========================================================
message(STATUS "=====================================================")
message(STATUS "[r3c] Cross-Platform Autonomous Build (v7.3 Safe Stub)")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "=====================================================")
