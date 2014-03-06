// this is evil, but used to preserve encapsulation in the tested object
// while being able to access private members for the test
#define private public 

#include "Chip8.hpp"
#include "gtest/gtest.h"

using namespace std;

TEST(Chip8Test, Reset)
{
    Chip8 chip8;
    chip8.reset();
    EXPECT_EQ(chip8.pc, 0x200) << "PC is not 0x200";
    EXPECT_EQ(chip8.sp, 0) << "SP is not 0";

    // start at 80 to account for preloaded sprites
    for(int i=80; i<4096; ++i)
    {
        EXPECT_EQ(chip8.memory.at(i), 0) << "Memory location " << i << " not 0";
    }

    for(int i=0; i<16; ++i)
    {
        EXPECT_EQ(chip8.stack.at(i), 0) << "Stack location " << i << "not 0";
    }

    for(int i=0; i<16; ++i)
    {
        EXPECT_EQ(chip8.vReg.at(i), 0) << "V register" << i << "not 0";
    }

    EXPECT_EQ(chip8.iReg, 0) << "I register not 0";
    EXPECT_EQ(chip8.delayTimer, 0) << "Delay Timer not 0";
    EXPECT_EQ(chip8.soundTimer, 0) << "Sound Timer not 0";
}

TEST(Chip8Test, LoadProgram)
{
    const string testProgram = "./games/MAZE";
    Chip8 chip8;
    chip8.reset();
    chip8.load(testProgram);

    ifstream fileInput;
    fileInput.open(testProgram);
    unsigned int addr = 0x200;

    // check the chip8 memory is the same as the file data
    while(fileInput.good())
    {
        unsigned char b = fileInput.get();
        ASSERT_EQ(b, chip8.memory.at(addr)) << "Memory at location " << hex << addr << " is different";
        addr++;
    }
}

TEST(Chip8Test, opcode_00EE)
{
    Chip8 chip8;
    chip8.reset();
    short memValue = 0x1234;
    int initialSP = 1;
    chip8.stack.at(initialSP) = memValue;
    chip8.sp = initialSP;
    chip8.performOp(0x00EE);
    EXPECT_EQ(chip8.pc, 0x1234) << "Program counter did not get address at top of stack";
    EXPECT_EQ(chip8.sp, initialSP-1) << "Stack pointer did not decremented";
}

TEST(Chip8Test, opcode_1NNN)
{
    Chip8 chip8;
    chip8.reset();
    chip8.performOp(0x1234);
    EXPECT_EQ(chip8.pc, 0x234) << "Program counter was not set to the correct address";
}

TEST(Chip8Test, opcode_2NNN)
{
    Chip8 chip8;
    chip8.reset();
    short initialPC = 0x254;
    chip8.pc = initialPC;
    chip8.performOp(0x2234);
    EXPECT_EQ(chip8.sp, 1) << "Stack pointer was not incremented";
    EXPECT_EQ(chip8.stack.at(chip8.sp), initialPC) << "Initial program counter value was not pushed to top of the stack";
    EXPECT_EQ(chip8.pc, 0x234) << "The program counter was not set to NNN";
}

TEST(Chip8Test, opcode_3xkk)
{
    Chip8 chip8;
    chip8.reset();

    // test if Vx == kk
    short initialPC = chip8.pc;
    chip8.performOp(0x3000);
    EXPECT_EQ(chip8.pc, initialPC + 2) << "The program counter was not incremented by 2.";

    // test if Vx != kk
    initialPC = chip8.pc;
    chip8.performOp(0x3011);
    EXPECT_EQ(chip8.pc, initialPC) << "The program counter's value changed on a negative test.";
}

TEST(Chip8Test, opcode_4xkk)
{
    Chip8 chip8;
    chip8.reset();

    // test if Vx == kk
    short initialPC = chip8.pc;
    chip8.performOp(0x4000);
    EXPECT_EQ(chip8.pc, initialPC) <<  "The program counter's value changed on a positive test.";

    // test if Vx != kk
    initialPC = chip8.pc;
    chip8.performOp(0x4011);
    EXPECT_EQ(chip8.pc, initialPC + 2) << "The program counter was not incremented by 2.";
}

