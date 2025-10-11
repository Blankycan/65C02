#include <catch2/catch_test_macros.hpp>
#include "../src/cpu/cpu.h"

TEST_CASE("CPU reset", "[cpu]") {
  // CPU start off with a reset
  CPU cpu;
  REQUIRE(cpu.a == 0);
  REQUIRE(cpu.x == 0);
  REQUIRE(cpu.y == 0);
  REQUIRE(cpu.pc == 0xFFFC);
  REQUIRE(cpu.sp == 0x00);
  REQUIRE(cpu.sr.value == 0b00100010);
  REQUIRE(cpu.cycles == 0);
}

TEST_CASE("Test all bits in the status register", "[cpu]") {
  CPU cpu;
  REQUIRE(cpu.sr.value == 0b00100010);

  cpu.sr.flags.C = 1;
  REQUIRE(cpu.sr.value == 0b00100011);

  cpu.sr.flags.Z = 0;
  REQUIRE(cpu.sr.value == 0b00100001);

  cpu.sr.flags.I = 1;
  REQUIRE(cpu.sr.value == 0b00100101);

  cpu.sr.flags.D = 1;
  REQUIRE(cpu.sr.value == 0b00101101);

  cpu.sr.flags.B = 1;
  REQUIRE(cpu.sr.value == 0b00111101);

  cpu.sr.flags.V = 1;
  REQUIRE(cpu.sr.value == 0b01111101);

  cpu.sr.flags.N = 1;
  REQUIRE(cpu.sr.value == 0b11111101);

  cpu.sr.flags.Z = 1;
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

TEST_CASE("Set the zero flag when the accumulator is zero", "[cpu]") {
  CPU cpu;
  REQUIRE(cpu.sr.flags.Z == 1);
  cpu.a = 0x22;
  cpu.updateStatusRegisterAfterLoadAccumulator();
  REQUIRE(cpu.sr.flags.Z == 0);
  cpu.a = 0x00;
  cpu.updateStatusRegisterAfterLoadAccumulator();
  REQUIRE(cpu.sr.flags.Z == 1);
}

TEST_CASE("Set the negative flag when the accumulator is negative", "[cpu]") {
  CPU cpu;
  REQUIRE(cpu.sr.flags.N == 0);
  cpu.a = 0x80;
  cpu.updateStatusRegisterAfterLoadAccumulator();
  REQUIRE(cpu.sr.flags.N == 1);
  cpu.a = 0x22;
  cpu.updateStatusRegisterAfterLoadAccumulator();
  REQUIRE(cpu.sr.flags.N == 0);
}