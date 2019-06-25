#ifndef PENTERSOFTWARE_H
#define PENTERSOFTWARE_H

class PenterSoftware{
public:
  PenterSoftware();
  ~PenterSoftware();

  void begin();
  void penState(bool state);// true->down, false->up
  void penPoint();// Draw a point in the paper
  void moveHome();// Calibrate the printer
  void moveAxes(float XMillimeters,float YMillimeters);
  void gotoPosition(float x, float y);// Go to a coordinate
  void point(float x, float y);// Go to the coordinate and make a point
private:
  float maxX = 150;
  float maxY = 100;
  float currX = 0;
  float currY = 0;
  const int motorStep[3] = {22,19,3};// penMotor, Xmotor, Ymotor
  const int motorDir[3] = {23,21,1};// penMotor, Xmotor, Ymotor
  const int stopButton[2] = {19,20};// X and Y
  float Kx=120;
  float Ky=100;
  enum motorName{
    pen = 0,
    motorX = 1,
    motorY = 2
  };
  enum stopButtonName{
    stopX = 0,
    stopY = 1
  };
};
#endif// PENTERSOFTWARE_H
