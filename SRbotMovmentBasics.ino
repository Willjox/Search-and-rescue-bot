// Motorshield pins
#define Left_Dir  12
#define Right_Dir  13
#define Left_PWM  3
#define Right_PWM  11
#define Left_I  0
#define Right_I  1
#define Left_Break  9
#define Right_Break  0
#define LEFT 111
#define RIGHT 222
#define FORWARD 11
#define REVERSE 22
//left right motor
int A;
int B;


void setup() {
 Serial.begin(9600);
 Serial.println("starting setup");
 pinMode(Left_Dir, OUTPUT);
 pinMode(Right_Dir, OUTPUT);
 pinMode(Left_PWM, OUTPUT);
 pinMode(Right_PWM, OUTPUT);
 pinMode(A_Break, OUTPUT);
 pinMode(B_Break, OUTPUT);
 digitalWrite(A_Break, LOW);
 digitalWrite(B_Break, LOW);
 A = 0;
 B = 0;
 Serial.println("Finished setup");
}

void motorPWMOutput(int leftSpeed, int rightSpeed) {
  analogWrite(Left_PWM, leftSpeed);
  analogWrite(Right_PWM), rightSpeed);
}

void motorDirection( int left, int right) {
    digitalWrite(Left_Dir, left);
    digitalWrite(Right_Dir, right);
}

void rotate(int direction) {
  if (direction == LEFT) {
    Serial.println("Rotating to the LEFT");
    motorDirection(LEFT)
  } else if (direction == RIGHT) {
    Serial.println("Rotating to the RIGHT");
  } else {
    Serial.println("ERROR Rotating");
  }
}

void straight(int direction) {
  if (direction == FORWARD) {
    Serial.println("Going forward");
  } else if (direction == REVERSE) {
    Serial.println("Reversing");
  }  else {
    Serial.println("ERROR going straight")
  }
}

void loop() {
  Serial.println("starting loop");
  Serial.println("starting backAndForth");
  backAndForth();
  Serial.println("starting Rotate");
  rotate();
}
