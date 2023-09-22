#include <Arduino.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(921600);
  Serial.println("Hello world_setup");
}

void loop()
{
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("Hello world_loop");
  delay(1000);
  Serial.println("Hello world_loop_off");
  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
}