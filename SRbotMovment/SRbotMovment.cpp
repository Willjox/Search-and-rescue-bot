#include "Arduino.h"
#include "SRbotMovment.h"
#include "Servo.h"
#include "SRbotSensors.h"

SRbotMovment::SRbotMovment() {
  //leftServo.attach(servoPins[0]);
  //rightServo.attach(servoPins[1]);
  servoOutput(90,90);
  lastError = 0;
  leftBaseSpeed = 110;
  rightBaseSpeed = 110;

  sensors = new SRbotSensors();



}

int SRbotMovment::followLine() {
  while (sensors->detectTurn() == 0) {
    control(sensors->getLinePos());
    if(((!sensors->midState()) && (sensors->distance() < 10)) ) {
      servoOutput(90,90);
      Serial.print("End of rine: ");
      Serial.println(sensors->distance());

      delay(2000);
      rotate();
      while(sensors->midState() == false) {
        delay(20);
      }
    }
    delay(50);
  }
}

  //servoOutput(90,90);
  //Serial.println("Turn detected");
  //turn(1);
  //delay(2000);   //FOR TESTING PURPOSES
  //while (sensors->detectTurn() == 0) {
  //  control(sensors->getLinePos());
  //  delay(50);
//  }
  //turn(1);
  //while (sensors->detectTurn() == 0) {
//    control(sensors->getLinePos());
  //  delay(50);
  //}
  //turn(2);

void SRbotMovment::turn(int direction) {
    if (direction == 1) {
        servoOutput(90,90);
        delay(1000);
        servoOutput(120,120);
        delay(500);
        servoOutput(75,120);
        delay(500);
        while(sensors->midState() != true) {
        delay(20);
        }
      } else if (direction == 2) {
          servoOutput(90,90);
          delay(1000);
          servoOutput(120,120);
          delay(500);
          servoOutput(120,75);
          delay(500);
          while(sensors->midState() != true) {
            delay(20);
        }
    }
    //WHILE DETECTMIDLINE
     servoOutput(90,90);
     Serial.println("Turn done");
     delay(2000);
}

void SRbotMovment::rotate() {
  servoOutput(60,120);
}

void SRbotMovment::servoOutput(int leftSpeed, int rightSpeed) {

  leftServo.write(180-leftSpeed);
  rightServo.write(rightSpeed);
  //Serial.println(leftServo.read());
  //Serial.println(rightServo.read());
}

void SRbotMovment::control(int position) {
  //Serial.println("i control");
  int error = position - 1000;
  int servoSpeed = kp * error + kd * (error - lastError);
  lastError = error;
  int leftSpeed = leftBaseSpeed + servoSpeed;
  int rightSpeed = rightBaseSpeed - servoSpeed;
  servoOutput(leftSpeed,rightSpeed);
//  Serial.print("Left: ");
//  Serial.print(rightSpeed);
//  Serial.print(" Right: ");
//  Serial.print(leftSpeed);
//  Serial.print(" Error: ");
//  Serial.println(error);
}
