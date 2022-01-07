// #include<stdio.h>
// #include<string.h>
// int k=1;

// void _find(int n,int m,int hang,int lie,int num[n][m],char str[n][m]);

// void substitution(int n,int m,int num[n][m],char str[n][m]){
//     for(int i=0;i<n;i++){
//         for(int j=0;j<m;j++){
//             if(str[i][j]=='.'){
//                 num[i][j]=0;
//             }
//             if(str[i][j]=='*'){
//                 if(num[i][j]==0){
//                     num[i][j]=k;
//                     _find(n,m,i,j,num,str);
//                     k++;
//                 }                
//             }
//         }
//     }
//     return ;
// }

// void _find(int n,int m,int hang,int lie,int num[n][m],char str[n][m]){
//     for(int i=hang;i<n;i++){
//         if(str[i][lie]=='*'){
//             num[i][lie]=k;
//         }
//         if(str[i][lie]=='.'){
//             break;
//         }
//     }
//     for(int i=lie;i<m;i++){
//         if(str[hang][i]=='*'){
//             num[hang][i]=k;
//         }
//         if(str[hang][i]=='.'){
//             break;
//         }
//     }
//     return ;
// }

// void minLaser(int n,int m,int num[n][m]){
//     int minL=0;//最小次数
//     for(int i=0;i<n;i++){
//         for(int j=0;j<m;j++){
//             if(minL<num[i][j]){
//                 minL=num[i][j];
//             }
//         }
//     }
//     printf("%d\n",minL);
// }
// int main(){
//     int n,m;
//     scanf("%d %d",&n,&m);
    
//     char str[n][m];

//     for(int i=0;i<n;i++){
//         scanf("%s",&str[i]);
//     }
//     int num[n][m];
//     memset(num,0,sizeof(num));
    
//     substitution(n,m,num,str);
//     for(int i=0;i<n;i++){
//         for(int j=0;j<m;j++){
//             printf("%d ",num[i][j]);
//         }
//         printf("\n");
//     }
    
//     minLaser(n,m,num);

//     return 0;
// }