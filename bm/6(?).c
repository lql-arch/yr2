#include<stdio.h>

int count=0;

int fabs(int n){
    if(n>=0){
        return n;
    }
    else{
        return -n;
    }
}

// int minl(int a,int b,int end1,int end2){
//     if(a==end1&&b==end2){
//         printf("%d\n",count);
//         return 1;
//     }

//     for(int c=0;c<109;c++){
//         for(int d=0;d<109;d++){
//             if(a+b==c+d){
//                 if(minl(c,d,end1,end2)==1){
//                     count++;
//                     return 1;
//                 }
//             }
//             if(a-b==c-d){
//                 if(minl(c,d,end1,end2)==1){
//                     count++;
//                     return 1;
//                 }
//             }
//             if(fabs(a-c)+fabs(b-d)<=3){
//                 if(minl(c,d,end1,end2)==1){
//                     count++;
//                     return 1;
//                 }
//             }
//         }
//     }

//     return 0;
// }

int main(){
    int x1,y1,x2,y2;
    //int num[109][109];

    scanf("%d %d %d %d",&x1,&y1,&x2,&x2);

    minl(x1,y1,x2,y2);
    
    return 0;
}