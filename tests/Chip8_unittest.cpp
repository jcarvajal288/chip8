// this is evil, but used to preserve encapsulation in the tested object
// while being able to access private members for the test
#define private public 

#include "Chip8.hpp"
#include "KeyPad.hpp"
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

TEST(Chip8Test, HexSprites)
{
    Chip8 chip8;
    chip8.reset();

    int addr = 0;
    bool success;

    // check 0
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite '0' not loaded correctly.";

    // check 1
    success = true;
    success = chip8.memory.at(addr++) == 0x20;
    success = chip8.memory.at(addr++) == 0x60;
    success = chip8.memory.at(addr++) == 0x20;
    success = chip8.memory.at(addr++) == 0x20;
    success = chip8.memory.at(addr++) == 0x70;
    EXPECT_TRUE(success) << "Sprite '1' not loaded correctly.";

    // check 2
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x10;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite '2' not loaded correctly.";

    // check 3
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x10;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x10;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite '3' not loaded correctly.";
    
    // check 4
    success = true;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x10;
    success = chip8.memory.at(addr++) == 0x10;
    EXPECT_TRUE(success) << "Sprite '4' not loaded correctly.";

    // check 5
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x10;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite '5' not loaded correctly.";

    // check 6
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite '6' not loaded correctly.";

    // check 7
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x10;
    success = chip8.memory.at(addr++) == 0x20;
    success = chip8.memory.at(addr++) == 0x40;
    success = chip8.memory.at(addr++) == 0x40;
    EXPECT_TRUE(success) << "Sprite '7' not loaded correctly.";

    // check 8
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite '8' not loaded correctly.";

    // check 9
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x10;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite '9' not loaded correctly.";

    // check A
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0x90;
    EXPECT_TRUE(success) << "Sprite 'A' not loaded correctly.";

    // check B
    success = true;
    success = chip8.memory.at(addr++) == 0xE0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xE0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xE0;
    EXPECT_TRUE(success) << "Sprite 'B' not loaded correctly.";

    // check C
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite 'C' not loaded correctly.";

    // check D
    success = true;
    success = chip8.memory.at(addr++) == 0xE0;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0x90;
    success = chip8.memory.at(addr++) == 0xE0;
    EXPECT_TRUE(success) << "Sprite 'D' not loaded correctly.";

    // check E
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0xF0;
    EXPECT_TRUE(success) << "Sprite 'E' not loaded correctly.";

    // check F
    success = true;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0xF0;
    success = chip8.memory.at(addr++) == 0x80;
    success = chip8.memory.at(addr++) == 0x80;
    EXPECT_TRUE(success) << "Sprite 'F' not loaded correctly.";
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
    EXPECT_TRUE(chip8.performOp(0x00EE)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, 0x1234) << "Program counter did not get address at top of stack";
    EXPECT_EQ(chip8.sp, initialSP-1) << "Stack pointer did not decremented";
}

TEST(Chip8Test, opcode_1NNN)
{
    Chip8 chip8;
    chip8.reset();
    EXPECT_TRUE(chip8.performOp(0x1234)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, 0x232) << "Program counter was not set to the correct address";
}

TEST(Chip8Test, opcode_2NNN)
{
    Chip8 chip8;
    chip8.reset();
    short initialPC = 0x254;
    chip8.pc = initialPC;
    EXPECT_TRUE(chip8.performOp(0x2234)) << "Opcode failed";
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
    EXPECT_TRUE(chip8.performOp(0x3000)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, initialPC + 2) << "The program counter was not incremented by 2.";

    // test if Vx != kk
    initialPC = chip8.pc;
    EXPECT_TRUE(chip8.performOp(0x3011)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, initialPC) << "The program counter's value changed on a negative test.";
}

