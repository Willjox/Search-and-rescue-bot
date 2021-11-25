#include "Arduino.h"
#include "QTRSensors.h"
#include "SRbotSensors.h"

SRbotSensors::SRbotSensors(int *linePins , int *turnPins) {
      this.linePins = lineSensors;
      this.turnPins = turnPins;
      lineFollower.setTypeRC();
      lineFollower.setSensorPins(linePins,3);
      turnDetectors.setTypeRC();
      turnDetectors.setSensorPins(linePins,2);
      //calibrate();
}

int SRbotSensors::getLinePos() {
  return lineFollower.readLineBlack(lineValues);
}

int SRbotSensors::detectTurn() {
  //TODO
}

boolean SRbotSensors::midState() {
  //TODO
}

void SRbotSensors::calibrate() {
  Serial.print("Iteration: ");
  for (uint8_t i = 0; i < 250; i++) {
    lineFollower.calibrate();
    turnDetectors.calibrate();
    if (i%25 == 0) {
      Serial.print(" ");
      Serial.print(i);
    }
    delay(20);
  }
  Serial.println("");
  Serial.print("Max: ");
  //Serial.println(lineFollower.calibratedMaximumOn);
  Serial.print("Min: ");
  //Serial.println(lineFollower.calibratedMinimumOn);
}
