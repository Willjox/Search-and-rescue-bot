//#include <Button.h>
#define RIGHT 1
#define LEFT 2
#define STRAIGHT 3
#define FORCEDRIGHT 4
#define FORCEDSTRAIGHT 5
#include <SRbotGripper.h>
#include <SRbotMovment.h>
//Button button(13);
SRbotGripper *gripper;
volatile SRbotMovment *movement;
int interruptPin;
int turnChoice;
int passengers;
const int directions[54] = {RIGHT , LEFT , LEFT , RIGHT , LEFT , LEFT, RIGHT, FORCEDRIGHT ,LEFT , LEFT ,STRAIGHT , RIGHT , LEFT , LEFT , RIGHT , LEFT,
                              RIGHT, RIGHT , LEFT , LEFT , STRAIGHT , RIGHT , RIGHT , LEFT , LEFT , LEFT , LEFT ,RIGHT ,LEFT , LEFT , RIGHT , RIGHT , LEFT, FORCEDRIGHT , LEFT , RIGHT , RIGHT , LEFT , LEFT , LEFT , RIGHT , LEFT , LEFT , RIGHT , RIGHT , LEFT , FORCEDSTRAIGHT, RIGHT , LEFT , LEFT , LEFT , RIGHT , LEFT};
void gripAndStore() {
  if(passengers == 2) {
    return;
  }
  gripper->rotate(80);
  delay(800);
  gripper->grip();
  delay(700);
  if ( passengers == 0) {
    gripper->rotate(-165);
    delay(800);
    gripper->grip();
    delay(1000);
    gripper->rotate(85);
    delay(800);
  } else if (passengers == 1) {
    gripper->rotate(-80);
    delay(800);
  }
  Serial.println(passengers);
  delay(1000);
  passengers++;
  //attachInterrupt(digitalPinToInterrupt(interruptPin),switchTrig, FALLING);
}
void switchTrig () {
  //detachInterrupt(digitalPinToInterrupt(interruptPin));
  movement->stop();
  Serial.println("yo ima interupting");
}
void setup() {
  Serial.begin(9600);
  turnChoice = 29 ;
   interruptPin = 2;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),switchTrig, FALLING);
  Serial.println("waiting for serial....");
//  while (Serial.available() == 0) {
//    delay(20);
//  }
//  Serial.read();
  delay(5000);
  gripper = new SRbotGripper(A0,A1);
  movement = new SRbotMovment();
}

void loop() {

  if (movement->followLine() != 10) {
    switch (directions[turnChoice]) {
      case LEFT:
      	Serial.println("vänster");
        movement->turn(1);
	break;
      case RIGHT:
      	Serial.println("höger");
        movement->turn(2);
	break;
      case STRAIGHT:
      	Serial.println("rakt");
        movement->straight();
	break;
      case FORCEDRIGHT:
      	Serial.println("Tvingahöger");
        movement->forceTurn();
        movement->turn(2);
	break;
      case FORCEDSTRAIGHT:
        Serial.println("tvigna framåt");
        movement->forceTurn();
        movement->straight();
  break;
    }
    Serial.println("incremeanting");
    turnChoice++;
    if (turnChoice == 16) {
    	movement->stop();
      passengers = 0;
      delay(5000);
      movement->start();
    } else if (turnChoice >= 54) {
      while(1) {
        movement->stop();
        delay(1000);
        movement->rotate();
        delay(2000);
        
      }
    }
    } else {
      gripAndStore();
      movement->start();
    }
//    while (Serial.available() >= 1) {
//      delay(20);
//      if ( Serial.available() >= 2) {
//      	Serial.read();
//	      Serial.read();
//      }
//    }
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
