# Arduino-Tachometer-Project
A Project involving Circuitry and Programming an Arduino Microcontroller

In this project I connected a servo motor, buzzer speaker, LED and potentiometer to an Arduino. I also added two resistors to properly design the circuit.

The following picture shows how I organized my breadboard, as well as the specifications of the resistors.
![20250411_010235317_iOS](https://github.com/user-attachments/assets/14c99555-ea58-47ad-bcda-ea72008f1e07)

Here you can see the pins I connected to the Microcontroller's power, ground and sensor pins:
![20250411_011954149_iOS](https://github.com/user-attachments/assets/ba27c6a9-c1c5-47ca-9a98-b338d1a6efb8)

This, with some totally incredible crafting skills, allowed me to program a program (tach.ino). This program processes the potentiometer's input and calculates an "RPM" Value. This value is used to calculate the position of the servo, the pitch of audio to play out of the buzzer speaker, and whether or not the "RPM" value is above a set redline value (7000 RPM). If so, a red LED is turned on.

In this picture you can see the final project assembly:
![20250411_010200185_iOS](https://github.com/user-attachments/assets/3b221713-9d15-4e73-9e90-744ac3bd539e)

I guide you to this Google Drive link, where you can find a demonstration video!
https://drive.google.com/drive/folders/1meicwedXO-g11gR-mPuycaAZoO-kGMt7?usp=sharing

# A Little Program Overview
Below you will find a logical diagram of the program:
<img width="3007" height="1207" alt="Tach Logic Diagram (2)" src="https://github.com/user-attachments/assets/46d5b722-0758-4fc6-8068-2f1ac93e3689" />

