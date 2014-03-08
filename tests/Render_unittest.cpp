#include "Render.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace Renderer;

TEST(RenderTest, ClearScreen)
{
    Screen screen;
    screen.clear();

    for(int x=0; x<screen.width(); ++x)
    {
        for(int y=0; y<screen.height(); ++y)
        {
            EXPECT_EQ(screen.at(x,y), 0) << "Pixel (" << x << "," << y << ") is not 0";
        }
    }
}

TEST(RenderTest, SetPixel)
{
    Screen screen;
    screen.clear();

    screen.set(0, 0, true);
    screen.set(0, 31, true);
    screen.set(63, 0, true);
    screen.set(63, 31, true);
    screen.set(31, 16, true);

    EXPECT_TRUE(screen.at(0,0)) << "Coordinate (0,0) not set";
    EXPECT_TRUE(screen.at(0,31)) << "Coordinate (0,31) not set";
    EXPECT_TRUE(screen.at(63,0)) << "Coordinate (63,0) not set";
    EXPECT_TRUE(screen.at(63,31)) << "Coordinate (63,31) not set";
    EXPECT_TRUE(screen.at(31,16)) << "Coordinate (31,16) not set";

    screen.set(31, 16, false);
    EXPECT_FALSE(screen.at(31,16)) << "Coordinate (31,16) still set";
}
