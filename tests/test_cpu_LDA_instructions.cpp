#include <catch2/catch_test_macros.hpp>
#include "../src/cpu/cpu.h"
#include "../src/memory/memory_512Kb.h"
#include "../src/cpu/instructions.h"

TEST_CASE("LDA immediate", "[cpu, lda, immediate]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_IMM);
  memory.write(0xFFFD, 0x10);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.A == 0x10);

  memory.write(0xFFFE, Instruction::LDA_IMM);
  memory.write(0xFFFF, 0x00);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.A == 0x00);
}

TEST_CASE("LDA immediate will affect the zero and negative flags", "[cpu, lda, immediate]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_IMM);
  memory.write(0xFFFD, 0xFF);
  memory.write(0xFFFE, Instruction::LDA_IMM);
  memory.write(0xFFFF, 0x00);

  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.A == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.A == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDA zero page", "[cpu, lda, zero_page]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ZP);
  memory.write(0xFFFD, 0x00);
  memory.write(0xFFFE, Instruction::LDA_ZP);
  memory.write(0xFFFF, 0x01);
  memory.write(0x0000, Instruction::LDA_ZP);
  memory.write(0x0001, 0xFF);
  memory.write(0x00FF, 0xCA);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.A == static_cast<uint8_t>(Instruction::LDA_ZP));

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.A == 0xFF);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.A == 0xCA);
}

TEST_CASE("LDA zero page will affect the zero and negative flags", "[cpu, lda, zero_page, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ZP);
  memory.write(0xFFFD, 0x00);
  memory.write(0xFFFE, Instruction::LDA_ZP);
  memory.write(0xFFFF, 0x01);
  memory.write(0x0000, 0xFF);
  memory.write(0x0001, 0x00);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.A == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  REQUIRE(cpu.execute(memory, 3) == 0);
  REQUIRE(cpu.A == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDA zero page, X", "[cpu, lda, zero_page, x]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ZPX);
  memory.write(0xFFFD, 0x80);
  cpu.X = 0x0F;
  memory.write(0x008F, 0x21);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0x21);

  // Test wrapping around
  cpu.PC = 0xFFFC;
  cpu.X = 0xFF;
  memory.write(0x007F, 0x22);
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0x22);
}

TEST_CASE("LDA zero page, X will affect the zero and negative flags", "[cpu, lda, zero_page, x, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ZPX);
  memory.write(0xFFFD, 0x00);
  memory.write(0xFFFE, Instruction::LDA_ZPX);
  memory.write(0xFFFF, 0x0A);
  memory.write(0x000F, 0xFF);
  memory.write(0x002B, 0x00);

  cpu.X = 0x0F;
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  cpu.X = 0x21;
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDA absolute", "[cpu, lda, absolute]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ABS);
  memory.write(0xFFFD, 0x01);
  memory.write(0xFFFE, 0x00);
  memory.write(0xFFFF, Instruction::LDA_ABS);
  memory.write(0x0000, 0xFC);
  memory.write(0x0001, 0xFF);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0xFF);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == static_cast<uint8_t>(Instruction::LDA_ABS));
}

TEST_CASE("LDA absolute will affect the zero and negative flags", "[cpu, lda, absolute, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ABS);
  memory.write(0xFFFD, 0x01);
  memory.write(0xFFFE, 0x00);
  memory.write(0xFFFF, Instruction::LDA_ABS);
  memory.write(0x0000, 0xFE);
  memory.write(0x0001, 0xFF);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0xFF);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDA absolute, X", "[cpu, lda, absolute, x]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ABX);
  memory.write(0xFFFD, 0x01);
  memory.write(0xFFFE, 0x00);
  cpu.X = 0x0F;
  memory.write(0x0010, 0x32);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0x32);

  // Test wrapping around
  cpu.PC = 0xFFFC;
  cpu.X = 0xFF;
  memory.write(0x0100, 0x33);
  REQUIRE(cpu.execute(memory, 5) == 0);
  REQUIRE(cpu.A == 0x33);
}

TEST_CASE("LDA absolute, X will affect the zero and negative flags", "[cpu, lda, absolute, x, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ABX);
  memory.write(0xFFFD, 0x01);
  memory.write(0xFFFE, 0x00);
  memory.write(0xFFFF, Instruction::LDA_ABX);
  memory.write(0x0000, 0x01);
  memory.write(0x0001, 0x00);

  memory.write(0x0010, 0xB2);
  memory.write(0x0011, 0x00);

  cpu.X = 0x0F;
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0xB2);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  cpu.X = 0x10;
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}

TEST_CASE("LDA absolute, Y", "[cpu, lda, absolute, y]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ABY);
  memory.write(0xFFFD, 0x01);
  memory.write(0xFFFE, 0x00);
  cpu.Y = 0x0F;
  memory.write(0x0010, 0x32);

  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0x32);

  // Test wrapping around
  cpu.PC = 0xFFFC;
  cpu.Y = 0xFF;
  memory.write(0x0100, 0x33);
  REQUIRE(cpu.execute(memory, 5) == 0);
  REQUIRE(cpu.A == 0x33);
}

TEST_CASE("LDA absolute, Y will affect the zero and negative flags", "[cpu, lda, absolute, y, flags]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, Instruction::LDA_ABY);
  memory.write(0xFFFD, 0x01);
  memory.write(0xFFFE, 0x00);
  memory.write(0xFFFF, Instruction::LDA_ABY);
  memory.write(0x0000, 0x01);
  memory.write(0x0001, 0x00);
  
  memory.write(0x0010, 0xB2);
  memory.write(0x0011, 0x00);

  cpu.Y = 0x0F;
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0xB2);
  REQUIRE(cpu.P.flags.Z == 0);
  REQUIRE(cpu.P.flags.N == 1);

  cpu.Y = 0x10;
  REQUIRE(cpu.execute(memory, 4) == 0);
  REQUIRE(cpu.A == 0x00);
  REQUIRE(cpu.P.flags.Z == 1);
  REQUIRE(cpu.P.flags.N == 0);
}