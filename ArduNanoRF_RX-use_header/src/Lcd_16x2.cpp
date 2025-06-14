#include "Lcd_16x2.h"

LCD_16x2::LCD_16x2(NRF24L01Handler* handler, uint8_t address, uint8_t columns, uint8_t rows) 
    : radioHandler(handler) {
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

void LCD_16x2::process() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousDisplayMillis >= displayInterval) {
        previousDisplayMillis = currentMillis;
        
        MyData data = radioHandler->get_rf_data();
        
        // Check if timestamp has changed
        if (data.timestamp != lastTimestamp) {
            lastTimestamp = data.timestamp;
            if (data.rf_id > 0 && data.rf_status >= 0) {
                displayData();
            } else {
                displayNoData();
            }
        } else {
            // Timestamp hasn't changed, display no data message
            lcd->clear();
            lcd->setCursor(0, 0);
            lcd->print("No data from RF");
            lcd->setCursor(0, 1);
            lcd->print("Last: ");
            lcd->print(lastTimestamp);
            delay(1000);
        }
    }
     
    if (currentMillis - lcd_clear_Millis >= lcd_clear_interval) {
        lcd->clear();
        lcd_clear_Millis = currentMillis;
    }
    // Read data at specified intervals
}

void LCD_16x2::clear() {
    lcd->clear();
}

void LCD_16x2::displayNoData() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("No data from RF");
}

void LCD_16x2::displayData() {
    MyData data = radioHandler->get_rf_data();
    
    // lcd->clear();
    
    // First line: Temperature and Humidity
    lcd->setCursor(0, 0);
    lcd->print("TEMP:");
    lcd->setCursor(5, 0);
    lcd->print(data.t, 1);  // Print temperature with 1 decimal place
    lcd->setCursor(9, 0);
    lcd->print("F,H:");

    lcd->print(data.h);
    lcd->setCursor(15, 0);
    lcd->print("%");

    // Second line: ID and Status
    lcd->setCursor(0, 1);
    lcd->print("Radio_#:");
    lcd->print(data.rf_id);
    if (data.rf_status == 1) {
        lcd->setCursor(14, 1);
        lcd->print("OK");
    }

    Serial.print("ID: ");
    Serial.print(data.rf_id);
    Serial.print(" Temp: ");
    Serial.print(data.t, 1);
    Serial.print("°F, Hum: ");
    Serial.print(data.h);
    Serial.print("%, Status: ");
    Serial.print(data.rf_status);
    Serial.print(" Time: ");
    Serial.print(data.timestamp);
    Serial.println(" LCD-OK ");
}