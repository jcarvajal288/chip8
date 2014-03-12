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

TEST(KeyPadTest, SetKeys)
{
    KeyPad::instance()->reset();
    KeyPad::instance()->setKey(0x0, true);
    KeyPad::instance()->setKey(0xF, true);

    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x0), true) << "Key 0 not pressed";
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xF), true) << "Key F not pressed";
}

TEST(KeyPadTest, KeyboardHandler)
{
    KeyPad::instance()->reset();
    keyDown('0', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x0), true) << "Key 0 not pressed";
    keyUp('0', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x0), false) << "Key 0 not released";

    keyDown('1', 1, 1);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x1), true) << "Key 1 not pressed";
    keyUp('1', 1, 1);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x1), false) << "Key 1 not released";

    keyDown('2', 2, 2);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x2), true) << "Key 2 not pressed";
    keyUp('2', 2, 2);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x2), false) << "Key 2 not released";

    keyDown('3', 3, 3);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x3), true) << "Key 3 not pressed";
    keyUp('3', 3, 3);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x3), false) << "Key 3 not released";

    keyDown('4', 4, 4);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x4), true) << "Key 4 not pressed";
    keyUp('4', 4, 4);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x4), false) << "Key 4 not released";

    keyDown('5', 5, 5);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x5), true) << "Key 5 not pressed";
    keyUp('5', 5, 5);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x5), false) << "Key 5 not released";

    keyDown('6', 6, 6);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x6), true) << "Key 6 not pressed";
    keyUp('6', 6, 6);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x6), false) << "Key 6 not released";

    keyDown('7', 7, 7);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x7), true) << "Key 7 not pressed";
    keyUp('7', 7, 7);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x7), false) << "Key 7 not released";

    keyDown('8', 8, 8);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x8), true) << "Key 8 not pressed";
    keyUp('8', 8, 8);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x8), false) << "Key 8 not released";

    keyDown('9', 9, 9);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x9), true) << "Key 9 not pressed";
    keyUp('9', 9, 9);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0x9), false) << "Key 9 not released";

    keyDown('a', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xA), true) << "Key A not pressed";
    keyUp('a', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xA), false) << "Key A not released";

    keyDown('b', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xB), true) << "Key B not pressed";
    keyUp('b', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xB), false) << "Key B not released";

    keyDown('c', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xC), true) << "Key C not pressed";
    keyUp('c', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xC), false) << "Key C not released";

    keyDown('d', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xD), true) << "Key D not pressed";
    keyUp('d', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xD), false) << "Key D not released";

    keyDown('e', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xE), true) << "Key E not pressed";
    keyUp('e', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xE), false) << "Key E not released";

    keyDown('f', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xF), true) << "Key F not pressed";
    keyUp('f', 0, 0);
    EXPECT_EQ(KeyPad::instance()->isKeyPressed(0xF), false) << "Key F not released";
}
