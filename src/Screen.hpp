#include <GL/freeglut.h>
#include <string>

// class that handles the output window and rendering
class Screen
{
    public:
        Screen()
        : pixelWidth(10.0), width(640), height(320), posX(100), posY(100), title("Chip8")
        {}

        void initWindow(int, char**) const;
        void drawPixel(const int, const int) const;

    private:
        float pixelWidth;
        int width, height;
        int posX, posY;
        std::string title;
};
