#include <catch2/catch_test_macros.hpp>
#include "../src/memory/memory_512Kb.h"

TEST_CASE("Memory reset", "[memory]") {
  Memory512Kb memory;
  REQUIRE(memory.read(0) == 0);
  REQUIRE(memory.read(Memory512Kb::MEMORY_SIZE - 1) == 0);
}

TEST_CASE("Memory write and read", "[memory]") {
  Memory512Kb memory;
  memory.write(0x0000, 0x10);
  REQUIRE(memory.read(0x0000) == 0x10);
  memory.write(0x0001, 0x20);
  REQUIRE(memory.read(0x0001) == 0x20);
  memory.write(0x0002, 0x30);
  REQUIRE(memory.read(0x0002) == 0x30);

  memory.write(0xFFFF, 0xFF);
  REQUIRE(memory.read(0xFFFF) == 0xFF);
}

TEST_CASE("Read outside of memory", "[memory]") {
  Memory512Kb memory;
  // Read outside of memory will just discard the most significant bit of the address
  REQUIRE(memory.read((uint16_t)Memory512Kb::MEMORY_SIZE) == 0);
  REQUIRE(memory.read((uint16_t)Memory512Kb::MEMORY_SIZE + 1) == 0);
}

TEST_CASE("Write outside of memory", "[memory]") {
  Memory512Kb memory;
  // Write outside of memory will just discard the most significant bit of the address
  REQUIRE(memory.read(0x0000) == 0);
  // Writing to 0x10000 will write to 0x0000
  memory.write((uint16_t)Memory512Kb::MEMORY_SIZE, 0xFF);
  REQUIRE(memory.read((uint16_t)Memory512Kb::MEMORY_SIZE) == 0xFF);
  REQUIRE(memory.read(0x0000) == 0xFF);
  // Writing to 0x10001 will write to 0x0001
  REQUIRE(memory.read(0x0001) == 0);
  memory.write((uint16_t)Memory512Kb::MEMORY_SIZE + 1, 0xFF);
  REQUIRE(memory.read((uint16_t)Memory512Kb::MEMORY_SIZE + 1) == 0xFF);
}