#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX 1000;

const char spc = ' ';

// add,sub,mul,div,sin,cos,tan,log 10,reciprocal,square,cube,power,
// absolute,factorial,square root,exponential,natural log,percentage
//log sqr cub abs fac log sin cos tan

double operands[1000];
char operations[1000], userTxt[1000];

char specialFunctions[8][3] = {"log", "sqr", "cub", "abs", "fac", "sin", "cos", "tan"};

void decodeString(char text[])
{
  //remove spaces
  int n = strlen(text);
  char filterTxt[1000];
  int j = 0;
  for (int i = 0; i < n; i++)
  {
    if (text[i] != spc)
    {
      filterTxt[j] = text[i];
      j++;
    }
  }

  int k = 0;
  int p = 0;
  for (int i = 0; i < j; i++)
  {
    int x = filterTxt[i];
    if (x >= 48 && x <= 57)
    {
      operands[k] = operands[k] * 10 + (filterTxt[i] - '0');
    }
    else
    {
      operations[p] = filterTxt[i];
      p++;
      k++;
    }
  }
}

int getFunNum(char currFun[], char funs[][3], int n)
{
  int res = 0;
  bool isEq = false;
  for (int i = 0; i < n; i++)
  {
    bool isE = false;
    for (int j = 0; j < 3; j++)
    {
      if (currFun[j] == funs[i][j])
      {
        isE = true;
      }
      else
      {
        isE = false;
        break;
      }
    }
    if (isE)
    {
      isEq = true;
      res = i + 1;
      break;
    }
  }
}

void decodeString2(char text[1000])
{
  int n = strlen(text);
  char filterTxt[1000];
  int j = 0;
  for (int i = 0; i < n; i++)
  {
    if (text[i] != spc)
    {
      filterTxt[j] = text[i];
      j++;
    }
  }
  int k = 0;
  int p = 0;
  char currFun[3];
  int r = 0;
  int funNumber = -1;
  for (int i = 0; i < j; i++)
  {
    int x = filterTxt[i];
    if ((x >= 48 && x <= 57) || (x >= 97 && x <= 122))
    {
      if (x >= 48 && x <= 57)
      {
        operands[k] = operands[k] * 10 + (filterTxt[i] - '0');
      }
      else
      {
        currFun[r] = filterTxt[i];
        r++;
        if (r == 3)
        {
          int funNum = getFunNum(currFun, specialFunctions, 8);
          r = 0;
          printf("%d", funNum);
        }
      }
    }
    else
    {
      operations[p] = filterTxt[i];
      p++;
      k++;
    }
  }
}

void printArr(double arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%lf", arr[i]);
  }
}

double giveAns(double a, double b, char op)
{

  switch (op)
  {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  case '%':
    return ((int)a) % ((int)b);
  default:
    return 0;
  }
}

int gLen(double arr[])
{
  int n = 0;
  while (arr[n] != 0)
  {
    n++;
  }
  return n;
}

void applyBodmas(double operands[], char operations[])
{
  char div = '/';
  char mul = '*';
  int l = gLen(operands);
  //solving for divisions
  for (int i = 0; i < l - 1; i++)
  {
    if (operations[i] == div)
    {
      operands[i] = giveAns(operands[i], operands[i + 1], '/');
      for (int k = i + 1; k < gLen(operands) - 1; k++)
      {
        operands[k] = operands[k + 1];
      }
      operands[gLen(operands) - 1] = 0;

      for (int k = i; k < l - 2; k++)
      {
        operations[k] = operations[k + 1];
      }
    }
  }

  int o = gLen(operands);
  //solving for multiplication
  for (int i = 0; i < o - 1; i++)
  {
    if (operations[i] == mul)
    {
      operands[i] = giveAns(operands[i], operands[i + 1], '*');
      for (int k = i + 1; k < gLen(operands) - 1; k++)
      {
        operands[k] = operands[k + 1];
      }
      operands[gLen(operands) - 1] = 0;

      for (int k = i; k < l - 2; k++)
      {
        operations[k] = operations[k + 1];
      }
    }
  }
}

double calculateOperation(double operands[], char operations[])
{
  double res = 0;
  int l = gLen(operands);
  for (int i = 0; i < l; i++)
  {
    if (i == 0)
    {
      res = operands[i];
    }
    else
    {
      res = giveAns(res, operands[i], operations[i - 1]);
    }
  }

  return res;
}

int main()
{
  printf("Enter the expression: ");
  gets(userTxt);
  for (int i = 0; i < 1000; i++)
  {
    operands[i] = 0;
  }
  decodeString2(userTxt);
  // applyBodmas(operands, operations);
  // double ans = calculateOperation(operands, operations);

  // printf("your answere is %lf", ans);
  // printArr(operands,10);
  return 0;
}