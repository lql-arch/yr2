 #include<stdio.h>
// int i;
// int main(int argc, char *argv[])
// {
//     i--;
//     if (i > sizeof(i))
//     {
//         printf(">\n");
//     }
//     else
//     {
//         printf("<\n");
//     }
//     printf("%d\n",sizeof(i));
//     return 0;
// }
//
// #define A 2 + 2
// #define B 3 + 3
// #define C A * B
// int main(int argc, char *argv[])
// {
//     printf("%d\n", C);
//     return 0;
// }

// int main(int argc, char *argv[])
// {
//     char str[] = "Welcome to XiyouLinuxGroup";
//     printf("%zu %zu\n", strlen(str), sizeof(str));
//     return 0;
// }

// void fun()
// {
//     int x = 0;
//     static int num = 0;
//     for (int i = 0; i < 5; i++)
//     {
//         x++;
//         num++;
//     }
//     printf("x = %d num = %d\n", x, num);
// }
// int main(){
//     fun();
//     fun();
// }

// int main(int argc, char *argv[])
// {
//     int number;
//     unsigned mask;
//     mask = 1u << 31;
//     printf("%lu\n",mask);
//     scanf("%d", &number);
//     while (mask)
//     {
//         printf("%d", (number & mask) ? 1 : 0);
//         mask >>= 1;
//     }
//     return 0;
// }

// int main(int argc, char *argv[])
// {
//     char *str = "Xiyou Linux Group";
//     printf("%c\n", *str + 1);
//     return 0;
// }

// int main(int argc, char *argv[])
// {
//     double a = 3.14;
//     float b = a;
//     if ((float)a == b)
//     {
//         printf("Xiyou");
//     }
//     if (a != b)
//     {
//         printf("LinuxGroup\n");
//     }
//     return 0;
// }

// #include<stdio.h>
// #include<math.h>
// int main(){
//     double a=1.14;
//     double b=0.9+0.24;
//
//     if(fabs(a-b)<0.00000001){
//         printf("True\n");
//     }else{
//         printf("False\n");
//     }
//
//     return 0;
// }

// int main(int argc, char *argv[])
// {
//     int a[6] = {0x6f796958, 0x694c2075, 0x2078756e, 0x756f7247, 0x30322070,0};
//     printf("%d\n", printf("%s", (char *)a));
//     return 0;
// }

// int main(){
//     int num = 0x12345678;
//     char cs = *(char*)&num;
//
//     // 低地址处是高字节，则为大端
//     if ( cs == 0x12 )    
//         printf("大端");
//     else{
//         printf("小端");
//     }
// }

// int main(int argc, char *argv[])
// {
//     int a[2][3] = {{5, 7}, {5, 2}};
//     int b[2][3] = {5, 7, 5, 2};
//     int c[2][2] = {{5, 7}, {5, 2}};
//     int d[2][2] = {5, 7, 5};
//     //printf("%d %d\n", a[1][0], b[1][1]);
//     // printf("%d %d\n", c[1][1], d[1][1]);
//     printf("%p %p\n",&a[0][2],&a[1][0]);
//     return 0;
// }

// int main(int argc, char *argv[])
// {
//     int a = 1;
//     printf("%d\n", *(char *)&a);
// }

// int main(int argc, char *argv[])
// {
//     /*const*/ char a[] = "XiyouLinux\0";
//     char *b = "XiyouLinux\0";
//     a[5] = '\0';
//     //b[5] = '\0';
//     printf("%s\n", a);
//     //printf("%s\n",b);
//     return 0;
// }

// void sort(int arr[], int size)
// {
//     int i, j, tmp;
//     for (i = 0; i < size - 1; i++)
//     {
//         for (j = 0; j < size - i - 1; j++)
//         {
//             if (arr[j] > arr[j + 1])
//             {
//                 tmp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = tmp;
//             }
//         }
//     }
// }

// int main(){
//     int num = 0x12345678;
//     char cs = (char)num;
//
//     // 低地址处是高字节，则为大端
//     if ( cs == 0x12 )    
//         printf("大端");
//     else{
//         printf("小端");
//     }
// }