#include "./instruction_LDY.h"
#include <cstdio>
#include "../cpu.h"

InstructionLDY::InstructionLDY():
  InstructionHandler({
    Instruction::LDY_IMM,
    Instruction::LDY_ZP,
    Instruction::LDY_ZPX,
    Instruction::LDY_ABS,
    Instruction::LDY_ABX
  }) {}

void InstructionLDY::execute(CPU& cpu, Memory512Kb& memory, Instruction opcode) {
  switch(opcode) {
    case Instruction::LDY_IMM:
      cpu.Y = cpu.fetch(memory);
      cpu.updateStatusRegisterAfterLoadYRegister();
      break;
    case Instruction::LDY_ZP: {
      uint8_t zeroPageAddress = cpu.fetch(memory);
      cpu.Y = memory.read(zeroPageAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadYRegister();
      break;
    }
    case Instruction::LDY_ZPX: {
      uint8_t zeroPageAddress = cpu.fetch(memory);
      zeroPageAddress += cpu.X;
      cpu.cycles++;
      cpu.Y = memory.read(zeroPageAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadYRegister();
      break;
    }
    case Instruction::LDY_ABS: {
      // Reads first low byte, then high byte
      uint16_t absoluteAddress = cpu.fetch(memory) | cpu.fetch(memory) << 8;
      cpu.Y = memory.read(absoluteAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadYRegister();
      break;
    }
    case Instruction::LDY_ABX: {
      uint16_t absoluteAddress = cpu.fetch(memory) | cpu.fetch(memory) << 8;
      // Check if the absolute address is crossing the page boundary, and hi byte changed
      if((absoluteAddress & 0xFF00) != ((absoluteAddress + cpu.X) & 0xFF00)) {
        cpu.cycles++;
      }
      absoluteAddress += cpu.X;
      cpu.Y = memory.read(absoluteAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadYRegister();
      break;
    }
    default:
      printf("Unknown LDY opcode: %d\n", (int)opcode);
      break;
  }
}