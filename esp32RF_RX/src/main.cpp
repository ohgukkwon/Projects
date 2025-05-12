#include <SPI.h>
//#include <nRF24L01.h>
#include <RF24.h>


// Define pins for NRF24L01
#define CE_PIN 4
#define CSN_PIN 5

// Create instances
RF24 radio(CE_PIN, CSN_PIN);

// Define the address through which two modules communicate
const byte address[6] = "00001";


void setup() {
  Serial.begin(115200);
  radio.begin();
  
  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1) {} // Hold in infinite loop
  }
  
  // Set the address
  radio.openReadingPipe(0, address);
  //radio.setPALevel(RF24_PA_MIN);  //  
  // Set module as transmitter
  radio.stopListening(); 
  Serial.println("Transmitter initialized");
}

int i =0;

void loop() {

  delay(2000);
  // Read temperature and humidity using the DHTTempReader class
  // if (dhtReader.readData()) {
  //   const float temperature = dhtReader.getTemperature();
  //   const float humidity = dhtReader.getHumidity();    
  //   const float temp_f = temperature * 9.0 / 5.0 + 32.0; // Convert to Fahrenheit
  Serial.print(i);
  Serial.print("  ");
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Received: ");    
    Serial.println(text);


  

    // radio.write(&temperature, sizeof(temperature));
    // Serial.print(temperature);
    // Serial.print("°C, ");
    // Serial.print(temp_f);
    // Serial.print("°F, ");
    // radio.write(&humidity, sizeof(temperature));
    // Serial.print(humidity);
    // Serial.print("%, ");

      // Serial.println(" %");
    Serial.println("Data Received !!");  
    
  } else {
    Serial.println("Failed to read Data!");
  }
  
  // Serial.print(" ");
  // Serial.print(dhtReader.getTemperature());
  // Serial.print(" ");
  // Serial.print(dhtReader.getHumidity());
  // Serial.println(" %");
  i++;

  if (i > 1000)
  {
    i=0;
  }

}



//   /dev/ttyCH341USB0