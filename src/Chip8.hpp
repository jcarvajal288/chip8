/*
 * Chip8 reference at devernay.free.fr/hacks/chip8/C8TECH10.HTM
 */
#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include <boost/chrono/chrono_io.hpp>

#include "KeyPad.hpp"
#include "Render.hpp"

typedef boost::chrono::steady_clock Clock;
typedef boost::chrono::duration<long long, boost::micro> Microseconds;

class Chip8
{
    public:
        Chip8() {}

        void reset();
        bool load(const std::string&);
        bool run();

    private:
        Renderer::Screen screen;

        unsigned short pc; // program counter
        unsigned short sp; // stack pointer
        std::array<unsigned char, 4096> memory;
        std::array<unsigned short, 16> stack;
        std::array<unsigned char, 16> vReg; // "V" registers
        unsigned short iReg; // 'I' register
        unsigned char delayTimer;
        unsigned char soundTimer;

        void loadBuiltinSprites();
        void loadSprite(const long long, int&);

        Clock::time_point updateTimers(Clock::time_point);

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

#endif
