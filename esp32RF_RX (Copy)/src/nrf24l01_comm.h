#ifndef NRF24L01_COMM_H
#define NRF24L01_COMM_H

#include <SPI.h>
#include <RF24.h>
#include "sensor_data.h"

class NRF24L01Comm {
private:
    RF24& radio;
    const byte* address;
    bool isTransmitter;
    static const uint8_t CHANNEL = 76;        // Channel (0-125)
    static const uint8_t PA_LEVEL = RF24_PA_MIN;  // RF24_PA_MAX for maximum range
    // static const uint8_t DATA_RATE = RF24_250KBPS; // Data rate

public:
    NRF24L01Comm(RF24& radioInstance, const byte* addr, bool transmitter = false)
        : radio(radioInstance), address(addr), isTransmitter(transmitter) {}

    bool begin() {
        if (!radio.begin()) {
            return false;
        }
        
        // Configure radio settings
        radio.setPALevel(PA_LEVEL);
        radio.setChannel(CHANNEL);
        // radio.setDataRate(DATA_RATE);
        radio.setRetries(3, 5);  // 3 retries, 5ms delay between retries
        
        if (isTransmitter) {
            radio.openWritingPipe(address);
            radio.stopListening();
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

    // Get radio status information
    bool isConnected() {
        return radio.isChipConnected();
    }

    // Get signal strength (if available)
    uint8_t getSignalStrength() {
        return radio.getPALevel();
    }

    // Reset radio to default settings
    void reset() {
        radio.powerDown();
        delay(10);
        radio.powerUp();
        begin();
    }
};

#endif // NRF24L01_COMM_H 