# =========================================================
# 🧱 R3C - Rust Independence Compiler
# Cross-Platform Build System (v6 Safe Stub)
# =========================================================
cmake_minimum_required(VERSION 3.16)
project(r3c LANGUAGES CXX)

# =========================================================
# ⚙️ Build Options
# =========================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Silence some warnings in GitHub CI
add_compile_options(-Wall -Wextra -Wno-unused-parameter)

# =========================================================
# 📦 Dependencies
# =========================================================
include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

include_directories(${nlohmann_json_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# =========================================================
# 🪄 Safe Stub Generator
# =========================================================
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

foreach(src_file ${SRC_FILES})
    # Extract base filename without extension (.cpp)
    get_filename_component(STUB_BASE ${src_file} NAME_WE)

    # Check if file exists and has content
    file(READ ${src_file} FILE_CONTENT)
    string(LENGTH "${FILE_CONTENT}" FILE_SIZE)

    if (FILE_SIZE EQUAL 0)
        file(WRITE ${src_file} "void r3c_stub_${STUB_BASE}() {}\n")
        message(STATUS "🪄 Stub generated: ${STUB_BASE}.cpp")
    endif()
endforeach()

# =========================================================
# 🧩 Source Files
# =========================================================
file(GLOB_RECURSE R3C_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(r3c ${R3C_SOURCES})

# =========================================================
# 🔗 Link Libraries
# =========================================================
target_link_libraries(r3c PRIVATE nlohmann_json::nlohmann_json)

# =========================================================
# 🧪 Tests (optional)
# =========================================================
enable_testing()
add_executable(r3c_tests tests/test_basic.cpp)
target_link_libraries(r3c_tests PRIVATE nlohmann_json::nlohmann_json)
add_test(NAME basic_test COMMAND r3c_tests)

# =========================================================
# 🌍 Install (optional)
# =========================================================
install(TARGETS r3c DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

# =========================================================
# ✅ Build Info
# =========================================================
message(STATUS "=====================================================")
message(STATUS "[r3c] Cross-Platform Build (v6 Safe Stub)")
message(STATUS "C++ Compiler : ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "Source Dir   : ${CMAKE_SOURCE_DIR}")
message(STATUS "=====================================================")
