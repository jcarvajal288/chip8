#ifndef RENDER_HPP
#define RENDER_HPP

#include <array>
#include <bitset>
#include <iostream>
#include <GL/freeglut.h>

namespace Renderer
{
    class Screen
    {
        public:
            Screen() {}

            bool at(const unsigned int, const unsigned int) const;
            void set(const unsigned int, const unsigned int, const bool);
            void setXOR(const unsigned int, const unsigned int, const bool);
            int getRow(const unsigned int, const unsigned int) const;
            void setRow(const unsigned int, const unsigned int, const unsigned char);
            void clear();
            void refresh();
            int width() const { return pixelArray.at(0).size(); }
            int height() const { return pixelArray.size(); }

        private:
            std::array< std::bitset<64>, 32 > pixelArray;
    };

    void drawPixel(const int, const int);
    void clearScreen();
    void init(int, char**);
}

#endif