TEST(Chip8Test, opcode_4xkk)
{
    Chip8 chip8;
    chip8.reset();

    // test if Vx == kk
    short initialPC = chip8.pc;
    EXPECT_TRUE(chip8.performOp(0x4000)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, initialPC) <<  "The program counter's value changed on a positive test.";

    // test if Vx != kk
    initialPC = chip8.pc;
    EXPECT_TRUE(chip8.performOp(0x4011)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, initialPC + 2) << "The program counter was not incremented by 2.";
}

TEST(Chip8Test, opcode_5xy0)
{
    Chip8 chip8;
    chip8.reset();

    // test when Vx = Vy
    short initialPC = chip8.pc;
    EXPECT_TRUE(chip8.performOp(0x5010)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, initialPC + 2) <<  "The program counter's value did not increment when Vx = Vy";

    // test when Vx != Vy
    chip8.vReg.at(0) = 4;
    initialPC = chip8.pc;
    EXPECT_TRUE(chip8.performOp(0x5010)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, initialPC) <<  "The program counter changed when Vx != Vy";
}

TEST(Chip8Test, opcode_6xkk)
{
    Chip8 chip8;
    chip8.reset();
    
    for(int i=0; i<=0xF; ++i)
    {
        EXPECT_TRUE(chip8.performOp(0x6011 + (0x100 * i))) << "Opcode failed";
        EXPECT_EQ(chip8.vReg.at(i), 0x11) << "Empty VReg " << i << " not set correctly.";

        EXPECT_TRUE(chip8.performOp(0x6022 + (0x100 * i))) << "Opcode failed";
        EXPECT_EQ(chip8.vReg.at(i), 0x22) << "Filled VReg " << i << "not set correctly.";
    }
}

TEST(Chip8Test, opcode_7xkk)
{
    Chip8 chip8;
    chip8.reset();

    for(int i=0; i<=0xF; ++i)
    {
        EXPECT_TRUE(chip8.performOp(0x7011 + (0x100 * i))) << "Opcode failed";
        EXPECT_EQ(chip8.vReg.at(i), 0x11) << "Empty VReg " << i << " not incremented correctly.";

        EXPECT_TRUE(chip8.performOp(0x7022 + (0x100 * i))) << "Opcode failed";
        EXPECT_EQ(chip8.vReg.at(i), 0x33) << "Filled VReg " << i << "not incremented correctly.";
    }
}

TEST(Chip8Test, opcode_8xy0)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(1) = 0x23;
    EXPECT_TRUE(chip8.performOp(0x8010)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0x23);
}

TEST(Chip8Test, opcode_8xy1)
{
    Chip8 chip8;
    chip8.reset();

    EXPECT_TRUE(chip8.performOp(0x8011)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0) << "0 | 0 not performed correctly";

    chip8.vReg.at(1) = 1;
    EXPECT_TRUE(chip8.performOp(0x8011)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 1) << "0 | 1 not performed correctly";

    chip8.vReg.at(1) = 0xF;
    EXPECT_TRUE(chip8.performOp(0x8011)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0xF) << "0 | 0xF not performed correctly";

    chip8.vReg.at(1) = 0x5;
    chip8.vReg.at(0) = 0xA;
    EXPECT_TRUE(chip8.performOp(0x8011)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0xF) << "0x5 | 0xA not performed correctly";

    chip8.vReg.at(1) = 0xF;
    chip8.vReg.at(0) = 0xF0;
    EXPECT_TRUE(chip8.performOp(0x8011)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0xFF) << "0xF | 0xF0 not performed correctly";
}

