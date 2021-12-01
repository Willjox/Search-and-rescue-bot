//#include <Button.h>

#include <SRbotGripper.h>
#include <SRbotMovment.h>
//Button button(13);
SRbotGripper *gripper;
volatile boolean stopped;
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
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  gripper = new SRbotGripper(A0,A1);
  pinMode(13,OUTPUT);
  interruptPin = 2;
  digitalWrite(13,HIGH);

  pinMode(interruptPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interruptPin),switchTrig, FALLING);
  //button.waitFor(HIGH,"Setup done waiting for buttonpress");
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
  if (turn >= 4) {
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
