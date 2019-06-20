#include <Arduino.h>

const int stepPin = 23;
const int dirPin = 22;

void setup() {
  pinMode(stepPin,OUTPUT);
pinMode(dirPin,OUTPUT);
}

void loop() {
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 3200; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(100);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(100);
    }
    delay(1000); // One second delay

    digitalWrite(dirPin,LOW); //Changes the rotations direction
    // Makes 400 pulses for making two full cycle rotation
    for(int x = 0; x < 3200; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(100);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(100);
    }
    delay(1000);
}
