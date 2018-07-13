#include<stdio.h>
#include<math.h>

int main(){
  // 行列の定義
  int i,j,k;
  double nolm = 0.0;
  double L[4][4]; /*下三角行列*/
  double U[4][4]; /*上三角行列*/
  double InverseL[4][4];
  double InverseU[4][4];
  double InverseQ[4][4];
  double InversMaxRow;
  double InversRow[4];
  double MaxRow;
  double Row[4];

  /*初期ベクトルの設定*/
  double initVector[4] = {0.5, 0.5, 0.5, 0.5}; 
  double alpha = 2 - sqrt(5);
  //H_1の定義
  double H_1[4][4] ={
    {(1-alpha*alpha)/(1 + alpha*alpha), 0 ,(-2*alpha)/(1 + alpha*alpha), 0}
    ,{0,1, 0, 0}
    ,{(-2*alpha)/(1 + alpha*alpha), 0, alpha*alpha - 1, 0}
    ,{0, 0, 0, 1}
  };

  // H_2の定義
  double H_2[4][4] = {
  {1,0,0,0}
  ,{0, (1 - alpha*alpha)/(1 + alpha*alpha), 0, (-2*alpha)/(1 + alpha*alpha)}
  ,{0, 0, 1, 0}
  ,{0,(-2*alpha)/(1 + alpha*alpha), 0, (alpha*alpha -1)/(1 + alpha*alpha)}
  };
  double Q[4][4];

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      printf("%lf ",H_1[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      printf("%lf ",H_2[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  //H_2*H_1の逆行列がQである
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){ 
      Q[i][j] = 0.0;
      for(k = 0; k < 4; k++){
        Q[i][j] += H_2[i][k]*H_1[k][j];
      }
      printf("%lf ", Q[i][j]);
    }
    printf("\n");
  }
  printf("\n");

 //逆行列の計算
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
        if( tmp > Q[i][j]){
        L[j][j] = sqrt(tmp - Q[j][j]);
        }else {
        L[j][j] = sqrt(Q[j][j] - tmp);
        }
      } else {
          double tmp = 0.0;
        for ( int k = 0; k < j; k++){
          tmp += L[i][k]*L[j][k];
        }
        L[i][j] = (Q[i][j] - tmp)/L[j][j]; 
      }
    } 
  }
  /*Uの計算とUの表示*/
  printf("\nUの表示\n");
  for(i=0; i<4; i++){
    for(j=0; j<4; j++){
      U[i][j] = L[j][i];
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


  /*Qの逆行列*/
  printf("\nQの逆行列\n");
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
        InverseQ[i][j]= 0.0;
     for(int k=0; k<4; k++){
        InverseQ[i][j]+= InverseU[i][k]*InverseL [k][j];
     } 
     printf("%lf ", InverseQ[i][j]);
    }
    printf("\n");
  }

}
