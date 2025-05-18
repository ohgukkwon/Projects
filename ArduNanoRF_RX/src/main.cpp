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

struct MyData {
  int h;
  float t;
  int rf_id;
  int rf_status;
  uint32_t timestamp;
};
MyData receivedData;

int count = 0;

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

// float temp_f = 0.0;
// int humidity = 0;
// int cout = 0;

uint32_t lastReceivedTime = 0;
const uint32_t TIMEOUT_MS = 3000; // 3 seconds timeout
uint16_t lastSequence = 0;
bool connectionLost = false;

void data_read() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    if (receivedData.rf_status = 0 ) {
      Serial.print("No RF Data :");
      Serial.print(receivedData.rf_status);
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("No RF Data");
    }
    return;
  }  
}
 

void loop() {
  delay(1500);

  data_read();

  if (receivedData.rf_status = 0 ) {
  Serial.print("No RF Data :");
  Serial.print(receivedData.rf_status);
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("No RF Data");

  return;
  }
  

  Serial.print(receivedData.rf_id);    // Print temperature with 1 decimal place
  Serial.print(" ");
  lcd.setCursor(0,0);
  lcd.print(receivedData.rf_id);

  Serial.print(receivedData.t, 1);    // Print temperature with 1 decimal place
  Serial.print("°F, ");
  lcd.setCursor(4,0);
  lcd.print(receivedData.t,1);
  lcd.print(F("F, "));

  // float humidity[32] = 0.0;
  radio.read(&receivedData.h, sizeof(receivedData.h));
  Serial.print("H: ");
  Serial.print(receivedData.h);
  Serial.println("%, ");

  lcd.setCursor(11,0);
  lcd.print("H:");
  lcd.print(receivedData.h);
  lcd.print(F("%"));

  lcd.setCursor(0,1);
  lcd.print("Rx Radio Data");

  receivedData.rf_status = 0;


}