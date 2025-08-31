# draadloze communicatie proof of concept
minimale hard- en software waarmee aangetoond wordt dat duplex kan gecommuniceerd worden tussen de microcontroller en een [laptop|smartphone] (schappen wat niet past), gebruik makend van [programma] (in te vullen)
<br />
### configuratie
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
} schrijf bij deze code een korte uitleg hoe je deze aansluit en gebruikt 
### opmerkingen

### gebruiksaanwijzing
-Uitleg voor het aansluiten en gebruiken van de ESP32 met Bluetooth:
Benodigdheden: ESP32-module.
Micro-USB-kabel om de ESP32 aan te sluiten op je computer.
PC met Arduino IDE geïnstalleerd.

-Verbind de ESP32 met je computer via de micro-USB-kabel.
Zorg ervoor dat de juiste COM-poort is geselecteerd in de Arduino IDE:
Ga naar Hulpmiddelen (Tools) → Poort (Port) → Selecteer de poort waarop je ESP32 is aangesloten.
Kies in Hulpmiddelen ook het juiste board (bijvoorbeeld: ESP32 Dev Module).

-Kopieer de bovenstaande code in de Arduino IDE.
Controleer of de bibliotheek BluetoothSerial.h is geïnstalleerd:
Ga naar Schets (Sketch) → Bibliotheek gebruiken (Include Library) → Bibliotheken beheren (Manage Libraries).
Zoek naar BluetoothSerial en installeer deze indien nodig.
Upload de code naar de ESP32:
Klik op de Upload-knop in de Arduino IDE.
Wacht tot de upload is voltooid.

-Verbinding maken via Bluetooth:
Activeer Bluetooth op je PC of telefoon.
Zoek naar beschikbare apparaten en selecteer ESP32_BT.
Maak verbinding. Als er om een code wordt gevraagd, gebruik 1234 of 0000.

-Gebruik een Bluetooth-terminalapp (bijvoorbeeld Serial Bluetooth Terminal op Android of PuTTY op Windows).
Verbind de app of software met de ESP32 via Bluetooth.
Stuur een bericht naar de ESP32. Dit bericht wordt door de ESP32 ontvangen en teruggestuurd.

-Open de seriële monitor in de Arduino IDE (115200 baudrate).
Controleer wat de ESP32 via Bluetooth ontvangt en terugstuurt.
