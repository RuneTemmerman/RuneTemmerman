
# Elektrisch Schema voor Lijnvolgende Robot

Dit project maakt gebruik van een **ESP32-microcontroller**, een **QTR-8A-sensorarray**, een **DRV8833N-motordriver**, en een paar **DC-motoren**. Hieronder vind je een overzicht van de belangrijkste onderdelen en hun functies.

---

## Belangrijke Componenten

### 1. **ESP32 Microcontroller**
- De ESP32 is de hoofdmicrocontroller die alle verwerking uitvoert.
- **Let op**: Zorg ervoor dat de voedingsspanning stabiel is om storingen te voorkomen.

### 2. **QTR-8A Reflectiesensor Array**
- Deze array wordt gebruikt voor lijndetectie.
- **Aandachtspunten**:
  - Controleer dat de **VCC** en **GND** correct zijn aangesloten.
  - Verbind de uitgangen van de sensorarray met de juiste **GPIO-pinnen** van de ESP32.

### 3. **Motordriver (DRV8833)**
- De DRV8833N is verantwoordelijk voor het besturen van de DC-motoren.
- **Aansluitingen**:
  - Verbind de signaalpinnen van de ESP32 met de correcte besturingspinnen van de DRV8833N.
  - Zorg ervoor dat de spanning en stroom van de motoren compatibel zijn met de driver.

### 4. **DC-Motoren**
- De motoren zorgen voor de aandrijving van de robot.
- **Tip**: Controleer of de motoren geschikt zijn voor de spanning en stroom die de L298N levert.


---

Met dit elektrisch schema kun je een functionele lijnvolgende robot bouwen. Zorg ervoor dat alle verbindingen goed zijn gecontroleerd voordat je de hardware inschakelt!
