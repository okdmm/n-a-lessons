#include<stdio.h>
#include<math.h>

int main(){
  int i,j,n,k;
  int pivot;
  int N=15;
  double Hilbelt[N][N];
  double A[N][N+1];

  double MaxRow;
  double Row[N];
  double b[N];
  double x[N];
  double k_A[3] = { 943656.000002, 35350806896537.182865, 18960736249266216480.000000};
  
  for(i=0; i < 3; i++){
    printf("%le\n", k_A[i]);
  }

  /*Hilbelt行列の定義*/
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      Hilbelt[i][j] = 1.0/(i + j + 1.0 );
    }
  }

  /*bの設定*/
  for(i=0;i<N;i++){
    b[i] = 0.0;
    for(j=0;j<N;j++){
      b[i] += Hilbelt[i][j];
    }
    printf("b[%d] = %le\n",i, b[i]);
  }


  /*誤差の上限を求める*/
  MaxRow = fabs(b[0]);
  for(i=0;i<N;i++){
    if(fabs(b[i]) > MaxRow){
      MaxRow= fabs(b[i]);
    }
  }
  printf("%le \n",MaxRow);

  /*誤差の混入*/
  b[0]*= 1.001; 
  printf("%le\n",b[0]);
  printf("%le\n",k_A[N%5-1]);
  printf("誤差の上限は%le\n",k_A[N/5-1]*fabs(b[0])/MaxRow);

}
