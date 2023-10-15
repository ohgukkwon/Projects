#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library 
#include "Arduino.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//sda #a4, scl #a5

// #include "max6675.h"
// int thermoDO = 4; // SO
// int thermoCS = 5; // CS
// int thermoCLK = 6; // SCK
// // float temp1 = 0;
// MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

#include "DHT.h"
#define DHTPIN 4     /*Nano pin 4 for DHT11 sensor input*/
#define DHTTYPE DHT11   /*DHT sensor type we are using*/
//#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
//void dht11();

const byte address[6] = "00001";
struct SendData{
  int tx_id;
  char sensor_data[3];
  int cnt;
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

  sendData.tx_id = 1;
}

int i =0;

void loop()
{ 
  if (i < 1000)
  {
    sendData.tx_id= 1;
    sendData.cnt = i;
    //sendData.str_temp= "Arduino";
    //sendData.max6675_c = thermocouple.readCelsius();

    sendData.dht_hum = dht.readHumidity(); /*float variable that stores humidity value*/
    sendData.dht_c = dht.readTemperature(); /*float variable that store temperature in Celsius*/
    sendData.dht_f = dht.readTemperature(true); /*variable to store temperature in Fahrenheit*/

    radio.write(&sendData, sizeof(sendData));
    // Serial.println(text);  
    lcd.setCursor(0,0);
    lcd.print(sendData.tx_id);
    //lcd.setCursor(0,1);
    lcd.print(",Ard, ");
    lcd.print(sendData.cnt);
    lcd.setCursor(0,1);
    lcd.print(sendData.dht_c,1);
    i++;
  }
  else
  {
    i =0;
    lcd.clear();
  }
    delay(250);
}