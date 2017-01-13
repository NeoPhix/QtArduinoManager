#include <AFMotor.h>
#include <Servo.h>


int stringToInt(char* str, int n)
{
  int res = 0;
  int p = 1;
  for (int i = 0; i < n-1; ++i)
  {
    p *= 10 ;
  }
  for (int i  = 0; i < n - 1; ++i)
  {
    res += (str[i] - 0x30)*p ;
    p /= 10;
  }
  return res;
}

//////////////
//MotorClass//
//////////////
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

enum LoopAction {ActionWait, ActionGo, ActionDelayChange, ActionPrintCoords};

/////////
//Setup//
/////////
MotorsWrapper moto(1000, 1000, 5);  //h = 1000, w = 1000, delaty = 5 ms
char incomingBytes[256];
LoopAction loopAction = ActionWait;
void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
}

////////
//Loop//
////////

void loop()
{
  switch (loopAction)
  {
    case ActionWait:
      {
        int n = Serial.available();
        for (int i = 0; i < n; i++)
        {
          if (i%2 == 0)
            incomingBytes[i] = Serial.read();
          else
            incomingBytes[i] = ' ';  
        }
        delay(500);
        if (n > 0)
          Serial.println("I have got new bytes!");
      }
      break;
    case ActionGo:
      loopAction = ActionWait ;
      break;
    case ActionDelayChange:
      loopAction = ActionWait ;
      break;
    default:
      loopAction = ActionWait ;
      break;
  }
}


