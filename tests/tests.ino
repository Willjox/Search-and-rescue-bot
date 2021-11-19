const int button = 13;

void setup() {
  Serial.begin(9600);
  pinMode(button,INPUT);
  Serial.println("waiting for start button"); 
  while {digitalRead(startButton == LOW) {
    delay(100);
  }
  Serial.println("Starting");
}

void loop() {
  int state = digitalRead(button);
  if (state == HIGH) {
    Serial.println("button is pushed in");
  } else if (state == LOW) {
    Serial.println("Button is not pushed"); 
  } else {
    Serial.println("error"); 
  }
  delay(50);
}
