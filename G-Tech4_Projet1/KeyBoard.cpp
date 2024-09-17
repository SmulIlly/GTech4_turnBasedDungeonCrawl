#include "KeyBoard.h"

#include <Windows.h>
#include <iostream>


/*bool Keyboard::isQWERTY() {
    HKL layout = GetKeyboardLayout(0);
    return LOWORD(layout) == 0x0409;
};
bool Keyboard::isAZERTY() {
    HKL layout = GetKeyboardLayout(0);
    return LOWORD(layout) == 0x040C;
}; */

/*bool Keyboard::isUPpressed() {

    //if (isQWERTY() == true) {
    if (GetAsyncKeyState(VK_UP))
    {
        return true;
    }

    //}
    //if (isAZERTY() == true) {


    //}
    return false;
};
bool Keyboard::isDOWNpressed() {
    if (GetAsyncKeyState(VK_DOWN))
    {
        return true;
    }
    return false;
};
bool Keyboard::isLEFTpressed() {

    //if (isQWERTY() == true) {
    if (GetAsyncKeyState(VK_LEFT))
    {
        return true;
    }

    //}
    //if (isAZERTY() == true) {

    //}
    return false;
};
bool Keyboard::isRIGHTpressed() {
    if (GetAsyncKeyState(VK_RIGHT))
    {
        return true;
    }
    return false;
};

bool Keyboard::isSPACEpressed() {
    if (GetAsyncKeyState(VK_SPACE))
    {
        return true;
    }
    return false;
}

bool Keyboard::isESCpressed() {
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        return true;
    }
    return false;
}



void Keyboard::updateInput() {
    m_state = NONE;

    if (isUPpressed()) {
        m_state |= UP;
    }
    if (isDOWNpressed()) {
        m_state |= DOWN;
    }
    if (isLEFTpressed()) {
        m_state |= LEFT;
    }
    if (isRIGHTpressed()) {
        m_state |= RIGHT;
    }
    if (isSPACEpressed()) {
        m_state |= RIGHT;
    }
    if (isESCpressed()) {
        m_state |= ESC;
    }
} */
