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

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";


void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  // Serial.begin(9600);
  // Serial.setTimeout(1000);


  lcd.init();                            // Initialize I2C LCD module
  lcd.backlight();  
}
int i =0;
void loop()
{

  //dht11()
  if (i <1000)
  {
  //if (radio.available()) {
  char text[30] = "#1:";
  // char num_str[20]="";
  
  // sprintf(num_str, "%d", i);   //convert int to string

  // strncat(text, num_str, 30);     //add string to string

  // char addE[100];
  // strcat(addE, text);
  // strcat(addE, " - ");
  // strcat(addE, addt);  

    // if (radio.available()) {  
    // radio.write(&text, sizeof(text));  
    //radio.write(&addt, sizeof(addt) );
    // Serial.print("Write, ");
    // Serial.println(text);
    //Serial.println(num);
    //Serial.print("\n");
  //float h = dht.readHumidity(); /*float variable that stores humidity value*/
  float h = 12.34;
  float t = dht.readTemperature(); /*float variable that store temperature in Celsius*/
  float f = dht.readTemperature(true); /*variable to store temperature in Fahrenheit*/
  // if (isnan(h) || isnan(t) || isnan(f)) 
  // {
  //   //Serial.println("Failed to read from DHT sensor!");
  //   lcd.setCursor(0, 0);               // Go to column 0, row 0
  //   lcd.print("DHT Fail        ");
  //   lcd.setCursor(0, 1);               // Go to column 0, row 0
  //   lcd.print("                ");
  //   return;
  //   }

  char hum[20]="";
  dtostrf(h,5,2,hum);                                //convert float to string, h -> hum
  char concast_str[30] = "";
  sprintf(concast_str,"%s %s%s %d", "test", hum,"%", i);   //concast string
  strcat(text, concast_str);
  radio.write(&text, sizeof(text));  

  lcd.setCursor(0,0);
  lcd.print(F("Humidity: ")); /*prints humidity value*/
  lcd.print(h);
  lcd.print(F("%"));
  lcd.setCursor(0,1);
  // lcd.print("T:");
  lcd.print(t);
  lcd.print(F("'C")); 
  lcd.print(",   ");
  lcd.print(i);
  // lcd.print(F("'F")); 


  }

  else
  {
    i=0;
  }

  i++;
  // delay(300);
}  


// void dht11(){           //DHT11 Temp and Humidity sensor
//   float h = dht.readHumidity(); /*float variable that stores humidity value*/
//   float t = dht.readTemperature(); /*float variable that store temperature in Celsius*/
//   float f = dht.readTemperature(true); /*variable to store temperature in Fahrenheit*/
//   if (isnan(h) || isnan(t) || isnan(f)) {
//     Serial.println("Failed to read from DHT sensor!");
//     lcd.setCursor(0, 0);               // Go to column 0, row 0
//     lcd.print("DHT Fail        ");
//     lcd.setCursor(0, 1);               // Go to column 0, row 0
//     lcd.print("                ");
//     return;
//   }

//   // lcd.setCursor(0,0);
//   // lcd.print("                ");
//   lcd.setCursor(0,0);
//   lcd.print(F("Humidity: ")); /*prints humidity value*/
//   lcd.print(h);
//   lcd.print(F("%"));
//   lcd.setCursor(0,1);
//   // lcd.print("T:");
//   lcd.print(t);
//   lcd.print(F("'C")); 
//   lcd.print(", ");
//   lcd.print(f);
//   lcd.print(F("'F")); 

  // Serial.print(F("Humidity: ")); /*prints humidity value*/
  // Serial.print(h);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(t);
  // Serial.print(F("°C ")); /*prints temp in Celsius*/
  // Serial.print(f);
  // Serial.println(F("°F ")); /*prints temp in Fahrenheit*/
//}
