/*
Button class for waiting for pressing or realeasing a button
*/

#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button
{
public:
  Button(int pin);
  void waitFor(boolean condition, char *string);

private:
  int _pin;
};
#endif
