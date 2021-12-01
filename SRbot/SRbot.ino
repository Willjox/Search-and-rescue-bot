//#include <Button.h>

#include <SRbotGripper.h>
#include <SRbotMovment.h>
//Button button(13);
SRbotGripper *gripper;
volatile SRbotMovment *movement;
int interruptPin;

void gripAndStore() {
  gripper->grip();
  delay(1000);
  gripper->rotate(-160);
  delay(2000);
  gripper->grip();
  delay(2000);
  gripper->rotate(160);
}
void switchTrig () {
    movement->stop();
    Serial.println("yo ima interupting");
}
void setup() {
  Serial.begin(9600);
  stopped = false;
  gripper = new SRbotGripper(A0,A1);
  interruptPin = 2;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),switchTrig, FALLING);

  while (Serial.available() == 1) {
    delay(20);
  }
  Serial.read();
  movement = new SRbotMovment();
}

void loop() {
  Serial.println("loop");
  int turn = movement->followLine();
  Serial.println(turn);
  if(turn = 10) {
      gripAndStore();
      movement->start();
    } else if (turn >= 4) {
        movement->turn(1);
      } else if (turn == 2) {
          movement->turn(2);
      }
//    while (Serial.available() == 1) {
//      delay(20);
//      if ( Serial.available() > 1) {
//      	Serial.read();
//	      Serial.read();
//      }
//    }
}
