#include <GL/freeglut.h>

#include "Render.hpp"

using namespace std;

namespace Renderer
{
    void Screen::clear()
    {
        array< bitset<64>, 32 >::iterator it;
        for(it=pixelArray.begin(); it!=pixelArray.end(); ++it)
        {
            it->reset();
        }
    }

    bool Screen::at(const unsigned int x, const unsigned int y) const
    {
        return pixelArray.at(y).test(x);
    }

    void Screen::set(const unsigned int x, const unsigned int y, const bool b)
    {
        pixelArray.at(y).set(x, b);
    }

    void Screen::setXOR(const unsigned int x, const unsigned int y, const bool b)
    {
        // sets the given location to the XOR of the current pixel and the new pixel
        bool val = at(x,y) ^ b;
        set(x, y, val);
    }

    int Screen::getRow(const unsigned int x, const unsigned int y) const
    {
        // used only for the unit tests
        // returns an integer representation of an 8 pixel long horizontal row
        // of the screen.  Sprites are all 8 pixels wide.
        int sum = 0;
        sum += pixelArray.at(y).test(x) * 0x80;
        sum += pixelArray.at(y).test(x+1) * 0x40;
        sum += pixelArray.at(y).test(x+2) * 0x20;
        sum += pixelArray.at(y).test(x+3) * 0x10;
        sum += pixelArray.at(y).test(x+4) * 0x8;
        sum += pixelArray.at(y).test(x+5) * 0x4;
        sum += pixelArray.at(y).test(x+6) * 0x2;
        sum += pixelArray.at(y).test(x+7) * 0x1;
        return sum;
    }

    void Screen::setRow(const unsigned int x, const unsigned int y, const unsigned char ch)
    {
        // sets an 8 pixel long horizontal row to the bitwise representation of the passed
        // in byte.  Useful for blitting sprites, which are all 8 pixels wide.  This uses
        // setXOR to fit with the requirements for opcode 6xyn.
        int val;
        for(int i=0; i<8; ++i)
        {
            val = ch & (0x1 << i);
            val >>= i;
            setXOR(x+(7-i),y, val);
        }
    }

    void drawPixel(const int x, const int flipped_y)
    {
        // openGL puts the origin at the lower left, so we need to switch
        // the y coordinate around to put it at the upper left
        int y = 32 - flipped_y;
        glBegin(GL_QUADS);
            glVertex2i(x, y);
            glVertex2i(x, y-1);
            glVertex2i(x+1, y-1);
            glVertex2i(x+1, y);
        glEnd();
    }

    void clearScreen()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }

    void init(int argc, char** argv)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(640, 320);
        glutCreateWindow("Chip 8");

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 64.0, 0.0, 32.0);
        glMatrixMode(GL_MODELVIEW);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
    }
}
