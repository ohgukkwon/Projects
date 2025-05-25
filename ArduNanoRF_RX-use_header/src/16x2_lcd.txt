#include <SPI.h>
#include <LiquidCrystal_I2C.h>  //LiquidCrystal_I2C lcd(0x27,20,2);
#include <Wire.h>
#include <millis_Led.h>

LiquidCrystal_I2C lcd(0x27,20,2);


void 16x2_lcd() {
    lcd.init();
    lcd.clear();         
    lcd.backlight();      // Make sure backlight is on
    lcd.print("Initializing..");
    delay(1000);
    lcd.clear();


  //   Serial.println("Data: 0");
  //   lcd.clear();
  //   lcd.setCursor(0,0);
  //   lcd.print("Data: 0");
  //   delay(1000);
  //   return;
      
  //   Serial.print(rData.rf_id);    // Print temperature with 1 decimal place
  //   Serial.print(" ");

  //   Serial.print(rData.t, 1);    // Print temperature with 1 decimal place
  //   Serial.print("°F, ");
  //   lcd.setCursor(0,0);
  //   lcd.print("T: ");
  //   lcd.setCursor(3,0);
  //   lcd.print(rData.t,1);
  //   lcd.print(F("F, "));

  //   Serial.print("H: ");
  //   Serial.print(rData.h);
  //   Serial.print("%, ");

  //   lcd.setCursor(10,0);
  //   lcd.print("H:");
  //   lcd.print(rData.h);
  //   lcd.print(F("%"));

  //   lcd.setCursor(0,1);
  //   lcd.print(rData.rf_id);
  //   lcd.setCursor(2,1);
  //   // lcd.print(i);
  //   // lcd.print(" ");
  //   lcd.setCursor(4,1);
  //   lcd.print("Rx Radio OK");

  //   Serial.print(rData.rf_status);
  //   Serial.print(" ");
    
  //   Serial.print(rData.timestamp);
  //   Serial.print(" ");
  //   Serial.println("RX-OK ");

  //   // Serial.print(receivedData.timestamp);


  // } else {
  //     // Serial.println("No data available");
  //     Serial.println("RF Status: 0");      
  //     lcd.setCursor(0,0);
  //     lcd.print("RF Status: 0");
  //     delay(1000);
  //     lcd.clear();
  //   return;
  // }
  // i++;
  // if (i >= 100) {
  //   lcd.clear();
  //   i = 0;
  }
