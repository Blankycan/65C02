#pragma once
#include <cstdint>

class CPU {
public:
  CPU();
  ~CPU();

  void reset();

  uint8_t a;
  uint8_t x;
  uint8_t y;
};