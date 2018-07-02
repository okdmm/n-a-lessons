#include<stdio.h>

int main(){
  double e;
  e = 1.0;

  while( 1.0 + e != 1.0){
    e /= 2.0;
  }
  printf("%g",e*2.0);
}
