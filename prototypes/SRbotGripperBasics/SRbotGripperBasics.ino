#include <Servo.h>
Servo gripperServo;
Servo rotateServo;
const int startButton = 13;
const int gripServoIO = 8;
const int rotateServoIO = 9;
void setup() {
 Serial.begin(9600);
 Serial.println("starting setup");
 rotateServo.attach(rotateServoIO);
 gripperServo.attach(gripServoIO);
 pinMode(startButton,INPUT);
 gripperServo.write(90);
 rotateServo.write(180);

Serial.println("Starting");
 Serial.println("Finished setup");
}

void loop() {
  int pos;
  int rotatePos = 180;
  Serial.println("waiting for start button, grip");
  while (digitalRead(startButton)== LOW) {
    delay(100);
  }

  for (pos = 90; pos >= 0; pos -= 1) {
    gripperServo.write(pos);
    Serial.println(pos);
    delay(15);
  }
  Serial.println("waiting for button, raise");
  while (digitalRead(startButton)== LOW) {
   delay(100);
  }

  for (rotatePos; rotatePos >= 60; rotatePos -= 1) {
    rotateServo.write(rotatePos);
    delay(30);
    Serial.println(rotatePos);
  }
  Serial.println("waiting for button, release");
  while (digitalRead(startButton)== LOW) {
   delay(100);
  }

  for (pos; pos <= 90; pos += 1) {
      gripperServo.write(pos);
      Serial.println(pos);
      delay(30);
  }
  Serial.println("waiting for button, lower");
  while (digitalRead(startButton)== LOW) {
   delay(100);
  }

    for (rotatePos; rotatePos <= 180; rotatePos += 1) {
    rotateServo.write(rotatePos);
    delay(30);
    Serial.println(rotatePos);
  }

}
