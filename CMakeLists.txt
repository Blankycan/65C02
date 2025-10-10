cmake_minimum_required(VERSION 3.20)
project(Emu65C02 LANGUAGES CXX VERSION 0.1.0)

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
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-Werror)
    endif()
endif()

# ==============================
#   Emulator Library
# ==============================
add_library(emu65c02
    src/main.cpp
    # src/cpu/Cpu65C02.cpp
    # src/cpu/InstructionSet.cpp
    # src/bus/Bus.cpp
    # src/bus/Memory.cpp
)
target_include_directories(emu65c02 PUBLIC src)

# ==============================
#   Executable
# ==============================
add_executable(65C02 src/main.cpp)
target_link_libraries(65C02 PRIVATE emu65c02)

# ==============================
#   Tests
# ==============================
# enable_testing()
# add_subdirectory(tests)
