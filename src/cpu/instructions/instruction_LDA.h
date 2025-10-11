#pragma once
#include "./instruction_handler.h"

class CPU;

class InstructionLDA : public InstructionHandler {
  public:
    InstructionLDA();
    virtual ~InstructionLDA() = default;

    virtual void execute(CPU& cpu, Memory512Kb& memory, Instruction opcode) override;
};