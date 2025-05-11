#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include "dht11_temp_read.h"
#include "nrf24l01_send.h"


void setup() {
  Serial.println(F("DHT11 test!"));
  Serial.println(F("NRF24L01 test!"));
  // Serial.println("");
  dht.begin();
  radio.begin();

}


void loop() {
  delay(2000);

  temp_read();

  mesg_send();
}

// /dev/ttyCH341USB0