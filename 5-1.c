#include<stdio.h>
#include<math.h>

int main(){
  // 行列の定義
  int A[4][4] = {{2,0,1,0}, {0,2,0,1}, {1,0,1,0},{0,1,0,1}};
  int i,j,k;
  double nolm;
  double L[4][4]; /*下三角行列*/
  double U[4][4]; /*上三角行列*/
  double InverseL[4][4];
  double InverseU[4][4];
  double InverseA[4][4];
  double InversMaxRow;
  double InversRow[4];
  double MaxRow;
  double Row[4];

  /*初期ベクトルの設定*/
  double initVector[4] = {0.5, 0.5, 0.5, 0.5}; 
  //反復回数
  int kmax = 10; 
  // 固有ベクトル候補
  double powerVector[kmax][4];
  // 正規化したベクトル
  double normalizeVector[kmax][4];
  // 固有値
  double lambda;

  /*Lの計算*/
  for(i = 0; i < 4; i++){
    for( j = 0; j < 4; j++){
      if( j > i ){
        L[i][j] = 0.0;
      }else if( j == i){
          double tmp = 0.0;
        for( int k = 0; k < j; k++){
          tmp += L[j][k]*L[j][k];
        }
        /*虚数を回避*/
        if( j > 12){
        L[j][j] = sqrt(tmp - A[j][j]);
        }else {
        L[j][j] = sqrt(A[j][j] - tmp);
        }
      } else {
          double tmp = 0.0;
        for ( int k = 0; k < j; k++){
          tmp += L[i][k]*L[j][k];
        }
        L[i][j] = (A[i][j] - tmp)/L[j][j]; 
      }
    } 
  }
  /*Lの表示 */
  printf("Lの表示\n");
  for(i=0; i<4; i++){
    for(j=0; j<4; j++){
      printf("%lf  ", L[i][j]);
    }
    printf("\n");
  }
  /*Uの計算とUの表示*/
  printf("\nUの表示\n");
  for(i=0; i<4; i++){
    for(j=0; j<4; j++){
      U[i][j] = L[j][i];
      printf("%lf ", U[i][j]);
    }
    printf("\n");
  }

  /*検算*/
  printf("\n検算\n");
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      double tmp = 0.0;
     for(int k=0; k<4; k++){
        tmp += L[i][k]*U[k][j];
     } 
     printf("%lf ", tmp);
    }
    printf("\n");
  }

  /*Lの逆行列*/
  printf("\nLの逆行列\n");
  for( i = 0;i < 4; i++){
    for( j = 0;j < 4; j++){
      if( i < j ){
        InverseL[i][j] = 0.0;
        printf("%lf ", InverseL[i][j]);
      }else if( i == j ){
        InverseL[i][i] = 1.0/L[i][i];
        printf("%lf ", InverseL[i][i]);
      }else {
        double tmp = 0.0;
        for(int k = 0; k < i; k++){
          tmp += L[i][k]*InverseL[k][j];
        }
        InverseL[i][j] = - tmp/L[i][i];
        printf("%lf ", InverseL[i][j]);
      }
    }
    printf("\n");
  }

  /*Uの逆行列*/
  printf("\nUの逆行列\n");
  for( i = 0; i < 4; i++ ){
    for(j = 0; j < 4; j++){
      InverseU[i][j] = InverseL[j][i];
      printf("%lf ", InverseU[i][j]);
    }
    printf("\n");
  }


  /*Aの逆行列*/
  printf("\nAの逆行列\n");
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
        InverseA[i][j]= 0.0;
     for(int k=0; k<4; k++){
        InverseA[i][j]+= InverseU[i][k]*InverseL [k][j];
     } 
     printf("%lf ", InverseA[i][j]);
    }
    printf("\n");
  }


  // /* べき乗法 */
  // 漸化式の初期値
  nolm = 0.0; //ノルムの初期化
  for(i = 0; i < 4; i++){
    powerVector[0][i] = 0.0;
    for(j = 0; j < 4; j++){
      powerVector[0][i] += A[i][j]*initVector[j]; //ただの掛け算
    }
    nolm += powerVector[0][i]*powerVector[0][i]; //正規化用のノルムの足し算
    printf("%lf ", powerVector[0][i]);
  }
  printf("\n");

  // nolmで正規化
  lambda = 0.0;
  for(i = 0; i < 4; i++){
    lambda += powerVector[0][i]*powerVector[0][i]/sqrt(nolm);
    powerVector[0][i] /= sqrt(nolm); //ここで正しい意味でのノルムになる。これで各要素を割って正規化
    printf("%ge ", powerVector[0][i]); 
  }
  printf("\n %lf", 1/lambda);

  //漸化式の始まり
  printf("\n\n");

  //漸化式
  for(k = 1; k < kmax; k++){
    //各項について計算
    nolm = 0.0;
    for(i = 0; i < 4; i++){
      powerVector[k][i] = 0.0;
      for(j = 0; j < 4; j++){
        powerVector[k][i] += A[i][j]*powerVector[k-1][j];
      }
      nolm += pow(powerVector[k][i],2); //ノルム導出用の準備
      printf("%ge ", powerVector[k][i]);
    }
    printf("\n");
    lambda = 0.0;
    for(i = 0; i < 4; i++){
      lambda += powerVector[0][i]*powerVector[0][i]/sqrt(nolm);
      powerVector[k][i] /= sqrt(nolm); //nolmで正規化
      printf("%ge ", powerVector[k][i]); 
    }
    printf("\n");
    for(i = 0; i < 4; i++){
      printf("%lf ", powerVector[k][i]/powerVector[k][0]);
    }
    printf("\n %lf\n",1/lambda);
    printf("\n\n");
  }
  printf("固有値\n");
  printf("%lf\n", 1/lambda);
  printf("固有ベクトル\n");
  for(i = 0; i < 4; i++){
    printf("%lf ", powerVector[kmax-1][i]/powerVector[kmax-1][0]);
  }
  printf("\n");


  // InversAの固有値など求める
  // /* べき乗法 */
  // 漸化式の初期値
  printf("\n べき乗法で最小の固有値と固有ベクトルを求める\n");
  nolm = 0.0; //ノルムの初期化
  for(i = 0; i < 4; i++){
    powerVector[0][i] = 0.0;
    for(j = 0; j < 4; j++){
      powerVector[0][i] += InverseA[i][j]*initVector[j]; //ただの掛け算
    }
    nolm += powerVector[0][i]*powerVector[0][i]; //正規化用のノルムの足し算
    printf("%lf ", powerVector[0][i]);
  }
  printf("\n");

  // nolmで正規化
  lambda = 0.0;
  for(i = 0; i < 4; i++){
    lambda += powerVector[0][i]*powerVector[0][i]/sqrt(nolm);
    powerVector[0][i] /= sqrt(nolm); //ここで正しい意味でのノルムになる。これで各要素を割って正規化
    printf("%ge ", powerVector[0][i]); 
  }
  printf("\n %lf", lambda);

  //漸化式の始まり
  printf("\n\n");

  //漸化式
  for(k = 1; k < kmax; k++){
    //各項について計算
    nolm = 0.0;
    for(i = 0; i < 4; i++){
      powerVector[k][i] = 0.0;
      for(j = 0; j < 4; j++){
        powerVector[k][i] += InverseA[i][j]*powerVector[k-1][j];
      }
      nolm += pow(powerVector[k][i],2); //ノルム導出用の準備
      printf("%ge ", powerVector[k][i]);
    }
    printf("\n");
    lambda = 0.0;
    for(i = 0; i < 4; i++){
      lambda += powerVector[0][i]*powerVector[0][i]/sqrt(nolm);
      powerVector[k][i] /= sqrt(nolm); //nolmで正規化
      printf("%ge ", powerVector[k][i]); 
    }
    printf("\n");
    for(i = 0; i < 4; i++){
      printf("%lf ", powerVector[k][i]/powerVector[k][0]);
    }
    printf("\n %lf\n",lambda);
    printf("\n\n");
  }
  printf("固有値\n");
  printf("%lf\n", lambda);
  printf("固有ベクトル\n");
  for(i = 0; i < 4; i++){
    printf("%lf ", powerVector[kmax-1][i]/powerVector[kmax-1][0]);
  }
  printf("\n");

}
