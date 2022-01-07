// #include<stdio.h>

// int main(){
//     char str[200];
//     char ch;
//     int i=0;
//     int count=0;
    
//     while ((ch=getchar())!='\n')
//     {
//         str[i++]=ch;
//         count++;
//         for(int k=0;k<i-1;k++){
//             if(ch==str[k]){
//                 count--;
//                 break;
//             }
//         }
//     }
//     for(int k=0;k<i-1;k++){
//         for(int j=k+1;j<i;j++){
//             if(str[k]!=str[j]){
//                 count++;
//             }
//             for(int l=k+1;l<j;l++){
//                 if(str[l]==str[j]){
//                     count--; 
//                     break;
//                 }
//             }
//         }
//     }

//     printf("%d\n",count);

// }