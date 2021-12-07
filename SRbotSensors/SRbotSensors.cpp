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
    echoPin = 11;
    turnFilter = 0;
    trigPin = 12;
    filterLineEnd = 0;
    pinMode(echoPin,INPUT);
    pinMode(trigPin,OUTPUT);
    loadCalibration();
}

int SRbotSensors::getLinePos() {
  return lineFollower.readLineBlack(lineValues);
}

int SRbotSensors::detectTurn() {
  //Serial.print("i detectTurn: ");
  turnDetectors.readCalibrated(turnValues);
  //Serial.print(turnValues[0]);
  //Serial.print(" ");
  //Serial.println(turnValues[1]);
  int result = (isBlack(turnValues[0]) * 4 )
              + (isBlack(turnValues[1]) * 2 );
  if (result > 0) {
	turnFilter++;
  } else {
	turnFilter = 0;
  }
  if (turnFilter >= 1) {
	  turnFilter = 0;
	  return result;
  } else {
	  return 0;
  }
}

int SRbotSensors::distance() {
  digitalWrite(trigPin, LOW);
  delay(5);
  digitalWrite(trigPin, HIGH);
  delay(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  int distance = duration / 29 / 2;
  return distance;
}
int SRbotSensors::isBlack(uint16_t mesurement) {
    return 1;
  } else {
    return 0;
  }
}

boolean SRbotSensors::midState() {
  lineFollower.readCalibrated(lineValues);
  //Serial.println(lineValues[1]);
  //Serial.println("MIDSTATE");
    return true;
  } else {
    return false;
  }
}

boolean SRbotSensors::allState() {
  lineFollower.readCalibrated(lineValues);
  for (int i = 0; i < 3; i++) {
    //Serial.println(lineValues[i]);
  Serial.print(lineValues[i]);
  Serial.print(" ");
  }
Serial.print(". ");
Serial.println(filterLineEnd);
  for (int i = 0; i < 3; i++) {
    if(lineValues[i] > 400) {
    filterLineEnd = 0;
    return true;
    }
  }
  if (filterLineEnd >= 3) {
  if (filterLineEnd > 4) {
      return false;
  }
  filterLineEnd++;
  return false;
  return true;
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
