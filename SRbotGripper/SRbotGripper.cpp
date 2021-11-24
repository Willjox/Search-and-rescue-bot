#include "Arduino.h"
#include "SRbotGripper.h"
#include "Servo.h"



SRbotGripper::SRbotGripper(int gripperPin, int rotatePin) {
  _rotateServo.attach(rotatePin);
  _gripperServo.attach(gripperPin);
  _rotateServo.write(180);
  _gripperServo.write(90);
}
void SRbotGripper::moveServo(int degrees, int waitTime, Servo servo) {
  _pos = servo.read();
  if (_pos > 0) {
    for (int i = _pos; i < _pos + degrees; i += 1 ) {
      servo.write(i);
      delay(delay);
    }
  } else if ( _pos < 0) {
    for (int i = _pos; i > _pos + degrees; i -= 1 ) {
      servo.write(i);
      delay(waitTime);
    }
  }
}
void SRbotGripper::grip() {
  //if closed open
  if (_gripperServo.read() == 5) {
    moveServo(85,5,_gripperServo);
  } else {
    // if not closed the gripper is open and should be closed
    moveServo(-85,5,_gripperServo);
  }
}
void SRbotGripper::rotate(int degrees) {
  moveServo(degrees,3,_rotateServo);
}
