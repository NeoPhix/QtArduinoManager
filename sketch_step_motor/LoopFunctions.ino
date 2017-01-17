char readBytes()
{
  bytesAvailable = Serial.available();
  if (bytesAvailable > 0)
  {
    for (int i = 0; i < bytesAvailable; ++i)
    {
      incomingBytes[iter] = Serial.read();
      iter++;
    }
    bytesAvailable = 0;

    if (incomingBytes[iter - 1] == endFlag)
    {
      Serial.println("Yep! We have ended reading!");
      Serial.println("Our results:");
      Serial.println(incomingBytes);
      iter = 0;
      return incomingBytes[0];  //G presents "Go to coords"; D presents delay changing
    }
  }
  return 'W'; //Wait action in main loop
}

//void delayChangeAction(incomingBytes, bytesNumber)
//{
//  int k = 0;
//}
//

void goAction (char *str)
{
  if (str[0] != ' ')
  {
    Serial.println("Error syntaxis of go command. Need arguments splited by spaces (X and Y coodinates)");
    return;
  }
  
  char x_str[5];
  char y_str[5];
  int i = 0;
  int n = 2;
  for (i = 0; str[n] != ' ' && str[n] != endFlag; ++n)
  {
    x_str[i] = str[n];
    i++;
  }
  x_str[i] = '\0';

  Serial.println(x_str);
  
  if (str[n] == endFlag)
  {
    Serial.println("Error syntaxis of go command. Need the second argument");
    return;
  }
  
  for (i = 0; str[n] != ' ' && str[n] != endFlag; ++n)
  {
    y_str[i] = str[n];
    i++;
  }
  y_str[i] = '\0';

  Serial.println(x_str);
  
  int x = stringToInt(x_str);
  int y = stringToInt(y_str);
  
  moto.go(x, y);
}


