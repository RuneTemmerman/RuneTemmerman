# Overzicht: Line-Following Robot Code  

Dit programma is ontworpen voor een ESP32-microcontroller en bestuurt een lijnvolgende robot. Het maakt gebruik van Bluetooth-communicatie, bevat een PID-regelkring voor motorbesturing en biedt functies om sensoren te kalibreren, instellingen aan te passen en debuggegevens op te vragen.  

## Functionaliteiten  

### Bluetooth-communicatie  
- **Apparaatnaam:** Standaard ingesteld op "ESP32_Lijnvolger".  
- **Interactie:** Via Bluetooth kunnen commando’s gestuurd worden om parameters te wijzigen, sensoren te kalibreren en de robot te starten of stoppen.  

### Motorbesturing  
- Aansturing van twee motoren via PWM.  
- PWM-signalen worden toegepast op vier pinnen: `motor1PWM1`, `motor1PWM2`, `motor2PWM1`, en `motor2PWM2`.  
- De snelheid en richting worden geregeld door een PID-regelaar.  

### PID-regelkring  
- De positie ten opzichte van de lijn wordt bepaald met 7 sensoren.  
- Een PID-regelaar (Proportioneel, Integrerend, Differentiërend) berekent een correctie-output.    

### Sensorinput  
- 7 sensoren op de pinnen: `{26, 25, 33, 32, 35, 34, 36}`.  
- Sensorwaarden worden genormaliseerd naar een bereik van 0–1000.  
- De donkerste sensor bepaalt de lijnpositie, met interpolatie voor nauwkeurigheid.  

### Commando's  
- **Parameteraanpassing:** Gebruikers kunnen motorkracht, PID-waarden (`kp`, `ki`, `kd`) en de cyclustijd aanpassen.  
- **Kalibratie:** Kalibreer sensoren voor zwart (`calibrate black`) en wit (`calibrate white`).  
- **Debugging:** Vraag instellingen, sensorwaarden en lijnpositie op via Bluetooth.  
- **Run:** Start (`run on`) of stop (`run off`) de robot.  
- **Cmd:** Toont de lijst met alle mogelijke commando’s.  

---

## Belangrijke Structuren en Variabelen  
- **`params`:** Bevat PID-parameters, motorkracht en kalibratiewaarden.  
- **EEPROM:** Slaat instellingen op zodat deze behouden blijven na een herstart.  
- **`normalised[7]`:** Array met genormaliseerde sensorwaarden.  
- **`debugPosition`:** Berekende lijnpositie.  

---

## Hoofdprogramma (loop)  
- **Bluetooth-commandoverwerking:** verwerkt binnenkomende commando’s.  
- **Sensorwaarden normaliseren:** analoge waarden → bereik 0–1000.  
- **Positiebepaling:** berekent lijnpositie t.o.v. de robot.  
- **PID-regeling:** berekent correctie-output op basis van foutwaarde.  
- **Motorsturing:** PWM-signalen sturen motoren voor snelheid en richting.  

---

## Debug-functionaliteit  
- Beschikbaar via Bluetooth:  
  - PID-instellingen  
  - Sensorwaarden (raw en genormaliseerd)  
  - Lijnpositie  
  - PID-berekeningstijd in microseconden  

---

## Gebruik  
Enkele voorbeelden van commando’s:  
- **`set cycle 3000`**: wijzig cyclustijd.  
- **`set kp 0.5`**: stel nieuwe kp in.  
- **`calibrate black`** en **`calibrate white`**: kalibreer sensoren.  
- **`debug`**: toon instellingen en sensordata.  
- **`run on`**: start lijnvolgen.  
- **`run off`**: stop lijnvolgen.  
