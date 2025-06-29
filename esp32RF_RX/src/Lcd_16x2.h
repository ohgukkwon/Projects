#ifndef LCD_16X2_H
#define LCD_16X2_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Rf_Data.h"

class LCD_16x2 {
    public:
        LCD_16x2(NRF24L01Handler* handler, uint8_t address = 0x27, uint8_t columns = 20, uint8_t rows = 2);
        ~LCD_16x2();
        
        void begin();
        void process();
        void clear();
        void displayNoData();
        void displayData();
    
    private:
        LiquidCrystal_I2C* lcd;
        unsigned long previousDisplayMillis = 0;
        const long displayInterval = 1000;  // 1 second for display update
        NRF24L01Handler* radioHandler;
        uint32_t lastTimestamp = 0;  // Track last received timestamp
        unsigned long lcd_clear_Millis = 0;
        const unsigned long lcd_clear_interval = 10000; // Interval in milliseconds
};

#endif 