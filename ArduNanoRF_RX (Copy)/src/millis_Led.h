#include <Arduino.h>

int led_R = 14;
int led_G = 15;
int led_fade = 10; // faded lde

int led_R_State = LOW;
int led_G_State = HIGH;

byte brightness = 0;
byte fadeIncrement = 1;   //  1 byte  => 0-255

unsigned long currentMillis = 0;

unsigned long previousMillis = 0;
unsigned long fadePreviousMillis = 0;

const unsigned long interval = 500; // Interval in milliseconds
const unsigned long fadePeriod = 30;

void blinkLed() {
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (led_R_State == LOW) {
      led_R_State = HIGH;
      led_G_State = LOW;
    }else {
      led_R_State = LOW;
      led_G_State = HIGH;
    }
    digitalWrite(led_R, led_R_State);
    digitalWrite(led_G, led_G_State);
  }
}

void fadeLed() {
  
  if (currentMillis - fadePreviousMillis >= fadePeriod) {
    
    fadePreviousMillis = currentMillis;
    Serial.print(fadePreviousMillis);
    Serial.print(" ");

    Serial.print("Brightness: ");
    Serial.println(brightness); 

    analogWrite(led_fade, brightness);
    brightness += fadeIncrement;
    // if (brightness <= 0 || brightness >= 255) {
    //   fadeIncrement = -fadeIncrement;
    // }
  }
}