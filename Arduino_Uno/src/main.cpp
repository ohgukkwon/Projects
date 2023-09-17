#include <SoftwareSerial.h>
#include <string.h>
#include <stdio.h>
#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library
#include <Arduino.h>    

#include "DHT.h"
#define DHTPIN 4     /*Nano pin 4 for DHT11 sensor input*/
#define DHTTYPE DHT11   /*DHT sensor type we are using*/
//#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
//sda #a4, scl #a5
 
String rData = "#000STA";

//actual turbo reponse  = "#000,\x85\x8b\xcc,25090,002,002,001,001,000,66,00800,070,037,0000000000000000000000000";
SoftwareSerial mySerial(10, 11); // RX, TX

void readString();
void readByte();
void readString_fromPC3();
void writeData_toPC();
//void turbo_rpm();
void dht11();

String row_read;
String row_read3;
//String row_read3;

int rpm;
String str_t;
String sub_s;
int rpm_t;
int mytime;

void setup() {

  int bard_rate = 9600;
  Serial.begin(bard_rate);
  mySerial.begin(bard_rate);
  Serial.print("USB Serial is ready"); // opens serial port, sets data rate to 9600 bps

  lcd.init();                        // Initialize I2C LCD module
  lcd.backlight();                   // Turn backlight ON
  dht.begin();   /*Starts DHT sensor*/
}

void loop() {
  if (mySerial.available()){

    writeData_toPC();
    Serial.print('\n');

    //readString();
    readByte();
    //readString_fromPC3();

    Serial.print('\n');
  }
  else{
    lcd.setCursor(0, 0);               // Go to column 0, row 0
    lcd.print("Serial NG      ");
    lcd.setCursor(0, 1);               // Go to column 0, row 0
    lcd.print("                ");
  }
  delay(1000);
}


void readString(){
  row_read = mySerial.readString();
  Serial.print("Read1 Data : ");
  Serial.print(row_read);

  mytime = millis()/1000;            //elapsed time check

  lcd.setCursor(0, 0);               // Go to column 0, row 0
  lcd.print(row_read);
  lcd.setCursor(0, 1);  
  lcd.print("RPM : ");            // Go to column 0, row 1
  for (int i = 9; i < 14; i++)
  {
    lcd.print(row_read[i]);
  }
 
}


char buf[50];
void readByte(){
  int len= mySerial.readBytes(buf, 50);

  // lcd.setCursor(0, 0);  
  // lcd.print(buf);   
  for (int i = 0; i < len; i++)
  {
    Serial.print(buf[i])+"\n";  }

  lcd.setCursor(0, 0); 
  for (int j = 0; j < 16; j++)
  { 
    lcd.print(buf[j]);   }

  lcd.setCursor(0, 1);  
  lcd.print("RPM:");            // Go to column 0, row 1
  lcd.setCursor(5, 1);  
  for (int k = 9; k < 14; k++)
  {
    lcd.print(buf[k]);
  }
  lcd.print(" ");

  int num5= (buf[9] -'0') * 10000;  //ASCii code '0' is 48, ex; int 2 is ASCii 50, so 50-48 = 2
  int num4= (buf[10] -'0') * 1000;
  int num3= (buf[11] -'0') * 100;
  int num2= (buf[12] -'0') * 10;
  int num1= buf[13] -'0'; 

  //Serial.print(numm);
  Serial.print("\n");

  int total = num1 + num2 +num3+ num4+ num5;
  //uint8_t xx = atoi(numm) ;
  lcd.print(total);

}


void readString_fromPC3(){
  row_read3 = mySerial.readString();
  int len = row_read3.length() +1;

  char rd[len];
  row_read3.toCharArray(rd, len);
  byte xx = row_read3[15];

  int x = xx;// *100;


  //char *p = &row_read3;
  // for (int i =0; i<len; i++)
  // {
  //   Serial.print(row_read3[i]);
  // }

  //mytime = millis()/1000;            //elapsed time check

  lcd.setCursor(0, 0); 
  lcd.print(x);  
                // Go to column 0, row 0
  //lcd.print(row_read3);
  // lcd.setCursor(0, 1);  
  // lcd.print("RPM : ");            // Go to column 0, row 1

  // lcd.print(row_read3[27]);
  //int rpm_x = atoi(row_read3.toint); ////fail

  // for (int k =25; k <33; k++)
  // {
  //   lcd.print(row_read3[k]);
  // }
  // lcd.print("    ");
  // lcd.setCursor(0, 5);  
  // lcd.print(rpm_x);
 
}

void dht11(){           //DHT11 Temp and Humidity sensor
  float h = dht.readHumidity(); /*float variable that stores humidity value*/
  float t = dht.readTemperature(); /*float variable that store temperature in Celsius*/
  float f = dht.readTemperature(true); /*variable to store temperature in Fahrenheit*/
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 2);               // Go to column 0, row 0
    lcd.print("DHT Fail");
    return;
  }
  Serial.print(F("Humidity: ")); /*prints humidity value*/
  Serial.print(h);
  lcd.setCursor(0,2);
  lcd.print("H: ");
  lcd.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C ")); /*prints temp in Celsius*/
  Serial.print(f);
  Serial.println(F("°F ")); /*prints temp in Fahrenheit*/

    if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print(F("Humidity: ")); /*prints humidity value*/
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C ")); /*prints temp in Celsius*/
  Serial.print(f);
  Serial.println(F("°F ")); /*prints temp in Fahrenheit*/

}

unsigned long myTime;
void writeData_toPC(){
  mySerial.write("000STA");
  Serial.print("Write Data : ");
  Serial.print(rData);
}

