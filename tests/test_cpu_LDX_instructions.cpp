#include <catch2/catch_test_macros.hpp>
#include "../src/cpu/cpu.h"
#include "../src/memory/memory_512Kb.h"
#include "../src/cpu/instructions.h"

TEST_CASE("LDX immediate", "[cpu, ldx, immediate]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDX_IMM);
  memory.write(0xFFFD, 0x10);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.X == 0x10);
  REQUIRE(cpu.cycles == 2);

  memory.write(0xFFFE, Instruction::LDX_IMM);
  memory.write(0xFFFF, 0x00);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.X == 0x00);
  REQUIRE(cpu.cycles == 4);
}

TEST_CASE("LDX immediate will affect the zero and negative flags", "[cpu, ldx, immediate]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDX_IMM);
  memory.write(0xFFFD, 0xFF);
  memory.write(0xFFFE, Instruction::LDX_IMM);
  memory.write(0xFFFF, 0x00);

  cpu.execute(memory, 2);
  REQUIRE(cpu.X == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  cpu.execute(memory, 2);
  REQUIRE(cpu.X == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDX zero page", "[cpu, ldx, zero_page]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDX_ZP);
  memory.write(0xFFFD, 0x00);
  memory.write(0xFFFE, Instruction::LDX_ZP);
  memory.write(0xFFFF, 0x01);
  memory.write(0x0000, Instruction::LDX_ZP);
  memory.write(0x0001, 0xFF);
  memory.write(0x00FF, 0xCA);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.X == static_cast<uint8_t>(Instruction::LDX_ZP));
  REQUIRE(cpu.cycles == 3);
  
  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.X == 0xFF);
  REQUIRE(cpu.cycles == 6);
  
  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.X == 0xCA);
  REQUIRE(cpu.cycles == 9);
}