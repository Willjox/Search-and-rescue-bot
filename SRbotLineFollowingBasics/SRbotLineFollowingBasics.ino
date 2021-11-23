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
int M1;
int M2;

int lastError = 0;
const float kp = 0.1;
const float kd = 5;
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

void calibrate() {
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
  Serial.println("");
  Serial.print("Max: ");
  //Serial.println(lineFollower.calibratedMaximumOn);
  Serial.print("Min: ");
  //Serial.println(lineFollower.calibratedMinimumOn);
  digitalWrite(LED_BUILTIN, LOW);

}

void setup() {
  pinMode(startButton,INPUT);
  Serial.begin(9600);
  Serial.println("starting setup");
  lineFollower.setTypeRC();
  lineFollower.setSensorPins(linePins,3);
  Serial.println("Sensors initiated.");
  delay(1000);
  if (digitalRead(startButton) == HIGH) {
    Serial.println("Initiating calibration");
    calibrate();
    Serial.println("calibration done");
  } else {
    Serial.println("Skipped calibration");
  }
  Serial.println("Calibration Done. waiting for start button");
  Serial.println("waiting for start button");
  while (digitalRead(startButton) == LOW) {
    delay(100);
  }
  while (digitalRead(startButton) == HIGH) {
    delay(100);
  }
  Serial.println("Starting");
  M1 = 100;
  M2 = 100;
}

void loop() {

  int position = lineFollower.readLineBlack(lineValues);
  int error = position - 1000;
  int motorSpeed = kp * error + kd * (error - lastError);
  lastError = error;
  int m1Speed = M1 + motorSpeed;
  int m2Speed = M2 - motorSpeed;
  Serial.print("Left: ");
  Serial.print(m1Speed);
  Serial.print(" Right: ");
  Serial.println(m2Speed);
  delay(4000);
}
