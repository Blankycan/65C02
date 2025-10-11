#include "cpu.h"
#include "instructions.h"

CPU::CPU() {
  reset();
}

CPU::~CPU() {}

void CPU::reset() {
  pc = 0xFFFC;
  sp = 0x00;
  a = 0;
  x = 0;
  y = 0;
  sr.value = 0b00100000;
}