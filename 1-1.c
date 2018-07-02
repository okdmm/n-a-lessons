#include<stdio.h>
#include<math.h>

int main(){
  int i;
  double a[100];
  double S[100];
  double epsiron = 2.22045e-16;

  /*級数のの定義*/
  a[0] = 0.0;
  a[1] = 1.0;

  S[0] = 0.0;
  S[1] = a[1];

  for(i=2; i< 100; i++){
    a[i] = a[i-1]/(i*i);
    S[i] = S[i-1] + a[i];
    printf("a[%d] = %g\n", i, a[i]);
    printf("S[%d] = %f \n",i,S[i]);
    if ( S[i] == S[i-1]){
      printf("n = %d\n", i);
      printf("S[%d] = %f \nS[%d] = %f \n ",i-1,S[i-1], i, S[i]);
      break;
    }
    /*if (fabs(S[i] - S[i-1]) <= epsiron ){
      printf("n = %d\n", i);
      printf("S[%d] = %f \nS[%d] = %f \n ",i-1,S[i-1], i, S[i]);
      break;
    }*/
  }
 }
