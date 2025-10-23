cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES C CXX ASM)

# ==========================================================
# 🧭 Global Build Settings
# ==========================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ==========================================================
# ⚙️ OS-Specific Optimizations
# ==========================================================
if(WIN32)
  message(STATUS "🪟 Windows build → dynamic CRT")
  add_compile_options(/O2 /DNDEBUG /EHsc)
  add_link_options(/OPT:REF /OPT:ICF)

elseif(APPLE)
  message(STATUS "🍎 macOS build → safe flags (keep symbols)")
  add_compile_options(-O2 -pipe -DNDEBUG -fno-exceptions -fno-rtti)
  add_link_options(-Wl,-dead_strip)

elseif(UNIX)
  message(STATUS "🐧 Linux build → static link & stripped binary")
  add_compile_options(-O2 -pipe -s -DNDEBUG -fno-exceptions -fno-rtti)
  add_link_options(-s -static-libgcc -static-libstdc++)
endif()

# ==========================================================
# 🧩 Directories
# ==========================================================
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
include_directories(${INCLUDE_DIR})

# ==========================================================
# 📁 Source Collection
# ==========================================================
# 모든 cpp/c/asm 파일을 자동 수집
file(GLOB_RECURSE R3C_SOURCES
  "${SRC_DIR}/*.cpp"
  "${SRC_DIR}/*.c"
  "${SRC_DIR}/*.S"
  "${SRC_DIR}/*.asm"
)

# main.cpp는 실행 타겟에서만 사용하므로 제외
list(FILTER R3C_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

# ==========================================================
# 🧱 Library Target
# ==========================================================
add_library(r3c STATIC ${R3C_SOURCES})
set_target_properties(r3c PROPERTIES LINKER_LANGUAGE CXX)

if(UNIX AND NOT WIN32)
  target_link_libraries(r3c pthread dl m)
endif()

# ==========================================================
# 🚀 Executable Target (CLI)
# ==========================================================
set(MAIN_SRC "${SRC_DIR}/main.cpp")

if(EXISTS ${MAIN_SRC})
  add_executable(r3c_cli ${MAIN_SRC})
  target_link_libraries(r3c_cli PRIVATE r3c)
else()
  message(FATAL_ERROR "❌ main.cpp not found in ${SRC_DIR}")
endif()

if(APPLE)
  set_target_properties(r3c_cli PROPERTIES
    XCODE_ATTRIBUTE_ARCHS "arm64;x86_64"
    MACOSX_BUNDLE_GUI_IDENTIFIER "com.r3c.compiler"
  )
endif()

# ==========================================================
# 📦 Install Targets
# ==========================================================
install(TARGETS r3c DESTINATION lib)
install(TARGETS r3c_cli DESTINATION bin)

# ==========================================================
# 🧾 Summary
# ==========================================================
message(STATUS "")
message(STATUS "==========================================================")
message(STATUS " 🧩 R3C LLVM-Free Build Summary (v6.6 LTS Stable)")
message(STATUS "----------------------------------------------------------")
message(STATUS " • Build Type     : ${CMAKE_BUILD_TYPE}")
message(STATUS " • Source Dir     : ${SRC_DIR}")
message(STATUS " • Include Dir    : ${INCLUDE_DIR}")
message(STATUS " • Output Library : ${CMAKE_BINARY_DIR}/libr3c.a")
message(STATUS " • Executable     : ${CMAKE_BINARY_DIR}/r3c_cli")
message(STATUS "==========================================================")
message(STATUS "")
