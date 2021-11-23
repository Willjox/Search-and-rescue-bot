#include "Arduino.h"
#include "SRbotGripper.h"
#include "Servo.h"



Gripper::Gripper(int gripperPin, int rotatePin) {
  _rotateServo.attach(rotatePin);
  _gripperServo.attach(gripperPin);
}
Gripper::moveServo(int degrees, int delay, Servo servo) {
  pos = servo.read();
  if (pos > 0) {
    for (int i = pos; i < pos + degrees; i += 1 ) {
      servo.write(i);
      delay(delay);
    }
  } else if ( pos < 0) {
    for (int i = pos; i > pos + degrees; i -= 1 ) {
      servo.write(i);
      delay(delay);
    }
  }
}
Gripper::grip() {
  //if closed open
  if (_gripperServo.read() == 5) {
    moveServo(170,5,_gripperServo);
  } else {
    // if not closed the gripper is open and should be closed
    moveServo(-170,5,_gripperServo);
  }
}
Gripper::rotate(int degrees) {
  moveServo(degrees,5,_rotateServo);
}
