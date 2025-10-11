#pragma once
#include <cstdint>

struct StatusFlags {
  uint8_t C : 1;    // Carry Flag
  uint8_t Z : 1;    // Zero Flag
  uint8_t I : 1;    // Interrupt Disable Flag
  uint8_t D : 1;    // Decimal Mode Flag
  uint8_t B : 1;    // Break Command Flag
  uint8_t _ : 1;    // Unused, pulled high by default
  uint8_t V : 1;    // Overflow Flag
  uint8_t N : 1;    // Negative Flag
};

/**
 65C02 CPU emulator.
 The 65C02 has an 8-bit microprocessor.
 It has an 8-bit data bus and 8-bit registers.
 But its program counter and address bus is 16-bit allowing it to address 64KB of memory.
 The program counter is always incremented by 1 when the CPU is not executing a branch instruction.
 The address bus is used to address memory and the data bus is used to transfer data between the CPU and memory.
 The data bus is also used to transfer data between the CPU and the registers.
 */
class CPU {
public:
  CPU();
  ~CPU();

  void reset();

  uint16_t pc;          // Program Counter
  uint16_t addressBus;  // Address Bus

  uint8_t dataBus;      // Data Bus
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