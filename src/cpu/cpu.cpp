#include "cpu.h"
#include <cstdio>
#include "instructions.h"
#include "instructions/instruction_LDA.h"

CPU::CPU() {
  instructionHandlers.push_back(new InstructionLDA());
  PC = 0xFFFC;
  SP = 0xFF;
  cycles = 0;
}

CPU::~CPU() {
  for(InstructionHandler* instructionHandler : instructionHandlers) {
    delete instructionHandler;
  }
  instructionHandlers.clear();
}

void CPU::reset(Memory512Kb& memory) {
  PC = memory.read(0xFFFC) | memory.read(0xFFFD) << 8;
  // Store PCH on Stack, 0x01FF
  // Store PCL on Stack, 0x01FE
  // Store P on Stack, 0x01FD
  SP = 0xFC;
  A = 0;
  X = 0;
  Y = 0;
  P.value = 0b00100000;
  cycles = 0;
}

uint8_t CPU::fetch(Memory512Kb& memory) {
  uint8_t opcode = memory.read(PC);
  PC++;
  cycles++;
  return opcode;
}

int32_t CPU::execute(Memory512Kb& memory, uint32_t cyclesToExecute) {
  uint32_t cyclesStartAt = cycles;

  // While cycles executed is less than cycles to execute, fetch and execute the opcode
  while((cycles - cyclesStartAt) < cyclesToExecute) {
    Instruction opcode = (Instruction)fetch(memory);

    bool instructionFound = false;
    for(InstructionHandler* instructionHandler : instructionHandlers) {
      if(instructionHandler->instructionIsSupported(opcode)) {
        instructionHandler->execute(*this, memory, opcode);
        instructionFound = true;
        break;
      }
    }

    if(!instructionFound) {
      printf("Unknown opcode: %d\n", (int)opcode);
    }
  }
  return int32_t(cycles - cyclesStartAt) - cyclesToExecute;
}

void CPU::updateStatusRegisterAfterLoadAccumulator() {
  // Set zero flag if accumulator is zero
  P.flags.Z = (A == 0);
  // Set negative flag if accumulator is negative
  P.flags.N = (A & 0x80) ? 1 : 0;
}