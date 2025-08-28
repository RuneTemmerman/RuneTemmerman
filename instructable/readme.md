# Instructable: Maak je eigen Line-Follower Robot

Met deze gids bouw je een eenvoudige line-following robot met een **ESP32** en andere componenten. Je start met het 3D-printen van de mechanische onderdelen en monteert vervolgens alles op het chassis. Tot slot laad je de software op de ESP32 om je robot tot leven te brengen.

---

## Benodigdheden
- **QTR-8A Reflectance Sensor Array** (Pololu)
- **ESP32**
- **DRV8833 Motor Driver**
- **DIP-schakelaar**
- **2 DC-motoren**
- **Batterijhouder**
- **3D-geprinte onderdelen** (wielhouders, chassis) – te vinden in de GitHub-repository
- **T-strip** of sterke lijm
- **Dubbelzijdige tape**
- **Elektronische bedrading**

---

## Stappenplan

### **Stap 1: Print de mechanische onderdelen**
- Download de STL-bestanden uit de map "Mechanische Onderdelen" in de GitHub-repository.  
- Print deze onderdelen met een 3D-printer.
- Zorg ervoor dat je de wielhouders en het chassis correct print en controleer de afmetingen.

---

### **Stap 2: Monteer de onderdelen**

#### 2.1 **Wielhouders plaatsen**
- Plaats de wielhouders aan de achterkant van het chassis.  
- Gebruik lijm of T-strip om ze stevig tegen het chassis te bevestigen.  
- Laat de lijm goed drogen voordat je verdergaat.

#### 2.2 **Motoren monteren**
- Schuif de motoren in de wielhouders.  
- Zorg ervoor dat de motorassen vrij kunnen draaien en goed zijn uitgelijnd.

#### 2.3 **Batterijhouder bevestigen**
- Bevestig de batterijhouder aan de bovenkant van het chassis met T-strip of sterke lijm.  
- Zorg ervoor dat de batterijhouder stevig vastzit.

---

### **Stap 3: Plaatsen van elektronica**

#### 3.1 **QTR-8A sensor bevestigen**
- Bevestig de QTR-8A Reflectance Sensor Array met dubbelzijdige tape aan de voorkant van het chassis.  
- Zorg ervoor dat de sensoren naar de grond gericht zijn en enkele millimeters boven het oppervlak zweven.

#### 3.2 **DIP-schakelaar en breadboard**
- Monteer de DIP-schakelaar op een breadboard.  
- Verbind de DIP-schakelaar met de ESP32 volgens het schema in de GitHub-repository.

---

### **Stap 4: Aansluiten van bedrading**

#### 4.1 **Motoren verbinden**
- Verbind de motoren met de juiste pinnen van de **DRV8833 dubbele H-brug**.  
- Volg het bedradingsschema in de GitHub-repository om fouten te vermijden.

#### 4.2 **DRV8833 aansluiten op ESP32**
- Verbind de **DRV8833 motorcontroller** met de ESP32 volgens het schema.  
- Sluit ook de voedingsdraden van de motorcontroller aan op de batterijhouder.

---

### **Stap 5: Controleer de assemblage**
- Bekijk de foto van het afgewerkte project in de GitHub-repository om te controleren of alles correct is gemonteerd.  
- Controleer dat alle draden goed zijn aangesloten en dat niets los zit.

---

### **Stap 6: Laat je robot tot leven komen!**
- Upload de software naar de ESP32 met behulp van de instructies in de GitHub-repository.  
- Controleer of de instellingen van de QTR-8A sensorarray zijn aangepast aan jouw lijnvolgeromgeving.  
- Zet de robot aan en test of deze de lijn correct volgt!

---

Met deze stappen kun je jouw eigen line-following robot bouwen. Veel succes en plezier met het project!

Gefeliciteerd! Je hebt nu een volledig functionele line-following robot. 🚗💨

Voor vragen of problemen kun je terugkijken naar de GitHub-repository. Veel succes!
