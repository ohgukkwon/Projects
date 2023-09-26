#include <Arduino.h>

#include "WiFi.h"
 
void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());    //30:AE:A4:97:45:50
}
 
void loop(){

}