#include <catch2/catch_test_macros.hpp>
#include "../src/cpu.h"

TEST_CASE("CPU reset", "[cpu]") {
  CPU cpu;
  cpu.reset();
  REQUIRE(cpu.a == 0);
  REQUIRE(cpu.x == 0);
  REQUIRE(cpu.y == 0);
}