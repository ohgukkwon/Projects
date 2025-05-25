#include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

#include <LiquidCrystal_I2C.h>  //LiquidCrystal_I2C lcd(0x27,20,2);
#include <Wire.h>
#include <millis_Led.h>
#include "rf_data.h"

// Define pins for NRF24L01
// #define CE_PIN 9
// #define CSN_PIN 10

// // Create instances
// RF24 radio(CE_PIN, CSN_PIN);

LiquidCrystal_I2C lcd(0x27,20,2);

// // Define the address through which two modules communicate
// // const byte address51[6] = "00051";
// const byte address51[6] = "00051";
// const byte address52[6] = "00052";

// unsigned long currentMillis = 0;
// MyData rData;

// struct __attribute__((__packed__)) MyData {
//   int rf_id;
//   int rf_status;
//   int h;
//   float t;
//   uint32_t timestamp;
// };

MyData rx_Data;

NRF24L01Handler radioHandler;

void setup() {
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);

  Serial.begin(9600);  

  if (!radioHandler.begin()) {
  Serial.println("Radio hardware not responding!");
  while (1) {} // Hold in infinite loop
  }  
  // // Set the address
  radioHandler.openReadingPipe(1, address52);
  // radio.openReadingPipe(1, address52);
  radioHandler.setPALevel(RF24_PA_MIN);  
  radioHandler.startListening();
  Serial.println("RX initialized");

  
  // // Set module as transmitter
  // radio.setPALevel(RF24_PA_MIN);  
  // radio.startListening();
  // Serial.println("RX initialized");

  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.print("Initializing..");
  delay(1000);
  lcd.clear();
}

int i = 0;



void loop() {
  delay(1000);
  if (radioHandler.available()) {
    if (radioHandler.read(rx_Data)) {
      if (rx_Data.rf_status == 0) {
        Serial.println("RF Status: 0");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("RF Status: 0");
        delay(1000);
        return;
      }
      
      Serial.print(rx_Data.rf_id);
      Serial.print(" ");

      Serial.print(rx_Data.t, 1);
      Serial.print("°F, ");
      lcd.setCursor(0,0);
      lcd.print("T: ");
      lcd.setCursor(3,0);
      lcd.print(rx_Data.t,1);
      lcd.print(F("F, "));

      Serial.print("H: ");
      Serial.print(rx_Data.h);
      Serial.print("%, ");

      lcd.setCursor(10,0);
      lcd.print("H:");
      lcd.print(rx_Data.h);
      lcd.print(F("%"));

      lcd.setCursor(0,1);
      lcd.print(rx_Data.rf_id);
      lcd.print(" ");
      lcd.setCursor(4,1);
      lcd.print("Rx Radio OK");

      Serial.print(rx_Data.rf_status);
      Serial.print(" ");
      
      Serial.print(rx_Data.timestamp);
      Serial.print(" ");
      Serial.println("RX-OK ");

      rx_Data = {0}; // Clear the received data structure
    }
  } else {
    Serial.println("RF Status: 0");      
    lcd.setCursor(0,0);
    lcd.print("RF Status: 0");
    delay(1000);
    lcd.clear();
    return;
  }
}