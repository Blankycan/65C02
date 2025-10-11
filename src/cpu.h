#pragma once
#include <cstdint>

struct StatusFlags {
  uint8_t C : 1;    // Carry Flag
  uint8_t Z : 1;    // Zero Flag
  uint8_t I : 1;    // Interrupt Disable Flag
  uint8_t D : 1;    // Decimal Mode Flag
  uint8_t B : 1;    // Break Command Flag
  uint8_t _ : 1;    // Unused
  uint8_t V : 1;    // Overflow Flag
  uint8_t N : 1;    // Negative Flag
};

/**
 65C02 CPU emulator.
 The 65C02 has a 16 bit address space (64K) arranged in 256 pages each of which is 256 bytes long.
 Page 0 ($0000-$00FF) has some special properties involving addressing modes and is very valuable memory.
 Page 1 ($0100-$01FF) is the stack.
 Bytes $FFFA-$FFFB are the NMIB interrupt vector.
 Bytes $FFFC-$FFFD are the reset vector.
 Bytes $FFFE-$FFFF are the IRQ/BRK vector.
 */
class CPU {
public:
  CPU();
  ~CPU();

  void reset();

  uint16_t pc;          // Program Counter
  uint8_t sp;           // Stack Pointer (256 byte stack located between 0x0100 and 0x01FF)
  // Registers
  uint8_t a;            // Accumulator
  uint8_t x;            // X Register
  uint8_t y;            // Y Register

  // Status Register (from 7 [highest] to 0 [lowest]): NV-BDIZC
  union {
    uint8_t value;
    StatusFlags flags;
  } sr;
};