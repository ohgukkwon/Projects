#include <SPI.h>
#include <Wire.h>
#include "Rf_Data.h"
#include "Lcd_16x2.h" // Make sure this file exists in the 'src' or 'include' directory, or correct the filename if needed
#include "SigIO.h"

// Create instances
NRF24L01Handler radioHandler;
SigIO sigIO;
LCD_16x2 lcd(&radioHandler, &sigIO);

MyData rx_Data;  // Data structure for received data


void setup() {
    Serial.begin(115200);  
    Serial.println("Starting...");

    if (!radioHandler.begin()) {
        Serial.println("Radio hardware not responding!");
        while (1) {} // Hold in infinite loop
    }  
    Serial.println("Radio initialized with settings:");
    Serial.println("Listening...");

    // initialize the pushbutton pin as an input

    lcd.begin();
}

void loop() {
    // Process radio data
    radioHandler.radio_process();
    
    // Process LCD updates
    lcd.process();
    sigIO.io_process();  // Process digital and analog I/O

}