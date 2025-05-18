#include <SPI.h>
//#include <nRF24L01.h>
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
const byte address[6] = "00052";

// Structure to hold sensor data
struct SensorData {
  float temperature;
  float humidity;
  int id_count;
  char sensorID[10] = "SENSOR2";

};

void setup() {
  Serial.begin(9600);
  dhtReader.begin();
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

int i =520;

void loop() {
  delay(1000);
  // Read temperature and humidity using the DHTTempReader class
  if (dhtReader.readData()) {
    const float temperature = dhtReader.getTemperature();
    const int humidity = dhtReader.getHumidity();   
    const float temp_f = temperature * 9.0 / 5.0 + 32.0; // Convert to Fahrenheit 
    const int cout = i;
      
    if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
    }

    // radio.write(&data, sizeof(data));
    radio.write(&cout, sizeof(cout));    
    radio.write(&temp_f, sizeof(temp_f));
    radio.write(&humidity, sizeof(humidity));

    Serial.print(i);
    Serial.print(" ");

    Serial.print(temp_f, 1);
    Serial.print("°F, ");
    Serial.print("H: ");
    Serial.print(humidity);
    Serial.print("%, ");

    Serial.println("Data sent !!");  
    
  }else {
    Serial.println("Failed to read from DHT sensor!");
  }
  i++;

  if (i > 529)
  {
    i=520;
  }

}



//   /dev/ttyCH341USB0