#include<stdio.h>
#include<math.h>

int main(){
  double x,y;
  double f,g;
  y = 0.0000004;
  x = 1.0;
  f = 1.0/(sqrt(x+y) - sqrt(x));
  printf("%.15f\n", sqrt(x+y)-sqrt(x));
  g = (sqrt(x+y) + sqrt(x))/y;
  printf("f = %f\n",f);
  printf("g = %f\n",g);
}
