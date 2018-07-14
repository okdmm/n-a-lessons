# 演習課題5
行列$A$の定義は

$$
A = 
\begin{pmatrix}
2 & 0 & 1 & 0 \\
0 & 2 & 0 & 1 \\
1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 
\end{pmatrix}
$$
であった。


## (1)

固有値を$ \lambda $単位行列を$ I $ とする
$$ \det(A - \lambda I) = 0 $$
を解く。行列式を余因子展開し$ (\lambda - 2)(\lambda - 1) $で括れば
$$ ( {(\lambda-1)(\lambda-2) -1)}^2 = 0 $$
を解いて
$$ \lambda = \frac{3 \pm \sqrt{5}}{2} $$
それぞれ重複度は2である。

## (2)

初期ベクトルとして
$$
x =
\begin{pmatrix}
0.5 \\
0.5 \\
0.5 \\
0.5
\end{pmatrix}
$$
べき乗法と逆べき乗法で固有値と固有ベクトルを求める。
逆べき乗法を使う際に$A$の逆行列を求めるがその際にこれスキー分解を用いる。

```power.c
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
     //ただの掛け算
      powerVector[0][i] += A[i][j]*initVector[j];
    }
    //正規化用のノルムの足し算
    nolm += powerVector[0][i]*powerVector[0][i]; 
    printf("%lf ", powerVector[0][i]);
  }
  printf("\n");

  // nolmで正規化
  lambda = 0.0;
  for(i = 0; i < 4; i++){
    lambda += powerVector[0][i]*powerVector[0][i]/sqrt(nolm);
    //ここで正しい意味でのノルムになる。これで各要素を割って正規化
    powerVector[0][i] /= sqrt(nolm); 
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
      //ノルム導出用の準備
      nolm += pow(powerVector[k][i],2); 
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
      powerVector[0][i] += InverseA[i][j]*initVector[j];
    }
    nolm += powerVector[0][i]*powerVector[0][i];
    printf("%lf ", powerVector[0][i]);
  }
  printf("\n");

  // nolmで正規化
  lambda = 0.0;
  for(i = 0; i < 4; i++){
    lambda += powerVector[0][i]*powerVector[0][i]/sqrt(nolm);
    powerVector[0][i] /= sqrt(nolm);
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
      nolm += pow(powerVector[k][i],2);
      printf("%ge ", powerVector[k][i]);
    }
    printf("\n");
    lambda = 0.0;
    for(i = 0; i < 4; i++){
      lambda += powerVector[0][i]*powerVector[0][i]/sqrt(nolm);
      powerVector[k][i] /= sqrt(nolm);
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
```

で求めた。結果を抜粋する。

```
固有値
2.618034
固有ベクトル
1.000000 1.000000 0.618034 0.618034
```

```
固有値
0.381966
固有ベクトル
1.000000 1.000000 -1.618034 -1.618034
```
となった。

## (3) 

$ A $ にハウスホルダー変換をする

まずは入れ替えたい列を決める。狙いとしては上三角行列になるようにしたいので
$$
x =
\begin{pmatrix}
2\\
0\\
1\\
0
\end{pmatrix}
と
x' = 
\begin{pmatrix}
|x|\\
0\\
0\\
0
\end{pmatrix}
$$
を入れ替えるようなハウスホルダー変換行列 $ H_1 $ を求める.

$$
H_1 = I - \frac{2(x - x')(x - x')^{T}}{|x-x'|^2}
$$
を具体的に計算する。$ \alpha = 2 - \sqrt{5} $として
$$
H_1 = 
\frac{1}{1 + {\alpha}^2}
\begin{pmatrix}
1 - {\alpha}^2 & 0 & -2\alpha & 0 \\
0 &  {\alpha}^2 + 1 & 0 & 0 \\
-2\alpha & 0 & \alpha^2 -1 & 0 \\
0 & 0 & 0 & {\alpha}^2 + 1
\end{pmatrix}
$$
となった。実際に計算してみると

$$
A_1 = H_1 A =
\begin{pmatrix}
\sqrt{5} & 0 & \frac{1 - {\alpha}^2 -2\alpha}{1 + {\alpha}^2} & 0\\
0 & 2 & 0 & 1 \\
0 & 0 & \frac{-2\alpha + {\alpha}^2 -1}{1 + {\alpha}^2} & 0 \\
0 & 1 & 0 &1
\end{pmatrix}
$$
と行を入れ替える事ができた。これを二行二列以降に繰り返していく。
つまり
$$
x = 
\begin{pmatrix}
2\\
0\\
1
\end{pmatrix}
と
x' = 
\begin{pmatrix}
|x|\\
0\\
0
\end{pmatrix}
$$
を入れ替えるような$ H'_2$ を求める。
実際には先ほどと同様に
$$
H'_2= I - \frac{2(x - x')(x - x')^{T}}{|x-x'|^2}
$$
を具体的に計算する。$ \alpha = 2 - \sqrt{5} $として
$$
H'_2= 
\frac{1}{1 + {\alpha}^2}
\begin{pmatrix}
1 - {\alpha}^2 & 0 & -2\alpha \\
0 &  {\alpha}^2 + 1 & 0 \\
-2\alpha & 0 & \alpha^2 -1 \\
\end{pmatrix}
$$
から
$$
H_2 = 
\begin{pmatrix}
1 & O\\
O & H'_2
\end{pmatrix}
$$
がも止まった。先ほどと同様に列の入れ替えを行う。つまり
$$
A_2 = H_2 A_1 =
\begin{pmatrix}
\sqrt{5} & 0 & \frac{1 - {\alpha}^2 -2\alpha}{1 + {\alpha}^2} & 0\\
0 & \sqrt{5} & 1 &\frac{1 - {\alpha}^2 -2\alpha}{1 + {\alpha}^2}   \\
0 & 0 & \frac{2\alpha}{1 + {\alpha}^2} & 0 \\
0 & 0 & 0 &\frac{2\alpha}{1 + {\alpha}^2}
\end{pmatrix}
$$
と上三角行列がも止まった。
以上で元の行列をハウスホルダー変換する事ができた。

## (4)
(3)で求めた行列を使いQR法を元の行列に一回使う。上三角行列の$ R $ は上で求めた$ A_2$ である。
$ A_2 = H_2 H_1 A$ であったのでハウスホルダー変換行列の逆行列を求め左からかけ直せば$ Q $が求まる。
簡単にプログラムで計算する。
結果は
$$
Q = 
\begin{pmatrix}
1.332097 &  0.000000  & -0.428127 & 0.000000 \\
0.000000 & 1.341641 & 0.000000 &-0.447214 \\
-0.428127 &  0.000000 & 0.856253 & 0.000000 \\
0.000000 & -0.447214 & 0.000000 & 0.894427
\end{pmatrix}
$$

となった。よって$ A $は上で求めた$ R$ と $ Q $ で分解できて固有値は$ R $ の体格成分である
$ \sqrt{5},\frac{2 \alpha}{1 + {\alpha}^2} $
である。ただし$ \alpha = 2 - \sqrt{5}$である。