TEST(Chip8Test, opcode_5xy0)
{
    Chip8 chip8;
    chip8.reset();

    // test when Vx = Vy
    short initialPC = chip8.pc;
    chip8.performOp(0x5010);
    EXPECT_EQ(chip8.pc, initialPC + 2) <<  "The program counter's value did not increment when Vx = Vy";

    // test when Vx != Vy
    chip8.vReg.at(0) = 4;
    initialPC = chip8.pc;
    chip8.performOp(0x5010);
    EXPECT_EQ(chip8.pc, initialPC) <<  "The program counter changed when Vx != Vy";
}

TEST(Chip8Test, opcode_6xkk)
{
    Chip8 chip8;
    chip8.reset();
    
    for(int i=0; i<0xF; ++i)
    {
        chip8.performOp(0x6011 + (0x100 * i));
        EXPECT_EQ(chip8.vReg.at(i), 0x11) << "Empty VReg " << i << " not set correctly.";

        chip8.performOp(0x6022 + (0x100 * i));
        EXPECT_EQ(chip8.vReg.at(i), 0x22) << "Filled VReg " << i << "not set correctly.";
    }
}

TEST(Chip8Test, opcode_7xkk)
{
    Chip8 chip8;
    chip8.reset();

    for(int i=0; i<0xF; ++i)
    {
        chip8.performOp(0x7011 + (0x100 * i));
        EXPECT_EQ(chip8.vReg.at(i), 0x11) << "Empty VReg " << i << " not incremented correctly.";

        chip8.performOp(0x7022 + (0x100 * i));
        EXPECT_EQ(chip8.vReg.at(i), 0x33) << "Filled VReg " << i << "not incremented correctly.";
    }
}

TEST(Chip8Test, opcode_8xy0)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(1) = 0x23;
    chip8.performOp(0x8010);
    EXPECT_EQ(chip8.vReg.at(0), 0x23);
}

TEST(Chip8Test, opcode_8xy1)
{
    Chip8 chip8;
    chip8.reset();

    chip8.performOp(0x8011);
    EXPECT_EQ(chip8.vReg.at(0), 0) << "0 | 0 not performed correctly";

    chip8.vReg.at(1) = 1;
    chip8.performOp(0x8011);
    EXPECT_EQ(chip8.vReg.at(0), 1) << "0 | 1 not performed correctly";

    chip8.vReg.at(1) = 0xF;
    chip8.performOp(0x8011);
    EXPECT_EQ(chip8.vReg.at(0), 0xF) << "0 | 0xF not performed correctly";

    chip8.vReg.at(1) = 0x5;
    chip8.vReg.at(0) = 0xA;
    chip8.performOp(0x8011);
    EXPECT_EQ(chip8.vReg.at(0), 0xF) << "0x5 | 0xA not performed correctly";

    chip8.vReg.at(1) = 0xF;
    chip8.vReg.at(0) = 0xF0;
    chip8.performOp(0x8011);
    EXPECT_EQ(chip8.vReg.at(0), 0xFF) << "0xF | 0xF0 not performed correctly";
}

TEST(Chip8Test, opcode_8xy2)
{
    Chip8 chip8;
    chip8.reset();

    chip8.performOp(0x8012);
    EXPECT_EQ(chip8.vReg.at(0), 0) << "0 & 0 not performed correctly";

    chip8.vReg.at(1) = 1;
    chip8.performOp(0x8012);
    EXPECT_EQ(chip8.vReg.at(0), 0) << "0 & 1 not performed correctly";

    chip8.vReg.at(0) = 1;
    chip8.vReg.at(1) = 1;
    chip8.performOp(0x8012);
    EXPECT_EQ(chip8.vReg.at(0), 1) << "1 & 1 not performed correctly";

    chip8.vReg.at(0) = 0;
    chip8.vReg.at(1) = 0xF;
    chip8.performOp(0x8012);
    EXPECT_EQ(chip8.vReg.at(0), 0x0) << "0 & 0xF not performed correctly";

    chip8.vReg.at(1) = 0x5;
    chip8.vReg.at(0) = 0xF;
    chip8.performOp(0x8012);
    EXPECT_EQ(chip8.vReg.at(0), 0x5) << "0x5 & 0xA not performed correctly";

    chip8.vReg.at(1) = 0xF5;
    chip8.vReg.at(0) = 0x5F;
    chip8.performOp(0x8012);
    EXPECT_EQ(chip8.vReg.at(0), 0x55) << "0xF5 & 0x5F not performed correctly";
}

