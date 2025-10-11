Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(65C02_tests
  test_cpu.cpp
  test_memory_512Kb.cpp
  test_cpu_with_memory.cpp
  test_cpu_lda_instructions.cpp
)
target_link_libraries(65C02_tests
  PRIVATE
  65C02_lib
  Catch2::Catch2WithMain
)

include(CTest)

message(STATUS "Catch2_SOURCE_DIR: ${Catch2_SOURCE_DIR}")
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

include(Catch)
catch_discover_tests(65C02_tests)
