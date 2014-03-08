/*
 * Chip8 reference at devernay.free.fr/hacks/chip8/C8TECH10.HTM
 */
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "Render.hpp"

class Chip8
{
    public:
        Chip8() {}

        void reset();
        bool load(const std::string&);
        void run();

    private:
        unsigned short pc; // program counter
        unsigned short sp; // stack pointer
        std::array<unsigned char, 4096> memory;
        std::array<unsigned short, 16> stack;
        std::array<unsigned char, 16> vReg; // "V" registers
        unsigned char iReg; // 'I' register
        unsigned char delayTimer;
        unsigned char soundTimer;

        void loadBuiltinSprites();
        void loadSprite(const long long, int&);

        bool performOp(const unsigned short);
        bool handle_0_codes(const unsigned short);
        bool handle_1_codes(const unsigned short);
        bool handle_2_codes(const unsigned short);
        bool handle_3_codes(const unsigned short);
        bool handle_4_codes(const unsigned short);
        bool handle_5_codes(const unsigned short);
        bool handle_6_codes(const unsigned short);
        bool handle_7_codes(const unsigned short);
        bool handle_8_codes(const unsigned short);
        bool handle_9_codes(const unsigned short);
        bool handle_A_codes(const unsigned short);
        bool handle_B_codes(const unsigned short);
        bool handle_C_codes(const unsigned short);
        bool handle_D_codes(const unsigned short);
        bool handle_E_codes(const unsigned short);
        bool handle_F_codes(const unsigned short);
};
