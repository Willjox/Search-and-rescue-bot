const int startButton = 13;
int duration;
int echoPin;
int trigPin;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
  echoPin = 11;
  trigPin = 12;
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  int length = duration / 29 / 2;
  Serial.println(length);
  delay(2000);
}
