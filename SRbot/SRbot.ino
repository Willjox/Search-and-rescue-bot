#include <Button.h>
#include <SRbotGripper.h>

Button button(13);
SRbotGripper gripper(7,8);

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
  gripAndStore();

}
