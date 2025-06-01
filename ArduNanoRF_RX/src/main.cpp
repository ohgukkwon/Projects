#include <SPI.h>
#include <Wire.h>
#include "Rf_Data.h"
#include "Lcd_16x2.h"

// Create instances
NRF24L01Handler radioHandler;
LCD_16x2 lcd(&radioHandler);

MyData rx_Data;  // Data structure for received data


unsigned long previousDataMillis = 0;
const long dataInterval = 1000;  // 1 second for data reading

void setup() {
    Serial.begin(9600);  
    Serial.println("Starting...");

    if (!radioHandler.begin()) {
        Serial.println("Radio hardware not responding!");
        while (1) {} // Hold in infinite loop
    }  
    Serial.println("Radio initialized with settings:");
    Serial.println("Address: 00052");
    Serial.println("Power Level: LOW");
    Serial.println("Data Rate: 250KBPS");
    Serial.println("Listening...");

    lcd.begin();
}

void loop() {
    // Process radio data
    radioHandler.radio_process();
    
    // Process LCD updates
    lcd.process();

}