#pragma once
#include <cstdint>
#include <vector>
#include "memory/memory_512Kb.h"
#include "instructions/instruction_handler.h"

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

  void reset(Memory512Kb& memory);
  uint8_t fetch(Memory512Kb& memory);
  int32_t execute(Memory512Kb& memory, uint32_t cyclesToExecute);

  void updateStatusRegisterAfterLoadAccumulator();

  uint16_t PC;          // Program Counter
  uint16_t addressBus;  // Address Bus

  uint8_t dataBus;      // Data Bus
  uint8_t SP;           // Stack Pointer (256 byte stack located between 0x0100 and 0x01FF)
  // Registers
  uint8_t A;            // Accumulator
  uint8_t X;            // X Register
  uint8_t Y;            // Y Register

  // Status Register (from 7 [highest] to 0 [lowest]): NV-BDIZC
  union {
    // NV-BDIZC
    uint8_t value;
    StatusFlags flags;
  } P;

  std::vector<InstructionHandler*> instructionHandlers;
  uint32_t cycles;      // Cycles that have been executed since last reset
};