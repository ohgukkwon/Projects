#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "dht11_temp_read.h"

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

struct SensorData {
  float temperature;
  float humidity;
  int id_count;
  char sensorID[10];
};
SensorData data;

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
  delay(2000);
  lcd.clear();
}

float temp_f = 0.0;
int humidity = 0;
int cout = 0;

void loop() {
  delay(1000);
  lcd.clear();

  if (radio.available()){
    // float temperature[32] = 0.0;
    radio.read(&cout, sizeof(cout));
    Serial.print(cout);    // Print temperature with 1 decimal place
    Serial.print(" T:");
    lcd.setCursor(0,0);
    lcd.print(cout);

    radio.read(&temp_f, sizeof(temp_f));
    Serial.print(temp_f, 1);    // Print temperature with 1 decimal place
    Serial.print("°F, ");
    lcd.setCursor(4,0);
    lcd.print(temp_f,1);
    lcd.print(F("F, "));

    // float humidity[32] = 0.0;
    radio.read(&humidity, sizeof(humidity));
    Serial.print("Hum: ");
    Serial.print(humidity);
    Serial.print("%, ");

    lcd.setCursor(11,0);
    lcd.print("H:");
    lcd.print(humidity);
    lcd.print(F("%"));


    Serial.println("RX_OK");

    


  }

  else{
    Serial.println("No Data");
  }

}




  //   i++;

  // if (i > 100)
  // {
  //   i=0;
  // }
