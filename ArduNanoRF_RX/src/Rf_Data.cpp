#include "Rf_Data.h"

// Define the address through which two modules communicate
unsigned long rf_pre_Millis = 0;

const unsigned long rf_interval = 1000; // Interval in milliseconds


NRF24L01Handler::NRF24L01Handler() : radio(CE_PIN, CSN_PIN), isInitialized(false) {
}

bool NRF24L01Handler::begin() {
    isInitialized = radio.begin();
    if (isInitialized) {
        // // Set radio configuration
        radio.setPALevel(RF24_PA_LOW);        
        Serial.println("Radio initialized successfully");
    } else {
        Serial.println("Radio initialization failed");
    }
    return isInitialized;
}

bool NRF24L01Handler::available() {
    return radio.available();
    // radio.available();
}

bool NRF24L01Handler::read(MyData& data) {
    if (!isInitialized || !radio.available()) {
        return false;
    }
    
    // Clear the data structure before reading
    memset(&data, 0, sizeof(MyData));
    
    // Read the data
    radio.read(&data, sizeof(MyData));
    
    // Check if the data is valid
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