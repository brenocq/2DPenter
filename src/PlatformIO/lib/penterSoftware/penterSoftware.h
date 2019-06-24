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
  void point(float x, float y);// Go to the coordinate and make a point
private:
  float maxX = 150;
  float maxY = 100;
  float currX;
  float currY;
  const int motorStep[3] = {22,19,3};
  const int motorDir[3] = {23,21,1};
  float Kx=120;
  float Ky=100;
  enum motorName{
    pen = 0,
    motorX = 1,
    motorY = 2
  };
};
#endif// PENTERSOFTWARE_H
