#include<stdio.h>
#include<math.h>

int main(){
  int i,j,n,k;
  int pivot;
  int N=10;
  double Hilbelt[N][N];
  double A[N][N+1];

  double MaxRow;
  double Row[N];
  double b[N];
  double c[N];
  double x[N];


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

  for(i=0;i<N;i++){
    for(j=0;j<N+1;j++){
      if(j == N){
        A[i][j] = b[i];
      }else{
        A[i][j] = Hilbelt[i][j];
      }
    }
  }

  for(i = 0; i < N; i++){
    for(j = 0; j < N+1; j++){
      printf("%le ", A[i][j] );
    }
    printf("\n");
  }

  /*消去法始まり*/
  for(k = 0; k < N-1; k++ ){
    /*pivotの軸探し*/
    pivot = k;
    MaxRow = fabs(A[k][k]);
    for(i=k+1; i < N; i++){
      if( fabs(A[i][k]) > MaxRow ){
        MaxRow = fabs(A[i][k]);
        pivot = i;
      }
    }

    /*もしpivotの必要があるならば交換*/
    if(pivot != k){
      for(i = k; i < N+1; i++){
        double tmp = A[k][i];
        A[k][i] = A[pivot][i];
        A[pivot][i] = tmp;
      }
    }
    /*pivot完了*/

    /*前進消去して行く*/
    for(i = k+1; i< N; i++){
      double tmp[N+1];
      tmp[i] = A[i][k]/A[k][k];
      A[i][k] = 0.0;
      for(j = k+1; j < N + 1; j++){
        A[i][j] = A[i][j] - A[k][j]*tmp[i];
      }
    }
  }
  /*掃き出し後の行列を確認*/
  for(i=0; i < N; i++){
    for(j = 0; j < N + 1; j++){
      printf("%le  ", A[i][j]);
    }
    printf("\n");
  }

    /*後退代入つまり解の計算*/
  for( i = N-1; i >= 0; i--){
    x[i] = A[i][N];
    for(j = i + 1; j < N; j++){
      x[i]  -=  A[i][j]*x[j];
      A[i][j] = 0.0;
    }
    x[i] /= A[i][i];
    A[i][i] = 1.0;
  }
  for(i = 0; i < N; i++){
    printf("x[%d] = %le\n",i, x[i]);
  }


  /*近似解との積 */
  /*残差ノルム*/
  for(i=0;i<N;i++){
    Row[i] = 0.0;
    for(j=0;j<N;j++){
      Row[i]+=Hilbelt[i][j]*x[j];
    }
    Row[i] = fabs(b[i] - Row[i]); 
    printf("%d行の和 = %le\n",i, Row[i]);
  }

  MaxRow = Row[0];
  for(i=0;i<N;i++){
    if(Row[i] > MaxRow){
      MaxRow = Row[i];
    }
  }
  printf("\n残差ノルム%le\n",MaxRow);

  /*誤差ノルム*/
  printf("\n誤差ノルム\n");
  for(i=0;i<N;i++){
    Row[i] = fabs(x[i] - 1.0);
    printf("%le\n", Row[i]);
  }

  MaxRow = Row[0];
  for(i=0;i<N;i++){
    if(Row[i] > MaxRow){
      MaxRow= Row[i];
    }
  }

  printf("\n誤差ノルム%le\n",MaxRow);
}
