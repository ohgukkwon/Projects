#include <SPI.h>
//#include <nRF24L01.h>
#include <RF24.h>

// Define pins for NRF24L01
#define CE_PIN 4
#define CSN_PIN 5

// Define pin for DHT11
#define DHTPIN 14
#define DHTTYPE DHT11

// Create instances
RF24 radio(CE_PIN, CSN_PIN);

// Define the address through which two modules communicate
const byte address[6] = "00001";

// Structure to hold sensor data
struct SensorData {
  float temperature;
  float humidity;
};

void setup() {
  Serial.begin(115200);
  radio.begin();  
  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1) {} // Hold in infinite loop
    }  
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);  //  
  radio.startListening(); 
  Serial.println("Transmitter initialized");
}
int i =0;
float temperature = 0.0;
int humidity = 0;

void loop() {
  delay(2000);
  // Read temperature and humidity using the DHTTempReader class
  if (radio.available()){
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print(text);
    Serial.print(": ");

    // float temperature[32] = 0.0;
    radio.read(&temperature, sizeof(temperature));
    Serial.print(temperature);
    Serial.print("°C, ");

    // float humidity[32] = 0.0;
    radio.read(&humidity, sizeof(humidity));
    Serial.print(humidity);
    Serial.print("%, ");


    // Serial.print(i);
    // Serial.print("  ");

    // radio.write(&temperature, sizeof(temperature));
    // Serial.print(temperature);
    // Serial.print("°C, ");
    // Serial.print(temp_f);
    // Serial.print("°F, ");
    // radio.write(&humidity, sizeof(temperature));
    // Serial.print(humidity);
    // Serial.print("%, ");

      // Serial.println(" %");
    Serial.println("Data received !!");
  }else{
    Serial.println("Data did not received !!");
  }
    i++;

  if (i > 1000)
  {
    i=0;
  }
}


  
  // Serial.print(" ");
  // Serial.print(dhtReader.getTemperature());
  // Serial.print(" ");
  // Serial.print(dhtReader.getHumidity());
  // Serial.println(" %");






//   /dev/ttyCH341USB0
