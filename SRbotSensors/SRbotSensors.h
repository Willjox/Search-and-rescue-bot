#ifndef SRbotSensors_h
#define SRbotSensors_h

#include "Arduino.h"
#include "QTRSensors.h"

class SRbotSensors
{
  public:
    SRbotSensors();
    int getLinePos();
    int detectTurn();
    boolean midState();

  private:
    int address;
    QTRSensors lineFollower;
    QTRSensors turnDetectors;

    uint16_t lineValues[3];
    uint16_t turnValues[2];
    int isBlack(uint16_t mesurement);
    void loadCalibration();
    void loadData(uint16_t *data, int size)
};

#endif
