#include <Servo.h>
Servo gripperServo;
Servo rotateServo;
void setup() {
 Serial.begin(9600);
 Serial.println("starting setup");
 rotateServo.attach(12);
 gripperServo.attach(5);
 Serial.println("Finished setup");
}

void loop() {
  int pos;
  for (pos = 0; pos <= 180; pos += 1) {
    rotateServo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    rotateServo.write(pos);
    delay(15);
  }

}
