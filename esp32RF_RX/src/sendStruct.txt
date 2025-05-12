#include "Arduino.h"
#include <stdio.h> //esp32 is 32bit, so need to add it

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(4, 5); // CE, CSN on Blue Pill  ESP32
//18 SCK, 19 MISO

#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library 
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//ESP32 sda #21, scl #22

#include "max6675.h"
int thermoDO = 27;                  //MISO
int thermoCS = 14;                  //CS
int thermoCLK = 12;                 //SCK
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
// SCK	This is the SPI clock pin.
// CS	This is the SPI Chip select pin.
// SO	This is the serial output pin (data out).

const byte address[6] = "00001";
struct SendData{
  int16_t tx_id;                         //if ESP32 int send to Arduino => declear int16_t and Arduino side (interger / 255)
  char sensor_data[3];
  int16_t cnt;
  float max6675_c;
  int dht_hum;
  float dht_c;
  float dht_f;                  
};
SendData sendData;

void setup() {
  //Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  lcd.clear();
  lcd.init();                            // Initialize I2C LCD module
  lcd.backlight();    
}

int i =0;
void loop()
{ 
  if (i < 100)
  {
    sendData.tx_id= 2;
    sendData.cnt = i;
    sendData.max6675_c = thermocouple.readCelsius();

    radio.write(&sendData, sizeof(sendData));
    // Serial.println(text);  
    lcd.setCursor(0,0);
    lcd.print(sendData.tx_id);
    lcd.print(",ESP,");
    lcd.print(sendData.cnt);
    lcd.setCursor(0,1);
    lcd.print(sendData.max6675_c,1);
    i++;
    
  }
  else
  {
    i =0;
    lcd.clear();
  }
    delay(250);
}