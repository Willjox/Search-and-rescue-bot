#include "Arduino.h"
#include "SRbotMovment.h"
#include "Servo.h"
#include "SRbotSensors.h"

SRbotMovment::SRbotMovment() {
  start();
  stopped = false;
  servoOutput(90,90);
  lastError = 0;
  leftBaseSpeed = 110;
  rightBaseSpeed = 110;

  sensors = new SRbotSensors();



}

int SRbotMovment::followLine() {
 int direction = 0;
 while ( direction == 0) {
    if(stopped) {
      return 10;
    }
    control(sensors->getLinePos());
    boolean deadEnd = ((!sensors->midState()) && (sensors->distance() < 15));
    boolean lineEnd = sensors->allState();
    if(deadEnd || !lineEnd) {

    }
    direction = sensors->detectTurn();
    delay(50);
  }
  return direction;
}

void SRbotMovment::endOfLine() {
  servoOutput(90,90);
  Serial.println("End of rine: ");
  rotate();
  while(sensors->midState() == false && !stopped) {
    delay(20);
  }
}

void SRbotMovment::turn(int direction) {
    if (direction == 1) {
        servoOutput(90,90);
        servoOutput(120,120);
        delay(500);
        servoOutput(120,75);
        delay(500);
        while(sensors->midState() != true && !stopped) {
        delay(20);
        }
      } else if (direction == 2) {
          servoOutput(90,90);
          servoOutput(120,120);
          delay(500);
          servoOutput(75,120);
          delay(500);
          while(sensors->midState() != true && !stopped) {
            delay(20);
        }
    }
     servoOutput(90,90);
     Serial.println("Turn done");
}

void SRbotMovment::stop() {
  servoOutput(90,90);
  leftServo.detach();
  rightServo.detach();
  stopped = true;
}

void SRbotMovment::start() {
  leftServo.attach(servoPins[1]);
  rightServo.attach(servoPins[0]);
  stopped = false;
}

void SRbotMovment::rotate() {
  servoOutput(65,115);
}

void SRbotMovment::servoOutput(int leftSpeed, int rightSpeed) {
  leftServo.write(leftSpeed);
  rightServo.write(180-rightSpeed);
}

void SRbotMovment::control(int position) {
  Serial.println("i control");
  int error = position - 1000;
  int servoSpeed = kp * error + kd * (error - lastError);
  lastError = error;
  int leftSpeed = leftBaseSpeed - servoSpeed;
  int rightSpeed = rightBaseSpeed + servoSpeed;
  servoOutput(leftSpeed,rightSpeed);
}
