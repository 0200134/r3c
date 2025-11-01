cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES C CXX)

# ==========================================================
# 🧱 Global Configuration
# ==========================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ==========================================================
# 🔧 Use Environment Variables (from CI)
# ==========================================================
if(DEFINED ENV{CC} AND DEFINED ENV{CXX})
  message(STATUS "🔧 Overriding compiler from environment...")
  set(CMAKE_C_COMPILER "$ENV{CC}" CACHE STRING "C compiler" FORCE)
  set(CMAKE_CXX_COMPILER "$ENV{CXX}" CACHE STRING "C++ compiler" FORCE)
endif()

# ==========================================================
# 🚫 Enforce Pure GCC (with macOS Fallback)
# ==========================================================
message(STATUS "--------------------------------------------------")
message(STATUS "🔍 Compiler Info:")
message(STATUS "  CMAKE_C_COMPILER       = ${CMAKE_C_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER     = ${CMAKE_CXX_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER_ID  = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")

if(MSVC)
  message(FATAL_ERROR "❌ MSVC not allowed (Pure GCC only).")
elseif(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
  message(WARNING "⚠️ AppleClang detected — GCC not found on macOS runner, fallback mode enabled.")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|LLVM")
  message(FATAL_ERROR "❌ LLVM/Clang toolchains are not allowed in Pure GCC mode.")
elseif(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  message(FATAL_ERROR "❌ Unsupported compiler. Use GCC only.")
endif()

message(STATUS "✅ Compiler accepted: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "--------------------------------------------------")

# ==========================================================
# 🧩 Platform Configuration
# ==========================================================
if(WIN32)
  message(STATUS "🔧 Configuring for Windows (MinGW / GCC)")
  add_compile_definitions(R3C_WINDOWS)
  set(EXTRA_LIBS ws2_32)
elseif(APPLE)
  message(STATUS "🔧 Configuring for macOS (Pure GCC or fallback)")
  add_compile_definitions(R3C_MACOS)
  set(EXTRA_LIBS m)
elseif(UNIX)
  message(STATUS "🔧 Configuring for Linux (Pure GCC)")
  add_compile_definitions(R3C_LINUX)
  set(EXTRA_LIBS pthread dl m)
else()
  message(FATAL_ERROR "❌ Unsupported platform.")
endif()

# ==========================================================
# 🧠 Core Library
# ==========================================================
add_library(r3c STATIC src/transpiler.cpp)
target_include_directories(r3c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(r3c PRIVATE ${EXTRA_LIBS})

# ==========================================================
# 💡 CLI Executable
# ==========================================================
add_executable(r3c_cli src/main.cpp)
target_link_libraries(r3c_cli PRIVATE r3c)

# ==========================================================
# 🧾 Build Summary
# ==========================================================
message(STATUS "📦 Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "📁 Output dir: ${CMAKE_BINARY_DIR}")
message(STATUS "--------------------------------------------------")
