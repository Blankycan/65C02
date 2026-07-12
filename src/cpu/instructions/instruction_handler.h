#pragma once
#include <algorithm>
#include <vector>
#include "../instructions.h"
#include "../../memory/memory_512Kb.h"

// declare class CPU
class CPU;

class InstructionHandler {
  public:
    InstructionHandler(std::vector<Instruction> instructions):
      instructions(instructions) {}
    virtual ~InstructionHandler() = default;

    virtual void execute(CPU& cpu, Memory512Kb& memory, Instruction opcode) = 0;
    bool instructionIsSupported(Instruction opcode) {
      return std::find(instructions.begin(), instructions.end(), opcode) != instructions.end();
    }

    std::vector<Instruction> instructions;
};