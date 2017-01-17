int stringToInt(char *str)
{
  int res = 0;
  int p = 1;
  for (int n = strlen(str) - 1; n >= 0; --n)
  {
    res += (str[n] - 0x30) * p;
    p *= 10;
  }
  return res;
}

void clearString(char *str, int n)
{
  for (int i = 0; i < n; i++)
  {
    str[i] = '\0' ;
  } 
}
