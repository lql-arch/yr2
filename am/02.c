// #include<stdio.h>

// int cmp(const void *a,const void *b){
//     return *(int*)a-*(int*)b;
// }

// struct lianjie {
//     int arr;
//     char s;
// };
// int main(){
//     char str[4][2][5]={{"10110","11001"},{"10001","00110"},
//     {"01101","11001"},{"01010","11001"}};
    
//     int num[4][2];
//     struct lianjie l[4];
//     for(int i=0;i<4;i++){
//         for(int j=0;j<2;j++){
//             num[i][j]=(str[i][j][0]-'0')*16+(str[i][j][1]-'0')*8+(str[i][j][2]-'0')*4+(str[i][j][3]-'0')*2+(str[i][j][4]-'0')*1;
//         }
//         l[i].arr=num[i][0]^num[i][1];
//     }
//     //qsort(arr,4,sizeof(int),cmp);
//     for(int i=0;i<4;i++){
//         printf("%c",(char)l[i].arr+65);
//     }
//     printf("\n");
// }