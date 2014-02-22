#include <GL/freeglut.h>
#include <iostream>

#include "Chip8.hpp"
#include "Render.hpp"

using namespace std;

void start()
{
    Chip8 chip8;
    chip8.reset();
    srand(time(NULL));
    bool loadSuccessful = chip8.load("./games/MAZE");
    if(!loadSuccessful)
    {
        cout << "Load Failed.  Aborting." << endl;
        return;
    }

    chip8.run();
}

int main(int argc, char **argv)
{
    Renderer::init(argc, argv);
    glutDisplayFunc(start);
    glutMainLoop();
}
