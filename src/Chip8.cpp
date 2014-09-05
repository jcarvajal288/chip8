#include "Chip8.hpp"

using namespace std;

// clears the Chip8's state
void Chip8::reset()
{
    screen.clear();
    pc = 0x200;
    sp = 0;
    memory.fill(0);
    stack.fill(0);
    vReg.fill(0);
    iReg = 0;
    delayTimer = 0;
    soundTimer = 0;

    KeyPad::instance()->reset();

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
        unsigned char b = fileInput.get();
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

bool Chip8::run()
{
    double time = timer.elapsed().system;
    unsigned short opcode;
    bool success = true;
    do
    {
        // read next opcode. each opcode is two bytes long, so load two memory locations at once
        opcode = memory.at(pc) << 8 | memory.at(pc + 1);

        success = performOp(opcode);
        if(!success)
        {
            return false;
        }

        updateTimers(time);
        screen.refresh();

        // increment program counter to point to next opcode
        pc += 2; 
    }
    while(opcode != 0);

    return true;
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
    for(int i=4; i>=0; --i)
    {
        memory.at(addr++) = (sprite >> (8*i)) & 0xFF;
    }
}

void Chip8::updateTimers(double& oldTime)
{
    // the timers are decremented once every 60th of a second
    double newTime = timer.elapsed().system;
    unsigned char numTicks = (newTime - oldTime) / 16666667;
    delayTimer -= numTicks;
    soundTimer -= numTicks;
    cout << delayTimer << endl;
    oldTime = newTime;

//    clock_t newTime = clock();
//    unsigned char numTicks = (newTime - oldTime) / (CLOCKS_PER_SEC / 60);
}

bool Chip8::performOp(const unsigned short opcode)
{
    switch(opcode & 0xF000)
    {
        case 0x0000:
            return handle_0_codes(opcode);
        case 0x1000:
            return handle_1_codes(opcode);
        case 0x2000:
            return handle_2_codes(opcode);
        case 0x3000:
            return handle_3_codes(opcode);
        case 0x4000:
            return handle_4_codes(opcode);
        case 0x5000:
            return handle_5_codes(opcode);
        case 0x6000:
            return handle_6_codes(opcode);
        case 0x7000:
            return handle_7_codes(opcode);
        case 0x8000:
            return handle_8_codes(opcode);
        case 0x9000:
            return handle_9_codes(opcode);
        case 0xA000:
            return handle_A_codes(opcode);
        case 0xB000:
            return handle_B_codes(opcode);
        case 0xC000:
            return handle_C_codes(opcode);
        case 0xD000:
            return handle_D_codes(opcode);
        case 0xE000:
            return handle_E_codes(opcode);
        case 0xF000:
            return handle_F_codes(opcode);
        default:
            cout << "Invalid opcode: " << hex << opcode << endl;
            return false;
    }
}

bool Chip8::handle_0_codes(const unsigned short opcode)
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
            return false;
    }
    return true;
}

bool Chip8::handle_1_codes(const unsigned short opcode)
{
    // 1nnn - JP addr - Jump to location nnn
    //
    // Set the program counter to nnn
    pc = opcode & 0xFFF;
    pc -= 2; // account for the automatic increment of the program counter after every opcode
    return true;
}

bool Chip8::handle_2_codes(const unsigned short opcode)
{
    // 2nnn - CALL addr - Call subroutine at nnn
    //
    // Increment the stack pointer, then push the program counter to 
    // the top of the stack.  Set the pc to nnn.
    sp++;
    stack.at(sp) = pc;
    pc = opcode & 0xFFF; 
    return true;
}

bool Chip8::handle_3_codes(const unsigned short opcode)
{
    // 3xkk - SE Vx, byte - Skip next instruction if Vx = kk.
    //
    // Compare register Vx to kk, and if they are equal, increment the 
    // program counter by 2.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    if(vReg.at(x) == kk)
    {
        pc += 2;
    }
    return true;
}

bool Chip8::handle_4_codes(const unsigned short opcode)
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
    return true;
}

bool Chip8::handle_5_codes(const unsigned short opcode)
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
    return true;
}

bool Chip8::handle_6_codes(const unsigned short opcode)
{
    // 6xkk - LD Vx, byte - Set Vx == kk.
    //
    // Put the value kk into register Vx.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    vReg.at(x) = kk;
    return true;
}

bool Chip8::handle_7_codes(const unsigned short opcode)
{
    // 7xkk - ADD Vx, byte - Set Vx = Vx + kk.
    //
    // Adds the value kk to the value of register Vx, then stores the result in Vx.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    vReg.at(x) = vReg.at(x) + kk;
    return true;
}

bool Chip8::handle_8_codes(const unsigned short opcode)
{
    // all 0x8 opcodes use the middle two nibbles to store register IDs
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char y = (opcode & 0x00F0) / 0x10;
    int sum;
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
            // 8xy4 - ADD Vx, Vy - Set Vx = Vx ADD Vy, Set VF = carry
            sum = vReg.at(x) + vReg.at(y);
            vReg.at(0xF) = (sum > 255) ? 1 : 0;
            vReg.at(x) = sum & 0xFF; 
            break;
        case 0x5:
            // 8xy5 - SUB Vx, Vy - Set Vx = Vx SUB Vy, VF = NOT borrow
            vReg.at(0xF) = (vReg.at(x) > vReg.at(y)) ? 1 : 0;
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
            return false;
    }
    return true;
}

