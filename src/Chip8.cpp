#include "Chip8.hpp"

using namespace std;

// clears the Chip8's state
void Chip8::reset()
{
    pc = 0x200;
    sp = 0;
    memory.fill(0);
    stack.fill(0);
    vReg.fill(0);
    iReg = 0;
    delayTimer = 0;
    soundTimer = 0;
}

bool Chip8::load(const string& program)
{
    cout << "Loading program " << program << endl;
    int startAddress = pc;
    ifstream fileInput;
    fileInput.open(program, ios::binary);
    if(!fileInput.is_open())
    {
        cout << "Unable to open file: " << program << endl;
        return false;
    }

    int currentAddress = startAddress;
    while(fileInput.good())
    {
        char b = fileInput.get();
        memory.at(currentAddress++) = b;
        if(currentAddress >= memory.size())
        {
            cout << "File too large for chip8!" << endl;
            return false;
        }
    }

    int fileSize = currentAddress - startAddress;
    cout << program << " loaded into memory. (" << fileSize << " bytes)" << endl;

    fileInput.close();
    return true;
}

void Chip8::run()
{
    short opcode;
    do
    {
        // read next opcode. each opcode is two bytes long, so load two memory locations at once
        opcode = memory.at(pc) << 8 | memory.at(pc + 1);

        performOp(opcode);

        // increment program counter to point to next opcode
        pc += 2; 
    }
    while(opcode != 0);
}

void Chip8::performOp(const short opcode)
{
    switch(opcode & 0xF000)
    {
        case 0x0000:
            cout << "\tCLS, RET, or SYS" << endl;
            break;
        case 0x1000:
            cout << "\tJP" << endl;
            break;
        case 0x2000:
            cout << "\tCALL" << endl;
            break;
        case 0x3000:
            cout << "\tSE" << endl;
            break;
        case 0x4000:
            cout << "\tSNE" << endl;
            break;
        case 0x5000:
            cout << "\tSE" << endl;
            break;
        case 0x6000:
            cout << "\tLD" << endl;
            break;
        case 0x7000:
            cout << "\tADD" << endl;
            break;
        case 0x8000:
            cout << "\tLOGIC" << endl;
            break;
        case 0x9000:
            cout << "\tSNE" << endl;
            break;
        case 0xA000:
            cout << "\tLD I" << endl;
            break;
        case 0xB000:
            cout << "\tJP v0" << endl;
            break;
        case 0xC000:
            cout << "\tRND Vx" << endl;
            break;
        case 0xD000:
            cout << "\tDRW" << endl;
            break;
        case 0xE000:
            cout << "\tSKP, SKNP" << endl;
            break;
        case 0xF000:
            cout << "\tLD or ADD" << endl;
            break;
        default:
            cout << "Invalid opcode!" << endl;
    }
}

int main(int argc, char** argv)
{
    Chip8 chip8;
    Screen screen;
    chip8.reset();
    bool loadSuccessful = chip8.load("./games/MAZE");
    if(!loadSuccessful)
    {
        cout << "Load Failed.  Aborting." << endl;
        return false;
    }

    chip8.run();

    screen.initWindow(argc, argv);

    return true;
}
