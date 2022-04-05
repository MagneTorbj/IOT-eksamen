Programkode
Programkode for Måle- og sender-enhet
/* Kode hentet fra:
* Arduino Wireless Communication Tutorial
* Example 1 - Transmitter Code
* by Dejan Nedelkovski, www.HowToMechatronics.com
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*
* Koden er modifisert av oss i forbindelse med eksamen i emnet 
* IOT3000, H2021, ved USN Vestfold.
* 
* Programkommentar: Oppsettet består av en Arduino, RF24 og Moisture-sensor.
* Data som blir avlest sendes videre til annet RF24-komponent som er 
programmert 
* til å fungere som receiver. 
*
*/
/* Bibliotek-import */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/* Pins og kommunikasjonsadresse */
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
pinMode(A0, INPUT);
Serial.begin(9600);
radio.begin();
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_MAX);
radio.stopListening();
}
void loop() {
int value;
value = analogRead(A0);
Serial.println("Sending sensor value:"); // Driftsmelding
radio.write(&value, sizeof(value)); // Skriver/sender data
Serial.println(value); // Driftsmelding
delay(1000);
}
Programkode for mottaker 
/* Kode hentet fra:
* Arduino Wireless Communication Tutorial
* Example 1 - Receiver Code 
* by Dejan Nedelkovski, www.HowToMechatronics.com 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
* 
* Koden er modifisert av oss i forbindelse med eksamen i emnet 
* IOT3000, H2021, ved USN Vestfold.
* 
* Programkommentar: Mottaker som består av Arduino Uno og RF24.
* Programmet mottar, leser og håndterer dataene som kommer inn og
* skriver ut beskjeder til bruker basert på dataene. 
*/
// Bibliotek
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/* Pins og kommunikasjonsadresse */
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
/* Oppstart */
void setup() {
Serial.begin(9600); delay(1000); 
Serial.println("Moisture sensor"); // driftsmelding
delay(500);
Serial.println("Preparing to receive signal.."); // driftsmelding
radio.begin(); 
radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MAX);
radio.startListening(); 
delay(2000);
// sjekker om det er bytes som kan leses av
if (radio.available()) {
Serial.println("Receiverdevice is ready!"); // driftsmelding
// brukerveiledning
Serial.println("Moisture levels from dry to wet: 1024-1");
delay(4000);
} else {
Serial.println("No signal received :("); // driftsmelding
}
}
/* Programkommentar:
* Lesing av mottatt data og utskrift:
* Ulike meldinger blir frembragt basert på verdiene gitt fra sensor. 
* Her er det statements som dekker hele skalaen til moisture-sensoren, som 
vil 
* skape en utskrift til «serial monitor» ut ifra verdiene som blir gitt.
*/
void loop() {
// Test whether there are bytes available to be read.
if (radio.available()) {
int value = ""; 
radio.read(&value, sizeof(value));
       if (value == 1022 || value == 1023) {
        Serial.println("-----------------------------");
        Serial.println("Plant 1");
        Serial.print("Moisture value: ");
        Serial.println(value);
        Serial.println("Moisture level estimate: 99-100%)");
        Serial.println("Soil not found, inspect moisture sensor device");
        Serial.println(""); delay(10000); }
       else if (value <= 1021 && value >= 950) {
        Serial.println("-----------------------------");
        Serial.println("Plant 1");
        Serial.print("Moisture value: ");
        Serial.println(value);
        Serial.println("Moisture level estimate: 90-98%");
        Serial.println("Soil is dry, add some water");
        Serial.println(""); delay(10000); }
       else if (value <= 949 && value >= 800 ) {
        Serial.println("-----------------------------");
        Serial.println("Plant 1");
        Serial.print("Moisture value: ");
        Serial.println(value);
        Serial.println("Moisture level estimate (70-89%)");
        Serial.println("Soil is somewhat damp");
        Serial.println(""); delay(10000); }
       else if (value <= 799 && value >= 700 ) {
        Serial.println("-----------------------------");
        Serial.println("Plant 1");
        Serial.print("Moisture value: ");
        Serial.println(value);
        Serial.println("Moisture level estimate (69-50%)");
        Serial.println("Soil moisture is healthy");
        Serial.println(""); delay(10000); }
       else if (value <= 699 && value >= 550 ) { 
        Serial.println("-----------------------------"); 
        Serial.println("Plant 1"); 
        Serial.print("Moisture value: "); 
        Serial.println(value); 
        Serial.println("Moisture level estimate (49-35%)"); 
        Serial.println("Soil is pretty wet"); 
        Serial.println(""); delay(10000); 
        } 
       else if (value <= 549 && value >= 386 ) { 
        Serial.println("-----------------------------"); 
        Serial.println("Plant 1"); 
        Serial.print("Moisture value: "); 
        Serial.println(value); 
        Serial.println("Moisture level estimate (30-34%)"); 
        Serial.println("Soil is soaking wet"); 
        Serial.println(""); delay(10000); 
        } 
       else if (value <= 385 && value >= 350 ) { 
        Serial.println("-----------------------------"); 
        Serial.println("Plant 1"); 
        Serial.print("Moisture value: "); 
        Serial.println(value); 
        Serial.println("Moisture level estimate: most likely just pure water"); 
        Serial.println("Soil not found, only water. (Typical values) "); 
        Serial.println("Inspect moisture sensor device"); 
        Serial.println(""); delay(10000); 
        } 
       else if (value <= 349 && value >= 1 ) { 
        Serial.println("-----------------------------"); 
        Serial.println("Plant 1"); 
        Serial.print("Moisture value: "); 
        Serial.println(value); 
        Serial.println("Moisture level estimate: Too much water! "); 
        Serial.println("Water is wet."); 
        Serial.println(""); delay(10000); 
        }         else { 
            Serial.println("Something went wrong");             delay(10000); 
            } 
  } 
} 
