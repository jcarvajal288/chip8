#include "KeyPad.hpp"
#include "gtest/gtest.h"

using namespace std;

TEST(KeyPadTest, Reset)
{
    KeyPad::instance()->reset();
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x0), false) << "Key 0 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x1), false) << "Key 1 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x2), false) << "Key 2 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x3), false) << "Key 3 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x4), false) << "Key 4 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x5), false) << "Key 5 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x6), false) << "Key 6 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x7), false) << "Key 7 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x8), false) << "Key 8 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x9), false) << "Key 9 pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xA), false) << "Key A pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xB), false) << "Key B pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xC), false) << "Key C pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xD), false) << "Key D pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xE), false) << "Key E pressed after reset.";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xF), false) << "Key F pressed after reset.";
}
