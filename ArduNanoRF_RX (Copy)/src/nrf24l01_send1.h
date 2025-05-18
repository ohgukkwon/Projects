#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "dht11_temp_read.h"

RF24 radio(9, 10); // CE, CSN()

const byte address[6] = "00001";


// void setup() {
//   Serial.begin(9600);
//   radio.begin();
//   radio.openWritingPipe(address);
//   radio.setPALevel(RF24_PA_MIN);
//   radio.stopListening();
// }

void mesg_send() {
  radio.begin();

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  Serial.println("TX-OK");  
  // delay(1000);
}