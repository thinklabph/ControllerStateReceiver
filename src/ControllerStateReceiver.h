#ifndef CONTROLLER_STATE_H
#define CONTROLLER_STATE_H

#include <stdint.h>
#include "RF24.h"

class ControllerStateReceiver {
public:
    // Constructor
    ControllerStateReceiver(uint8_t CE_PIN, uint8_t CSN_PIN, uint8_t* RF24_ADDRESS);

    void init();
    bool update();

    bool select();
    bool l3();
    bool r3();
    bool start();
    bool up();
    bool right();
    bool down();
    bool left();
    bool l2();
    bool r2();
    bool l1();
    bool r1();
    bool triangle();
    bool circle();
    bool cross();
    bool square();

    uint8_t lx();
    uint8_t ly();
    uint8_t rx();
    uint8_t ry();

private:
    RF24 _radio;

    uint8_t _address[5];

    uint64_t _controllerState;
    
    bool _select;
    bool _l3;
    bool _r3;
    bool _start;
    bool _up;
    bool _right;
    bool _down;
    bool _left;
    bool _l2;
    bool _r2;
    bool _l1;
    bool _r1;
    bool _triangle;
    bool _circle;
    bool _cross;
    bool _square;

    uint8_t _lx;
    uint8_t _ly;
    uint8_t _rx;
    uint8_t _ry;

    void updateButtonState(uint64_t controllerState);
};

#endif
