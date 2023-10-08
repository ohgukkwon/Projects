#include <string.h>
#include <stdio.h>
#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library 
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//sda #a4, scl #a5

void setup() {

  // int bard_rate = 115200;
  Serial.begin(115200);
  Serial.setTimeout(1000);
  Serial.print("USB Serial is ready");   // opens serial port, sets data rate to 9600 bps

  lcd.init();                            // Initialize I2C LCD module
  lcd.backlight();  

}

void loop() {
  lcd.setCursor(0, 0);               // Go to column 0, row 0
  lcd.print("Serial NG      ");
  lcd.setCursor(0, 1);               // Go to column 0, row 0
  lcd.print("                ");
  delay(1000);
}

