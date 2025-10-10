#include "cpu.h"

CPU::CPU() {
  reset();
}

CPU::~CPU() {}

void CPU::reset() {
  a = 0;
  x = 0;
  y = 0;
}