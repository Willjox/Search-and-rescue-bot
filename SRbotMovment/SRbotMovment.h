#ifndef SRbotMovment_h
#define SRbotMovment_h

#include "Arduino.h"
#include "Servo.h"
#include "SRbotSensors.h"

class SRbotMovment
{
  public:
  SRbotMovment(int *servoPins, int *linePins, int *turnPins);
  void followLine();
  void turn(int direction);
  void rotate();


  private:
    SRbotSensors sensors;
    Servo leftServo;
    Servo rightServo;

    const float kp = 0.01;
    const float kd = 0.02;

    int lastError;
    int leftBaseSpeed;
    int rightBaseSpeed;

    void adjustSpeed(int left, int right);
    void servoOutput(int left , int right);
    void control();
};

#endif
