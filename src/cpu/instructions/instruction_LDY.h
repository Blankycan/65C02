#pragma once
#include "./instruction_handler.h"

class CPU;

class InstructionLDY : public InstructionHandler {
  public:
    InstructionLDY();
    virtual ~InstructionLDY() = default;

    virtual void execute(CPU& cpu, Memory512Kb& memory, Instruction opcode) override;
};