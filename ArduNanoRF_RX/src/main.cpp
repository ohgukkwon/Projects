#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "dht11_temp_read.h"

// Define pins for NRF24L01
#define CE_PIN 9
#define CSN_PIN 10

// Define pin for DHT11
#define DHTPIN 14
#define DHTTYPE DHT11

// Create instances
RF24 radio(CE_PIN, CSN_PIN);
DHTTempReader dhtReader(DHTPIN, DHTTYPE);

// Define the address through which two modules communicate
const byte address[6] = "00001";

// Structure to hold sensor data
struct SensorData {
  float temperature;
  float humidity;
};

void setup() {
  Serial.begin(9600);
  
  // Initialize DHT sensor
  dhtReader.begin();
  
  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1) {} // Hold in infinite loop
  }
  
  // Set the address
  radio.openWritingPipe(address);
  
  // Set module as transmitter
  radio.stopListening();
  
  Serial.println("Transmitter initialized");
}

void loop() {
  // Read temperature and humidity using the DHTTempReader class
  if (dhtReader.readData()) {
    // Create data structure
    SensorData data;
    data.temperature = dhtReader.getTemperature();
    data.humidity = dhtReader.getHumidity();
    
    // Send the data
    if (radio.write(&data, sizeof(data))) {
      Serial.println("Data sent successfully");
      Serial.print("Temperature: ");
      Serial.print(data.temperature);
      Serial.print(" °C, Humidity: ");
      Serial.print(data.humidity);
      Serial.println(" %");
    } else {
      Serial.println("Failed to send data");
    }
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
  
  // Wait for 2 seconds before next reading
  delay(2000);
}



///dev/ttyCH341USB0