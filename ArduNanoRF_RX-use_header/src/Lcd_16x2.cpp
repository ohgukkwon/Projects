#include "Lcd_16x2.h"

LCD_16x2::LCD_16x2(uint8_t address, uint8_t columns, uint8_t rows) {
    lcd = new LiquidCrystal_I2C(address, columns, rows);
}

LCD_16x2::~LCD_16x2() {
    delete lcd;
}

void LCD_16x2::begin() {
    lcd->init();
    lcd->clear();
    lcd->backlight();
    lcd->print("Initializing..");
    delay(1000);
    lcd->clear();
}

void LCD_16x2::update(MyData& newData) {
    currentData = newData;
    newDataAvailable = true;
}

void LCD_16x2::process() {
    unsigned long currentMillis = millis();

    // Check if it's time to update the display (every 2 seconds)
    if (currentMillis - previousDisplayMillis >= displayInterval) {
        previousDisplayMillis = currentMillis;
        
        if (newDataAvailable) {
            displayData();
            newDataAvailable = false;
        } else {
            displayNoData();
        }
    }
}

void LCD_16x2::clear() {
    lcd->clear();
}

void LCD_16x2::displayNoData() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("lcd no data");
}

void LCD_16x2::displayData() {
    lcd->clear();
    
    // First line: Temperature and Humidity
    lcd->setCursor(0, 0);
    lcd->print("T: ");
    lcd->print(currentData.t, 1);
    lcd->print("F, ");
    
    lcd->setCursor(10, 0);
    lcd->print("H:");
    lcd->print(currentData.h);
    lcd->print("%");

    // Second line: ID and Status
    lcd->setCursor(0, 1);
    lcd->print(currentData.rf_id);
    lcd->print(" ");
    lcd->setCursor(4, 1);
    lcd->print("Radio OK");
}