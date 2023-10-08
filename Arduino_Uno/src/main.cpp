#include <string.h>
#include <stdio.h>
#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library 
#include "Arduino.h"

#include "DHT.h"
#define DHTPIN 4     /*Nano pin 4 for DHT11 sensor input*/
#define DHTTYPE DHT11   /*DHT sensor type we are using*/
//#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
//void dht11();

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//sda #a4, scl #a5

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "max6675.h"
int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

RF24 radio(7, 8); // CE, CSN

const byte address2[6] = "00002";


void setup() {
  radio.begin();
  radio.openWritingPipe(address2);
  // radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  radio.printDetails(); 

  // Serial.begin(9600);
  // Serial.setTimeout(1000);

  lcd.clear();
  lcd.init();                            // Initialize I2C LCD module
  lcd.backlight();  
}
struct tempStrut {
  int tx_id = 02;
  float t_6672;
  int cnt;
  int h;      // = dht.readHumidity(); /*float variable that stores humidity value*/
  float t;    // = dht.readTemperature(); /*float variable that store temperature in Celsius*/
  float f;    // = dht.readTemperature(true); /*variable to store temperature in Fahrenheit*/
} sendData2;

int i =0;
// void radio_init();
void loop()
{
 
  //dht11()
  int h = dht.readHumidity(); /*float variable that stores humidity value*/
  float t = dht.readTemperature(); /*float variable that store temperature in Celsius*/
  float f = dht.readTemperature(true); /*variable to store temperature in Fahrenheit*/

  if (i <100) 
  {
    sendData2.t_6672 = thermocouple.readCelsius();
    sendData2.cnt = i;
      
    radio.write(&sendData2, sizeof(sendData2)); 
    lcd.setCursor(0,0);
    //lcd.print(sendData);
    lcd.setCursor(0,0);
    lcd.print(sendData2.t_6672);
    lcd.setCursor(0,1);
    lcd.print(sendData2.cnt);
  }
  else
  {
    i=0;
    lcd.clear();
  }
  i++;
  delay(300);
}
