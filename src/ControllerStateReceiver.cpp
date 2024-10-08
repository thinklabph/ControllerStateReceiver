#include "ControllerStateReceiver.h"
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

// Constructor implementation
ControllerStateReceiver::ControllerStateReceiver(uint8_t CE_PIN, uint8_t CSN_PIN, uint8_t* RF24_ADDRESS)
    : _select(false), _l3(false), _r3(false), _start(false),
      _up(false), _right(false), _down(false), _left(false),
      _l2(false), _r2(false), _l1(false), _r1(false),
      _triangle(false), _circle(false), _cross(false), _square(false),
      _lx(128), _ly(128), _rx(128), _ry(128), 
      _controllerState(0), _radio(CE_PIN, CSN_PIN)
{
   memcpy(_address, RF24_ADDRESS, 5);
}


void ControllerStateReceiver::init() {
    if (!_radio.begin()) {
      Serial.println(F("radio hardware is not responding!!"));
      while (1) {}  // hold in infinite loop
    }

    _radio.setPALevel(RF24_PA_LOW);
    _radio.setPayloadSize(sizeof(_controllerState));

    _radio.openWritingPipe(_address);
    _radio.openReadingPipe(1, _address);
    _radio.startListening();
}


// Method to update the controller state from uint64_t
bool ControllerStateReceiver::update() {

  uint64_t newControllerState;

  uint8_t pipe;
  if (_radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
    _radio.read(&newControllerState, sizeof(newControllerState));   // fetch payload from FIFO

    if (newControllerState != _controllerState) {
      
      updateButtonState(newControllerState);
    }
    // Return true when there is message received
    return true;
  }
  else {
    // Return false when there is no message received
    return false;
  }
}

void ControllerStateReceiver::updateButtonState(uint64_t controllerState) {

    _controllerState = controllerState;

    // Extract ry (bits 0-7)
    _ry = controllerState & 0xFF;

    controllerState >>= 8;

    // Extract rx (bits 0-7)
    _rx = controllerState & 0xFF;

    controllerState >>= 8;

    // Extract ly (bits 0-7)
    _ly = controllerState & 0xFF;

    controllerState >>= 8;

    // Extract lx (bits 0-7)
    _lx = controllerState & 0xFF;

    controllerState >>= 8;

    // Extract buttonWord (bits 0-15)
    uint16_t buttonWord = controllerState & 0xFFFF;

    // Active low logic (0 = pressed, 1 = released)
    _select   = (buttonWord & 0x0001);
    _l3       = (buttonWord & 0x0002);
    _r3       = (buttonWord & 0x0004);
    _start    = (buttonWord & 0x0008);
    _up       = (buttonWord & 0x0010);
    _right    = (buttonWord & 0x0020);
    _down     = (buttonWord & 0x0040);
    _left     = (buttonWord & 0x0080);
    _l2       = (buttonWord & 0x0100);
    _r2       = (buttonWord & 0x0200);
    _l1       = (buttonWord & 0x0400);
    _r1       = (buttonWord & 0x0800);
    _triangle = (buttonWord & 0x1000);
    _circle   = (buttonWord & 0x2000);
    _cross    = (buttonWord & 0x4000);
    _square   = (buttonWord & 0x8000);
}


// Getter methods for button states
bool ControllerStateReceiver::select() { return _select; }
bool ControllerStateReceiver::l3() { return _l3; }
bool ControllerStateReceiver::r3() { return _r3; }
bool ControllerStateReceiver::start() { return _start; }
bool ControllerStateReceiver::up() { return _up; }
bool ControllerStateReceiver::right() { return _right; }
bool ControllerStateReceiver::down() { return _down; }
bool ControllerStateReceiver::left() { return _left; }
bool ControllerStateReceiver::l2() { return _l2; }
bool ControllerStateReceiver::r2() { return _r2; }
bool ControllerStateReceiver::l1() { return _l1; }
bool ControllerStateReceiver::r1() { return _r1; }
bool ControllerStateReceiver::triangle() { return _triangle; }
bool ControllerStateReceiver::circle() { return _circle; }
bool ControllerStateReceiver::cross() { return _cross; }
bool ControllerStateReceiver::square() { return _square; }

// Getter methods for analog stick positions
uint8_t ControllerStateReceiver::lx() { return _lx; }
uint8_t ControllerStateReceiver::ly() { return _ly; }
uint8_t ControllerStateReceiver::rx() { return _rx; }
uint8_t ControllerStateReceiver::ry() { return _ry; }
