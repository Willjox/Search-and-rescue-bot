#include <QTRSensors.h>
#include <Servo.h>
#define leftLineSensor  A0
#define rightLineSensor A1
#define middleLineSensor A2
#define leftTurnSensor
#define rightTurnSensor


QTRSensors lineFollower;
QTRSensors turnDetectors;
Servo leftServo;
Servo rightServo;

int M1;
int M2;

int lastError = 0;
const float kp = 0.01;
const float kd = 0.02;
const uint8_t linePins[3] = {4, 3 , 2};
const uint8_t startButton = 13;
//int turnPins[] = {leftTurnSensor, rightTurnSensor};
uint16_t lineValues[3];

void servoOutput(int leftSpeed, int rightSpeed) {
  leftServo.write(180-leftSpeed);
  rightServo.write(rightSpeed);
}

void adjustSpeed(int left, int right) {
  left = constrain(left + leftServo.read() , 5 , 175);
  right = constrain(right + rightServo.read() , 5 , 175);
  servoOutput(left,right);
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
  leftServo.attach(9);
  rightServo.attach(10);
  servoOutput(90,90);
  while(1) {
    Serial.println("testar");
  }

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
  //while (digitalRead(startButton) == HIGH) {
    //delay(100);
  //}
  Serial.println("Starting");
  M1 = 110;
  M2 = 110;
}

void loop() {

  int position = lineFollower.readLineBlack(lineValues);
  int error = position - 1000;
  int motorSpeed = kp * error + kd * (error - lastError);
  lastError = error;
  int m2Speed = M1 + motorSpeed;
  int m1Speed = M2 - motorSpeed;
  Serial.print("Left: ");
  Serial.print(m1Speed);
  Serial.print(" Right: ");
  Serial.print(m2Speed);
  Serial.print(" Error: ");
  Serial.println(error);
  servoOutput(m2Speed,m1Speed);
  delay(100);
}
