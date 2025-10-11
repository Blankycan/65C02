#pragma once
#include <cstddef>
#include <cstdint>

/**
 64KB memory for the 65C02, which means 2^16 addresses/words of 8-bit data (So 512Kbit of data).
 Page 0 ($0000-$00FF) has some special properties involving addressing modes and is very valuable memory.
 Page 1 ($0100-$01FF) is the stack.
 Bytes $FFFA-$FFFB are the NMIB interrupt vector.
 Bytes $FFFC-$FFFD are the reset vector.
 Bytes $FFFE-$FFFF are the IRQ/BRK vector.
 */
class Memory512Kb {
  public:
    Memory512Kb();
    ~Memory512Kb();

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

    static constexpr size_t MEMORY_SIZE = 1 << 16; // 64KB
    uint8_t memory[MEMORY_SIZE]; // 64KB
};