TEST(Chip8Test, opcode_8xy3)
{
    Chip8 chip8;
    chip8.reset();

    chip8.performOp(0x8013);
    EXPECT_EQ(chip8.vReg.at(0), 0) << "0 ^ 0 not performed correctly";

    chip8.vReg.at(1) = 1;
    chip8.performOp(0x8013);
    EXPECT_EQ(chip8.vReg.at(0), 1) << "0 ^ 1 not performed correctly";

    chip8.vReg.at(0) = 1;
    chip8.vReg.at(1) = 1;
    chip8.performOp(0x8013);
    EXPECT_EQ(chip8.vReg.at(0), 0) << "1 ^ 1 not performed correctly";

    chip8.vReg.at(0) = 0;
    chip8.vReg.at(1) = 0xF;
    chip8.performOp(0x8013);
    EXPECT_EQ(chip8.vReg.at(0), 0xF) << "0 ^ 0xF not performed correctly";

    chip8.vReg.at(1) = 0x5;
    chip8.vReg.at(0) = 0xF;
    chip8.performOp(0x8013);
    EXPECT_EQ(chip8.vReg.at(0), 0xA) << "0x5 ^ 0xA not performed correctly";

    chip8.vReg.at(1) = 0xF5;
    chip8.vReg.at(0) = 0x5F;
    chip8.performOp(0x8013);
    EXPECT_EQ(chip8.vReg.at(0), 0xAA) << "0xF5 ^ 0x5F not performed correctly";
}

TEST(Chip8Test, opcode_8xy4)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 5;
    chip8.vReg.at(1) = 2;
    chip8.performOp(0x8014);
    EXPECT_EQ(chip8.vReg.at(0), 7) << "wrong sum of 5 and 2";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after <255 addition";

    chip8.vReg.at(3) = 3;
    chip8.vReg.at(4) = 7;
    chip8.performOp(0x8344);
    EXPECT_EQ(chip8.vReg.at(3), 10) << "wrong sum of 3 and 7";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after <255 addition";

    chip8.vReg.at(5) = 250;
    chip8.vReg.at(7) = 250;
    chip8.performOp(0x8574);
    EXPECT_EQ(chip8.vReg.at(5), 0xF4) << "wrong sum of 250 and 250";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit 0 after >255 addition";
}

TEST(Chip8Test, opcode_8xy5)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 5;
    chip8.vReg.at(1) = 2;
    chip8.performOp(0x8015);
    EXPECT_EQ(chip8.vReg.at(0), 3) << "wrong difference of 5 and 2";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit 0 after non-carry subtraction";

    chip8.vReg.at(3) = 3;
    chip8.vReg.at(4) = 7;
    chip8.performOp(0x8345);
    EXPECT_EQ(chip8.vReg.at(3), 0xFC) << "wrong difference of 3 and 7";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after carried subtraction";
}

TEST(Chip8Test, opcode_8xy6)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 0x0F;
    chip8.vReg.at(1) = 0xF0;

    chip8.performOp(0x8006);
    EXPECT_EQ(chip8.vReg.at(0), 0x7) << "0xF shifted right is not 0x7";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit not 1 after borrowed shift right";

    chip8.performOp(0x8106);
    EXPECT_EQ(chip8.vReg.at(1), 0x78) << "0xF0 shifted right is not 0x78";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after non-borrowed shift right";
}

TEST(Chip8Test, opcode_8xy7)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 5;
    chip8.vReg.at(1) = 2;
    chip8.performOp(0x8017);
    EXPECT_EQ(chip8.vReg.at(0), 0xFD) << "wrong difference of 2 and 5";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after carried subtraction";

    chip8.vReg.at(3) = 3;
    chip8.vReg.at(4) = 7;
    chip8.performOp(0x8347);
    EXPECT_EQ(chip8.vReg.at(3), 0x4) << "wrong difference of 7 and 3";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit 0 after non-carry subtraction";
}

TEST(Chip8Test, opcode_8xyE)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 0x0F;
    chip8.vReg.at(1) = 0xF0;

    chip8.performOp(0x800E);
    EXPECT_EQ(chip8.vReg.at(0), 0x1E) << "0xF shifted left is not 0x1E";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after non-borrowed shift left";

    chip8.performOp(0x810E);
    EXPECT_EQ(chip8.vReg.at(1), 0xE0) << "0xF0 shifted left is not 0xE0";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit not 1 after borrowed shift left";
}

