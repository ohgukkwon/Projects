#ifndef RF_DATA_H
#define RF_DATA_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte address52[6] = "00052";

// Create instances

struct __attribute__((__packed__)) MyData {
    int rf_id;
    int rf_status;
    int h;
    float t;
    uint32_t timestamp;
};

class NRF24L01Handler {
public:
    NRF24L01Handler();
    bool begin();
    bool available();
    bool read(MyData& data);
    void startListening();
    void stopListening();
    void setPALevel(uint8_t level);
    void openReadingPipe(uint8_t pipe, const byte* address);

private:
    RF24 radio;
};

#endif // NRF24L01_HANDLER_H 