TEST(Chip8Test, opcode_8xy2)
{
    Chip8 chip8;
    chip8.reset();

    EXPECT_TRUE(chip8.performOp(0x8012)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0) << "0 & 0 not performed correctly";

    chip8.vReg.at(1) = 1;
    EXPECT_TRUE(chip8.performOp(0x8012)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0) << "0 & 1 not performed correctly";

    chip8.vReg.at(0) = 1;
    chip8.vReg.at(1) = 1;
    EXPECT_TRUE(chip8.performOp(0x8012)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 1) << "1 & 1 not performed correctly";

    chip8.vReg.at(0) = 0;
    chip8.vReg.at(1) = 0xF;
    EXPECT_TRUE(chip8.performOp(0x8012)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0x0) << "0 & 0xF not performed correctly";

    chip8.vReg.at(1) = 0x5;
    chip8.vReg.at(0) = 0xF;
    EXPECT_TRUE(chip8.performOp(0x8012)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0x5) << "0x5 & 0xA not performed correctly";

    chip8.vReg.at(1) = 0xF5;
    chip8.vReg.at(0) = 0x5F;
    EXPECT_TRUE(chip8.performOp(0x8012)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0x55) << "0xF5 & 0x5F not performed correctly";
}

TEST(Chip8Test, opcode_8xy3)
{
    Chip8 chip8;
    chip8.reset();

    EXPECT_TRUE(chip8.performOp(0x8013)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0) << "0 ^ 0 not performed correctly";

    chip8.vReg.at(1) = 1;
    EXPECT_TRUE(chip8.performOp(0x8013)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 1) << "0 ^ 1 not performed correctly";

    chip8.vReg.at(0) = 1;
    chip8.vReg.at(1) = 1;
    EXPECT_TRUE(chip8.performOp(0x8013)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0) << "1 ^ 1 not performed correctly";

    chip8.vReg.at(0) = 0;
    chip8.vReg.at(1) = 0xF;
    EXPECT_TRUE(chip8.performOp(0x8013)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0xF) << "0 ^ 0xF not performed correctly";

    chip8.vReg.at(1) = 0x5;
    chip8.vReg.at(0) = 0xF;
    EXPECT_TRUE(chip8.performOp(0x8013)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0xA) << "0x5 ^ 0xA not performed correctly";

    chip8.vReg.at(1) = 0xF5;
    chip8.vReg.at(0) = 0x5F;
    EXPECT_TRUE(chip8.performOp(0x8013)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0xAA) << "0xF5 ^ 0x5F not performed correctly";
}

TEST(Chip8Test, opcode_8xy4)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 5;
    chip8.vReg.at(1) = 2;
    EXPECT_TRUE(chip8.performOp(0x8014)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 7) << "wrong sum of 5 and 2";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after <255 addition";

    chip8.vReg.at(3) = 3;
    chip8.vReg.at(4) = 7;
    EXPECT_TRUE(chip8.performOp(0x8344)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(3), 10) << "wrong sum of 3 and 7";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after <255 addition";

    chip8.vReg.at(5) = 250;
    chip8.vReg.at(7) = 250;
    EXPECT_TRUE(chip8.performOp(0x8574)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(5), 0xF4) << "wrong sum of 250 and 250";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit 0 after >255 addition";
}

TEST(Chip8Test, opcode_8xy5)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 5;
    chip8.vReg.at(1) = 2;
    EXPECT_TRUE(chip8.performOp(0x8015)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 3) << "wrong difference of 5 and 2";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit 0 after non-carry subtraction";

    chip8.vReg.at(3) = 3;
    chip8.vReg.at(4) = 7;
    EXPECT_TRUE(chip8.performOp(0x8345)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(3), 0xFC) << "wrong difference of 3 and 7";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after carried subtraction";
}

TEST(Chip8Test, opcode_8xy6)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 0x0F;
    chip8.vReg.at(1) = 0xF0;

    EXPECT_TRUE(chip8.performOp(0x8006)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0x7) << "0xF shifted right is not 0x7";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit not 1 after borrowed shift right";

    EXPECT_TRUE(chip8.performOp(0x8106)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(1), 0x78) << "0xF0 shifted right is not 0x78";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after non-borrowed shift right";
}

