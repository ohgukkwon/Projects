#ifndef NRF24L01_COMM_H
#define NRF24L01_COMM_H

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
    NRF24L01Comm(RF24& radioInstance, const byte* addr, bool transmitter = false)
        : radio(radioInstance), address(addr), isTransmitter(transmitter) {}

    bool begin() {
        if (!radio.begin()) {
            return false;
        }
        
        radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX for maximum range
        radio.setChannel(76);           // Set channel (0-125)
        radio.setDataRate(RF24_250KBPS); // Set data rate
        
        if (isTransmitter) {
            radio.openWritingPipe(address);
        } else {
            radio.openReadingPipe(1, address);
            radio.startListening();
        }
        
        return true;
    }

    bool sendSensorData(const SensorData& data) {
        if (!isTransmitter) return false;
        return radio.write(&data, sizeof(SensorData));
    }

    bool receiveSensorData(SensorData& data) {
        if (isTransmitter) return false;
        
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