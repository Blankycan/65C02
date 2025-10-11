#include <catch2/catch_test_macros.hpp>
#include "../src/cpu/cpu.h"
#include "../src/memory/memory_512Kb.h"

TEST_CASE("LDA immediate", "[cpu]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0xA9);
  memory.write(0xFFFD, 0x10);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.a == 0x10);
  REQUIRE(cpu.cycles == 2);

  memory.write(0xFFFE, 0xA9);
  memory.write(0xFFFF, 0x00);
  REQUIRE(cpu.execute(memory, 2) == 0);
  REQUIRE(cpu.a == 0x00);
  REQUIRE(cpu.cycles == 4);
}

TEST_CASE("LDA immediate will affect the status register", "[cpu]") {
  CPU cpu;
  Memory512Kb memory;
  memory.write(0xFFFC, 0xA9);
  memory.write(0xFFFD, 0xFF);
  memory.write(0xFFFE, 0xA9);
  memory.write(0xFFFF, 0x00);

  REQUIRE(cpu.a == 0);
  REQUIRE(cpu.sr.flags.Z == 1);
  REQUIRE(cpu.sr.flags.N == 0);
  REQUIRE(cpu.sr.value == 0b00100010);

  cpu.execute(memory, 2);
  REQUIRE(cpu.a == 0xFF);
  REQUIRE(cpu.sr.flags.Z == 0);
  REQUIRE(cpu.sr.flags.N == 1);
  REQUIRE(cpu.sr.value == 0b10100000);

  cpu.execute(memory, 2);
  REQUIRE(cpu.a == 0x00);
  REQUIRE(cpu.sr.flags.Z == 1);
  REQUIRE(cpu.sr.flags.N == 0);
  REQUIRE(cpu.sr.value == 0b00100010);
}