TEST(Chip8Test, opcode_8xy7)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 5;
    chip8.vReg.at(1) = 2;
    EXPECT_TRUE(chip8.performOp(0x8017)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0xFD) << "wrong difference of 2 and 5";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after carried subtraction";

    chip8.vReg.at(3) = 3;
    chip8.vReg.at(4) = 7;
    EXPECT_TRUE(chip8.performOp(0x8347)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(3), 0x4) << "wrong difference of 7 and 3";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit 0 after non-carry subtraction";
}

TEST(Chip8Test, opcode_8xyE)
{
    Chip8 chip8;
    chip8.reset();

    chip8.vReg.at(0) = 0x0F;
    chip8.vReg.at(1) = 0xF0;

    EXPECT_TRUE(chip8.performOp(0x800E)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(0), 0x1E) << "0xF shifted left is not 0x1E";
    EXPECT_EQ(chip8.vReg.at(0xF), 0) << "carry bit 1 after non-borrowed shift left";

    EXPECT_TRUE(chip8.performOp(0x810E)) << "Opcode failed";
    EXPECT_EQ(chip8.vReg.at(1), 0xE0) << "0xF0 shifted left is not 0xE0";
    EXPECT_EQ(chip8.vReg.at(0xF), 1) << "carry bit not 1 after borrowed shift left";
}

TEST(Chip8Test, opcode_9xy0)
{

    Chip8 chip8;
    chip8.reset();

    short initialPC = chip8.pc;
    chip8.vReg.at(0) = 0x1;
    chip8.vReg.at(1) = 0x1;
    EXPECT_TRUE(chip8.performOp(0x9010)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, initialPC) << "pc increased when registers were equal";

    initialPC = chip8.pc;
    chip8.vReg.at(0) = 0x1;
    chip8.vReg.at(1) = 0x2;
    EXPECT_TRUE(chip8.performOp(0x9010)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, initialPC+2) << "pc not increased when registers were not equal";
}

TEST(Chip8Test, opcode_Annn)
{
    Chip8 chip8;
    chip8.reset();

    EXPECT_TRUE(chip8.performOp(0xA045)) << "Opcode failed";
    EXPECT_EQ(chip8.iReg, 0x45) << "I register not set correctly";

    EXPECT_TRUE(chip8.performOp(0xA222)) << "Opcode failed";
    EXPECT_EQ(chip8.iReg, 0x222) << "I register not set correctly for three digit number";
}

TEST(Chip8Test, opcode_Bnnn)
{
    Chip8 chip8;
    chip8.reset();

    char offset = 0x23;
    chip8.vReg.at(0) = offset; 
    EXPECT_TRUE(chip8.performOp(0xB123)) << "Opcode failed";
    EXPECT_EQ(chip8.pc, chip8.vReg.at(0) + offset) << "JP not performed correctly";
}

TEST(Chip8Test, opcode_Cxkk)
{
    Chip8 chip8;
    chip8.reset();

    for(int i=0; i<300; ++i)
    {
        EXPECT_TRUE(chip8.performOp(0xC0FF)) << "Opcode failed";
        EXPECT_GE(chip8.vReg.at(0), 0) << "random value is less than 0";
        EXPECT_LE(chip8.vReg.at(0), 255) << "random value is greater than 255";

        EXPECT_TRUE(chip8.performOp(0xC000)) << "Opcode failed";
        EXPECT_EQ(chip8.vReg.at(0), 0) << "random value anded with 0x00 is not 0";
    }
}

TEST(Chip8Test, opcode_Dxyn_noWrap)
{
    Chip8 chip8;
    chip8.reset();

    // test the built in '0' sprite
    chip8.iReg = 0;
    chip8.performOp(0x0D005);
    // test each row of the sprite (each row is a byte long)
    EXPECT_EQ(chip8.screen.getRow(0, 0), 0xF0) << "Incorrect blitting at row (0,0)";
    EXPECT_EQ(chip8.screen.getRow(0, 1), 0x90) << "Incorrect blitting at row (0,1)";
    EXPECT_EQ(chip8.screen.getRow(0, 2), 0x90) << "Incorrect blitting at row (0,2)";
    EXPECT_EQ(chip8.screen.getRow(0, 3), 0x90) << "Incorrect blitting at row (0,3)";
    EXPECT_EQ(chip8.screen.getRow(0, 4), 0xF0) << "Incorrect blitting at row (0,4)";
}

