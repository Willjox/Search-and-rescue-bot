#ifndef SRbotMovment_h
#define SRbotMovment_h

#include "Arduino.h"
#include "Servo.h"
#include "SRbotSensors.h"

class SRbotMovment
{
  public:
  SRbotMovment();
  int followLine();
  void turn(int direction);
  void rotate();
  void stop();
  void start();


  private:
    const int servoPins[2] = {9,10};
    const float kp = 0.015;
    const float kd = 0.022;

    SRbotSensors *sensors;
    Servo leftServo;
    Servo rightServo;

    boolean stopped;

    int lastError;
    int leftBaseSpeed;
    int rightBaseSpeed;

    void adjustSpeed(int left, int right);
    void servoOutput(int left , int right);
    void control(int position);
    void endOfLine();
};

#endif
