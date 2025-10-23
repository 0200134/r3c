cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES C CXX ASM)

# ==========================================================
# 🧭 Global Build Settings
# ==========================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 💡 Default to Release build
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ==========================================================
# ⚙️ OS-Specific Optimization Flags
# ==========================================================
if(WIN32)
  message(STATUS "🪟 Windows build → dynamic CRT, small binary")
  add_compile_options(/O2 /DNDEBUG /EHsc)
  add_link_options(/OPT:REF /OPT:ICF)

elseif(APPLE)
  message(STATUS "🍎 macOS build → LLVM libc++, no static gcc")
  add_compile_options(-O2 -pipe -DNDEBUG -fno-exceptions -fno-rtti)
  add_link_options(-Wl,-dead_strip -Wl,-s)

elseif(UNIX)
  message(STATUS "🐧 Linux build → static link, stripped binary")
  add_compile_options(-O2 -pipe -s -DNDEBUG -fno-exceptions -fno-rtti)
  add_link_options(-s -static-libgcc -static-libstdc++)
endif()

# ==========================================================
# 🧩 Include & Source Directories
# ==========================================================
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE R3C_SOURCES
  "${SRC_DIR}/*.cpp"
  "${SRC_DIR}/*.c"
  "${SRC_DIR}/*.S"
  "${SRC_DIR}/*.asm"
)

# ==========================================================
# 🧱 Target Definition
# ==========================================================
add_executable(r3c ${R3C_SOURCES})

# ==========================================================
# 🚀 Linking (Unix/macOS)
# ==========================================================
if(UNIX AND NOT WIN32)
  target_link_libraries(r3c pthread dl m)
endif()

# ==========================================================
# 🧹 Post-Build Strip (Unix/macOS only)
# ==========================================================
if(UNIX AND NOT WIN32)
  add_custom_command(TARGET r3c POST_BUILD
    COMMAND ${CMAKE_STRIP} $<TARGET_FILE:r3c> || true
    COMMENT "🪶 Stripping symbols to minimize binary size"
  )
endif()

# ==========================================================
# 🧱 Install (optional)
# ==========================================================
install(TARGETS r3c DESTINATION bin)

# ==========================================================
# 📜 Summary
# ==========================================================
message(STATUS "")
message(STATUS "==========================================================")
message(STATUS " R3C LLVM-Free Optimized Build Summary")
message(STATUS "----------------------------------------------------------")
message(STATUS "  • Build Type     : ${CMAKE_BUILD_TYPE}")
message(STATUS "  • Source Dir     : ${SRC_DIR}")
message(STATUS "  • Include Dir    : ${INCLUDE_DIR}")
message(STATUS "  • Output Binary  : ${CMAKE_BINARY_DIR}/r3c")
message(STATUS "==========================================================")
message(STATUS "")
