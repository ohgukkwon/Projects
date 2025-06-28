#include <SPI.h>
//#include <nRF24L01.h>
#include <RF24.h>
// #include "dht11_temp_read.h"
#include <DHT.h>

// Define pins for NRF24L01
#define CE_PIN 9
#define CSN_PIN 10

// Define pin for DHT11
#define DHTPIN 14
#define DHTTYPE DHT11

// Create instances
RF24 radio(CE_PIN, CSN_PIN);
DHT dht(DHTPIN, DHTTYPE);

// Define the address through which two modules communicate
const byte address[6] = "00051";

// Structure to hold sensor data
struct __attribute__((__packed__)) MyData {
  int id;
  int rf_status;
  int h;
  float t;
  uint32_t timestamp;

};
MyData data;

void setup() {
  Serial.begin(9600);
  dht.begin();
  radio.begin();
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1) {} // Hold in infinite loop
  }  
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);  
  radio.stopListening();  
  Serial.println("Transmitter initialized");
}

int id =atoi((char*)address);
int rf_status = 1;
int i = 0;

void loop() {
  delay(1000);  

  // Read temperature and humidity using the DHTTempReader class
  if (dht.read()) {
    // Serial.println("data read from DHT11");
    data.t = dht.readTemperature(true); // true for Fahrenheit
    data.h = dht.readHumidity(); 

    data.id = id;
    data.rf_status = rf_status;
    data.timestamp = millis();

    if (isnan(data.h) || isnan(data.t)) {
      Serial.println("Failed to read from DHT sensor!");
      delay(2000);
      return;
      }

    // radio.write(&data, sizeof(data));
    radio.write(&data, sizeof(data));    

    Serial.print(data.id);
    Serial.print(" ");

    Serial.print(i);
    Serial.print(" ");

    Serial.print(data.t, 1);
    Serial.print("°F, ");
    Serial.print("H: ");
    Serial.print(data.h, 1);
    Serial.print("%, ");
    Serial.print(data.rf_status);
    Serial.print(" ");
    Serial.print(data.timestamp);
    Serial.print(" ");

    Serial.println("Data sent !!");  
    
    }else {
      Serial.println("No Data from DHT");
    }
    
  i++;
  if (i >= 10){
    i = 0;
  }
}



//   /dev/ttyCH341USB0