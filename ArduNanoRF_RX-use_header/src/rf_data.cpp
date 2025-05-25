#include "rf_data.h"

// Define the address through which two modules communicate


NRF24L01Handler::NRF24L01Handler() : radio(CE_PIN, CSN_PIN) {
}

bool NRF24L01Handler::begin() {
    return radio.begin();
}

bool NRF24L01Handler::available() {
    return radio.available();
}

bool NRF24L01Handler::read(MyData& data) {
    if (!radio.available()) {
        return false;
    }
    
    // Simply call read() without trying to use its return value
    radio.read(&data, sizeof(MyData));
    return true;
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