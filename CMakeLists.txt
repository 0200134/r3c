cmake_minimum_required(VERSION 3.10)
project(r3c LANGUAGES CXX)

# =====================================
# 🔧 기본 설정
# =====================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =====================================
# 🔍 NASM 확인
# =====================================
find_program(NASM_EXECUTABLE nasm)
if (NASM_EXECUTABLE)
    message(STATUS "✅ NASM found: ${NASM_EXECUTABLE}")
else()
    message(FATAL_ERROR "❌ NASM not found. Please install NASM before building.")
endif()

# =====================================
# 📁 소스 파일 목록
# =====================================
set(SRC_FILES
    src/main.cpp
    src/docgen.cpp
    src/formatter.cpp
    src/manifest.cpp
    src/pkgmgr.cpp
    src/r3c.cpp
    src/r3cpkg.cpp
)

# =====================================
# ⚙️ 실행 파일 타깃
# =====================================
add_executable(r3c ${SRC_FILES})

# =====================================
# 💾 출력 디렉토리 지정
# =====================================
set_target_properties(r3c PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# =====================================
# 🧩 추가 include / 링크 설정 (필요시)
# =====================================
# target_include_directories(r3c PRIVATE include)
# target_link_libraries(r3c PRIVATE ...)

# =====================================
# 🧪 조건부 테스트 설정
# =====================================
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/test_basic.cpp")
    message(STATUS "🧪 Test file found → enabling test build...")
    enable_testing()
    add_executable(r3c_tests tests/test_basic.cpp)
    add_test(NAME r3c_tests COMMAND r3c_tests)
else()
    message(WARNING "⚠️ No tests found (tests/test_basic.cpp missing) → skipping test target.")
endif()

# =====================================
# 🧾 빌드 정보 출력
# =====================================
message(STATUS "=====================================================")
message(STATUS "[r3c] Rust → NASM → Executable build pipeline enabled")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build Type  : ${CMAKE_BUILD_TYPE}")
message(STATUS "=====================================================")
