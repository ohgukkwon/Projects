#include <SoftwareSerial.h>
#include <string.h>
#include <stdio.h>
#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library 

#include "DHT.h"
#define DHTPIN 4     /*Nano pin 4 for DHT11 sensor input*/
#define DHTTYPE DHT11   /*DHT sensor type we are using*/
//#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
 
//String rData = "#000STA";

//actual turbo reponse  = "#000,\x85\x8b\xcc,25090,002,002,001,001,000,66,00800,070,037,0000000000000000000000000";
SoftwareSerial mySerial(10, 11); // RX, TX

// void readString();
// void readByte();
// void readString_fromPC3();
// void writeData_toPC();
//void turbo_rpm();
void dht11();

// String row_read;
// String row_read3;
//String row_read3;

// int rpm;
// String str_t;
// String sub_s;
// int rpm_t;
// int mytime;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//sda #a4, scl #a5

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";


void setup() {

  // int bard_rate = 115200;
  Serial.begin(9600);
  Serial.setTimeout(1000);
  // mySerial.begin(115200);
  // mySerial.setTimeout(1000);
  // Serial.print("USB Serial is ready");   // opens serial port, sets data rate to 9600 bps

  lcd.init();                            // Initialize I2C LCD module
  lcd.backlight();  

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {
  // if (mySerial.available())
  // {
  //   writeData_toPC();
  //   Serial.print('\n');

  //   //readString();
  //   //readByte();
  //   //readString_fromPC3();
  //   Serial.print('\n');
  //   }
  // else{
  //   lcd.setCursor(0, 0);               // Go to column 0, row 0
  //   lcd.print("Serial NG      ");
  //   lcd.setCursor(0, 1);               // Go to column 0, row 0
  //   lcd.print("                ");
  // }
  dht11();

  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  Serial.print("\n");
  Serial.println(text);

  delay(1000);
}

void dht11(){           //DHT11 Temp and Humidity sensor
  float h = dht.readHumidity(); /*float variable that stores humidity value*/
  float t = dht.readTemperature(); /*float variable that store temperature in Celsius*/
  float f = dht.readTemperature(true); /*variable to store temperature in Fahrenheit*/
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 0);               // Go to column 0, row 0
    lcd.print("DHT Fail");
    return;
  }

  // lcd.setCursor(0,0);
  // lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print(F("Humidity: ")); /*prints humidity value*/
  lcd.print(h);
  lcd.print(F("%"));
  lcd.setCursor(0,1);
  // lcd.print("T:");
  lcd.print(t);
  lcd.print(F("'C")); 
  lcd.print(", ");
  lcd.print(f);
  lcd.print(F("'F")); 

  Serial.print(F("Humidity: ")); /*prints humidity value*/
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C ")); /*prints temp in Celsius*/
  Serial.print(f);
  Serial.println(F("°F ")); /*prints temp in Fahrenheit*/
}

// unsigned long myTime;
// void writeData_toPC(){
//   mySerial.write("000STA");
//   Serial.print("Write Data : ");
//   Serial.print(rData);
// }

