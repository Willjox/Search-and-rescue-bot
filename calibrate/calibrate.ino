
#include "QTRSensors.h"
#include <EEPROM.h>
int address;
const uint8_t linePins[3] = {5, 4, 3 };
const uint8_t turnPins[2] = { 7 , 6};

QTRSensors lineFollower;
QTRSensors turnDetectors;


void calibrate() {
  Serial.println("starting calibration in 5 sec");
  delay(5000);
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
}

void save(uint16_t *data , int size ) {
  Serial.print("Saving: ");
  for(int i = 0; i < size; i++) {
      EEPROM.put(address, data[i]);
      Serial.print(data[i]);
      Serial.print(" ");
      address += sizeof(uint16_t);
  }
  Serial.println("");
}

void setup() {
  Serial.begin(9600);
  lineFollower.setTypeRC();
  lineFollower.setSensorPins(linePins,3);
  turnDetectors.setTypeRC();
  turnDetectors.setSensorPins(turnPins,2);
  calibrate();
  address = 0;
  save(lineFollower.calibrationOn.minimum, 3);
  save(lineFollower.calibrationOn.maximum, 3);
  save(turnDetectors.calibrationOn.minimum, 2);
  save(turnDetectors.calibrationOn.maximum, 2);

}

void loop() {
  delay(100000);
}
