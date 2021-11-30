#include <Button.h>
//#include <SRbotGripper.h>
#include <SRbotMovment.h>

Button button(13);
//SRbotGripper gripper(A0,A1);
SRbotMovment *movement;

//void gripAndStore() {
//  button.waitFor(HIGH,"push to GRIP");
//  gripper.grip();
//  button.waitFor(HIGH,"push to RAISE");
//  gripper.rotate(-90);
//  button.waitFor(HIGH,"push to RELEASE");
//  gripper.grip();
//  button.waitFor(HIGH,"push to LOWER");
//  gripper.rotate(90);
//}

void setup() {
  Serial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  button.waitFor(HIGH,"Setup done waiting for buttonpress");
  movement = new SRbotMovment();
  while (Serial.available() == 0) {
    delay(20);
  }
}

void loop() {
  Serial.println("loop");
  int turn = movement->followLine();
  if (turn >= 4) {
    movement->turn(1);
    } else if (turn == 2) {
      movement->turn(2);
    }
}
