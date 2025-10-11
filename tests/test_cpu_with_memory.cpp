#include <catch2/catch_test_macros.hpp>
#include "../src/cpu/cpu.h"

TEST_CASE("CPU reset", "[cpu, memory]") {
  // CPU start off with a reset
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0x00);
  memory.write(0xFFFD, 0x11);

  cpu.reset(memory);
  REQUIRE(cpu.A == 0);
  REQUIRE(cpu.X == 0);
  REQUIRE(cpu.Y == 0);
  REQUIRE(cpu.PC == 0x1100);
  REQUIRE(cpu.SP == 0xFC);
  REQUIRE(cpu.P.value == 0b00100000);
  REQUIRE(cpu.cycles == 0);
}

TEST_CASE("Read opcode and increment program counter", "[cpu, memory]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0xFF);

  uint8_t opcode = cpu.fetch(memory);
  REQUIRE(opcode == 0xFF);
  REQUIRE(cpu.PC == 0xFFFD);
  REQUIRE(cpu.cycles == 1);
}

TEST_CASE("Execute one cycle will increment program counter", "[cpu, memory]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0xFF); // Unknown opcode

  REQUIRE(cpu.execute(memory, 1) == 0);
  REQUIRE(cpu.cycles == 1);
  REQUIRE(cpu.PC == 0xFFFD);
}

TEST_CASE("Execute many cycles will increment program counter", "[cpu, memory]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0xFF); // Unknown opcode
  memory.write(0xFFFD, 0xFF);
  memory.write(0xFFFE, 0xFF);
  memory.write(0xFFFF, 0xFF);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.cycles == 4);
  REQUIRE(cpu.PC == 0x0000);
}