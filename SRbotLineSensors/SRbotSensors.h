#ifndef SRbotSensors_h
#define SRbotSensors_h

#include "Arduino.h"
#include "QTRSensors.h"

class SRbotSensors
{
  public:
    SRbotSensors(int *linePins, int *turnPins);
    int getLinePos();
    int detectTurn();
    boolean midState();
  private:
    int *linePins;
    int *turnPins;
    uint16_t lineValues[3];
    QTRSensors lineFollower;
    QTRSensors turnDetectors;

    void calibrate();


};

#endif
