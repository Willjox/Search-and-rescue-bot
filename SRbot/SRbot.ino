//#include <Button.h>
#define h 1
#define v 2
#define r 3
#define ht 4
#include <SRbotGripper.h>
#include <SRbotMovment.h>
//Button button(13);
SRbotGripper *gripper;
volatile SRbotMovment *movement;
int interruptPin;
int i;
const int directions[16] = {h, v, v, h,v , v, h, ht ,v,v,r,h,v,v,h,v};
void gripAndStore() {
  gripper->rotate(75);
  delay(1000);
  gripper->grip();
  delay(1000);
  gripper->rotate(-160);
  delay(2000);
  gripper->grip();
  delay(2000);
  gripper->rotate(80);
  delay(1000);
}
void switchTrig () {
    movement->stop();
    Serial.println("yo ima interupting");
}
void setup() {
  Serial.begin(9600);
  int i = 0;
   interruptPin = 2;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),switchTrig, FALLING);
  Serial.println("waiting for serial....");
  while (Serial.available() == 0) {
    delay(20);
  }
  Serial.read();
  gripper = new SRbotGripper(A0,A1);
  movement = new SRbotMovment();
}

void loop() {

  if (movement->followLine() != 10) {
    switch (directions[i]) {
      case v:
      	Serial.println("vänster");
        movement->turn(1);
      case h:
      	Serial.println("höger");
        movement->turn(2);
      case r:
      	Serial.println("rakt");
        movement->straight();
      case ht:
      	Serial.println("Tvingahöger");
        movement->forceTurn();
        movement->turn(2);
    }
    i++;
    } else {
      gripAndStore();
      movement->start();
    }
    while (Serial.available() >= 1) {
      delay(20);
      if ( Serial.available() >= 2) {
      	Serial.read();
	      Serial.read();
      }
    }
}



//if(turn == 10) {
//    gripAndStore();
//    turn = 0;
//    movement->start();
//  } else if (turn >= 4) {
  //    movement->turn(1);
  //  } else if (turn == 2 || turn == 3) {
    //    movement->turn(2);
  //  } else if (turn == 1) {
  //    //Go straight
  //  }
