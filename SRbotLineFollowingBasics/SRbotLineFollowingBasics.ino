#include <QTRSensors.h>
#define leftLineSensor  A0
#define rightLineSensor A1
#define middleLineSensor A2
#define leftTurnSensor
#define rightTurnSensor
#define ledLeft 10
#define ledMiddle 9
#define ledRight 8

QTRSensors lineFollower;
QTRSensors turnDetectors;

const uint8_t linePins[3] = {A0, A2 , A1};
//int turnPins[] = {leftTurnSensor, rightTurnSensor};
uint16_t lineValues[3];
//int turnStates[];
bool states[3];

void getState() {

}

void controlAlgorithm () {

}

void followLine() {

}

void detectTurns() {

}

void setup() {
  Serial.begin(9600);
  Serial.println("starting setup");
  lineFollower.setTypeAnalog();
  lineFollower.setSensorPins(linePins,3);
  Serial.println("Sensors initiated, Calibrating");
  digitalWrite(LED_BUILTIN, HIGH);
  for (uint8_t i = 0; i < 250; i++) {
    lineFollower.calibrate();
    if (i%10 == 1) {
      Serial.print("Iteration: ");
      Serial.println(i);
    }
    delay(20);
  }
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.println("Calibration Done. Starting loop");

}

void loop() {
 lineFollower.read(lineValues);
 Serial.println(lineValues[0]);
 Serial.println(lineValues[1]);
 Serial.println(lineValues[2]);
 for (int i = 0; i < 3; i++) {
   states[i] = (lineValues[i] > 500);
 }
 digitalWrite(ledLeft,states[0]);
 digitalWrite(ledMiddle,states[1]);
 digitalWrite(ledRight,states[2]);
 delay(30);
}
