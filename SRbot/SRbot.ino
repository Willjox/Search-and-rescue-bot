#include <Button.h>
//#include <SRbotGripper.h>
#include <SRbotMovment.h>

Button button(13);
//SRbotGripper gripper(7,8);
SRbotMovment *movement;

//void gripAndStore() {
  //button.waitFor(HIGH,"push to GRIP");
  //gripper.grip();
  //button.waitFor(HIGH,"push to RAISE");
  //gripper.rotate(-90);
  //button.waitFor(HIGH,"push to RELEASE");
  //gripper.grip();
  //button.waitFor(HIGH,"push to LOWER");
  //gripper.rotate(90);
//}

void setup() {
  Serial.begin(9600);
  //button.waitFor(HIGH,"Setup done waiting for buttonpress");
  movement = new SRbotMovment();
}

void loop() {
  Serial.println("loop");
  movement->followLine();
//  switch (movement.followLine()) {
//      movment.turn(LEFT);
//    case 2:
//      movment.turn(RIGHT);
//    case 3:
//    movment.followLine();
//    case 4:
//    movment.rotate();
//      default:
//        Serial.println("turn");
//        movement.turn(10);
//  }
  delay(1000000);
}
