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
const byte address51[6] = "00051";
const byte address52[6] = "00052";

// Structure to hold sensor data
// struct SensorData {
//   float temperature;
//   float humidity;
//   float temp_f = temperature * 9.0 / 5.0 + 32.0; // Convert to Fahrenheit
// };

void setup() {
  Serial.begin(9600);  
  radio.begin();  
  
  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1) {} // Hold in infinite loop
  }  
  // Set the address
  radio.openReadingPipe(1, address51);
  // radio.openReadingPipe(1, address52);
  
  // Set module as transmitter
  radio.startListening(); 
  radio.setPALevel(RF24_PA_MIN);  
  Serial.println("RX initialized");

  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.print("Initializing..");
  delay(2000);
  lcd.clear();
}

int add_num =0;
float temperature = 0.0;
int humidity = 0;

void loop() {
  delay(1500);
  // Read temperature and humidity using the DHTTempReader class
  if (radio.available()){
    // const char text[] = "";
    // radio.read(&text, sizeof(text));

    // Serial.print(i);
    // Serial.print(" ");
    // Serial.print(text);
    // Serial.print(": ");

    // float temperature[32] = 0.0;
    radio.read(&add_num, sizeof(add_num));
    Serial.print(add_num);    // Print temperature with 1 decimal place
    Serial.print(" ");
    lcd.setCursor(0,0);    // Print temperature with 1 decimal place
    lcd.print(add_num);
    lcd.print(" ");

    radio.read(&temperature, sizeof(temperature));
    Serial.print(temperature, 1);
    Serial.print("°F, ");


    lcd.setCursor(4,0);
    lcd.print("T: ");
    lcd.print(temperature, 1);
    lcd.print(" F, ");

    // float humidity[32] = 0.0;
    radio.read(&humidity, sizeof(humidity));
    Serial.print("Hum: ");
    Serial.print(humidity);
    Serial.print("%, ");


      // Serial.println(" %");
    Serial.println("Data-OK");
  }else{
    Serial.println("No Data received");
  }
  //   i++;

  // if (i > 100)
  // {
  //   i=0;
  // }
}


//   /dev/ttyCH341USB0