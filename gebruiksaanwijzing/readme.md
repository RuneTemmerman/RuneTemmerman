# Gebruiksaanwijzing

### opladen / vervangen batterijen
Bijj een platte batterij dien je deze op teladen door deze uit de houder te halen.

### draadloze communicatie
#### verbinding maken
Draadloze verbindingen wordt gemaakt via de seriele bluetooth app met een android phone. gebruik geen IOS deze werkt niet voor een ESP 32.

#### commando's
debug.  
run on.  
run off.  
set cycle [µs]  
set power [0..255]  
set diff [0..1]  
set kp [0..]  
set ki [0..]  
set kd [0..]  
calibrate black  
calibrate white  

### kalibratie
Voor het kalibreren van de sensor moet je de auto op een zwarte ondergrond plaatsen en via de bluetooth app het comando calibrate black ingeven daarna plaats je de auto op een witte achtergrond en geef je het comando calibrate white in. na dat dit gebeurd is druk je op debug om te kijken of deze waardes wel stroken met de gewenste waardes

### settings
De robot rijdt stabiel met volgende parameters: DIFF: 0,5- KI: 0 - Kp: 10 KD: 0,3- power:70


