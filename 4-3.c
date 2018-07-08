#include<stdio.h>
#include<math.h>

int main(){
  int i,j,n;
  int N=15;
  long double Hilbelt[N][N];

  /*LU分解で逆行列を求める*/
  /*特にHilebert行列は実対象行列つまり正定置よってコレスキー分解ができる*/
  long double L[15][15]; /*下三角行列*/
  long double U[15][15]; /*上三角行列*/
  long double InverseL[15][15];
  long double InverseU[15][15];
  long double InverseHierbert[15][15];
  long double InversMaxRow;
  long double InversRow[15];
  long double MaxRow;
  long double Row[15];

  /* N = 5  */

  /*Hilbelt行列の定義*/
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      Hilbelt[i][j] = 1.0/(i + j + 1.0 );
    }
  }

  /*Lの計算*/
  for(i = 0; i < N; i++){
    for( j = 0; j < N; j++){
      if( j > i ){
        L[i][j] = 0.0;
      }else if( j == i){
          double tmp = 0.0;
        for( int k = 0; k < j; k++){
          tmp += L[j][k]*L[j][k];
        }
        /*虚数を回避*/
        if( j > 12){
        L[j][j] = sqrt(tmp - Hilbelt[j][j]);
        }else {
        L[j][j] = sqrt(Hilbelt[j][j] - tmp);
        }
      } else {
          double tmp = 0.0;
        for ( int k = 0; k < j; k++){
          tmp += L[i][k]*L[j][k];
        }
        L[i][j] = (Hilbelt[i][j] - tmp)/L[j][j]; 
      }
    } 
  }
  /*Lの表示 */
  printf("Lの表示\n");
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      printf("%Lf  ", L[i][j]);
    }
    printf("\n");
  }
  /*Uの計算とUの表示*/
  printf("\nUの表示\n");
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
      U[i][j] = L[j][i];
      printf("%Lf ", U[i][j]);
    }
    printf("\n");
  }

  /*検算*/
  printf("\n検算\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      long double tmp = 0.0;
     for(int k=0; k<N; k++){
        tmp += L[i][k]*U[k][j];
     } 
     printf("%Lf ", tmp);
    }
    printf("\n");
  }

  /*Lの逆行列*/
  printf("\nLの逆行列\n");
  for( i = 0;i < N; i++){
    for( j = 0;j < N; j++){
      if( i < j ){
        InverseL[i][j] = 0.0;
        printf("%Lf ", InverseL[i][j]);
      }else if( i == j ){
        InverseL[i][i] = 1.0/L[i][i];
        printf("%Lf ", InverseL[i][i]);
      }else {
        long double tmp = 0.0;
        for(int k = 0; k < i; k++){
          tmp += L[i][k]*InverseL[k][j];
        }
        InverseL[i][j] = - tmp/L[i][i];
        printf("%Lf ", InverseL[i][j]);
      }
    }
    printf("\n");
  }

  /*L検算*/
  printf("\n検算\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      long double tmp = 0.0;
     for(int k=0; k<N; k++){
        tmp += L[i][k]*InverseL[k][j];
     } 
     printf("%Lf ", tmp);
    }
    printf("\n");
  }

  /*Uの逆行列*/
  printf("\nUの逆行列\n");
  for( i = 0; i < N; i++ ){
    for(j = 0; j < N; j++){
      InverseU[i][j] = InverseL[j][i];
      printf("%Lf ", InverseU[i][j]);
    }
    printf("\n");
  }

  /*U検算*/
  printf("\n検算\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      long double tmp = 0.0;
     for(int k=0; k<N; k++){
        tmp += InverseU[i][k]*U[k][j];
     } 
     printf("%Lf ", tmp);
    }
    printf("\n");
  }

  /*Hilebertの逆行列*/
  printf("\nHilbertの逆行列\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
        InverseHierbert[i][j]= 0.0;
     for(int k=0; k<N; k++){
        InverseHierbert[i][j]+= InverseU[i][k]*InverseL [k][j];
     } 
     printf("%Lf ", InverseHierbert[i][j]);
    }
    printf("\n");
  }

  /*Hilbertの検算*/
  printf("\nHilbertの検算\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      long double tmp = 0.0;
     for(int k=0; k<N; k++){
        tmp += Hilbelt[i][k]*InverseHierbert[k][j];
     } 
     printf("%Lf ", tmp);
    }
    printf("\n");
  }

  /*infinity-nolmを求める*/
  /*逆行列のノルム*/
  InversRow[0] = 0.0;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      InversRow[i]+= InverseHierbert[i][j];
    }
    printf("%d行の和 = %Lf\n",i, InversRow[i]);
  }
  InversMaxRow = InversRow[0];
  for(i=0;i<N;i++){
    if(InversRow[i] > InversMaxRow)
      InversMaxRow = InversRow[i];
  }

  /*ノルム*/
  Row[0] = 0.0;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      Row[i]+= Hilbelt[i][j];
    }
    printf("%d行の和 = %Lf\n",i, Row[i]);
  }
  MaxRow = Row[0];
  for(i=0;i<N;i++){
    if(Row[i] > MaxRow)
      MaxRow = Row[i];
  }
  printf("\n条件数= %Lf\n", MaxRow*InversMaxRow);
}
