cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ==========================================================
# 🧩 Prefer environment CC/CXX over system defaults
# ==========================================================
if(DEFINED ENV{CC} AND DEFINED ENV{CXX})
  set(CMAKE_C_COMPILER "$ENV{CC}" CACHE STRING "C compiler" FORCE)
  set(CMAKE_CXX_COMPILER "$ENV{CXX}" CACHE STRING "C++ compiler" FORCE)
endif()

# ==========================================================
# 🚫 Pure GCC Enforcement
# ==========================================================
message(STATUS "--------------------------------------------------")
message(STATUS "🔍 Compiler Info:")
message(STATUS "  CMAKE_C_COMPILER       = ${CMAKE_C_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER     = ${CMAKE_CXX_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER_ID  = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")

if(MSVC)
  message(FATAL_ERROR "❌ MSVC not allowed (Pure GCC only).")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|LLVM")
  message(FATAL_ERROR "❌ LLVM/Clang/AppleClang toolchains are not allowed in Pure GCC mode.")
elseif(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  message(FATAL_ERROR "❌ Unsupported compiler. Use GCC only.")
endif()

message(STATUS "✅ Verified Pure GCC Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "--------------------------------------------------")

# ==========================================================
# 🧠 Core Library
# ==========================================================
add_library(r3c STATIC src/transpiler.cpp)
target_include_directories(r3c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(WIN32)
  target_compile_definitions(r3c PUBLIC R3C_WINDOWS)
  target_link_libraries(r3c PRIVATE ws2_32)
elseif(APPLE)
  target_compile_definitions(r3c PUBLIC R3C_MACOS)
  target_link_libraries(r3c PRIVATE m)
elseif(UNIX)
  target_compile_definitions(r3c PUBLIC R3C_LINUX)
  target_link_libraries(r3c PRIVATE pthread dl m)
endif()

# ==========================================================
# 🧾 CLI Executable
# ==========================================================
add_executable(r3c_cli src/main.cpp)
target_link_libraries(r3c_cli PRIVATE r3c)

message(STATUS "📦 Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "📁 Output directory: ${CMAKE_BINARY_DIR}")
message(STATUS "--------------------------------------------------")
