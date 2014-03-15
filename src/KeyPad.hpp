#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include <bitset>
#include <fstream>
#include <iostream>
#include <map>

class KeyPad
{
    public:
        void reset();
        bool isKeyPressed(const unsigned char) const;
        void setKey(const unsigned char, const bool);

        static KeyPad* instance();

    private:
        static KeyPad* _instance;
        std::bitset<16> keys;

        KeyPad() {}
};

void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);

#endif
