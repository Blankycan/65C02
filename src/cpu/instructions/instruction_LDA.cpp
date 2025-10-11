#include "./instruction_LDA.h"
#include <cstdio>
#include "../cpu.h"

InstructionLDA::InstructionLDA():
  InstructionHandler({
    Instruction::LDA_IMM,
    Instruction::LDA_ZP,
    Instruction::LDA_ZPX,
    Instruction::LDA_ABS
  }) {}

void InstructionLDA::execute(CPU& cpu, Memory512Kb& memory, Instruction opcode) {
  switch(opcode) {
    case Instruction::LDA_IMM:
      cpu.A = cpu.fetch(memory);
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    case Instruction::LDA_ZP: {
      uint8_t zeroPageAddress = cpu.fetch(memory);
      cpu.A = memory.read(zeroPageAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    }
    case Instruction::LDA_ZPX: {
      uint8_t zeroPageAddress = cpu.fetch(memory);
      zeroPageAddress += cpu.X;
      cpu.cycles++;
      cpu.A = memory.read(zeroPageAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    }
    case Instruction::LDA_ABS: {
      // Reads first low byte, then high byte
      uint16_t absoluteAddress = cpu.fetch(memory) | cpu.fetch(memory) << 8;
      cpu.A = memory.read(absoluteAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    }
    default:
      printf("Unknown LDA opcode: %d\n", (int)opcode);
      break;
  }
}