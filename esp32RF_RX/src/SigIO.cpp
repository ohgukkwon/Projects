#include "SigIO.h"
#include <Arduino.h>

// Define pin numbers and interval if not defined elsewhere
const int buttonPin1 = 13;    // Example pin for button
const int buttonPin2 = 14;    // Example pin for button

const int ledPin1 = 25;      // Example pin for LED
const int ledPin2 = 26;      // Example pin for LED
const int ledPin3 = 27;      // Example pin for LED
const int ledPin4 = 12;       // Example pin for LED

const int potPin = 34;      // Example analog pin for potentiometer

unsigned long previousDataMillis = 0;
const long dataInterval = 1000;  // 1 second for data reading

SigIO::SigIO() : buttonState1(0), buttonState2(0), potValue(0), ADIO_pre_Millis(0) {
}

void SigIO::io_process() {
    unsigned long currentMillis = millis();
    
    // Process digital input
    if (currentMillis - ADIO_pre_Millis >= ADIO_Interval) {
        ADIO_pre_Millis = currentMillis;
        digital();
        analog();
    }
}   

void SigIO::digital() {
    // Read the state of the pushbutton
    pinMode(buttonPin1, INPUT);  
    // initialize the pushbutton pin as an input
    pinMode(ledPin3, OUTPUT);    
    // initialize the LED pin as an output

    buttonState1 = digitalRead(buttonPin1);  // Read the state of the pushbutton

    if (buttonState1 == LOW) {  // Check if the button is pressed    
        digitalWrite(ledPin3, HIGH);  // Turn the LED on
    } else {
        digitalWrite(ledPin3, LOW);  // Turn the LED off
    }
}

void SigIO::analog() {

    pinMode(ledPin3, OUTPUT);  
    pinMode(ledPin4, OUTPUT);    

    potValue = analogRead(potPin);
    Serial.println(potValue);
    v_in = (potValue / 4095.0) * 4.598; // Convert ADC value to voltage and store in class member
    Serial.print("Potentiometer Value: ");
    Serial.println(v_in);

    if (v_in > 1.5 && v_in < 2.5) {  // Example threshold for LED control
        digitalWrite(ledPin3, HIGH);  // Turn the LED on if voltage is above threshold
        digitalWrite(ledPin4, LOW);  // Turn another LED off
    } else if (v_in >= 2.5 && v_in <= 3.5) {  // Another threshold for LED control
        digitalWrite(ledPin3, LOW);  // Turn the first LED off if voltage is above threshold
        digitalWrite(ledPin4, HIGH);  // Turn the second LED on if voltage is above threshold   
    } else {
        digitalWrite(ledPin3, LOW);  // Turn the LED off if voltage is below threshold
        digitalWrite(ledPin4, LOW);  // Turn the first LED off if voltage is below threshold
    }
    
}
