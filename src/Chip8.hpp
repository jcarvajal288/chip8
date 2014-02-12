#include <array>
#include <iostream>

class Chip8
{
    public:
        Chip8() {}

        void reset();

    private:
        int pc; // program counter
        int sp; // stack pointer
        std::array<int, 4096> memory;
        std::array<int, 16> stack;
        std::array<int, 16> vReg; // "V" registers
        int iReg; // 'I' register
        int delayTimer;
        int soundTimer;
};
