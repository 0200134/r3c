cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES C CXX)

# ==========================================================
# 🧭 Global Build Settings
# ==========================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

option(R3C_BUILD_DEMOS "Build demo CLI and example pipeline" ON)

# ==========================================================
# ⚙️ Compiler Selection — MinGW only (no MSVC, no LLVM)
# ==========================================================
if(WIN32)
  if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "❌ MSVC/LLVM toolchains are not allowed in Pure MinGW mode.")
  endif()

  # ✅ Force MinGW GCC if not explicitly set
  find_program(MINGW_GCC g++)
  if(MINGW_GCC)
    message(STATUS "✅ Using MinGW GCC compiler: ${MINGW_GCC}")
    set(CMAKE_CXX_COMPILER "${MINGW_GCC}" CACHE FILEPATH "C++ compiler" FORCE)
  else()
    message(FATAL_ERROR "❌ MinGW GCC compiler not found. Install MinGW-w64.")
  endif()
endif()

# ==========================================================
# Sources / Includes
# ==========================================================
add_library(r3c STATIC
  src/transpiler.cpp
)

target_include_directories(r3c PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ==========================================================
# 🧩 Platform-Specific Settings
# ==========================================================
if(WIN32)
  message(STATUS "Configuring for pure MinGW Windows build...")
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
# 🧩 Demo CLI (r3c_cli)
# ==========================================================
if(R3C_BUILD_DEMOS)
  add_executable(r3c_cli src/main.cpp)
  target_link_libraries(r3c_cli PRIVATE r3c)

  # ✅ 동일한 실행파일 경로 보장
  set_target_properties(r3c_cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME "r3c_cli"
  )
endif()

# ==========================================================
# 📦 Install Rules
# ==========================================================
include(GNUInstallDirs)
install(TARGETS r3c
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(R3C_BUILD_DEMOS)
  install(TARGETS r3c_cli
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
