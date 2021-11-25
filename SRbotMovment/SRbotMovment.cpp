#include "Arduino.h"
#include "SRbotMovment.h"
#include "Servo.h"
#include "SRbotSensors.h"

SRbotMovment::SRbotMovment(int *servoPins, int *linePins, int *turnPins) {
  leftServo.attach(servoPins[0]);
  rightServo.attach(servoPins[1]);
  sensors(sensorPins);
  lastError = 0;
  leftBaseSpeed = 110;
  rightBaseSpeed = 110;
  leftServo.write(90);
  rightServo.write(90);
}

void SRbotMovment::followLine() {
  while (detectTurn == false) {
    control(sensors.getLinePos());
  }
}

void SRbotMovment::turn() {
    //WHILE DETECTMIDLINE
    // GO forward
    //WHEN NOT DETECTING
    //START TURNING direction
    // UNTIL DETECTING MIDLINE
}

void SRbotMovment::rotate() {
  // ROTATE TILL NO MIDLINE,
  // KEEP TURNING TILL MIDLINE visible again
}

void SRbotMovment::adjustSpeed(int left, int right) {
  //nödvändig?
  left = constrain(left + leftServo.read() , 5 , 175);
  right = constrain(right + rightServo.read() , 5 , 175);
  servoOutput(left,right);
}

void SRbotMovment::servoOutput(int left, int right) {
  leftServo.write(180-leftSpeed);
  rightServo.write(rightSpeed);
}

void SRbotMovment::control(int position) {
  int error = position - 1000;
  int servoSpeed = kp * error + kd * (error - lastError);
  lastError = error;
  servoOutput(m2Speed,m1Speed);
  int leftSpeed = leftBaseSpeed + servoSpeed;
  int rightSpeed = rightBaseSpeed - servoSpeed;
  servoOutput(leftSpeed,RightSpeed);
  Serial.print("Left: ");
  Serial.print(m1Speed);
  Serial.print(" Right: ");
  Serial.print(m2Speed);
  Serial.print(" Error: ");
  Serial.println(error);

}
