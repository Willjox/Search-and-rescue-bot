#include "Arduino.h"
#include "SRbotMovment.h"
#include "Servo.h"
#include "SRbotSensors.h"
#define loopTime 15

SRbotMovment::SRbotMovment() {
    start();
    stopped = false;
    forcedTurn = false;
    servoOutput(90,90);
    lastError = 0;
    integrator = 0;
    leftBaseSpeed = 115;
    rightBaseSpeed = 115;
    sensors = new SRbotSensors();




}

int SRbotMovment::followLine() {
 int direction = 0;
 while ( direction == 0) {
    if(stopped) {
      Serial.println("gripklo engage!");
      return 10;
    }
    //boolean deadEnd = ((!sensors->midState()) && (sensors->distance() < 15));
    boolean lineEnd = sensors->allState();
    if(!lineEnd) {
      if (forcedTurn) {
        forcedTurn = false;
        freeTurn();
      } else {
        endOfLine();
      }
    }
    control(sensors->getLinePos());
    direction = sensors->detectTurn();
    delay(loopTime);
  }
  //integrator = 0;
  return direction;
}
int SRbotMovment::followLineToEndOfLine() {
 int direction = 0;
 while ( direction == 0) {
    //boolean deadEnd = ((!sensors->midState()) && (sensors->distance() < 15));
    boolean lineEnd = sensors->allState();
    if(!lineEnd) {
      return 0;
    }
    control(sensors->getLinePos());
    delay(loopTime);
  }
}


void SRbotMovment::endOfLine() {
  servoOutput(90,90);
  Serial.println("End of rine: ");
  rotate();
  while(!sensors->midState() && !stopped) {
    delay(10);
  }
}

void SRbotMovment::turn(int direction) {

    if (direction == 1) {
        Serial.println("Turning left");
        servoOutput(90,90);
        servoOutput(leftBaseSpeed,rightBaseSpeed);
        delay(525);
        servoOutput(leftBaseSpeed - 4,180-rightBaseSpeed + 4);
        delay(500);
        while(!sensors->midState() && !stopped) {
        delay(10);
      //  Serial.println("turn loop");
        }
      } else if (direction == 2) {
          Serial.println("Turning Right");
          servoOutput(90,90);
          servoOutput(leftBaseSpeed,rightBaseSpeed);
          delay(535);
          servoOutput(180-leftBaseSpeed + 4,rightBaseSpeed - 4);
          delay(500);
          while(!sensors->midState() && !stopped) {
            delay(10);
          //  Serial.println("turn loop");
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
  servoOutput(180 - leftBaseSpeed + 4,rightBaseSpeed - 4);
}

void SRbotMovment::servoOutput(int leftSpeed, int rightSpeed) {

  leftServo.write(leftSpeed);
  rightServo.write(180-rightSpeed);
}

void SRbotMovment::control(int position) {
  //Serial.println("i control");
  int error = position - 1000;
  integrator = constrain(integrator + error,-10000,10000);
  int servoSpeed = kp * error + kd * (error - lastError) + (integrator * ki) ;
  lastError = error;
  int leftSpeed = leftBaseSpeed - servoSpeed;
  int rightSpeed = rightBaseSpeed + servoSpeed;
  servoOutput(leftSpeed,rightSpeed);
}

void SRbotMovment::freeTurn() {
  //servoOutput(115,65);
  //delay(200);
  servoOutput(115,114);
  delay(465);
  servoOutput(100,115);
  while(!sensors->allState() && !stopped) {
    delay(10);
  }
}

void SRbotMovment::straight() {
  while(sensors->detectTurn() > 0) {
    control(sensors->getLinePos());
    delay(10);
  }
}

void SRbotMovment::forceTurn() {
  forcedTurn = true;
}
