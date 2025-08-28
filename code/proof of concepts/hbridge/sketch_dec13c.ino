const int motor1Pin1 = 13;  // IN1 voor Motor 1
const int motor1Pin2 = 14;  // IN2 voor Motor 1
const int motor2Pin1 = 16;  // IN3 voor Motor 2
const int motor2Pin2 = 17;  // IN4 voor Motor 2

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  // Beide motoren voorwaarts
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(2000);  // Draai motoren vooruit voor 2 seconden
  
  // Beide motoren achterwaarts
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);  // Draai motoren achteruit voor 2 seconden
}
