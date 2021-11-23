/*
Controls Gripping and rotating of gripping claw with one joint.
*/

#ifndef SRbotGripper_h
#define SRbotGripper_h

#include "Arduino.h"
#include "servo.h"

class Gripper
{
public:
  Gripper(int gripperPin, int rotatePin);
  void rotate(int degrees);
  void grip();
private:
  void moveServo(int degrees)
  Servo _rotateServo;
  Servo _gripperServo;
}
#enddif
