#ifndef SRbotMovment_h
#define SRbotMovment_h

#include "Arduino.h"
#include "Servo.h"
#include "QTRSensors.h"



class SRbotMovment
{
public:
  SRbotMovment();
  boolean followLine();


private:
  QTRSensors turnDetectors;
  QTRSensors lineFollower;
  Servo leftServo;
  Servo rightServo;
  const float kp = 0.01;
  const float kd = 0,02;
  const uint8_t linePins[3] = {4 , 3 , 3};
  int lastError;
  int leftBaseSpeed;
  int rightBaseSpeed;

  void adjustSpeed(int left, int right);
  void servoOutput(int left , int right);
  void control();
  void loop();
  int detectTurn();

}

#endif
