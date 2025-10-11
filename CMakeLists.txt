cmake_minimum_required(VERSION 3.20)
project(65C02 LANGUAGES CXX VERSION 0.1.0)

# Generate compile_commands.json for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==============================
#   Global Compiler Settings
# ==============================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Debug / Release compiler flags
if (MSVC)
    add_compile_options(/W4 /permissive- /Zc:preprocessor)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-nested-anon-types)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-Werror)
    endif()
endif()

# ==============================
#   Emulator Library
# ==============================
add_library(65C02_lib STATIC
    src/cpu.cpp
    src/memory_512Kb.cpp
)
target_include_directories(65C02_lib PUBLIC src)

# ==============================
#   Executable
# ==============================
add_executable(65C02 src/main.cpp)
target_link_libraries(65C02 PRIVATE 65C02_lib)

# ==============================
#   Tests
# ==============================
enable_testing()
add_subdirectory(tests)
