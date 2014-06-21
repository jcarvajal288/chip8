#include <GL/freeglut.h>
#include <iostream>
#include <string>

#include "Chip8.hpp"
#include "KeyPad.hpp"
#include "Render.hpp"

using namespace std;

string gameName;

void start()
{
    Chip8 chip8;
    chip8.reset();
    srand(time(NULL));
    bool loadSuccessful = chip8.load(gameName);
    if(!loadSuccessful)
    {
        cout << "Load Failed.  Aborting." << endl;
        return;
    }

    chip8.run();
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        cout << "Usage: chip8 <path to game>" << endl;
        return 1;
    }
    else
    {
        gameName = argv[1];
    }
    Renderer::init(argc, argv);
    glutDisplayFunc(start);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
}
