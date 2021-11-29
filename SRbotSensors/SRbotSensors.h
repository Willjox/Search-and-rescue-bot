#ifndef SRbotSensors_h
#define SRbotSensors_h

#include "Arduino.h"
#include "QTRSensors.h"
#include "EEPROM.h"

class SRbotSensors
{
  public:
    SRbotSensors();
    int getLinePos();
    int detectTurn();
    boolean midState();
    int distance();

  private:
    int address;
    int duration;
    int echoPin;
    int trigPin;
    QTRSensors lineFollower;
    QTRSensors turnDetectors;

    uint16_t turnDetectorsMax[2];
    uint16_t turnDetectorsMin[2];
    uint16_t lineFollowerMax[3];
    uint16_t lineFollowerMin[3];

    uint16_t lineValues[3];
    uint16_t turnValues[2];
    int isBlack(uint16_t mesurement);
    void loadCalibration();
    void loadData(uint16_t *data, int size);

};

#endif
