#include "Arduino.h"
#include "QTRSensors.h"
#include "SRbotSensors.h"
#include "EEPROM.h"

SRbotSensors::SRbotSensors() {
    Serial.println("In CONStruct for sensors");
    uint8_t linePins[3] = {5, 4 , 3};
    uint8_t turnPins[2] = { 7 , 6};
    lineFollower.setTypeRC();
    lineFollower.setSensorPins(linePins,3);
    turnDetectors.setTypeRC();
    turnDetectors.setSensorPins(turnPins,2);
    int echoPin = 11;
    int trigPin = 12;
    pinMode(echoPin,INPUT);
    pinMode(trigPin,OUTPUT);
    loadCalibration();
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

int SRbotSensors::distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  return duration / 29 / 2;
}
int SRbotSensors::isBlack(uint16_t mesurement) {
  Serial.println(mesurement);
  if(mesurement >= 500) {
    return 1;
  } else {
    return 0;
  }
}

boolean SRbotSensors::midState() {
  lineFollower.readCalibrated(lineValues);
  if(lineValues[1] > 800) {
    return true;
  } else {
    return false;
  }
}
void SRbotSensors::loadCalibration() {
  address = 0;
  lineFollower.calibrationOn.minimum = &lineFollowerMin[0];
  lineFollower.calibrationOn.maximum = &lineFollowerMax[0];
  lineFollower.calibrationOn.initialized = true;

  turnDetectors.calibrationOn.minimum = &turnDetectorsMin[0];
  turnDetectors.calibrationOn.maximum = &turnDetectorsMax[0];
  turnDetectors.calibrationOn.initialized = true;

  loadData(lineFollower.calibrationOn.minimum, 3);
  loadData(lineFollower.calibrationOn.maximum, 3);

  loadData(turnDetectors.calibrationOn.minimum, 2);
  loadData(turnDetectors.calibrationOn.maximum, 2);
}

void SRbotSensors::loadData (uint16_t *data, int size) {
  Serial.print("loaded: ");
  for(int i = 0; i < size; i++) {
      EEPROM.get(address, data[i]);
      Serial.print(data[i]);
      Serial.print(" ");
      address += sizeof(uint16_t);
  }
  Serial.println("");
}
