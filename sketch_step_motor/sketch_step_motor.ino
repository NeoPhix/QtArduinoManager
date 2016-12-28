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

//bool strEqual(char[] str1, char[] str2)
//{
//  int i = 0;
//  while (str1[i] != '\0' && str2[i] != '\0')
//  {
//    if (str1[i] != str2[i])
//      return false;
//    i++;
//  }
//  return true;
//}

AF_Stepper motorX(200, 1);
AF_Stepper motorY(200, 2);

class MotorsWrapper
{
  public:
    MotorsWrapper(int w_, int h_, int del_)
    {
      x = 0;
      y = 0;
      w = w_;
      h = h_;
      del = del_;
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
        for (; x < x_new; ++x)
        {
          motorX.step(1, FORWARD, DOUBLE);
          delay(del);
        }
      }
      else if (x_new < x)
      {
        for (; x > x_new; --x)
        {
          motorX.step(1, BACKWARD, DOUBLE);
          delay(del);
        }
      }

      //Y coordinates
      if (y_new > y)
      {
        for (; y < y_new; ++y)
        {
          motorY.step(1, FORWARD, DOUBLE);
          delay(del);
        }
      }
      else if (y_new < y)
      {
        for (; y > y_new; --y)
        {
          motorY.step(1, BACKWARD, DOUBLE);
          delay(del);
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

    void setDelay(int del_)
    {
      del = del_;
    }

    void setWidth(int w_)
    {
      w = w_;
    }

    void setHeight(int h_)
    {
      h = h_;
    }

  private:
    int x;
    int y;
    int w;
    int h;

    int del;
};

MotorsWrapper moto(1000, 1000, 5);
char incomingByte[256];

void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
}


void loop()
{
  int n = Serial.available();
  for (int i = 0; i < n; i++)
  {
    incomingByte[i] = Serial.read();
    Serial.print(incomingByte[i]);
    Serial.print(" ");
  }
}


