// // #include<stdio.h>
// // #include<string.h>
// // char Ch(char a){
// //     if(a==')') return '(';
// //     if(a==']') return '[';
// //     if(a=='}') return '{';
// //     return 0;
// // }

// // int match(char* str){
// //     //根据题意，就不考虑字符串为空了
// //     int n=strlen(str);
// //     char a[n+1];
// //     if(n%2==1){
// //         return 0;
// //     }
// //     int m=0;
// //     for(int i=0;i<n;i++){
// //         char ch=Ch(str[i]);
// //         if(ch){
// //             if(m==0||a[m-1]!=ch){
// //                 return 0;
// //             }
// //             m--;
// //         }else{
// //             a[m++]=str[i];
// //         }
// //     }
// //     return  m==0;

// // }

// #include<stdio.h>
// #include<string.h>
// char left(char s){
//     if(s==')'){
//         return '(';
//     }
//     if(s==']'){
//         return '[';
//     }
//     if(s=='}'){
//         return '{';
//     }
//     return 0;
// }
// int match(char*str){
//     int l=strlen(str);
//     if(l%2!=0){
//         return 0;
//     }
//     char arr[l+1];
//     memset(arr,0,l+1);
//     int k=0;
//     char ch;
//     for (int  i = 0; i < l; i++)
//     {   
//         ch=left(str[i]);
//         if(ch){
//             if(k==0||ch!=arr[k-1]){
//                return 0;
//             }
//            k--;
//         }else{
//            arr[k++]=str[i];
//         }
//     }
//     return k==0;
// }

// int main(){
//     char*str="{[()]()}";
//     int bool=match(str);
//     printf("%d\n",bool);

//     return 0;
// }