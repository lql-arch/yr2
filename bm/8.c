#include<stdio.h>

// int main(){
//     long long int m=0;
//     scanf("%lld",&m);
//     int num[m];
//     for(int i=0;i<m;i++){
//         num[i]=0;
//     }

//     for(int i=1;i<=m;i++){
//         for(int j=1;j<=m;j++){
//             if(j%i==0){
//                 if(num[j-1]==0){
//                     num[j-1]=1;
//                 }else{
//                     num[j-1]=0;
//                 }
//             }
//         }
//     }

//     for(int i=0;i<m;i++){
//         if(num[i]!=0){
//             printf("%d ",i+1);
//         }
//     }
//     printf("\n");
//     return 0;
// }

int main(){
    long long m=0;//2^44

    scanf("%lld",&m);

    for(int i=1;i*i<=m;i++){
        printf("%lld ",i*i);
    }
    printf("\n");

    return 0;
}