#include <catch2/catch_test_macros.hpp>
#include "../src/cpu.h"

TEST_CASE("CPU reset", "[cpu]") {
  CPU cpu;
  cpu.reset();
  REQUIRE(cpu.a == 0);
  REQUIRE(cpu.x == 0);
  REQUIRE(cpu.y == 0);
  REQUIRE(cpu.pc == 0xFFFC);
  REQUIRE(cpu.sp == 0x00);
  REQUIRE(cpu.sr.value == 0);
}

TEST_CASE("Test all bits in the status register", "[cpu]") {
  CPU cpu;
  cpu.reset();
  REQUIRE(cpu.sr.value == 0b00100000);

  cpu.sr.flags.C = 1;
  REQUIRE(cpu.sr.value == 0b00100001);

  cpu.sr.flags.Z = 1;
  REQUIRE(cpu.sr.value == 0b00100011);

  cpu.sr.flags.I = 1;
  REQUIRE(cpu.sr.value == 0b00100111);

  cpu.sr.flags.D = 1;
  REQUIRE(cpu.sr.value == 0b00101111);

  cpu.sr.flags.B = 1;
  REQUIRE(cpu.sr.value == 0b00111111);

  cpu.sr.flags.V = 1;
  REQUIRE(cpu.sr.value == 0b01111111);

  cpu.sr.flags.N = 1;
  REQUIRE(cpu.sr.value == 0b11111111);
  REQUIRE(cpu.sr.value == 255);

  cpu.sr.value = 32;
  REQUIRE(cpu.sr.flags.C == 0);
  REQUIRE(cpu.sr.flags.Z == 0);
  REQUIRE(cpu.sr.flags.I == 0);
  REQUIRE(cpu.sr.flags.D == 0);
  REQUIRE(cpu.sr.flags.B == 0);
  REQUIRE(cpu.sr.flags.V == 0);
  REQUIRE(cpu.sr.flags.N == 0);
}