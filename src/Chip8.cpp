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

    loadBuiltinSprites();
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
    unsigned short opcode;
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

// loads the hex character sprites into chip8 memory
void Chip8::loadBuiltinSprites()
{
    int addr = 0x0;
    loadSprite(0xF0909090F0, addr); // 0
    loadSprite(0x2060202070, addr); // 1
    loadSprite(0xF010F080F0, addr); // 2
    loadSprite(0xF010F010F0, addr); // 3
    loadSprite(0x9090F01010, addr); // 4
    loadSprite(0xF080F010F0, addr); // 5
    loadSprite(0xF080F090F0, addr); // 6
    loadSprite(0xF010204040, addr); // 7
    loadSprite(0xF090F090F0, addr); // 8
    loadSprite(0xF090F010F0, addr); // 9
    loadSprite(0xF090F09090, addr); // A
    loadSprite(0xE090E090E0, addr); // B
    loadSprite(0xF0808080F0, addr); // C
    loadSprite(0xE0909090E0, addr); // D
    loadSprite(0xF080F080F0, addr); // E
    loadSprite(0xF080F08080, addr); // F
}

// loads the given sprite (represented as an integer) into memory
// at the given memory address. Sprites are assumed to be five bytes long.
void Chip8::loadSprite(const long long sprite, int& addr)
{
    for(int i=5; i>0; --i)
    {
        memory.at(addr++) = (sprite >> static_cast<int>(pow(2, i))) & 0xFF;
    }
}

void Chip8::performOp(const unsigned short opcode)
{
    switch(opcode & 0xF000)
    {
        case 0x0000:
            cout << hex << opcode << endl;
            handle_0_codes(opcode);
            break;
        case 0x1000:
            cout << hex << opcode << endl;
            handle_1_codes(opcode);
            break;
        case 0x2000:
            cout << hex << opcode << endl;
            handle_2_codes(opcode);
            break;
        case 0x3000:
            cout << hex << opcode << endl;
            handle_3_codes(opcode);
            break;
        case 0x4000:
            cout << hex << opcode << endl;
            handle_4_codes(opcode);
            break;
        case 0x5000:
            cout << hex << opcode << endl;
            handle_5_codes(opcode);
            break;
        case 0x6000:
            cout << hex << opcode << endl;
            handle_6_codes(opcode);
            break;
        case 0x7000:
            cout << hex << opcode << endl;
            handle_7_codes(opcode);
            break;
        case 0x8000:
            cout << hex << opcode << endl;
            handle_8_codes(opcode);
            break;
        case 0x9000:
            cout << hex << opcode << endl;
            handle_9_codes(opcode);
            break;
        case 0xA000:
            cout << hex << opcode << endl;
            handle_A_codes(opcode);
            break;
        case 0xB000:
            cout << hex << opcode << endl;
            handle_B_codes(opcode);
            break;
        case 0xC000:
            cout << hex << opcode << endl;
            handle_C_codes(opcode);
            break;
        case 0xD000:
            cout << hex << opcode << endl;
            handle_D_codes(opcode);
            break;
        case 0xE000:
            cout << hex << opcode << endl;
            handle_E_codes(opcode);
            break;
        case 0xF000:
            cout << hex << opcode << endl;
            handle_F_codes(opcode);
            break;
        default:
            cout << "Invalid opcode: " << hex << opcode << endl;
            exit(EXIT_FAILURE);
    }
}

void Chip8::handle_0_codes(const unsigned short opcode)
{
    switch(opcode)
    {
        case 0x00E0: 
            // CLS - Clear the display
            Renderer::clearScreen();
            break;
        case 0x00EE: 
            // RET - Return from a subroutine
            pc = stack.at(sp--);
            break;
        default:
            cerr << "Invalid 0x0NNN opcode: " << hex << opcode << endl;
            exit(EXIT_FAILURE);
    }
}

void Chip8::handle_1_codes(const unsigned short opcode)
{
    // 1nnn - JP addr - Jump to location nnn
    //
    // Set the program counter to nnn
    pc = opcode & 0xFFF;
}

void Chip8::handle_2_codes(const unsigned short opcode)
{
    // 2nnn - CALL addr - Call subroutine at nnn
    //
    // Increment the stack pointer, then push the program counter to 
    // the top of the stack.  Set the pc to nnn.
    sp++;
    stack.at(sp) = pc;
    pc = opcode & 0xFFF; 
}

void Chip8::handle_3_codes(const unsigned short opcode)
{
    // 3xkk - SE Vx, byte - Skip next instruction if Vx - kk.
    //
    // Compare register Vx to kk, and if they are equal, increment the 
    // program counter by 2.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    if(vReg.at(x) == kk)
    {
        pc += 2;
    }
}

void Chip8::handle_4_codes(const unsigned short opcode)
{
    // 4xkk - SNE Vx, byte - Skip next instruction if Vx != kk.
    //
    // Compare register Vx to kk, and if they are not equal, increment
    // program counter by 2.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    if(vReg.at(x) != kk)
    {
        pc += 2;
    }
}

void Chip8::handle_5_codes(const unsigned short opcode)
{
    // 5xy0 - SE Vx, Vy - Skip next instruction if Vx == Vy.
    //
    // Compare register Vx to register Vy and if they are equal,
    // increment program counter by 2.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char y = (opcode & 0x00F0) / 0x10;
    if(vReg.at(x) == vReg.at(y))
    {
        pc += 2;
    }
}

