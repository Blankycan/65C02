#include "cpu.h"
#include <cstdio>
#include "instructions.h"
#include "instructions/instruction_LDA.h"

CPU::CPU() {
  instructionHandlers.push_back(new InstructionLDA());
  reset();
}

CPU::~CPU() {
  for(InstructionHandler* instructionHandler : instructionHandlers) {
    delete instructionHandler;
  }
  instructionHandlers.clear();
}

void CPU::reset() {
  pc = 0xFFFC;
  sp = 0x00;
  a = 0;
  x = 0;
  y = 0;
  sr.value = 0b00100000;
  updateStatusRegisterAfterLoadAccumulator();
  cycles = 0;
}

void CPU::updateStatusRegisterAfterLoadAccumulator() {
  // Set zero flag if accumulator is zero
  sr.flags.Z = (a == 0);
  // Set negative flag if accumulator is negative
  sr.flags.N = (a & 0x80) ? 1 : 0;
}

uint8_t CPU::fetch(Memory512Kb& memory) {
  uint8_t opcode = memory.read(pc);
  pc++;
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