#pragma once
#include "./instruction_handler.h"

class CPU;

class InstructionLDX : public InstructionHandler {
  public:
    InstructionLDX();
    virtual ~InstructionLDX() = default;

    virtual void execute(CPU& cpu, Memory512Kb& memory, Instruction opcode) override;
};