#ifndef LCD_16X2_H
#define LCD_16X2_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Rf_Data.h"

class LCD_16x2 {
private:
    LiquidCrystal_I2C* lcd;
    unsigned long previousDataMillis = 0;    // For data reading timing
    unsigned long previousDisplayMillis = 0; // For display update timing
    const long dataInterval = 1000;          // 1 second for data reading
    const long displayInterval = 2000;       // 2 seconds for display update
    MyData currentData;
    bool newDataAvailable = false;

public:
    LCD_16x2(uint8_t address = 0x27, uint8_t columns = 20, uint8_t rows = 2);
    ~LCD_16x2();
    
    void begin();
    void update(MyData& newData);
    void process();
    void clear();
    void displayNoData();
    void displayData();
};

#endif