TEST(Chip8Test, opcode_Dxyn_wrapHorizontal)
{
    Chip8 chip8;
    chip8.reset();

    // test the built in '0' sprite
    chip8.iReg = 0;
    int x = 62, y = 0;
    chip8.vReg.at(0) = x;
    chip8.vReg.at(1) = y;
    chip8.performOp(0x0D015);

    // test the row on the right side of the screen
    EXPECT_EQ(chip8.screen.getRow(56, 0), 0x3) << "Incorrect blitting at row (56,0)";
    EXPECT_EQ(chip8.screen.getRow(56, 1), 0x2) << "Incorrect blitting at row (56,1)";
    EXPECT_EQ(chip8.screen.getRow(56, 2), 0x2) << "Incorrect blitting at row (56,2)";
    EXPECT_EQ(chip8.screen.getRow(56, 3), 0x2) << "Incorrect blitting at row (56,3)";
    EXPECT_EQ(chip8.screen.getRow(56, 4), 0x3) << "Incorrect blitting at row (56,4)";

    // test the row on the left side of the screen
    EXPECT_EQ(chip8.screen.getRow(0, 0), 0xC0) << "Incorrect blitting at row (0,0)";
    EXPECT_EQ(chip8.screen.getRow(0, 1), 0x40) << "Incorrect blitting at row (0,1)";
    EXPECT_EQ(chip8.screen.getRow(0, 2), 0x40) << "Incorrect blitting at row (0,2)";
    EXPECT_EQ(chip8.screen.getRow(0, 3), 0x40) << "Incorrect blitting at row (0,3)";
    EXPECT_EQ(chip8.screen.getRow(0, 4), 0xC0) << "Incorrect blitting at row (0,4)";
}

TEST(Chip8Test, opcode_Dxyn_wrapVertical)
{
    Chip8 chip8;
    chip8.reset();

    // test the built in '0' sprite
    chip8.iReg = 0;
    int x = 0, y = 29;
    chip8.vReg.at(0) = x;
    chip8.vReg.at(1) = y;
    chip8.performOp(0x0D015);

    // test the rows on the bottom of the screen
    EXPECT_EQ(chip8.screen.getRow(0, 29), 0xF0) << "Incorrect blitting at row (0,29)";
    EXPECT_EQ(chip8.screen.getRow(0, 30), 0x90) << "Incorrect blitting at row (0,30)";
    EXPECT_EQ(chip8.screen.getRow(0, 31), 0x90) << "Incorrect blitting at row (0,31)";

    // test the rows on the top of the screen
    EXPECT_EQ(chip8.screen.getRow(0, 0), 0x90) << "Incorrect blitting at row (0,0)";
    EXPECT_EQ(chip8.screen.getRow(0, 1), 0xF0) << "Incorrect blitting at row (0,1)";
}

TEST(Chip8Test, opcode_Ex9E)
{
    Chip8 chip8;
    chip8.reset();
    
    int opcode;
    int initialPC = chip8.pc;
    for(int i=0x0; i<=0xF; ++i)
    {
        opcode = 0xE09E + (i * 0x100);
        chip8.performOp(opcode);
        EXPECT_EQ(chip8.pc, initialPC) << "PC incremented for unpressed key " << hex << i;
        KeyPad::instance()->setKey(i, true);
        chip8.performOp(opcode);
        EXPECT_EQ(chip8.pc, initialPC + 2) << "PC not incremented for pressed key " << hex << i;
        initialPC += 2;
    }
}

