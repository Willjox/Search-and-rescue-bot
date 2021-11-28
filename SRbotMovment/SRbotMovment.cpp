#include "Arduino.h"
#include "SRbotMovment.h"
#include "Servo.h"
#include "SRbotSensors.h"

SRbotMovment::SRbotMovment() {
  leftServo.attach(9);
  rightServo.attach(10);
  servoOutput(90,90);
  lastError = 0;
  leftBaseSpeed = 130;
  rightBaseSpeed = 130;

  sensors = new SRbotSensors();



}

int SRbotMovment::followLine() {
  while (1) {
    //control(sensors->getLinePos());
    servoOutput(90,90);
    delay(500);
  }
  servoOutput(90,90);
  delay(1500);   //FOR TESTING PURPOSES
}

void SRbotMovment::turn(int direction) {
    //WHILE DETECTMIDLINE
    servoOutput(95,95);
    while(sensors->midState() == true) {
      delay(20);
    }
    servoOutput(90,90);
    delay(1000);
    servoOutput(95,120);
    while(sensors->midState() != true) {
      delay(20);
    }
    int timer = millis() + 1000;
    while(millis() < timer ) {
      servoOutput(110,110);
     }

}

void SRbotMovment::rotate() {
  Serial.println("i calibrate");
  sensors->calibrate();
}

void SRbotMovment::servoOutput(int leftSpeed, int rightSpeed) {

  leftServo.write(90);
  rightServo.write(90);
  Serial.println(leftServo.read());
  Serial.println(rightServo.read());
}

void SRbotMovment::control(int position) {
  Serial.println("i control");
  int error = position - 1000;
  int servoSpeed = kp * error + kd * (error - lastError);
  lastError = error;
  int leftSpeed = leftBaseSpeed + servoSpeed;
  int rightSpeed = rightBaseSpeed - servoSpeed;
  servoOutput(leftSpeed,rightSpeed);
  Serial.print("Left: ");
  Serial.print(rightSpeed);
  Serial.print(" Right: ");
  Serial.print(leftSpeed);
  Serial.print(" Error: ");
  Serial.println(error);
}
