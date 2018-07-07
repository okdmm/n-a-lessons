#include<stdio.h>
#include<math.h>

int main(){
  int i,j,n;
  int N=15;
  double Hilbelt[N][N];

  /*Hilbelt行列の定義*/

  /* N = 5 */
  printf(" n = 5\n\n");
  for(i = 0; i < 5; i++){
    for(j = 0; j < 5; j++){
      Hilbelt[i][j] = 1.0/(i + j + 1.0 );
      printf("%lf ", Hilbelt[i][j] );
    }
    printf("\n");
  }
  printf("\n");
  
  /* N = 10 */
  printf(" n = 10\n\n");
  for(i = 0; i < 10; i++){
    for(j = 0; j < 10; j++){
      Hilbelt[i][j] = 1.0/(i + j + 1.0 );
      printf("%lf ", Hilbelt[i][j] );
    }
    printf("\n");
  }
  printf("\n");

  /* N = 15 */
  printf(" n = 15\n\n");
  for(i = 0; i < 15; i++){
    for(j = 0; j < 15; j++){
      Hilbelt[i][j] = 1.0/(i + j + 1.0 );
      printf("%lf ", Hilbelt[i][j] );
    }
    printf("\n");
  }
  printf("\n");
}
