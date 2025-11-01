cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ==========================================================
# 🩹 Self-Heal: Missing Version Header
# ==========================================================
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include/r3c_version.h.in")
  message(WARNING "⚠️ Missing include/r3c_version.h.in — auto-generating fallback.")
  file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")
  file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/include/r3c_version.h.in" "#pragma once\n")
  file(APPEND "${CMAKE_CURRENT_SOURCE_DIR}/include/r3c_version.h.in" "#define R3C_VERSION_HASH      \"@GIT_HASH@\"\n")
  file(APPEND "${CMAKE_CURRENT_SOURCE_DIR}/include/r3c_version.h.in" "#define R3C_BUILD_DATE        \"@BUILD_DATE@\"\n")
  file(APPEND "${CMAKE_CURRENT_SOURCE_DIR}/include/r3c_version.h.in" "#define R3C_PLATFORM_NAME     \"@PLATFORM_NAME@\"\n")
  file(APPEND "${CMAKE_CURRENT_SOURCE_DIR}/include/r3c_version.h.in" "#define R3C_LTS_VERSION       \"@LTS_VERSION@\"\n")
endif()

# ==========================================================
# 🔧 CI Environment Override
# ==========================================================
if(DEFINED ENV{CC} AND DEFINED ENV{CXX})
  message(STATUS "🔧 Overriding compiler from environment...")
  set(CMAKE_C_COMPILER "$ENV{CC}" CACHE STRING "C compiler" FORCE)
  set(CMAKE_CXX_COMPILER "$ENV{CXX}" CACHE STRING "C++ compiler" FORCE)
endif()

# ==========================================================
# 🚫 Soft Enforcement: Pure GCC Mode
# ==========================================================
message(STATUS "--------------------------------------------------")
message(STATUS "🔍 Compiler Info:")
message(STATUS "  CMAKE_C_COMPILER       = ${CMAKE_C_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER     = ${CMAKE_CXX_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER_ID  = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")

set(GCC_REQUIRED TRUE)

if(MSVC)
  message(WARNING "⚠️ MSVC detected — switching to MinGW/GCC fallback.")
  set(GCC_REQUIRED TRUE)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|LLVM")
  message(WARNING "⚠️ LLVM/Clang detected — switching to GCC fallback.")
  set(GCC_REQUIRED TRUE)
elseif(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
  message(WARNING "⚠️ AppleClang detected — GCC fallback mode on macOS.")
  set(GCC_REQUIRED TRUE)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  message(STATUS "✅ Pure GCC detected.")
  set(GCC_REQUIRED FALSE)
else()
  message(WARNING "⚠️ Unknown compiler — enforcing GCC fallback.")
  set(GCC_REQUIRED TRUE)
endif()

if(GCC_REQUIRED)
  if(WIN32)
    message(STATUS "🔄 Forcing MinGW (Windows)")
    set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler" FORCE)
    set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler" FORCE)
  elseif(APPLE)
    message(STATUS "🔄 Forcing GCC (macOS)")
    set(CMAKE_C_COMPILER "/opt/homebrew/opt/gcc/bin/gcc-14" CACHE STRING "C compiler" FORCE)
    set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/gcc/bin/g++-14" CACHE STRING "C++ compiler" FORCE)
  else()
    message(STATUS "🔄 Forcing GCC (Linux/Unix)")
    set(CMAKE_C_COMPILER "gcc" CACHE STRING "C compiler" FORCE)
    set(CMAKE_CXX_COMPILER "g++" CACHE STRING "C++ compiler" FORCE)
  endif()
endif()

message(STATUS "✅ Active Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "--------------------------------------------------")

# ==========================================================
# 🧩 Platform Configuration
# ==========================================================
if(WIN32)
  add_compile_definitions(R3C_WINDOWS)
  set(EXTRA_LIBS ws2_32)
elseif(APPLE)
  add_compile_definitions(R3C_MACOS)
  set(EXTRA_LIBS m)
elseif(UNIX)
  add_compile_definitions(R3C_LINUX)
  set(EXTRA_LIBS pthread dl m)
endif()

# ==========================================================
# 🧠 Embedded Build Metadata
# ==========================================================
execute_process(COMMAND git rev-parse --short HEAD OUTPUT_VARIABLE GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE)
string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M:%S")
set(LTS_VERSION "2025–2030 LTSS")

if(WIN32)
  set(PLATFORM_NAME "Windows (MinGW)")
elseif(APPLE)
  set(PLATFORM_NAME "macOS (GCC)")
else()
  set(PLATFORM_NAME "Linux (GCC)")
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/r3c_version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/generated/r3c_version.h
  @ONLY
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)

# ==========================================================
# 🧩 Core Library
# ==========================================================
add_library(r3c STATIC src/transpiler.cpp)
target_include_directories(r3c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(r3c PRIVATE ${EXTRA_LIBS})

# ==========================================================
# 💡 CLI Executable
# ==========================================================
add_executable(r3c_cli src/main.cpp)
target_link_libraries(r3c_cli PRIVATE r3c)

message(STATUS "📦 Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "📁 Output Directory: ${CMAKE_BINARY_DIR}")
message(STATUS "--------------------------------------------------")
message(STATUS "🌍 Embedded Metadata Enabled | LTSS ${LTS_VERSION}")
message(STATUS "--------------------------------------------------")
