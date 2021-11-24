#include "Arduino.h"
#include "Button.h"
Button::Button(int pin) {
  _pin = pin;
  pinMode(_pin,INPUT);
}
void Button::waitFor(boolean condition, char *string) {
  Serial.println(string);
  while (digitalRead(_pin) != condition) {
    delay(50);
  }
}
