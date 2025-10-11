#include <catch2/catch_test_macros.hpp>
#include "../src/cpu/cpu.h"

TEST_CASE("Read opcode and increment program counter", "[cpu]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0xFF);

  uint8_t opcode = cpu.fetch(memory);
  REQUIRE(opcode == 0xFF);
  REQUIRE(cpu.pc == 0xFFFD);
  REQUIRE(cpu.cycles == 1);
}

TEST_CASE("Execute one cycle will increment program counter", "[cpu]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0xFF); // Unknown opcode

  cpu.execute(memory, 1);
  REQUIRE(cpu.cycles == 1);
  REQUIRE(cpu.pc == 0xFFFD);
}

TEST_CASE("Execute many cycles will increment program counter", "[cpu]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0xFF); // Unknown opcode
  memory.write(0xFFFD, 0xFF);
  memory.write(0xFFFE, 0xFF);
  memory.write(0xFFFF, 0xFF);

  cpu.execute(memory, 4);
  REQUIRE(cpu.cycles == 4);
  REQUIRE(cpu.pc == 0x0000);
}