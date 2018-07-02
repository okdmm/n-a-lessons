#include<stdio.h>
#include<math.h>

int main(){
  double x,y;
  double f,g;
  y = 0.000001;
  x = 10000000.0;
  f = 1/(sqrt(x+y) - sqrt(x));
  printf("1/f = %.24f\n", sqrt(x+y)-sqrt(x));
  g = (sqrt(x+y) + sqrt(x))/y;
  printf("f = %f\n",f);
  printf("g = %f\n",g);
}
