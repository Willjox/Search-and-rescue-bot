// Motorshield pins

#define LEFT 111
#define RIGHT 222
#define FORWARD 120
#define REVERSE 60
Servo leftServo;
Servo rightServo;


void setup() {
 Serial.begin(9600);
 Serial.println("starting setup");
 leftServo.attach(8);
 rightServo.attach(7);
 Serial.println("Finished setup");
}

void servoOutput(int leftSpeed, int rightSpeed) {
  leftServo.write(leftSpeed);
  rightServo.write(rightSpeed);
}

void rotate(int direction) {
  if (direction == LEFT) {
    Serial.println("Rotating to the LEFT");
    servoOutput(REVERSE,FORWARD );
  } else if (direction == RIGHT) {
    Serial.println("Rotating to the RIGHT");
    servoOutput(FORWARD,REVERSE);
  } else {
    Serial.println("ERROR Rotating");
  }
}

void straight(int direction) {
  if (direction == FORWARD) {
    Serial.println("Going forward");
    servoOutput(FORWARD,FORWARD);
  } else if (direction == REVERSE) {
    Serial.println("Reversing");
    servoOutput(REVERSE,REVERSE);
  }  else {
    Serial.println("ERROR going straight");
  }
}

void loop() {
  Serial.println("starting loop");
  Serial.println("starting BackAndForth");
  straight(FORWARD);
  delay(2000);
  straight(REVERSE);
  delay(2000);
  Serial.println("starting Rotate");
  rotate(LEFT);
  delay(3000);
  rotate(RIGHT);
  delay(3000);
}
