#pragma once

enum class Instruction {
  // Load Accumulator
  LDA_IMM = 0xA9,    // Immediate, 2 bytes, 2 cycles
  LDA_ZP = 0xA5,     // Zero Page, 2 bytes, 3 cycles
};