#ifndef Rf_Data_H
#define Rf_Data_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte address52[6] = "00052";

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
        void radio_process();
        void startListening();
        void stopListening();
        void setPALevel(uint8_t level);
        void openReadingPipe(uint8_t pipe, const byte* address);
        void printDetails();
        void rf_serial();
        MyData get_rf_data() { return rf_Data; }

    private:
        RF24 radio;
        bool isInitialized;
        MyData rf_Data;
        unsigned long rf_pre_Millis = 0;
        const long rf_Interval = 1000; // 1 second interval
};

#endif 