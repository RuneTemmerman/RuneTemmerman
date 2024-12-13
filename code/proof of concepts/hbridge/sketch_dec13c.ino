#define AIN1 9       // AIN1 voor Motor A
#define AIN2 10      // AIN2 voor Motor A
#define BIN1 6       // BIN1 voor Motor B
#define BIN2 5       // BIN2 voor Motor B
#define SLP 7        // SLP pin om de motor driver te activeren

void setup() {
  // Stel alle pinnen in als output
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(SLP, OUTPUT);

  // Activeer de motor driver
  digitalWrite(SLP, HIGH);

  Serial.begin(115200);
  Serial.println("Typ commands zoals 'A_FORWARD 150' of 'B_BACKWARD 200'.");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Lees de invoer van de seriële monitor
    input.trim(); // Verwijder overbodige spaties en nieuwe regels
    handleCommand(input);
  }
}

void handleCommand(String command) {
  int spaceIndex = command.indexOf(' '); // Zoek naar de spatie tussen het commando en de snelheid
  String motorCommand = command.substring(0, spaceIndex); // Command zoals "A_FORWARD"
  int speed = command.substring(spaceIndex + 1).toInt(); // Snelheid (0-255)

  // Beperk snelheid tussen 0 en 255
  speed = constrain(speed, 0, 255);

  if (motorCommand.equalsIgnoreCase("A_FORWARD")) {
    controlMotor(AIN1, AIN2, speed, true); // Motor A vooruit
    Serial.println("Motor A draait vooruit met snelheid: " + String(speed));
  } else if (motorCommand.equalsIgnoreCase("A_BACKWARD")) {
    controlMotor(AIN1, AIN2, speed, false); // Motor A achteruit
    Serial.println("Motor A draait achteruit met snelheid: " + String(speed));
  } else if (motorCommand.equalsIgnoreCase("B_FORWARD")) {
    controlMotor(BIN1, BIN2, speed, true); // Motor B vooruit
    Serial.println("Motor B draait vooruit met snelheid: " + String(speed));
  } else if (motorCommand.equalsIgnoreCase("B_BACKWARD")) {
    controlMotor(BIN1, BIN2, speed, false); // Motor B achteruit
    Serial.println("Motor B draait achteruit met snelheid: " + String(speed));
  } else if (motorCommand.equalsIgnoreCase("STOP")) {
    stopMotors();
    Serial.println("Beide motoren gestopt.");
  } else {
    Serial.println("Onbekend commando. Gebruik bijvoorbeeld: A_FORWARD 150.");
  }
}

void controlMotor(int in1, int in2, int speed, bool forward) {
  if (forward) {
    analogWrite(in1, speed); // Stel snelheid in op IN1
    digitalWrite(in2, LOW);  // Zet IN2 laag
  } else {
    analogWrite(in2, speed); // Stel snelheid in op IN2
    digitalWrite(in1, LOW);  // Zet IN1 laag
  }
}

void stopMotors() {
  // Stop Motor A
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  // Stop Motor B
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}