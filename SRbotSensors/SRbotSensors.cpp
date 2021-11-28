#include "Arduino.h"
#include "QTRSensors.h"
#include "SRbotSensors.h"

SRbotSensors::SRbotSensors() {
    Serial.println("I CONS");
    uint8_t linePins[3] = {4, 3 , 2};
    uint8_t turnPins[2] = { 6 , 5};
    Serial.println(linePins[0]);
    Serial.println(linePins[1]);
    Serial.println(linePins[2]);

    lineFollower.setTypeRC();
    lineFollower.setSensorPins(linePins,3);
    turnDetectors.setTypeRC();
    turnDetectors.setSensorPins(turnPins,2);
}

int SRbotSensors::getLinePos() {
  return lineFollower.readLineBlack(lineValues);
}

int SRbotSensors::detectTurn() {
  Serial.println("i detectTurn");
  turnDetectors.readCalibrated(turnValues);
  int result = (isBlack(turnValues[0]) * 4 )
              + (isBlack(turnValues[1]) * 2 );
  //if result > 0
  // measure UltraSonic
  // if > nåttvärde
  // result + 1

  return result;


}
int SRbotSensors::isBlack(uint16_t mesurement) {
  if(mesurement >= 500) {
    return 1;
  } else {
    return 0;
  }
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
