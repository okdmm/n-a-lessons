#include<stdio.h>
#include<math.h>


double p(x)
     double x;
 {  double y;
  y =  x*x*x + x*x - 5*x + 3;
  return (y);
    }

double dp(x)
     double x;
{
  double y;
  y = 3*x*x + 2*x - 5;
  return (y);
}

int main(){


  
  double x, xx, tmp, eps;
  int k, kmax;
  kmax=50;
  eps = 1.e-12;

  x =30;
  printf("\nx = 30のとき\n\n");

  for (k=1; k <= kmax; ++k){
    tmp= p(x)/dp(x);
    xx = x - tmp;
    if (fabs(p(xx)) <= eps) break;
    else
      x = xx;
      printf("%5d    %21.17e\n", k, xx);
      printf("e[%d]  %21.2e\n", k, fabs(xx-1.0));
  }
  printf("%5d    %21.17e\n", k, xx);
  printf("e[%d]  %21.2e\n", k, fabs(xx-1.0));

  x = -30;
  printf("\nx = -30のとき\n\n");

  for (k=1; k <= kmax; ++k){
    tmp= p(x)/dp(x);
    xx = x - tmp;
    if (fabs(p(xx)) <= eps) break;
    else
      x = xx;
      printf("%5d    %21.17e\n", k, xx);
      printf("e[%d]  %21.2e\n", k, fabs(xx+3.0));
  }
  printf("%5d    %21.17e\n", k, xx);
  printf("e[%d]  %21.2e\n", k, fabs(xx+3.0));
 }
