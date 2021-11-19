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

const uint8_t linePins[3] = {2, 3 , 4};
const uint8_t startButton = 13;
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
  lineFollower.setTypeRC();
  lineFollower.setSensorPins(linePins,3);
  Serial.println("Sensors initiated, Calibrating");
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("Iteration: ");
  for (uint8_t i = 0; i < 250; i++) {
    lineFollower.calibrate();
    if (i%25 == 0) {
      Serial.print(" ");
      Serial.print(i);
    }
    delay(20);
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("");
  Serial.println("Calibration Done. waiting for start button");
  pinMode(startbutton,INPUT);
  Serial.println("waiting for start button");
  while {digitalRead(startButton == LOW) {
    delay(100);
  }
  Serial.println("Starting");

}

void loop() {
 lineFollower.readCalibrated(lineValues);
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
