#include "./instruction_LDX.h"
#include <cstdio>
#include "../cpu.h"

InstructionLDX::InstructionLDX():
  InstructionHandler({
    Instruction::LDX_IMM,
    Instruction::LDX_ZP,
    Instruction::LDX_ZPY,
    Instruction::LDX_ABS
  }) {}

void InstructionLDX::execute(CPU& cpu, Memory512Kb& memory, Instruction opcode) {
  switch(opcode) {
    case Instruction::LDX_IMM:
      cpu.X = cpu.fetch(memory);
      cpu.updateStatusRegisterAfterLoadXRegister();
      break;
    case Instruction::LDX_ZP: {
      uint8_t zeroPageAddress = cpu.fetch(memory);
      cpu.X = memory.read(zeroPageAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadXRegister();
      break;
    }
    case Instruction::LDX_ZPY: {
      uint8_t zeroPageAddress = cpu.fetch(memory);
      zeroPageAddress += cpu.Y;
      cpu.cycles++;
      cpu.X = memory.read(zeroPageAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadXRegister();
      break;
    }
    case Instruction::LDX_ABS: {
      // Reads first low byte, then high byte
      uint16_t absoluteAddress = cpu.fetch(memory) | cpu.fetch(memory) << 8;
      cpu.X = memory.read(absoluteAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadXRegister();
      break;
    }
    default:
      printf("Unknown LDX opcode: %d\n", (int)opcode);
      break;
  }
}