bool Chip8::handle_9_codes(const unsigned short opcode)
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
    return true;
}

bool Chip8::handle_A_codes(const unsigned short opcode)
{
    // Annn - LD I, addr - Set I = nnn.
    //
    // The value of register I is set to nnn.
    const unsigned short nnn = opcode & 0xFFF;
    iReg = nnn;
    return true;
}

bool Chip8::handle_B_codes(const unsigned short opcode)
{
    // Bnnn - JP V0, addr - Jump to location nnn + V0.
    //
    // The program counter is set to nnn plus the value of V0.
    const unsigned char nnn = opcode & 0xFFF;
    pc = vReg.at(0x0) + nnn;
    return true;
}

bool Chip8::handle_C_codes(const unsigned short opcode)
{
    // Cxkk - RND Vx, byte - Set Vx = random byte AND kk.
    //
    // Generate a random number from 0 to 255, which is then ANDed with
    // the value kk. The results are stored in Vx.
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    const unsigned char kk = opcode & 0xFF;
    const unsigned char randomByte = rand() % 255;
    vReg.at(x) = randomByte & kk;
    return true;
}

bool Chip8::handle_D_codes(const unsigned short opcode)
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
    const unsigned char vx = (opcode & 0x0F00) / 0x100;
    const unsigned char vy = (opcode & 0x00F0) / 0x10;
    const unsigned char numBytes = opcode & 0xF;
    unsigned char spriteRow;

    int x = vReg.at(vx);
    int y = vReg.at(vy);

    for(int i=0; i<numBytes; ++i)
    {
        spriteRow = memory.at(iReg+i);
        screen.setRow(x, y+i, spriteRow);
    }

    return true;
}

bool Chip8::handle_E_codes(const unsigned short opcode)
{
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    switch(opcode & 0xFF)
    {
        case 0x9E:
            // SKP Vx - Skip next instruction if key with the value of Vx is pressed.
            //
            // Checks the keyboard, and if the key corresponding to the value of Vx is currently
            // in the down position, PC is increased by 2.
            if(KeyPad::instance()->isKeyPressed(x))
                pc += 2;
            break;
        case 0xA1:
            // SKP Vx - Skip next instruction if key with the value of Vx is not pressed.
            //
            // Checks the keyboard, and if the key corresponding to the value of Vx is currently
            // in the up position, PC is increased by 2.
            if(!KeyPad::instance()->isKeyPressed(x))
                pc += 2;
            break;
        default:
            cerr << "Invalid 0xE opcode: " << hex << opcode << endl;
            return false;
    }
    return true;
}

bool Chip8::handle_F_codes(const unsigned short opcode)
{
    const unsigned char x = (opcode & 0x0F00) / 0x100;
    unsigned char key;
    int val;
    switch(opcode & 0xFF) 
    {
        case 0x07:
            // LD Vx, DT - Set Vx = delay timer value.
            //
            // The value of DT is placed into Vx.
            vReg.at(x) = delayTimer;
            break;
        case 0x0A:
            // LD Vx, K - Wait for a key press, store the value of the key in Vx.
            //
            // All execution stops until a key is pressed, then the value of that key is
            // stored in Vx.
            key = KeyPad::instance()->waitForKeypress();
            vReg.at(x) = key;
            break;
        case 0x15:
            // LD DT, Vx - Set delay timer = Vx.
            //
            // DT is set equal to the value of Vx.
            delayTimer = vReg.at(x);
            break;
        case 0x18:
            // LD ST, Vx - Set sound timer = Vx.
            //
            // ST is set equal to the value of Vx.
            soundTimer = vReg.at(x);
            break;
        case 0x1E:
            // ADD I, Vx - Set I = I + Vx.
            //
            // The values of I and Vx are added, and the results are stored in I
            iReg += vReg.at(x);
            break;
        case 0x29:
            // Set I = location of sprite for digit Vx.
            //
            // The value of I is set to the location for the hexidecimal sprite corresponding
            // to the value of Vx.
            iReg = vReg.at(x) * 5; // each sprite is 5 bytes long
            break;
        case 0x33:
            // Store BCD representation of Vx in memory locations I, I+1, and I+2.
            //
            // The interpreter takes the decimal value of Vx, and places the hundreds digit in
            // memory at location I, the tens digit at location I+1, and the ones digit at 
            // location I+2.
            val = vReg.at(x);
            memory.at(iReg) = val / 100;
            memory.at(iReg+1) = (val / 10) % 10;
            memory.at(iReg+2) = val % 10;
            break;
        case 0x55:
            // LD [I], Vx
            //
            // Store registers V0 through Vx in memory starting at location I
            for(int i=0; i<=x; ++i)
            {
                memory.at(iReg+i) = vReg.at(i);
            }
            break;
        case 0x65:
            // LD Vx, [I]
            //
            // Read registers V0 through Vx from memory starting at location I.
            for(int i=0; i<=x; ++i)
            {
                vReg.at(i) = memory.at(iReg+i);
            }
            break;
        default:
            cerr << "Invalid 0xF opcode: " << hex << opcode << endl;
            return false;
    }
    return true;
}
