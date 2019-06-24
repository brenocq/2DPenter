#include <Arduino.h>
#include"penterSoftware.h"

PenterSoftware::PenterSoftware(){

}

PenterSoftware::~PenterSoftware(){

}

void PenterSoftware::begin(){
  for (int i = 0; i < 3; i++) {
    pinMode(motorStep[i],OUTPUT);
    pinMode(motorDir[i],OUTPUT);
  }
}

void PenterSoftware::point(float x, float y){

}

void PenterSoftware::moveHome(){

}

void PenterSoftware::moveAxes(float XMillimeters,float YMillimeters){
//Serial.print(XMillimeters);Serial.print(" ");Serial.print(Kx);Serial.print(" ");Serial.print(XMillimeters*Kx);Serial.print(" ");Serial.print(int(XMillimeters*Kx));
  if(XMillimeters>=0){
    digitalWrite(motorDir[motorX],HIGH);// Changes the rotation direction
    for(int i = 0; i < abs(int(XMillimeters*Kx)); i++) {

      digitalWrite(motorStep[motorX],HIGH);
      delayMicroseconds(300);
      digitalWrite(motorStep[motorX],LOW);
      delayMicroseconds(300);
    }
  }else{
    digitalWrite(motorDir[motorX],LOW);// Changes the rotation direction
    for(int i = 0; i < -int((XMillimeters*Kx)); i++) {
      digitalWrite(motorStep[motorX],HIGH);
      delayMicroseconds(300);
      digitalWrite(motorStep[motorX],LOW);
      delayMicroseconds(300);
    }
  }

  if(YMillimeters>=0){
    digitalWrite(motorDir[motorY],HIGH);// Changes the rotation direction
    for(int i = 0; i < abs(int(YMillimeters*Ky)); i++) {

      digitalWrite(motorStep[motorY],HIGH);
      delayMicroseconds(300);
      digitalWrite(motorStep[motorY],LOW);
      delayMicroseconds(300);
    }
  }else{
    digitalWrite(motorDir[motorY],LOW);// Changes the rotation direction
    for(int i = 0; i < -int((XMillimeters*Ky)); i++) {
      digitalWrite(motorStep[motorY],HIGH);
      delayMicroseconds(300);
      digitalWrite(motorStep[motorY],LOW);
      delayMicroseconds(300);
    }
  }
}

void PenterSoftware::penPoint(){
    digitalWrite(motorDir[pen],LOW);// Changes the rotation direction
    for(int i = 0; i < 500; i++) {
      digitalWrite(motorStep[pen],HIGH);
      delayMicroseconds(300);
      digitalWrite(motorStep[pen],LOW);
      delayMicroseconds(300);
    }
    digitalWrite(motorDir[pen],HIGH);// Changes the rotation direction
    for(int i = 0; i < 500; i++) {
      digitalWrite(motorStep[pen],HIGH);
      delayMicroseconds(300);
      digitalWrite(motorStep[pen],LOW);
      delayMicroseconds(300);
  }
}
