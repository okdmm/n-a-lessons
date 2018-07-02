#include<stdio.h>
#include<math.h>


double p(x)
     double x;
 {  double y;
  y =  cos(x)+(x+1)*exp(x);
  return (y);
    }

double dp(x)
     double x;
{
  double y;
  y = -sin(x)+exp(x)+(x+1)*exp(x);
  return (y);
}

main(){


  
  double x, xx, tmp, eps;
  int k, kmax;
  kmax=50;
  eps = 1.e-15;
  x =1.0;  /*  x=1.5; */
  for (k=1; k <= kmax; ++k){
    tmp= p(x)/dp(x);
    xx = x - tmp;
    if (fabs(tmp) <= eps) break;
    else
      x = xx;
      printf("%5d    %21.17e\n", k, xx);
  }
   printf("%5d    %21.17e\n", k, xx);
 }
        
