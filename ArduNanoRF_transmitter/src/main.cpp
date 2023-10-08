#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library 
#include "Arduino.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//sda #a4, scl #a5

const byte address[6] = "00001";

void setup() {
  //Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  lcd.clear();
  lcd.init();                            // Initialize I2C LCD module
  lcd.backlight();  
}

void loop() {
  const char text[] = "Tx Ardu#1";
  radio.write(&text, sizeof(text));
  //Serial.println(text);  
  delay(100);
  lcd.setCursor(0,0);
  lcd.print(text);
  lcd.setCursor(0,1);
  lcd.print("                         ");
}