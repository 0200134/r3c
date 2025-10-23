cmake_minimum_required(VERSION 3.22)
project(r3c LANGUAGES C CXX ASM)

# ==========================================================
# 🧭 Build Settings (Cross-Platform / LLVM-Free)
# ==========================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 💡 Default: Release build unless otherwise specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ==========================================================
# ⚙️ OS-Specific Optimizations
# ==========================================================
if(WIN32)
  message(STATUS "🪟 Windows build detected → dynamic CRT, small binary")
  add_compile_options(/O2 /DNDEBUG /EHsc)
  add_link_options(/OPT:REF /OPT:ICF)
else()
  message(STATUS "🐧 Unix-like build detected → static link, stripped binary")
  add_compile_options(-O2 -pipe -s -DNDEBUG -fno-exceptions -fno-rtti)
  add_link_options(-s -static-libgcc -static-libstdc++)
endif()

# ==========================================================
# 🧩 Paths
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
# 🔧 Target
# ==========================================================
add_executable(r3c ${R3C_SOURCES})

# ==========================================================
# 🚀 Link Settings
# ==========================================================
if(UNIX)
  target_link_libraries(r3c pthread dl m)
endif()

# ==========================================================
# 🧹 Size Reduction (Post-Build Strip)
# ==========================================================
if(UNIX)
  add_custom_command(TARGET r3c POST_BUILD
    COMMAND ${CMAKE_STRIP} $<TARGET_FILE:r3c>
    COMMENT "🪶 Stripping symbols to minimize binary size"
  )
endif()

# ==========================================================
# 🧱 Install Step (optional)
# ==========================================================
install(TARGETS r3c DESTINATION bin)

# ==========================================================
# 🪶 Summary
# ==========================================================
message(STATUS "")
message(STATUS "==========================================================")
message(STATUS "R3C LLVM-Free Optimized Build Summary:")
message(STATUS "  • Build Type     : ${CMAKE_BUILD_TYPE}")
message(STATUS "  • Source Dir     : ${SRC_DIR}")
message(STATUS "  • Output Binary  : ${CMAKE_BINARY_DIR}/r3c")
message(STATUS "==========================================================")
message(STATUS "")
else()
    add_custom_target(generate_stubs ALL
        COMMAND bash ${CMAKE_SOURCE_DIR}/scripts/generate_stubs.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "🧩 Generating stubs (Unix Shell)"
    )
endif()

add_dependencies(r3c generate_stubs)

# =========================================================
# 🩹 Safe Stub Generator (Auto-Heal)
# =========================================================
foreach(f ${R3C_SRC})
    if (NOT EXISTS ${f})
        get_filename_component(name ${f} NAME_WE)
        string(REPLACE "." "_" name ${name})        # ✅ Replace dots with underscores
        message(WARNING "⚠️ Missing source file: ${f}, generating stub -> r3c_stub_${name}()")
        file(WRITE ${f} "// Auto-generated stub\nvoid r3c_stub_${name}() {}\n")
    endif()
endforeach()

# =========================================================
# 🧪 Post-build summary
# =========================================================
message(STATUS "=====================================================")
message(STATUS "[r3c] Cross-Platform Autonomous Build (v7.4 Safe Stub Fix)")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "=====================================================")
