
Overzicht: Line-Following Robot Code

Dit programma is ontworpen voor een ESP32-microcontroller en bestuurt een lijnvolgende robot. Het maakt gebruik van Bluetooth-communicatie, bevat een PID-regelkring voor motorbesturing en biedt functies om sensoren te kalibreren, instellingen aan te passen en debuggegevens op te vragen.

Functionaliteiten
Bluetooth-communicatie

Apparaatnaam: Standaard ingesteld op "ESP32_Lijnvolger".

Interactie: Via Bluetooth kunnen commando’s gestuurd worden om parameters te wijzigen, sensoren te kalibreren en de robot te starten of stoppen.

Motorbesturing

Twee motoren worden gestuurd via PWM-signalen.

PWM-pinnen: motor1PWM1 (13), motor1PWM2 (14), motor2PWM1 (16), motor2PWM2 (17).

Richting en snelheid van de motoren worden aangepast door de PID-uitgang.

PID-regelkring

Sensoren bepalen de positie ten opzichte van de lijn.

De PID-regelaar gebruikt kp, ki en kd om correcties te berekenen.

iTerm en lastErr worden gebruikt om de integrale en afgeleide componenten te bewaren.

Sensorinput

7 sensoren aangesloten op de ESP32: {26, 25, 33, 32, 35, 34, 36}.

Ruwe waardes worden genormaliseerd naar een bereik van 0-1000.

De index van de donkerste sensor bepaalt de lijnpositie; berekening verfijnt dit met interpolatie.

Commando’s (via Bluetooth)

set cycle x: Stel de cyclustijd in microseconden in.

set power x: Stel de motorsnelheid in (0…255).

set diff x: Stel het verschil tussen linker en rechter motor in.

set kp/ki/kd x: Pas PID-waarden aan.

calibrate black: Kalibreer sensoren voor zwart.

calibrate white: Kalibreer sensoren voor wit.

debug: Toon PID-instellingen, rekentijd, ruwe en genormaliseerde sensorwaarden en lijnpositie.

run on / run off: Start of stop het programma.

cmd: Toon de lijst van beschikbare commando’s.

Belangrijke Structuren en Variabelen

params: Struct waarin PID-parameters, motorkracht en kalibratiewaarden worden opgeslagen.

EEPROM: Instellingen worden permanent opgeslagen en hersteld bij herstart.

normalised[7]: Array met de genormaliseerde sensorwaarden.

debugPosition: Huidige berekende lijnpositie.

Hoofdprogramma (loop)

Bluetooth-commandoverwerking

Verwerkt commando’s via SerialCommand en Bluetooth.

Sensorwaarden uitlezen en normaliseren

Sensoren worden continu gelezen en omgerekend naar waarden tussen 0 en 1000.

Lijnpositie berekenen

Bepaalt de relatieve positie van de lijn t.o.v. de robot.

PID-regeling

Berekent een foutwaarde en genereert een correctiesignaal voor de motoren.

Motorsturing

Past PWM-signalen toe om snelheid en richting van de motoren aan te passen.

Debug-functionaliteit

Beschikbaar via Bluetooth:

Cyclustijd, vermogen en PID-instellingen.

Ruwe sensorwaarden (analogRead).

Genormaliseerde waarden (0-1000).

Berekende lijnpositie.

PID-berekeningstijd in microseconden.

Gebruik

De robot kan volledig via Bluetooth geconfigureerd en bestuurd worden.
Voorbeelden van commando’s:

set cycle 3000 → wijzig cyclustijd.

calibrate black / calibrate white → kalibreer sensoren.

debug → toon instellingen en sensordata.

run on → start het lijnvolgprogramma.

run off → stop het lijnvolgprogramma.
