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

  memory.write(0xFFFE, Instruction::LDY_IMM);
  memory.write(0xFFFF, 0x00);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.Y == 0x00);
}

TEST_CASE("LDY immediate will affect the zero and negative flags", "[cpu, ldy, immediate, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_IMM);
  memory.write(0xFFFD, 0xFF);
  memory.write(0xFFFE, Instruction::LDY_IMM);
  memory.write(0xFFFF, 0x00);

  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.Y == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  REQUIRE(cpu.execute(memory, 2) == 0);
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

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.Y == 0xFF);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.Y == 0xCA);
}

TEST_CASE("LDY zero page will affect the zero and negative flags", "[cpu, ldy, zero_page, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_ZP);
  memory.write(0xFFFD, 0x00);
  memory.write(0xFFFE, Instruction::LDY_ZP);
  memory.write(0xFFFF, 0x01);
  memory.write(0x0000, 0xFF);
  memory.write(0x0001, 0x00);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.Y == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.Y == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDY zero page, X", "[cpu, ldy, zero_page, x]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_ZPX);
  memory.write(0xFFFD, 0x80);
  cpu.X = 0x0F;
  memory.write(0x008F, 0x21);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.Y == 0x21);

  // Test wrapping around
  cpu.PC = 0xFFFC;
  cpu.X = 0xFF;
  memory.write(0x007F, 0x22);
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.Y == 0x22);
}

TEST_CASE("LDY zero page, X will affect the zero and negative flags", "[cpu, ldy, zero_page, x, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_ZPX);
  memory.write(0xFFFD, 0x00);
  memory.write(0xFFFE, Instruction::LDY_ZPX);
  memory.write(0xFFFF, 0x0A);
  memory.write(0x000F, 0xFF);
  memory.write(0x002B, 0x00);

  cpu.X = 0x0F;
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.Y == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  cpu.X = 0x21;
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.Y == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDY absolute", "[cpu, ldy, absolute]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_ABS);
  memory.write(0xFFFD, 0x01);
  memory.write(0xFFFE, 0x00);
  memory.write(0xFFFF, Instruction::LDY_ABS);
  memory.write(0x0000, 0xFC);
  memory.write(0x0001, 0xFF);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.Y == 0xFF);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.Y == static_cast<uint8_t>(Instruction::LDY_ABS));
}

TEST_CASE("LDY absolute will affect the zero and negative flags", "[cpu, ldy, absolute, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDY_ABS);
  memory.write(0xFFFD, 0x01);
  memory.write(0xFFFE, 0x00);
  memory.write(0xFFFF, Instruction::LDY_ABS);
  memory.write(0x0000, 0xFE);
  memory.write(0x0001, 0xFF);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.Y == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.Y == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}