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
  # ✅ main 심볼 보존 + 불필요한 섹션 제거
  add_link_options(-Wl,-dead_strip -Wl,-no_pie)

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
file(GLOB_RECURSE R3C_SOURCES
  "${SRC_DIR}/*.cpp"
  "${SRC_DIR}/*.c"
  "${SRC_DIR}/*.S"
  "${SRC_DIR}/*.asm"
)
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
# 🚀 Executable Target
# ==========================================================
set(MAIN_SRC "${SRC_DIR}/main.cpp")
set(FALLBACK_SRC "${SRC_DIR}/_fallback_main.cpp")

if(EXISTS ${MAIN_SRC})
  message(STATUS "🧩 Using main.cpp as entry point")
  add_executable(r3c_cli ${MAIN_SRC})
else()
  message(WARNING "⚠️ main.cpp not found. Using _fallback_main.cpp instead")
  if(EXISTS ${FALLBACK_SRC})
    add_executable(r3c_cli ${FALLBACK_SRC})
  else()
    message(FATAL_ERROR "❌ Neither main.cpp nor _fallback_main.cpp found!")
  endif()
endif()

target_link_libraries(r3c_cli PRIVATE r3c)

# ==========================================================
# 🧪 Post-Build Messages
# ==========================================================
add_custom_command(TARGET r3c_cli POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo ""
  COMMAND ${CMAKE_COMMAND} -E echo "==============================================="
  COMMAND ${CMAKE_COMMAND} -E echo "✅ R3C CLI built successfully!"
  COMMAND ${CMAKE_COMMAND} -E echo "👉 Output: ${CMAKE_BINARY_DIR}/r3c_cli"
  COMMAND ${CMAKE_COMMAND} -E echo "==============================================="
)

# ==========================================================
# 📦 Install
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
