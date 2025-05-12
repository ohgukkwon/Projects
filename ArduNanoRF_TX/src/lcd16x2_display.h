#ifndef LCD16X2_DISPLAY_H
#define LCD16X2_DISPLAY_H

#include <LiquidCrystal.h>
#include "nrf24l01_comm.h"

class LCD16x2Display {
private:
    LiquidCrystal& lcd;
    static const int DISPLAY_WIDTH = 16;
    static const int DISPLAY_HEIGHT = 2;

public:
    LCD16x2Display(LiquidCrystal& lcdInstance) : lcd(lcdInstance) {}

    void begin() {
        lcd.begin(DISPLAY_WIDTH, DISPLAY_HEIGHT);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Initializing...");
    }

    void displaySensorData(const SensorData& data) {
        lcd.clear();
        
        // First line: Temperature
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(data.temperature, 1);
        lcd.print("C ");
        lcd.print(data.temp_f, 1);
        lcd.print("F");
        
        // Second line: Humidity
        lcd.setCursor(0, 1);
        lcd.print("Humidity: ");
        lcd.print(data.humidity, 1);
        lcd.print("%");
    }

    void displayError(const char* errorMessage) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Error:");
        lcd.setCursor(0, 1);
        lcd.print(errorMessage);
    }

    void clear() {
        lcd.clear();
    }
};

#endif // LCD16X2_DISPLAY_H 