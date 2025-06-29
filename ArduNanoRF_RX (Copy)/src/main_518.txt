#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <LiquidCrystal_I2C.h>  //LiquidCrystal_I2C lcd(0x27,20,2);
#include <Wire.h>

// Define pins for NRF24L01
#define CE_PIN 9
#define CSN_PIN 10

// Create instances
RF24 radio(CE_PIN, CSN_PIN);

LiquidCrystal_I2C lcd(0x27,20,2);

// Define the address through which two modules communicate
// const byte address51[6] = "00051";
const byte address52[6] = "00052";

struct __attribute__((__packed__)) MyData {
  int rf_id;
  int rf_status;
  int h;
  float t;
  uint32_t timestamp;
};
MyData receivedData;

void setup() {
  Serial.begin(9600);  
  radio.begin();  
  
  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1) {} // Hold in infinite loop
  }  
  // Set the address
  // radio.openReadingPipe(1, address51);
  radio.openReadingPipe(1, address52);
  
  // Set module as transmitter
  radio.setPALevel(RF24_PA_MIN);  
  radio.startListening();
  Serial.println("RX initialized");

  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.print("Initializing..");
  delay(1000);
  lcd.clear();
}

void loop() {
  delay(1000);
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    if (receivedData.rf_status == 0) {
      Serial.println("RF Status: 0");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("RF Status: 0");
      delay(1000);
      return;
    }
    
    Serial.print(receivedData.rf_id);    // Print temperature with 1 decimal place
    Serial.print(" ");

    Serial.print(receivedData.t, 1);    // Print temperature with 1 decimal place
    Serial.print("°F, ");
    lcd.setCursor(0,0);
    lcd.print("T: ");
    lcd.setCursor(3,0);
    lcd.print(receivedData.t,1);
    lcd.print(F("F, "));

    Serial.print("H: ");
    Serial.print(receivedData.h);
    Serial.print("%, ");

    lcd.setCursor(10,0);
    lcd.print("H:");
    lcd.print(receivedData.h);
    lcd.print(F("%"));

    lcd.setCursor(0,1);
    lcd.print(receivedData.rf_id);
    lcd.print(" ");
    lcd.setCursor(4,1);
    lcd.print("Rx Radio OK");

    Serial.print(receivedData.rf_status);
    Serial.print(" ");
    
    Serial.print(receivedData.timestamp);
    Serial.print(" ");
    Serial.println("RX-OK ");

    receivedData = {0}; // Clear the received data structure
    // Serial.print(receivedData.timestamp);


  } else {
      // Serial.println("No data available");
      Serial.println("RF Status: 0");      
      lcd.setCursor(0,0);
      lcd.print("RF Status: 0");
      delay(1000);
      lcd.clear();
    return;
  }


}