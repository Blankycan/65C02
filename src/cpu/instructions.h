#pragma once
#include <cstdint>

enum class Instruction : uint8_t {
  // Load Accumulator
  LDA_IMM = 0xA9,    // Immediate, 2 bytes, 2 cycles
  LDA_ZP  = 0xA5,    // Zero Page, 2 bytes, 3 cycles
  LDA_ABS = 0xAD,    // Absolute, 3 bytes, 4 cycles
  // Load X Register
  LDX_IMM = 0xA2,    // Immediate, 2 bytes, 2 cycles
  LDX_ZP  = 0xA6,    // Zero Page, 2 bytes, 3 cycles
  LDX_ABS = 0xAE,    // Absolute, 3 bytes, 4 cycles
  // Load Y Register
  LDY_IMM = 0xA0,    // Immediate, 2 bytes, 2 cycles
  LDY_ZP  = 0xA4,    // Zero Page, 2 bytes, 3 cycles
  LDY_ABS = 0xAC,    // Absolute, 3 bytes, 4 cycles
};