#include "KeyPad.hpp"

using namespace std;

KeyPad* KeyPad::_instance = 0;

void KeyPad::reset()
{
    keys.none();
}

bool KeyPad::isKeyPressed(const char ch) const
{
    return keys.test(ch);
}

void KeyPad::setKey(const char ch, const bool b)
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

