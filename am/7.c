////算牌王
// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>

// int cmp(const void *a,const void *b){
//     return (*(int*)a-*(int*)b);
// }

// void arr(char *str,int count,int *num,int n){//将字符串转化为数组
//     for(int j=0;j<n;j++){
//             switch (str[j]) {
//                 case 'A':
//                     num[j]=14;
//                     break;
//                 case '2':
//                     num[j]=15;
//                     break;
//                 case 'K':
//                     num[j]=13;
//                     break;
//                 case 'Q':
//                     num[j]=12;
//                     break;
//                 case 'J':
//                     num[j]=11;
//                     break;
//                 case '0':
//                     num[j]=10;
//                     break;
//                 default :
//                     num[j]=str[j]-'0';
//                     break;
//             }
//         }
//     qsort(num,n,sizeof(int),cmp);
// }

// int shunzi(int*num,int k,int begin){//计算顺子（递归）
//     if(k==begin+4){
//         return 1;
//     }
//     if(num[k]+1==num[k+1]){
//         k++;
//         if(shunzi(num,k,begin)){
//             return 1;
//         }
//     }
//     return 0;
// }

// int jishu(int*num,int count,int len){//计算单个牌和对子，三条，炸弹
//     int k=0;
//     count=len;
//     for(int i=0;i<len-1;i++){
//         for(int j=i+1;j<len;j++){
//             if(num[i]==num[j]){
//                 count--;
//                 break;
//             }
//         }
//     }
//     int duizi=0;
//     int santiao=0;
//     // 记得记录对子()
//     while(k<len){
//         if(num[k]==num[k+1]){
//             count++;
//             k++;
//             duizi++;
//             if( (k+1)<len && num[k]==num[k+1]){
//                 count++;
//                 k++;
//                 santiao++;
//                 if((k+1)<len && num[k]==num[k+1]){
//                     count++;
//                     k++;
//                 }
//             }
//         }
//         k++;
//     }
//     for(int i=0;i<santiao;i++){//计算葫芦（三条+对子）
//         for(int j=0;j<duizi-1;j++){
//                 count++;
//         }
//     }

//     return count;
// }

// int Szsort(int *num,int len){//计算顺子所需要的排序
//     int l=0;
//     int l_t=1;//相同数
//     for(int i=0;i<len-1;i+=l_t){
//         l_t=1;
//         for(int j=i+1;j<i+3&&j<len;j++){
//             if(num[i]==num[j]){
//                 l_t++;
//                 if(num[j]!=20){
//                     l++;           
//                 }
//                 num[j]=20;
//             }
//         }
//     }
//     qsort(num,len,sizeof(int),cmp);
//     len-=l;

//     return len;
// }

// int ShunZi(int *num,int len){//计算顺子
//     int count=0;
//     len=Szsort(num,len);

//     int k=0;
//     while(k<len){
//         if((k+4)<len && num[k+4]!=15 && num[k]!=15)
//             if(shunzi(num,k,k)){
//                 count++;
//             }
//         k++;
//     }
//     return count;
// }

// int main(){
//     int n=0;
//     char str[10000][14];
//     int count=0;
//     int l=0;

//     scanf("%d",&n);
//     getchar();
//     for(int i=0;i<n;i++){
//         count=0;
//         scanf("%s",str[i]);

//         l=strlen(str[i]);
//         int *num;
//         num=(int*) malloc(sizeof(int)*l);
//         memset(num,0,sizeof(int)*l);
//         arr(str[i],count,num,l);

//         count+=jishu(num,count,l);
//         count+=ShunZi(num,l);

//         printf("%d\n",count);
//         free(num);
//     }

// }