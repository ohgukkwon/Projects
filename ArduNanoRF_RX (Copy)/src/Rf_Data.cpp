#include "Rf_Data.h"

// Define the address through which two modules communicate
// unsigned long rf_pre_Millis = 0;
// const unsigned long rf_interval = 1000; // Interval in milliseconds

MyData rf_Data;

NRF24L01Handler::NRF24L01Handler() : radio(CE_PIN, CSN_PIN), isInitialized(false) {
}

bool NRF24L01Handler::begin() {
    isInitialized = radio.begin();
    if (isInitialized) {
        radio.setPALevel(RF24_PA_HIGH);  // Set power level to HIGH
        radio.setDataRate(RF24_1MBPS);   // Set data rate to 1MBPS
        radio.openReadingPipe(1, address51);
        radio.startListening();
        Serial.println("Radio initialized successfully");
    } else {
        Serial.println("Radio initialization failed");
        while (1) {} // Hold in infinite loop
    }
    return isInitialized;
}

void NRF24L01Handler::radio_process() {
    unsigned long currentMillis = millis();

    if (currentMillis - rf_pre_Millis >= rf_Interval) {
        rf_pre_Millis = currentMillis;
        
        if (available()) {
            MyData tempData;
            if (read(tempData)) {
                rf_Data = tempData;
                rf_serial();
            }
        } else {
            Serial.println("No data available");
        }
    }
}

bool NRF24L01Handler::available() {
    return radio.available();
}

bool NRF24L01Handler::read(MyData& data) {
    if (!available()) {
        return false;
    }
    
    memset(&data, 0, sizeof(MyData));
    radio.read(&data, sizeof(MyData));
    
    if (data.rf_id > 0 && data.rf_status >= 0) {
        return true;
    }    
    return false;
}

void NRF24L01Handler::startListening() {
    radio.startListening();
}

void NRF24L01Handler::stopListening() {
    radio.stopListening();
}

void NRF24L01Handler::setPALevel(uint8_t level) {
    radio.setPALevel(level);
}

void NRF24L01Handler::openReadingPipe(uint8_t pipe, const byte* address) {
    radio.openReadingPipe(pipe, address);
} 

void NRF24L01Handler::printDetails() {
    if (isInitialized) {
        radio.printDetails();
    }
}

void NRF24L01Handler::rf_serial() {
    Serial.print("ID: ");
    Serial.print(rf_Data.rf_id);
    Serial.print(" Temp: ");
    Serial.print(rf_Data.t, 1);
    Serial.print("°F, Hum: ");
    Serial.print(rf_Data.h);
    Serial.print("%, Status: ");
    Serial.print(rf_Data.rf_status);
    Serial.print(" Time: ");
    Serial.print(rf_Data.timestamp);
    Serial.println(" RX-OK ");
}