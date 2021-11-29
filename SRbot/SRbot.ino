#include <Button.h>
#include <SRbotGripper.h>
#include <SRbotMovment.h>

Button button(13);
SRbotGripper *gripper;
SRbotMovment *movement;

void gripAndStore() {
  gripper->grip();
  delay(3000);
  gripper->rotate(-175);
  delay(4000);
  //gripper->grip();
  delay(3000);
  gripper->rotate(175);
  delay(3000);
}

void setup() {
  Serial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  //button.waitFor(HIGH,"Setup done waiting for buttonpress");
  movement = new SRbotMovment();
  gripper = new SRbotGripper(A0,A1);

}

void loop() {
  Serial.println("loop");
  delay(3000);
  gripAndStore();
  delay(5000);
  //int turn = movement->followLine();
  //if (turn >= 4) {
  //  movement->turn(1);
  //  } else if (turn == 2) {
  //    movement->turn(2);
  //  }
}
