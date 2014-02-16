/*
 * Chip8 reference at devernay.free.fr/hacks/chip8/C8TECH10.HTM
 */
#include <array>
#include <iostream>
#include <fstream>
#include <stdlib.h>
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

        void performOp(const unsigned short);
        void handle_0_codes(const unsigned short);
        void handle_1_codes(const unsigned short);
        void handle_2_codes(const unsigned short);
        void handle_3_codes(const unsigned short);
        void handle_4_codes(const unsigned short);
        void handle_5_codes(const unsigned short);
        void handle_6_codes(const unsigned short);
        void handle_7_codes(const unsigned short);
        void handle_8_codes(const unsigned short);
        void handle_9_codes(const unsigned short);
        void handle_A_codes(const unsigned short);
        void handle_B_codes(const unsigned short);
        void handle_C_codes(const unsigned short);
        void handle_D_codes(const unsigned short);
        void handle_E_codes(const unsigned short);
        void handle_F_codes(const unsigned short);
};
