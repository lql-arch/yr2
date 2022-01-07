// #include<stdio.h>
// typedef struct {
//     int a;
//     char b;
//     double c;
//     char d[7];
// }A;
// typedef struct{
//     char b;
//     double c;
//     int a;
//     char d[7];
// }B;

// typedef struct {
//     int a;
//     short b;
//     double c;
//     char d;
// }C;

// int main(){
//     A A1;
//     B B1;
//     C c;
//     printf("A=%d\nB=%d\n%d\n",sizeof(A1),sizeof(B1),sizeof(c));
//     printf("%p\t%p\t%p\t%p\n",&A1.a,&A1.b,&A1.c,&A1.d);
//     printf("%p\t%p\t%p\t%p\n",&B1.a,&B1.b,&B1.c,&B1.d);

//     return 0;
// }

// // 计算机是以字节（Byte）为单位划分的，理论上来说CPU是可以访问任一编号的字节数据的，我们又知道CPU的寻址其实是通过地址总线来访问内
// // 存的，CPU又分为32位和64位，在32位的CPU一次可以处理4个字节（Byte）的数据，那么CPU实际寻址的步长就是4个字节，也就是只对编号是4的
// // 倍数的内存地址进行寻址。同理64位的CPU的寻址步长是8字节，只对编号是8的倍数的内存地址进行寻址,
