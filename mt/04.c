// #include<stdio.h>

// void intobit(int num)
// /*
// num是要以二进制形式输出的int值
// 将二进制数据逐个置1，在右移，依次实现逐个输出
// */
// {
//     int i;
//     for(i=31;i>=0;i--)//int类型下一共32位
//     {
//         int tnum=num;
//         tnum=num&(1<<i);
//         //((i+1)%8==0&&i!=31)?printf(" %d",tnum>>i):printf("%d",tnum>>i);
//         printf("%d",tnum>>i);
//         if(i%8==0){
//             printf(" ");
//         }
//     }
//     printf("\n");
// }

// int main(){
//     int num=0;
//     scanf("%d",&num);
//     (num);

//     return 0;
// }


// #define swap(x,y) do{int temp=x;x=y;y=temp;}while(0)
// int main(){
//     int a=1;
//     int b=2;
//     swap(a,b);
//     printf("%d %d",a,b);
//     printf("\n");
//     return 0;
// }