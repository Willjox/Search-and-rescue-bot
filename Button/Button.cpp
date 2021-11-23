#include "Arduino.h"
#include "Button.h"
Button::Button(int pin) {
  _pin = pin;
  pinMode(_pin,INPUT);
}
Button::waitFor(boolean condition) {
  while (digitalRead(_pin) != condition) {
    delay(50);
  }
}
