# 65C02 Microprocessor emulator
Inspired by http://6502.org/users/obelisk/

## Setup
```
rm -rf build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Run
Run the 65C02 emulator
```
./build/65C02
```
## Test
Run tests manually in console with:
```
./build/tests/65C02_tests -s -r compact
```