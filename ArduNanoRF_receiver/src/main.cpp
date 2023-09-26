/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Arduino.h"

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
unsigned long myTime;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

int i = 0;
void loop() {
  
  if (radio.available()) {
    char text[32] = "";
    
    //myTime = millis();
    radio.read(&text, sizeof(text));
    Serial.print("Hello world ");    
    Serial.println(text); 
    delay(300);   
  }

 
  }