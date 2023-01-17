#include <Arduino.h>
#include <HID-Project.h>
#include <Encoder.h>

Encoder encDial(7, 8, 16, 2);
#define DialRotateDelta 25

// initialisation
void setup()
{
  SurfaceDial.begin();
}

// real time loop
void loop()
{
  // handle inputs
  encDial.handle();
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
