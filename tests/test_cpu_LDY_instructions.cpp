#include <catch2/catch_test_macros.hpp>
#include "../src/cpu/cpu.h"
#include "../src/memory/memory_512Kb.h"
#include "../src/cpu/instructions.h"

TEST_CASE("LDY immediate", "[cpu, ldy, immediate]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_IMM);
  memory.write(0xFFFD, 0x10);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.Y == 0x10);
  REQUIRE(cpu.cycles == 2);

  memory.write(0xFFFE, Instruction::LDY_IMM);
  memory.write(0xFFFF, 0x00);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.Y == 0x00);
  REQUIRE(cpu.cycles == 4);
}

TEST_CASE("LDY immediate will affect the zero and negative flags", "[cpu, ldy, immediate]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_IMM);
  memory.write(0xFFFD, 0xFF);
  memory.write(0xFFFE, Instruction::LDY_IMM);
  memory.write(0xFFFF, 0x00);

  cpu.execute(memory, 2);
  REQUIRE(cpu.Y == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  cpu.execute(memory, 2);
  REQUIRE(cpu.Y == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDY zero page", "[cpu, ldy, zero_page]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_ZP);
  memory.write(0xFFFD, 0x00);
  memory.write(0xFFFE, Instruction::LDY_ZP);
  memory.write(0xFFFF, 0x01);
  memory.write(0x0000, Instruction::LDY_ZP);
  memory.write(0x0001, 0xFF);
  memory.write(0x00FF, 0xCA);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.Y == static_cast<uint8_t>(Instruction::LDY_ZP));
  REQUIRE(cpu.cycles == 3);
  
  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.Y == 0xFF);
  REQUIRE(cpu.cycles == 6);
  
  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.Y == 0xCA);
  REQUIRE(cpu.cycles == 9);
}