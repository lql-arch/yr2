#include<stdio.h>
#include<math.h>

#define pi 3.1415926

double fun(double x,int n){
    if(x*x==1){
        return 0;
    }
    return (pow(x,n)/sqrt(1-x*x));
}

double jifen(int n,double (*p)(double,int)){
    int a=1,b=-1;
    double wide=0.0000001;
    double m=(a-b)/wide;
    double s=0;
    for(int i=0;i<m;i++){
        s+=(*p)(b+i*wide,n)*wide;
    }
    return s;
}

int main(){
    int n=0;
    scanf("%d",&n);

    printf("%lf",(jifen(n,fun)));

    return 0;

}
