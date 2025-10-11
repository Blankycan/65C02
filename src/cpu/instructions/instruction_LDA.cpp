#include "./instruction_LDA.h"
#include "../cpu.h"

InstructionLDA::InstructionLDA():
  InstructionHandler({
    Instruction::LDA_IMM,
    Instruction::LDA_ZP
  }) {}

void InstructionLDA::execute(CPU& cpu, Memory512Kb& memory, Instruction opcode) {
  switch(opcode) {
    case Instruction::LDA_IMM:
      cpu.a = cpu.fetch(memory);
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
    case Instruction::LDA_ZP:
      cpu.a = cpu.fetch(memory);
      cpu.updateStatusRegisterAfterLoadAccumulator();
      break;
  
  }
}