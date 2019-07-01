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
  for (int i = 0; i < 2; i++) {
    pinMode(stopButton[i],INPUT);
  }
}

void PenterSoftware::moveHome(){
    // Home X axis
    moveAxes(10,0);// Move 1cm positive
    digitalWrite(motorDir[motorX],LOW);// Move negative until endstop
    while(digitalRead(stopX)!=0){
      digitalWrite(motorStep[motorX],HIGH);
      delayMicroseconds(200);
      digitalWrite(motorStep[motorX],LOW);
      delayMicroseconds(200);
    }
    digitalWrite(motorDir[motorX],HIGH);// Move 1cm positive
    for(int i = 0; i < abs(int(10*Kx)); i++) {
      digitalWrite(motorStep[motorX],HIGH);
      delayMicroseconds(400);
      digitalWrite(motorStep[motorX],LOW);
      delayMicroseconds(400);
    }
    digitalWrite(motorDir[motorX],LOW);// Move negative until endstop (slower)
    while(digitalRead(stopX)!=0){
      digitalWrite(motorStep[motorX],HIGH);
      delayMicroseconds(400);
      digitalWrite(motorStep[motorX],LOW);
      delayMicroseconds(400);
    }
    currX=0;

    // Home Y axis
    moveAxes(0,10);// Move 1cm positive
    digitalWrite(motorDir[motorY],LOW);// Move negative until endstop
    while(digitalRead(stopY)!=0){
      digitalWrite(motorStep[motorY],HIGH);
      delayMicroseconds(200);
      digitalWrite(motorStep[motorY],LOW);
      delayMicroseconds(200);
    }
    digitalWrite(motorDir[motorY],HIGH);// Move 1cm positive
    for(int i = 0; i < abs(int(10*Ky)); i++) {
      digitalWrite(motorStep[motorY],HIGH);
      delayMicroseconds(400);
      digitalWrite(motorStep[motorY],LOW);
      delayMicroseconds(400);
    }
    digitalWrite(motorDir[motorY],LOW);// Move negative until endstop (slower)
    while(digitalRead(stopY)!=0){
      digitalWrite(motorStep[motorY],HIGH);
      delayMicroseconds(400);
      digitalWrite(motorStep[motorY],LOW);
      delayMicroseconds(400);
    }
    currY=0;
}

void PenterSoftware::moveAxes(float XMillimeters,float YMillimeters){
    Serial.print("CurrX:");Serial.print(currX);Serial.print(" Xmili:");Serial.print(XMillimeters);Serial.print("\t");
    Serial.print("CurrY:");Serial.print(currY);Serial.print(" Ymili:");Serial.print(YMillimeters);Serial.println("\t");
    if(currX+XMillimeters>maxX){
      XMillimeters = maxX-currX;
      Serial.print("NewXmili:");Serial.println(XMillimeters);
    }
    if(currX+XMillimeters<0){
      XMillimeters=0;
    }
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
    currX+=XMillimeters;
    if(currY+YMillimeters>maxY){
      YMillimeters = maxY-currY;
            Serial.print("NewYmili:");Serial.println(YMillimeters);
    }
    if(currY+YMillimeters<0){
      YMillimeters=0;
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
      for(int i = 0; i < -int((YMillimeters*Ky)); i++) {
        digitalWrite(motorStep[motorY],HIGH);
        delayMicroseconds(300);
        digitalWrite(motorStep[motorY],LOW);
        delayMicroseconds(300);
      }
    }
    currY+=YMillimeters;
    Serial.println();
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

void PenterSoftware::gotoPosition(float x, float y){
  Serial.print("Go to (");Serial.print(x);Serial.print(",");Serial.print(y);Serial.println("):");
  float deltaX = x-currX;
  float deltaY = y-currY;
  moveAxes(deltaX,deltaY);
}

void PenterSoftware::point(float x, float y){
  gotoPosition(x, y);
  penPoint();
}
