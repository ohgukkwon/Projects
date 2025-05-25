#include <SPI.h>
#include <Wire.h>
#include "Rf_Data.h"
#include "Lcd_16x2.h"

// Create instances
NRF24L01Handler radioHandler;
LCD_16x2 lcd;

MyData rx_Data;  // Data structure for received data

unsigned long currentMillis = 0;
unsigned long previousDataMillis = 0;
const long dataInterval = 1000;  // 1 second for data reading

void setup() {
    Serial.begin(9600);  
    Serial.println("Starting...");

    // Initialize radio with more detailed error checking
    if (!radioHandler.begin()) {
        Serial.println("Radio hardware not responding!");
        while (1) {} // Hold in infinite loop
    }  

    // Configure radio settings
    radioHandler.setPALevel(RF24_PA_LOW);  // Try LOW instead of MIN for better range
    // Open reading pipe
    radioHandler.openReadingPipe(1, address52);
    radioHandler.startListening();
    
    // Print radio details for debugging
    Serial.println("Radio initialized with settings:");
    Serial.println("Address: 00052");
    Serial.println("Power Level: LOW");
    Serial.println("Data Rate: 250KBPS");
    Serial.println("Listening...");

    lcd.begin();
}

void loop() {
  currentMillis = millis();
  
  if (currentMillis - previousDataMillis >= dataInterval) {
      previousDataMillis = currentMillis;
      
    // Check if radio is available
    if (radioHandler.available()) {
      // Clear the data structure before reading
      memset(&rx_Data, 0, sizeof(MyData));
      // Read the data
      radioHandler.read(rx_Data);
      // Check if the data is valid
      if (rx_Data.rf_id > 0 && rx_Data.rf_status >= 0) {
        if (rx_Data.rf_status == 0) {
            Serial.println("RF Status: 0");
            lcd.displayNoData();
            return;
        }
        
        // Update LCD with new data
        lcd.update(rx_Data);
        
        // Print to Serial
        Serial.print("ID: ");
        Serial.print(rx_Data.rf_id);
        Serial.print(" Temp: ");
        Serial.print(rx_Data.t, 1);
        Serial.print("°F, Hum: ");
        Serial.print(rx_Data.h);
        Serial.print("%, Status: ");
        Serial.print(rx_Data.rf_status);
        Serial.print(" Time: ");
        Serial.print(rx_Data.timestamp);
        Serial.println(" RX-OK ");
      } else {
          Serial.println("Invalid data received");
          lcd.displayNoData();
      }
    } else {
        Serial.println("RF NOT available");
        lcd.displayNoData();
    }
  }
  
  // Process LCD updates
  lcd.process();
}