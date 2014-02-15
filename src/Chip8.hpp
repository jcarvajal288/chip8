#include <array>
#include <iostream>
#include <fstream>
#include <GL/freeglut.h>

#include "Render.hpp"

class Chip8
{
    public:
        Chip8() {}

        void reset();
        bool load(const std::string&);
        void run();

    private:
        short pc; // program counter
        short sp; // stack pointer
        std::array<char, 4096> memory;
        std::array<short, 16> stack;
        std::array<char, 16> vReg; // "V" registers
        char iReg; // 'I' register
        char delayTimer;
        char soundTimer;

        void performOp(const short);
};
