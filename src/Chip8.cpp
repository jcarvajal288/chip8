#include "Chip8.hpp"

using namespace std;

// clears the Chip8's state
void Chip8::reset()
{
    pc = 0;
    sp = 0;
    memory.fill(0);
    stack.fill(0);
    vReg.fill(0);
    iReg = 0;
    delayTimer = 0;
    soundTimer = 0;
}

int main()
{
    Chip8 chip8;
    chip8.reset();
    cout << "Chip8 initialized successfully" << endl;
}
