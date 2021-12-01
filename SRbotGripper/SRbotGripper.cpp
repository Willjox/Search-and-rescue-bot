#include "Arduino.h"
#include "SRbotGripper.h"
#include "Servo.h"



SRbotGripper::SRbotGripper(int gripperPin, int rotatePin) {
  _rotateServo.attach(rotatePin);
  _gripperServo.attach(gripperPin);
  _rotateServo.write(180);
  _gripperServo.write(179);
}
void SRbotGripper::moveServo(int degrees, int waitTime, Servo servo) {
  _pos = servo.read();
  servo.write(_pos + degrees);
}
void SRbotGripper::grip() {
  //if closed open
  if (_gripperServo.read() == 179) {
    moveServo(-51,10,_gripperServo);
  } else {
    // if not closed the gripper is open and should be closed
    moveServo(51,10,_gripperServo);
  }
}
void SRbotGripper::rotate(int degrees) {
  moveServo(degrees,10,_rotateServo);
}
