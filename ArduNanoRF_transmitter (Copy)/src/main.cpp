#include <Arduino.h>
#include <SPI.h>
#include "dht11_temp_read.h"
#include "nrf24l01_send.h"



void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));

  dht.begin();
}

int i = 0;

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  mesg_send();
  temp_read();
  i++;
  if (i > 1000) {
    i = 0;
  } 
}

// /dev/ttyCH341USB0