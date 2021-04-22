#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX 1000;

const char spc = ' ';

double operands[1000];
char operations[1000], userTxt[1000];
char strOperands[1000][1000];

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
  int l = 0;
  for (int i = 0; i < j; i++)
  {
    int x = filterTxt[i];
    if ((x >= 48 && x <= 57) || (x >= 97 && x <= 122))
    {
      strOperands[k][l] = filterTxt[i];
      l++;
      strOperands[k][l] = '\0';
    }
    else
    {
      operations[p] = filterTxt[i];
      k++;
      p++;
      l = 0;
    }
  }
}

int getLen2(double opnds[]){
  int x = 0;
  while(opnds[x] !=  0){
    x++;
  }

  return x;
}

double getFunNum(char currFun[3], char funs[][3], int n)
{
  double res = 0;
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
  return res;
}

long int factorial(int n){
  if(n<=1){
    return 1;
  }
  else{
    return n*factorial(n-1);
  }
}
double degreeToRadian(double deg)
{
  return deg * 0.0175;
}

double getValOfOp(double functionNumber,double operand){
  int x = (int)functionNumber;
  switch(x){
    case 1:
      return log(operand);
    case 2:
      return operand*operand;
    case 3:
      return powf(operand,3);
    case 4:
      if(operand<0){
        return (0-operand);
      }  
      else{
        return operand;
      } 
    case 5:
      return (double)(factorial((int)operand));
    case 6:
      return sin(degreeToRadian(operand)); 
    case 7:
      return cos(degreeToRadian(operand));
    case 8:
      return tan(degreeToRadian(operand));    
  }
}

double getAnsOp(char exp[1000])
{
  int x = 0;
  double val = 0;
  while (exp[x] != '\0')
  {
    x++;
  }

  int a = exp[0];
  if (a >= 48 && a <= 57)
  {
    double ans = 0;
    for (int i = 0; i < x; i++)
    {
      ans = ans * 10 + (exp[i] - '0');
    }
    val = ans;
  }
  else
  {
    double funNum = -1;
    char fun[3];
    for (int i = 0; i < 3; i++)
    {
      fun[i] = exp[i];
    }

    funNum = getFunNum(fun, specialFunctions, 8);
    double num = 0;
    for(int i=3;i<x;i++){
      num = num*10 + (exp[i] - '0');
    }

    double spcAns = getValOfOp(funNum,num);

    val = spcAns;
  }

  return val;
}

void fillOperands(char arr[][1000])
{
  int l = 0;
  while(arr[l][0] != '\0'){
    l++;
  }
  for (int i = 0; i < l; i++)
  {
    double temp = getAnsOp(arr[i]);
    operands[i] = temp;
  }
}


void printArr2(char arr[][1000], int n)
{

  for (int i = 0; i < n; i++)
  {
    int j = 0;
    while (strOperands[i][j] != '\0')
    {
      printf("%c", strOperands[i][j]);
      j++;
    }
    printf("   ");
  }
}

void printOpnds(double opnds[]){
  int x = getLen2(opnds);
  printf("\n");
  for(int i=0; i<x;i++){
    printf("%lf  ",opnds[i]);
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


void applyBodmas(double operands[], char operations[])
{
  char div = '/';
  char mul = '*';
  int l = getLen2(operands);
  //solving for divisions
  for (int i = 0; i < l - 1; i++)
  {
    if (operations[i] == div)
    {
      operands[i] = giveAns(operands[i], operands[i + 1], '/');
      for (int k = i + 1; k < getLen2(operands) - 1; k++)
      {
        operands[k] = operands[k + 1];
      }
      operands[getLen2(operands) - 1] = 0;

      for (int k = i; k < l - 2; k++)
      {
        operations[k] = operations[k + 1];
      }
    }
  }

  int o = getLen2(operands);
  //solving for multiplication
  for (int i = 0; i < o - 1; i++)
  {
    if (operations[i] == mul)
    {
      operands[i] = giveAns(operands[i], operands[i + 1], '*');
      for (int k = i + 1; k < getLen2(operands) - 1; k++)
      {
        operands[k] = operands[k + 1];
      }
      operands[getLen2(operands) - 1] = 0;

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
  int l = getLen2(operands);
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
  printf("These are the functions you can use \n");
  printf("log for getting log of a number\nsqr for getting square of a number\ncub for getting cube of a number\nabs for getting absolute of a number\nfac for getting factorial of a number\nsin,cos ,tan for getting respective valuse\n");
  printf("exampe: 23+sin45+sq4+cub3+log20\n");
  printf("Enter the expression: ");
  gets(userTxt);
  for (int i = 0; i < 1000; i++)
  {
    operands[i] = 0;
    strOperands[i][0] = '\0';
  }
  decodeString(userTxt);
  
  fillOperands(strOperands);
  // printArr2(strOperands, 10);
  // printOpnds(operands);
  applyBodmas(operands,operations);
  double ans = calculateOperation(operands, operations);
  printf("your answere is %lf", ans);


  return 0;
}