TEST(Chip8Test, opcode_ExA1)
{
    Chip8 chip8;
    chip8.reset();
    
    int opcode;
    int initialPC = chip8.pc;
    for(int i=0x0; i<=0xF; ++i)
    {
        opcode = 0xE0A1 + (i * 0x100);
        chip8.performOp(opcode);
        EXPECT_EQ(chip8.pc, initialPC + 2) << "PC incremented for pressed key " << hex << i;
        initialPC += 2;
        KeyPad::instance()->setKey(i, true);
        chip8.performOp(opcode);
        EXPECT_EQ(chip8.pc, initialPC) << "PC not incremented for unpressed key " << hex << i;
    }
}

TEST(Chip8Test, opcode_Fx07)
{
    Chip8 chip8;
    chip8.reset();

    char value = 0x23;
    for(int i=0; i<=0xF; ++i)
    {
        chip8.delayTimer = value + i;
        EXPECT_TRUE(chip8.performOp(0xF007 + (0x100 * i))) << "Opcode failed";
        EXPECT_EQ(chip8.vReg.at(i), value + i)  << "V" << i << " not set from delay timer";
    }
}

TEST(Chip8Test, opcode_Fx15)
{
    Chip8 chip8;
    chip8.reset();

    char value = 0x23;
    for(int i=0; i<=0xF; ++i)
    {
        chip8.vReg.at(i) = value + i;
        EXPECT_TRUE(chip8.performOp(0xF015 + (0x100 * i))) << "Opcode failed";
        EXPECT_EQ(chip8.delayTimer, value + i)  << "V" << i << " not set from delay timer";
    }
}

TEST(Chip8Test, opcode_Fx18)
{
    Chip8 chip8;
    chip8.reset();

    char value = 0x23;
    for(int i=0; i<=0xF; ++i)
    {
        chip8.vReg.at(i) = value + i;
        EXPECT_TRUE(chip8.performOp(0xF018 + (0x100 * i))) << "Opcode failed";
        EXPECT_EQ(chip8.soundTimer, value + i)  << "V" << i << " not set from sound timer";
    }
}

TEST(Chip8Test, opcode_Fx1E)
{
    Chip8 chip8;
    chip8.reset();

    char value = 0x23;
    for(int i=0; i<=0xF; ++i)
    {
        chip8.iReg = value; 
        chip8.vReg.at(i) = i;
        EXPECT_TRUE(chip8.performOp(0xF01E + (0x100 * i))) << "Opcode failed";
        EXPECT_EQ(chip8.iReg, value + i)  << "V" << i << " not added to Vi";
    }
}

TEST(Chip8Test, opcode_Fx29)
{
    Chip8 chip8;
    chip8.reset();

    for(int i=0; i<=0xF; ++i)
    {
        chip8.vReg.at(0) = i;
        EXPECT_TRUE(chip8.performOp(0xF029)) << "Opcode failed";
        EXPECT_EQ(chip8.iReg, i * 5) << "wrong location in I for opcode " << hex << i;
    }
}

TEST(Chip8Test, opcode_Fx33)
{
    Chip8 chip8;
    chip8.reset();

    int addr = 0x200;
    char val = 123;
    chip8.vReg.at(0) = val;
    chip8.iReg = addr;
    EXPECT_TRUE(chip8.performOp(0xF033)) << "Opcode failed";
    EXPECT_EQ(chip8.memory.at(addr), 1) << "Hundreds digit incorrect";
    EXPECT_EQ(chip8.memory.at(addr+1), 2) << "Tens digit incorrect";
    EXPECT_EQ(chip8.memory.at(addr+2), 3) << "Ones digit incorrect";
}

TEST(Chip8Test, loadAndRun)
{
    Chip8 chip8;
    chip8.reset();
    srand(time(NULL));
    bool loadSuccessful = chip8.load("./games/MAZE");
    ASSERT_TRUE(loadSuccessful) << "Load failed.  Aborting";
    bool runSuccessful = chip8.run();
    ASSERT_TRUE(runSuccessful) << "Run failed.";
    chip8.run();
}
