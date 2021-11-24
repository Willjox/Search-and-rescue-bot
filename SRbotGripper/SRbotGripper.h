/*
Controls Gripping and rotating of gripping claw with one joint.
*/

#ifndef SRbotGripper_h
#define SRbotGripper_h

#include "Arduino.h"
#include "Servo.h"

class SRbotGripper
{
public:
  SRbotGripper(int gripperPin, int rotatePin);
  void rotate(int degrees);
  void grip();
private:
  void moveServo(int degrees, int waitTime, Servo servo);
  Servo _rotateServo;
  Servo _gripperServo;
  int _pos;
};
#endif
