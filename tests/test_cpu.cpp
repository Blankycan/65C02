#include <catch2/catch_test_macros.hpp>
#include "../src/cpu/cpu.h"

TEST_CASE("CPU initial state", "[cpu]") {
  CPU cpu;
  REQUIRE(cpu.PC == 0xFFFC);
  REQUIRE(cpu.SP == 0xFF);
  REQUIRE(cpu.cycles == 0);
}

TEST_CASE("Test all bits in the status register", "[cpu]") {
  CPU cpu;
  cpu.P.value = 0b00100000;

  cpu.P.flags.C = 1;
  REQUIRE(cpu.P.value == 0b00100001);

  cpu.P.flags.Z = 1;
  REQUIRE(cpu.P.value == 0b00100011);

  cpu.P.flags.I = 1;
  REQUIRE(cpu.P.value == 0b00100111);

  cpu.P.flags.D = 1;
  REQUIRE(cpu.P.value == 0b00101111);

  cpu.P.flags.B = 1;
  REQUIRE(cpu.P.value == 0b00111111);

  cpu.P.flags.V = 1;
  REQUIRE(cpu.P.value == 0b01111111);

  cpu.P.flags.N = 1;
  REQUIRE(cpu.P.value == 0b11111111);

  REQUIRE(cpu.P.value == 255);

  cpu.P.value = 32;
  REQUIRE(cpu.P.flags.C == 0);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.I == 0);
  REQUIRE(cpu.P.flags.D == 0);
  REQUIRE(cpu.P.flags.B == 0);
  REQUIRE(cpu.P.flags.V == 0);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("Set the zero flag when the accumulator is zero", "[cpu]") {
  CPU cpu;
  cpu.A = 0x22;
  cpu.updateStatusRegisterAfterLoadAccumulator();
  REQUIRE(cpu.P.flags.Z == 0);
  cpu.A = 0x00;
  cpu.updateStatusRegisterAfterLoadAccumulator();
  REQUIRE(cpu.P.flags.Z == 1);
}

TEST_CASE("Set the negative flag when the accumulator is negative", "[cpu]") {
  CPU cpu;
  cpu.A = 0x80;
  cpu.updateStatusRegisterAfterLoadAccumulator();
  REQUIRE(cpu.P.flags.N == 1);
  cpu.A = 0x22;
  cpu.updateStatusRegisterAfterLoadAccumulator();
  REQUIRE(cpu.P.flags.N == 0);
}