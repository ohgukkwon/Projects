#ifndef NRF24L01_COMM_H
#define NRF24L01_COMM_H

#include <SPI.h>
#include <RF24.h>

// Structure to hold sensor data
struct SensorData {
    float temperature;
    float humidity;
    float temp_f;
};

class NRF24L01Comm {
private:
    RF24& radio;
    const byte* address;
    bool isTransmitter;

public:
    // Constructor
    NRF24L01Comm(RF24& radioInstance, const byte* addr, bool transmitter = true) 
        : radio(radioInstance), address(addr), isTransmitter(transmitter) {}

    // Initialize the radio
    bool begin() {
        if (!radio.begin()) {
            return false;
        }
        
        radio.openWritingPipe(address);
        if (!isTransmitter) {
            radio.openReadingPipe(1, address);
            radio.startListening();
        } else {
            radio.stopListening();
        }
        
        return true;
    }

    // Send sensor data
    bool sendSensorData(const SensorData& data) {
        return radio.write(&data, sizeof(SensorData));
    }

    // Receive sensor data
    bool receiveSensorData(SensorData& data) {
        if (radio.available()) {
            radio.read(&data, sizeof(SensorData));
            return true;
        }
        return false;
    }

    // Check if data is available
    bool dataAvailable() {
        return radio.available();
    }
};

#endif // NRF24L01_COMM_H 