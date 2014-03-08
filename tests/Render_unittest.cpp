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
