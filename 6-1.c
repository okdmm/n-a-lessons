#include<stdio.h>
#include<math.h>

double f(z,a,y)
     double z;
     double a;
     double y;
 {  double dz;
   dz = -a*(1-y*y)*z + y;
  return (dz);
  }

double g(z)
  double z;
{ double y;
  y = z;
  return y;
}

int main(){
  int N = 100;
  int i, j;
  double a;
  double z[N];
  double y[N];
  double h = 1.0/N;

  FILE *gp;

  //初期値の設定
  z[0] = 0.0;
  y[0] = 1.0;

  a = 1.0;

  for(i = 1; i < N; i++){
   z[i] = z[i-1] + h* f(z[i-1],a,y[i-1]); 
   y[i] = y[i-1] + h*g(y[i-1]);
   printf("z[%d] = %lf  y[%d] = %lf\n", i, z[i], i, y[i]);
  }

  // グラフ
  gp = popen("gnuplot -persist", "w");
  fprintf(gp,"plot '-' with lines linetype 1 title \"a = 1.0\"\n");

  for(i = 0; i < N; i++){
    fprintf(gp, "%f\t%f\n",z[i],y[i]);
  } 

  fprintf(gp,"e\n");
  pclose(gp);

}
