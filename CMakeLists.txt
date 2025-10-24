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
# Sources / Includes
# ==========================================================
add_library(r3c STATIC
  src/transpiler.cpp
)

target_include_directories(r3c PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# OS-specific link deps (avoid libdl on macOS)
if(APPLE)
  target_link_libraries(r3c m)
elseif(UNIX)
  target_link_libraries(r3c pthread dl m)
endif()

if(R3C_BUILD_DEMOS)
  add_executable(r3c_cli
    src/main.cpp
  )
  target_link_libraries(r3c_cli r3c)
endif()

# Install rules
include(GNUInstallDirs)
install(TARGETS r3c
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
if(R3C_BUILD_DEMOS)
  install(TARGETS r3c_cli
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})