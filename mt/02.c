// #include<stdio.h>
// #include<stdlib.h>
// // void func(int arr[][10][20]){//必须知道一维和二维的数值
// //     for(int i=0;i<5;i++){
// //         for(int j=0;j<10;j++){
// //             for(int k=0;k<20;k++){
// //                 arr[i][j][k]=rand()%100+1;
// //             }
// //         }
// //     }
// // }
// void func(int (*arr)[10][20]){
//     for(int i=0;i<5;i++){
//         for(int j=0;j<10;j++){
//             for(int k=0;k<20;k++){
//                 arr[i][j][k]=rand()%100+1;
//             }
//         }
//     }
// }
// // void func(int l,int m,int n,int arr[l][m][n]){
// //     for(int i=0;i<l;i++){
// //         for(int j=0;j<m;j++){
// //             for(int k=0;k<n;k++){
// //                 arr[i][j][k]=rand()%100+1;
// //             }
// //         }
// //     }
// // }

// // void print(int arr[][10][20]){//输出方式一
// //     for(int i=0;i<5;i++){
// //         for(int j=0;j<10;j++){
// //             for(int k=0;k<20;k++){
// //                 printf("%d ",arr[i][j][k]);
// //             }
// //             printf("\n");
// //         }
// //         printf("\n");
// //     }
// // }

// void print(int (*arr)[10][20]){//输出方式二
//     for(int i=0;i<5;i++){
//         for(int j=0;j<10;j++){
//             for(int k=0;k<20;k++){
//                 //printf("%d ",arr[i][j][k]);
//                 printf("%d ",*(*(*(arr+i)+j)+k));
//             }
//             printf("\n");
//         }
//         printf("\n");
//     }
// }

// int main(){
//     int l=5,m=10,n=20;
//     int arr[l][m][n];
//     //func(l,m,n,arr);
//     func(arr);
//     print(arr);

//     return 0;
// }