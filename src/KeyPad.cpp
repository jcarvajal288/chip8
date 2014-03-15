#include "KeyPad.hpp"

using namespace std;

KeyPad* KeyPad::_instance = 0;

void KeyPad::reset()
{
    keys.reset();
}

bool KeyPad::isKeyPressed(const unsigned char ch) const
{
    return keys.test(ch);
}

void KeyPad::setKey(const unsigned char ch, const bool b)
{
    keys.set(ch, b);
}

// Implements Singleton design pattern
KeyPad* KeyPad::instance()
{
    if(_instance == 0)
    {
        _instance = new KeyPad;
    }
    return _instance;
}

void keyDown(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '0':
            KeyPad::instance()->setKey(0x0, true);
            break;
        case '1':
            KeyPad::instance()->setKey(0x1, true);
            break;
        case '2':
            KeyPad::instance()->setKey(0x2, true);
            break;
        case '3':
            KeyPad::instance()->setKey(0x3, true);
            break;
        case '4':
            KeyPad::instance()->setKey(0x4, true);
            break;
        case '5':
            KeyPad::instance()->setKey(0x5, true);
            break;
        case '6':
            KeyPad::instance()->setKey(0x6, true);
            break;
        case '7':
            KeyPad::instance()->setKey(0x7, true);
            break;
        case '8':
            KeyPad::instance()->setKey(0x8, true);
            break;
        case '9':
            KeyPad::instance()->setKey(0x9, true);
            break;
        case 'a':
            KeyPad::instance()->setKey(0xa, true);
            break;
        case 'b':
            KeyPad::instance()->setKey(0xb, true);
            break;
        case 'c':
            KeyPad::instance()->setKey(0xc, true);
            break;
        case 'd':
            KeyPad::instance()->setKey(0xd, true);
            break;
        case 'e':
            KeyPad::instance()->setKey(0xe, true);
            break;
        case 'f':
            KeyPad::instance()->setKey(0xf, true);
            break;
        default:
            return;
    }
}

void keyUp(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '0':
            KeyPad::instance()->setKey(0x0, false);
            break;
        case '1':
            KeyPad::instance()->setKey(0x1, false);
            break;
        case '2':
            KeyPad::instance()->setKey(0x2, false);
            break;
        case '3':
            KeyPad::instance()->setKey(0x3, false);
            break;
        case '4':
            KeyPad::instance()->setKey(0x4, false);
            break;
        case '5':
            KeyPad::instance()->setKey(0x5, false);
            break;
        case '6':
            KeyPad::instance()->setKey(0x6, false);
            break;
        case '7':
            KeyPad::instance()->setKey(0x7, false);
            break;
        case '8':
            KeyPad::instance()->setKey(0x8, false);
            break;
        case '9':
            KeyPad::instance()->setKey(0x9, false);
            break;
        case 'a':
            KeyPad::instance()->setKey(0xa, false);
            break;
        case 'b':
            KeyPad::instance()->setKey(0xb, false);
            break;
        case 'c':
            KeyPad::instance()->setKey(0xc, false);
            break;
        case 'd':
            KeyPad::instance()->setKey(0xd, false);
            break;
        case 'e':
            KeyPad::instance()->setKey(0xe, false);
            break;
        case 'f':
            KeyPad::instance()->setKey(0xf, false);
            break;
        default:
            return;
    }
}
