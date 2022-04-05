/************************************************************************** 
 This is an example for our Monochrome OLEDs based on SSD1306 drivers 
 
 Pick one up today in the adafruit shop! 
 ------> http://www.adafruit.com/category/63_98 
 
 This example is for a 128x64 pixel display using I2C to communicate  3 pins are required to interface (two I2C and one reset). 
 
 Adafruit invests time and resources providing this open  source code, please support Adafruit and open-source  hardware by purchasing products from Adafruit! 
 
 Written by Limor Fried/Ladyada for Adafruit Industries,  with contributions from the open source community.  BSD license, check license.txt for more information  All text above, and the splash screen below must be  included in any redistribution. 
 **************************************************************************/  /* 
  Koden er modifisert av oss i forbindelse med eksamen i emnet 
  IOT3000, H2021, ved USN Vestfold 
 
  Programkommentar: Programmet leser av data fra sensor   og skriver ut resultatet på OLED-display i form av meter,cm og mm. 
 */ 
 
#include <SPI.h> 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels 
#define SCREEN_HEIGHT 64 // OLED display height, in pixels 
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins) 
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin) 
 
// String ds;               // Ikke benyttet int trigPin = 8; int echoPin = 7; 
long distance;              // "duration" tatt vekk fra original kode 
String meter;               // Meter 
String cm;                  // Centimeter 
String mm;                  // Millimeter 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); void setup() {   Serial.begin(9600);   pinMode(trigPin, OUTPUT);   pinMode(echoPin, INPUT); 
 
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64     Serial.println(F("SSD1306 allocation failed"));     for(;;); // Don't proceed, loop forever 
  } 
  // Show initial display buffer contents on the screen -- 
  // the library initializes this with an Adafruit splash screen. 
   
  // Instillinger for skjerm og start-skjerm   display.clearDisplay();   display.setTextSize(1);   display.display();   display.setCursor(0,0);   display.setTextColor(SSD1306_WHITE);   display.println("Distanse måler");   display.display();   delay(5000); // Pause for 2 seconds   display.clearDisplay(); 
}  
void loop () { // Regning cm = String(distance) + " cm";          // centimenter mm = String(distance / 0.1) + " mm";    // millimeter meter = String(distance / 100) + " m";  // meter  
// print til serial monitor 
Serial.print("Meter: "); Serial.println(meter); 
Serial.print("CM: "); Serial.println(cm); 
Serial.print("MM: "); 
Serial.println(mm); 
 
// print til OLED-display display.clearDisplay(); display.println(meter); display.println(cm); display.println(mm); display.display(); delay(500); 
} 