void Chip8::handle_6_codes(const unsigned short opcode)
{
    // 6xkk - LD Vx, byte - Set Vx == kk.
    //
    // Put the value kk into register Vx.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    vReg.at(x) = kk;
}

void Chip8::handle_7_codes(const unsigned short opcode)
{
    // 7xkk - ADD Vx, byte - Set Vx = Vx + kk.
    //
    // Adds the value kk to the value of register Vx, then stores the result in Vx.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    vReg.at(x) = vReg.at(x) + kk;
}

void Chip8::handle_8_codes(const unsigned short opcode)
{
    // all 0x8 opcodes use the middle two nibbles to store register IDs
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char y = (opcode & 0x00F0) / 0x10;
    switch(opcode & 0xF) // switch against the least significant nibble
    {
        case 0x0:
            // 8xy0 - LD Vx, Vy - Set Vx = Vy
            vReg.at(x) = vReg.at(y);
            break;
        case 0x1:
            // 8xy1 - OR Vx, Vy - Set Vx = Vx OR Vy
            vReg.at(x) |= vReg.at(y);
            break;
        case 0x2:
            // 8xy2 - AND Vx, Vy - Set Vx = Vx AND Vy
            vReg.at(x) &= vReg.at(y);
            break;
        case 0x3:
            // 8xy3 - XOR Vx, Vy - Set Vx = Vx XOR Vy
            vReg.at(x) ^= vReg.at(y);
            break;
        case 0x4:
            // 8xy4 - ADD Vx, Vy - Set Vx = Vx ADD Vy
            vReg.at(x) += vReg.at(y);
            break;
        case 0x5:
            // 8xy5 - SUB Vx, Vy - Set Vx = Vx SUB Vy
            vReg.at(x) -= vReg.at(y);
            break;
        case 0x6:
            // 8xy6 - SHR Vx {, Vy} - Set Vx = Vx SHR 1
            //
            // If the least-significant bit of Vx is 1, then VF is set to 1,
            // otherwise 0.  Then Vx is divided by 2.
            vReg.at(0xF) = vReg.at(x) % 2;
            vReg.at(x) >>= 1;
            break;
        case 0x7:
            // 8xy7 - SUBN Vx, Vy - Set VF = NOT borrow.
            //
            // If Vy > Vx, then VF is set to 1, otherwise 0.  Then Vx is
            // subtracted from Vy, and the results stored in Vx.
            vReg.at(0xF) = (vReg.at(y) > vReg.at(x)) ? 1 : 0;
            vReg.at(x) = vReg.at(y) - vReg.at(x);
            break;
        case 0xE:
            // 8xyE - SHL Vx {, Vy}
            //
            // If the most-significant bit of Vx is 1, then VF is set to 1, otherwise
            // to 0.  Then Vx is multiplied by 2.
            vReg.at(0xF) = vReg.at(x) >> 7;
            vReg.at(x) <<= 1;
            break;
        default:
            cerr << "Invalid 0x8 opcode: " << hex << opcode << endl;
            exit(EXIT_FAILURE);
    }
}

void Chip8::handle_9_codes(const unsigned short opcode)
{
    // 9xy0 - SNE Vx, Vy - Skip next instruction if Vx != Vy.
    //
    // if Vx is not equal to Vy, increment the program counter by 2.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char y = (opcode & 0x00F0) / 0x10;
    if(vReg.at(x) != vReg.at(y))
    {
        pc += 2;
    }
}

void Chip8::handle_A_codes(const unsigned short opcode)
{
    // Annn - LD I, addr - Set I = nnn.
    //
    // The value of register I is set to nnn.
    const unsigned char nnn = opcode & 0xFFF;
    iReg = nnn;
}

void Chip8::handle_B_codes(const unsigned short opcode)
{
    // Bnnn - JP V0, addr - Jump to location nnn + V0.
    //
    // The program counter is set to nnn plus the value of V0.
    const unsigned char nnn = opcode & 0xFFF;
    pc = vReg.at(0x0) + nnn;
}

void Chip8::handle_C_codes(const unsigned short opcode)
{
    // Cxkk - RND Vx, byte - Set Vx = random byte AND kk.
    //
    // Generate a random number from 0 to 255, which is then ANDed with
    // the value kk. The results are stored in Vx.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    const unsigned char randomByte = rand() % 255;
    vReg.at(x) = randomByte & kk;
}

void Chip8::handle_D_codes(const unsigned short opcode)
{
    // Dxyn - DRW Vx, Vy, nibble
    // Display n-byte sprite starting at memory location I at (Vx, Vy),
    // set VF = collision.
    //
    // Read n bytes from memory, starting at the address stored in I.  These bytes are
    // then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed
    // onto the existing screen. If this causes any pixels to be erased, VF is set to 1, 
    // otherwise it is set to 0.  If the sprite is positioned so part of it is outside
    // the coordinates of the display, it wraps around to the opposite side of the screen.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char y = (opcode & 0x00F0) / 0x10;
    const unsigned char n = opcode & 0xF;
}

void Chip8::handle_E_codes(const unsigned short opcode)
{

}

void Chip8::handle_F_codes(const unsigned short opcode)
{

}



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
