cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES C CXX)

# ==========================================================
# 🧱 Build Configuration
# ==========================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ==========================================================
# 🚫 Pure GCC Enforcement (No LLVM / No MSVC)
# ==========================================================
message(STATUS "--------------------------------------------------")
message(STATUS "🔍 Compiler Info:")
message(STATUS "  CMAKE_C_COMPILER       = ${CMAKE_C_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER     = ${CMAKE_CXX_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER_ID  = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")

# ❌ Block MSVC
if(MSVC)
  message(FATAL_ERROR "❌ MSVC not allowed (Pure GCC only).")

# ❌ Block Clang, AppleClang, LLVM variants
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
       CMAKE_CXX_COMPILER_ID MATCHES "AppleClang" OR
       CMAKE_CXX_COMPILER_ID MATCHES "LLVM")
  message(FATAL_ERROR "❌ LLVM/Clang/AppleClang toolchains are not allowed in Pure GCC mode.")

# ❌ Block unknown compilers
elseif(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  message(FATAL_ERROR "❌ Unsupported compiler. Use GCC only.")
endif()

message(STATUS "✅ Verified Pure GCC Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "--------------------------------------------------")

# ==========================================================
# 🧩 Platform-Specific Configuration
# ==========================================================
if(WIN32)
  message(STATUS "🔧 Building for Windows (MinGW / GCC)")
  add_compile_definitions(R3C_WINDOWS)
  set(EXTRA_LIBS ws2_32)

elseif(APPLE)
  message(STATUS "🔧 Building for macOS (Pure GCC mode)")
  add_compile_definitions(R3C_MACOS)
  set(EXTRA_LIBS m)

elseif(UNIX)
  message(STATUS "🔧 Building for Linux (Pure GCC mode)")
  add_compile_definitions(R3C_LINUX)
  set(EXTRA_LIBS pthread dl m)

else()
  message(FATAL_ERROR "❌ Unsupported platform detected.")
endif()

# ==========================================================
# 🧠 Core Library
# ==========================================================
add_library(r3c STATIC src/transpiler.cpp)
target_include_directories(r3c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(r3c PRIVATE ${EXTRA_LIBS})

# ==========================================================
# 💡 CLI Binary
# ==========================================================
add_executable(r3c_cli src/main.cpp)
target_link_libraries(r3c_cli PRIVATE r3c)

# ==========================================================
# 🧾 Build Summary
# ==========================================================
message(STATUS "📦 Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "📁 Output directory: ${CMAKE_BINARY_DIR}")
message(STATUS "--------------------------------------------------")
