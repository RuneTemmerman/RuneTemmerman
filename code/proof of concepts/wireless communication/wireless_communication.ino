#include <BluetoothSerial.h>  // Inclusie van de Bluetooth-bibliotheek

BluetoothSerial BTSerial;     // Maak een BluetoothSerial-object aan

void setup() {
  Serial.begin(115200);       // Debug-output naar USB-seriële monitor
  BTSerial.begin("ESP32_BT"); // Stel de naam van de Bluetooth-verbinding in

  Serial.println("Bluetooth is klaar. Verbind met 'ESP32_BT' via PuTTY.");
}

void loop() {
  // Controleer of er gegevens beschikbaar zijn via Bluetooth
  if (BTSerial.available()) {
    String incoming = BTSerial.readString(); // Lees de ontvangen gegevens
    Serial.print("Ontvangen via Bluetooth: ");
    Serial.println(incoming);               // Debug-output via USB

    // Stuur een bevestigingsbericht terug via Bluetooth
    String response = "ESP32 ontving: " + incoming;
    BTSerial.println(response);
  }

  // Debug-monitor, type vanaf USB-seriële poort
  if (Serial.available()) {
    String command = Serial.readString(); // Lees invoer van de USB-seriële monitor
    BTSerial.println("Van USB: " + command); // Stuur het naar Bluetooth
  }
}