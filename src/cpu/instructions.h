#pragma once
#include <cstdint>

enum class Instruction : uint8_t {
  // Load Accumulator
  LDA_IMM = 0xA9,    // Immediate, 2 bytes, 2 cycles
  LDA_ZP = 0xA5,     // Zero Page, 2 bytes, 3 cycles
  LDA_ABS = 0xAD,    // Absolute, 3 bytes, 4 cycles
};