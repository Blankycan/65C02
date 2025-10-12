#include "./instruction_LDA.h"
#include <cstdio>
#include "../cpu.h"

InstructionLDA::InstructionLDA():
  InstructionHandler({
    Instruction::LDA_IMM,
    Instruction::LDA_ZP,
    Instruction::LDA_ZPX,
    Instruction::LDA_ABS,
    Instruction::LDA_ABX,
    Instruction::LDA_ABY,
    Instruction::LDA_IDX,
    Instruction::LDA_IDY,
    Instruction::LDA_IDZ
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
    case Instruction::LDA_ABX: {
      uint16_t absoluteAddress = cpu.fetch(memory) | cpu.fetch(memory) << 8;
      // Check if the absolute address is crossing the page boundary, and hi byte changed
      if((absoluteAddress & 0xFF00) != ((absoluteAddress + cpu.X) & 0xFF00)) {
        cpu.cycles++;
      }
      absoluteAddress += cpu.X;
      cpu.A = memory.read(absoluteAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    }
    case Instruction::LDA_ABY: {
      uint16_t absoluteAddress = cpu.fetch(memory) | cpu.fetch(memory) << 8;
      // Check if the absolute address is crossing the page boundary, and hi byte changed
      if((absoluteAddress & 0xFF00) != ((absoluteAddress + cpu.Y) & 0xFF00)) {
        cpu.cycles++;
      }
      absoluteAddress += cpu.Y;
      cpu.A = memory.read(absoluteAddress);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    }
    case Instruction::LDA_IDX: {
      uint8_t zp = cpu.fetch(memory);
      
      // Increase the zero-page pointer by X (takes one cycle)
      uint8_t lo = zp + cpu.X;
      uint8_t hi = zp + cpu.X + 1;
      cpu.cycles += 1;

      uint16_t addr = memory.read(lo) | memory.read(hi) << 8;
      cpu.cycles += 2;

      cpu.A = memory.read(addr);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    }
    case Instruction::LDA_IDY: {
      uint8_t zp = cpu.fetch(memory);

      // Fetch the zero page address
      uint8_t lo = zp;
      uint8_t hi = zp + 1;
      uint16_t base = memory.read(lo) | memory.read(hi) << 8;
      cpu.cycles += 2;

      // Add Y to the read address
      uint16_t addr = base + cpu.Y;

      // Add cycle if page boundary is crossed, and hi byte changed
      if((base & 0xFF00) != ((addr) & 0xFF00)) {
        cpu.cycles++;
      }

      cpu.A = memory.read(addr);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    }
    case Instruction::LDA_IDZ: {
      uint8_t zp = cpu.fetch(memory);

      uint8_t lo = zp;
      uint8_t hi = zp + 1;
      uint16_t addr = memory.read(lo) | memory.read(hi) << 8;
      cpu.cycles += 2;

      cpu.A = memory.read(addr);
      cpu.cycles++;
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    }
    default:
      printf("Unknown LDA opcode: %d\n", (int)opcode);
      break;
  }
}