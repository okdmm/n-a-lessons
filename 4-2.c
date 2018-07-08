#include<stdio.h>
#include<math.h>

int main(){
  int i,j,n;
  int N=15;
  double Hilbelt[N][N];

  /*LU分解で逆行列を求める*/
  /*特にHilebert行列は実対象行列つまり正定置よってコレスキー分解ができる*/
  double L[15][15]; /*下三角行列*/
  double U[15][15]; /*上三角行列*/
  double InverseL[15][15];
  double InverseU[15][15];
  double InverseHierbert[15][15];

  /* N = 5  */

  /*Hilbelt行列の定義*/
  printf(" n = 5\n\n");
  for(i = 0; i < 5; i++){
    for(j = 0; j < 5; j++){
      Hilbelt[i][j] = 1.0/(i + j + 1.0 );
    }
  }

  /*Lの計算*/
  for(i = 0; i < 5; i++){
    for( j = 0; j < 5; j++){
      if( j > i ){
        L[i][j] = 0.0;
      }else if( j == i){
          double tmp = 0.0;
        for( int k = 0; k < j; k++){
          tmp += L[j][k]*L[j][k];
        }
        L[j][j] = sqrt(Hilbelt[j][j] - tmp);
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
  for(i=0; i<5; i++){
    for(j=0; j<5; j++){
      printf("%lf  ", L[i][j]);
    }
    printf("\n");
  }
  /*Uの計算とUの表示*/
  printf("\nUの表示\n");
  for(i=0; i<5; i++){
    for(j=0; j<5; j++){
      U[i][j] = L[j][i];
      printf("%lf", U[i][j]);
    }
    printf("\n");
  }

  /*検算*/
  printf("\n検算\n");
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      double tmp = 0.0;
     for(int k=0; k<5; k++){
        tmp += L[i][k]*U[k][j];
     } 
     printf("%lf ", tmp);
    }
    printf("\n");
  }

  /*Lの逆行列*/
  printf("\nLの逆行列\n");
  for( i = 0;i < 5; i++){
    for( j = 0;j < 5; j++){
      if( i < j ){
        InverseL[i][j] = 0.0;
        printf("%f ", InverseL[i][j]);
      }else if( i == j ){
        InverseL[i][i] = 1.0/L[i][i];
        printf("%f ", InverseL[i][i]);
      }else {
        double tmp = 0.0;
        for(int k = 0; k < i; k++){
          tmp += L[i][k]*InverseL[k][j];
        }
        InverseL[i][j] = - tmp/L[i][i];
        printf("%f ", InverseL[i][j]);
      }
    }
    printf("\n");
  }

  /*L検算*/
  printf("\n検算\n");
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      double tmp = 0.0;
     for(int k=0; k<5; k++){
        tmp += L[i][k]*InverseL[k][j];
     } 
     printf("%lf ", tmp);
    }
    printf("\n");
  }

  /*Uの逆行列*/
  printf("\nUの逆行列\n");
  for( i = 0; i < 5; i++ ){
    for(j = 0; j < 5; j++){
      InverseU[i][j] = InverseL[j][i];
      printf("%f ", InverseU[i][j]);
    }
    printf("\n");
  }

  /*U検算*/
  printf("\n検算\n");
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      double tmp = 0.0;
     for(int k=0; k<5; k++){
        tmp += InverseU[i][k]*U[k][j];
     } 
     printf("%lf ", tmp);
    }
    printf("\n");
  }

  /*Hilebertの逆行列*/
  printf("\nHilbertの逆行列\n");
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
        InverseHierbert[i][j]= 0.0;
     for(int k=0; k<5; k++){
        InverseHierbert[i][j]+= InverseU[i][k]*InverseL [k][j];
     } 
     printf("%lf ", InverseHierbert[i][j]);
    }
    printf("\n");
  }

  /*Hilbertの検算*/
  printf("\nHilbertの検算\n");
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      double tmp = 0.0;
     for(int k=0; k<5; k++){
        tmp += Hilbelt[i][k]*InverseHierbert[k][j];
     } 
     printf("%lf ", tmp);
    }
    printf("\n");
  }

  /*infinity-nolmを求める*/
  for(i=0;i<5;i++){
    double tmp = 0.0;
    for(j=0;j<5;j++){
      tmp+= InverseHierbert[i][j];
    }
    printf("%f\n", tmp);
  }
}
