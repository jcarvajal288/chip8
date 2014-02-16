#ifndef RENDER_HPP
#define RENDER_HPP

#include <GL/freeglut.h>

namespace Renderer
{
    void drawPixel(const int, const int);
    void clearScreen();
    void init(int, char**);
}

#endif
