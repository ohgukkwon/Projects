/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

// #include <SPI.h>
// #include <nRF24L01.h>
#include <RF24.h>
#include "Arduino.h"
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library 

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
unsigned long myTime;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//sda #a4, scl #a5

void setup() {
  // Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

    lcd.init();                            // Initialize I2C LCD module
  lcd.backlight();  
}

int i = 0;
void loop() {
  
  if (radio.available()) {
    char text[50] = "";
    
    //myTime = millis();
    radio.read(&text, sizeof(text));
    //Serial.print("Hello world "); 
    // Serial.print("Read, ");   
    // Serial.println(text); 
    //delay(300);   
  
  lcd.setCursor(0,0);
  lcd.print(F("Read            ")); /*prints humidity value*/
  // lcd.print(h);
  // lcd.print(F("%"));
  lcd.setCursor(0,1);
  lcd.print(text); /*prints humidity value*/
  }

 
  }