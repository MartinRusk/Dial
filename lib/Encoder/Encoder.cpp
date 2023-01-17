#include <Arduino.h>
#include "Encoder.h"

#define DEBOUNCE_DELAY 50
enum
{
  eNone,
  ePressed,
  eReleased
};

// Encoder with button functionality
Encoder::Encoder(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pulses)
{
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pulses = pulses;
  _count = 0;
  _state = 0;
  _transition = eNone;
  pinMode(_pin1, INPUT_PULLUP);
  pinMode(_pin2, INPUT_PULLUP);
  if (_pin3 != 255)
  {
    pinMode(_pin3, INPUT_PULLUP);
  }
}

// Encoder without button functionality
Encoder::Encoder(uint8_t pin1, uint8_t pin2, uint8_t pulses) : Encoder(pin1, pin2, 255, pulses)
{
}

// real time handling
void Encoder::handle()
{
  // collect new state
  _state = ((_state & 0x03) << 2) | (!digitalRead(_pin2) << 1) | (!digitalRead(_pin1));
  // evaluate state change
  switch (_state)
  {
  case 1:
  case 7:
  case 8:
  case 14:
    _count++;
    break;
  case 2:
  case 4:
  case 11:
  case 13:
    _count--;
    break;
  case 3:
  case 12:
    _count += 2;
    break;
  case 6:
  case 9:
    _count -= 2;
    break;
  default:
    break;
  }

  // optional button functionality
  if (_pin3 != 255)
  {
    if (!digitalRead(_pin3))
    {
      if (_debounce == 0)
      {
        _debounce = DEBOUNCE_DELAY;
        _transition = ePressed;
      }
    }
    else if (_debounce > 0)
    {
      if (--_debounce == 0)
      {
        _transition = eReleased;
      }
    }
  }
}

// Return counter
int16_t Encoder::pos()
{
  return _count;
}

// consume up event
bool Encoder::up()
{
  if (_count >= _pulses)
  {
    _count -= _pulses;
    return true;
  }
  return false;
}

// consume down event
bool Encoder::down()
{
  if (_count <= -_pulses)
  {
    _count += _pulses;
    return true;
  }
  return false;
}

// consume pressed event
bool Encoder::pressed()
{
  if (_transition == ePressed)
  {
    _transition = eNone;
    return true;
  }
  return false;
}

// consume released event
bool Encoder::released()
{
  if (_transition == eReleased)
  {
    _transition = eNone;
    return true;
  }
  return false;
}
