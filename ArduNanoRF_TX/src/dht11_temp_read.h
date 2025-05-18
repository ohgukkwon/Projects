#ifndef DHT_TEMP_READ_H
#define DHT_TEMP_READ_H

#include <DHT.h>

class DHTTempReader {
private:
    DHT* dht;
    float temperature;
    float humidity;
    bool lastReadSuccess;

public:
    DHTTempReader(uint8_t pin, uint8_t type) {
        dht = new DHT(pin, type);
        temperature = 0.0;
        humidity = 0.0;
        lastReadSuccess = false;
    }

    void begin() {
        dht->begin();
    }

    bool readData() {
        temperature = dht->readTemperature(true);
        humidity = dht->readHumidity();
        
        // Check if any reads failed
        lastReadSuccess = !(isnan(temperature) || isnan(humidity));
        return lastReadSuccess;
    }

    float getTemperature() {
        return temperature;
    }

    float getHumidity() {
        return humidity;
    }

    bool isLastReadSuccessful() {
        return lastReadSuccess;
    }

    ~DHTTempReader() {
        delete dht;
    }
};

#endif