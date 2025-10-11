#include "memory_512Kb.h"
#include <cstring>

Memory512Kb::Memory512Kb() {
  memset(memory, 0, sizeof(memory));
}

Memory512Kb::~Memory512Kb() {}

uint8_t Memory512Kb::read(uint16_t address) {
  return memory[address];
}

void Memory512Kb::write(uint16_t address, uint8_t value) {
  memory[address] = value;
}