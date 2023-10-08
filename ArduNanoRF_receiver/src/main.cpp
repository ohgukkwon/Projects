#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library 
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//sda #a4, scl #a5

RF24 radio(7, 8); // CE-7, CSN-8, SCK-13, MISO-12, MOSI-11
//NRF24L01 power is 3.3V --

const byte address[6] = "00001";

void setup() {
  // Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  lcd.clear();
  lcd.init();                            // Initialize I2C LCD module
  lcd.backlight();  
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    // Serial.print("Rx: ");
    // Serial.println(text);
    lcd.setCursor(0,0);
    lcd.print("Rx: ");
    lcd.print(text);
    lcd.setCursor(0,1);
    lcd.print("                         ");
    delay(300);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Fail                          ");
    lcd.setCursor(0,1);
    lcd.print("                         ");
    delay(300);
  }
}