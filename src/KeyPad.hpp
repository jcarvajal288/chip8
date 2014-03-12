#include <bitset>
#include <fstream>
#include <iostream>
#include <map>

class KeyPad
{
    public:
        void reset();
        bool isKeyPressed(const char) const;
        void setKey(const char, const bool);

        static KeyPad* instance();

    private:
        static KeyPad* _instance;
        std::bitset<16> keys;

        KeyPad() {}
        //std::map<unsigned char, unsigned char> keyMap;
};
