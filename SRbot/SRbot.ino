#include <Button.h>
#include <SRbotGripper.h>
#include <SRbotMovment.h>

const int servoPins[2] = {9,10};
const int linePins[3] = {4, 3 , 2};
const int turnPins[2] = { 1 , 2};

Button button(13);
SRbotGripper gripper(7,8);
SRbotMovment movment(servoPins,linePins,turnPins);

void gripAndStore() {
  button.waitFor(HIGH,"push to GRIP");
  gripper.grip();
  button.waitFor(HIGH,"push to RAISE");
  gripper.rotate(-90);
  button.waitFor(HIGH,"push to RELEASE");
  gripper.grip();
  button.waitFor(HIGH,"push to LOWER");
  gripper.rotate(90);
}

void setup() {
  Serial.begin(9600);
  button.waitFor(HIGH,"Setup done waiting for buttonpress");
}

void loop() {
//  switch (movment.followLine()) {
//    case 1:
//      movment.turn(LEFT);
//    case 2:
//      movment.turn(RIGHT);
//    case 3:
//    movment.followLine();
//    case 4:
//    movment.rotate();
//  }
}
