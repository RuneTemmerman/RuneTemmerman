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
