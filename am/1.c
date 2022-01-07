// #include<stdio.h>
// //#include<math.h>
// #define MAX 100
// #define eps 2.2204e-16

// typedef struct{
//     int a;
//     int b;
//     int c;
//     int d;
// }num; 

// double _sqrt(double m);

// double _fabs(double k);

// int main(){
//     num n[MAX];
//     int x;
//     double sum[MAX];
//     scanf("%d",&x);
//     for(int i=0;i<x;i++){
//         scanf("%d %d %d %d",&n[i].a,&n[i].b,&n[i].c,&n[i].d);
//     }
//     for(int i=0;i<x;i++){
//         double t=(n[i].a-n[i].c)*(n[i].a-n[i].c)+(-n[i].b-n[i].d)*(-n[i].b-n[i].d);
//         sum[i]=_sqrt(t);
//         printf("%.2f\n",sum[i]);
//     }
//     return 0;
// }

// double _sqrt(double m){
//     double val=m;
//     double t=0;

//     do{
//         t=val;
//         val=(val + m/val) / 2;
//     }while(_fabs(val-t) > eps);

//     return val;
// }

// double _fabs(double k){
//     if(k>=0){
//         return k;
//     }else if(k<0){
//         k=-k;
//         return k;
//     }
// }