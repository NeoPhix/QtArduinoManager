#include <AFMotor.h>
#include <Servo.h>

// Подключаем шаговый двигатель к порту 1
// порт 1 - M1, M2
// порт 2 - M3, M4
// 48 - количество шагов для полного оборота

//int w = 1000;  //our size
//int h = 1000;
//
//int x = 0;  //that's our coords
//int y = 0;

  AF_Stepper motorX(200, 1);
  AF_Stepper motorY(200, 2);

class MotorsWrapper
{
public:
  MotorsWrapper(int w_, int h_)
  {
    x = 0;
    y = 0;
    w = w_;
    h = h_;
  }
  void go(int x_new, int y_new)
  {
    //Try!
    if (x_new >= w || x_new < 0)
    {
      Serial.println("X coordinate is unavailable");
      return;
    }
    if (y_new >= h || y_new < 0)
    {
      Serial.println("Y coordinate is unavailable");
    }

    //Y coordinate
    if (x_new > x)
    {
      for (; x <= x_new; ++x)
      {
        motorX.step(1, FORWARD, DOUBLE);
        delay(5);
      }
    }
    else if (x_new < x)
    {
      for (; x >= x_new; --x)
      {
        motorX.step(1, BACKWARD, DOUBLE);
        delay(5);
      }
    }
    
    //Y coordinates
    if (y_new > y)
    {
      for (; y <= y_new; ++y)
      {
        motorY.step(1, FORWARD, DOUBLE);
        delay(5);
      }
    }
    else if (y_new < y)
    {
      for (; y >= y_new; --y)
      {
        motorY.step(1, BACKWARD, DOUBLE);
        delay(5);
      }
    }
  }

  void printCurrentCoordinate()
  {
    Serial.print("current: X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.println(y);
  }
  
private:
  int x;
  int y;
  int w;
  int h;  
};

MotorsWrapper moto(1000, 1000);

void setup() 
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
}

void loop()
{
  //how to paint a square

  moto.printCurrentCoordinate();
  moto.go(100, 100);
  
  moto.printCurrentCoordinate();
  moto.go(100, 400);
  moto.printCurrentCoordinate();
  moto.go(400, 400);
  moto.printCurrentCoordinate();
  moto.go(400, 100);
  moto.printCurrentCoordinate();
  moto.go(100, 100);
  moto.printCurrentCoordinate();

//  for (; x < 100; ++x, ++y)
//  {
//    motorX.step(1, FORWARD, DOUBLE);
//    motorY.step(1, FORWARD, DOUBLE);
//    delay(5);
//  }
//  //X range
//  Serial.println("X range");
//  for (; x < w - 100; ++x)
//  {
//     motorX.step(1, FORWARD, DOUBLE);
//     delay(5);
//  }
//  
//  //Y range
//  Serial.println("Y range");
//  for (; y < h - 100; ++y)
//  {
//     motorY.step(1, FORWARD, DOUBLE);
//     delay(5);
//  }
//  
//  //X range back
//  Serial.println("X range back");
//  for (; x >= 100; --x)
//  {
//     motorX.step(1, BACKWARD, DOUBLE);
//     delay(5);
//  }
//  //Y range back
//  Serial.println("Y range back");
//  for (; y >= 100; --y)
//  {
//     motorY.step(1, BACKWARD, DOUBLE);
//     delay(5);
//  }
//  
//  delay(50);
}


