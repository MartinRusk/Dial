#include <Arduino.h>
#include <HID-Project.h>
#include <XPLDevices.h>

// Encoder device
Encoder encDial(7, 8, 16, enc2Pulse);
// Encoder encDial(8, 7, 14, enc2Pulse);
#define DialRotateDelta 25

// initialisation
void setup()
{
  // Dial
  SurfaceDial.begin();
  // Setup interface
  Serial.begin(XPLDIRECT_BAUDRATE);
  XP.begin("Dial");
}

// real time loop
void loop()
{
  // handle inputs
  encDial.handle();
  // handle XPlane
  XP.xloop();

  // evaluate events
  if (encDial.up())
  {
    SurfaceDial.rotate(DialRotateDelta);
  }
  if (encDial.down())
  {
    SurfaceDial.rotate(-DialRotateDelta);
  }
  if (encDial.pressed())
  {
    SurfaceDial.press();
  }
  if (encDial.released())
  {
    SurfaceDial.release();
  }
}
