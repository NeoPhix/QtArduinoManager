#include <AFMotor.h>
#include <Servo.h>

//Motors
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

    //X coordinate
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

//Setup//
//Motors params
MotorsWrapper moto(1000, 1000, 5); //h = 1000, w = 1000, delaty = 5 ms

//Input string params
char endFlag = '!';
const int bytesNumber = 256;
char incomingBytes[bytesNumber];
int bytesAvailable = 0;
int incomingByte = 0;
int iter = 0;

//to do ? 
char command = 'W';   //wait

void setup()
{
  Serial.begin(9600); // set up Serial library at 9600 bps
}

//Loop//

int cur = 0;  //will be cleared

void loop()
{
  if (iter > 256)
  {
    Serial.println("Fail input string length. Maximal length is 256 symbols includind '\\n' symbol!!!");
    clearString(incomingBytes, bytesNumber);
    iter = 0;
  }
  //reading
  command = readBytes();
  
  //switch/case
  switch (command)
  {
    case 'W': //Wait
      break;
    case 'G': //Go to X and Y
      Serial.print("GO");
      
      goAction(incomingBytes);
      
      clearString(incomingBytes, bytesNumber);
      command = 'W';
      break;
    case 'D': //Change delay to N ms
      Serial.print("DELAY");

      
      //delayChangeAction(incomingBytes, bytesNumber);
      clearString(incomingBytes, bytesNumber);
      command = 'W';
      break;
  }
}


