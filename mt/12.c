#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// int main(int argc , char *argv[]) {
//     unsigned char a = 255;
//     printf("%d\n",a);
//     char ch = 128;
//     a -= ch;    
//     printf("a = %d ch = %d\n", a, ch);
// }

// int main(int argc, char *argv[]) {
//     char *str = "Xi You Linux Group 20";
//     printf("%d\n", printf(str));
//     printf(str);
//     return 0;
// }

// int i = 2;
// void func() {
//     if(i != 0) {
//         static int m = 0;
//         int n = 0;
//         n++;
//         m++;
//         printf("m = %d, n = %d\n", m, n);
//         i--;
//         func();
//     }else{
//         return;
//     }
// }
// int main(){
//     func();
//     return 0;
// }

// int main(int argc, char * argv[]) {
//     char ch = 'A';
//     int i = 65;
//     unsigned int f = 33554433;
//     *(int *)&f >>= 24;
//     char a=-65;
//     printf("%d %d\n",*(int *)&f,'?');
//     *(int *)&f = *(int *)&f + '?';
//     printf("ch = %c i = %c f = %c\n", ch, i, *(int *)&f);
//     printf("%d\n",a);
//     return 0;
// }

// int main(int argc, char *argv[]) {
//     int a[2][2];
//     printf("&a = %p \t&a[0] = %p \t&a[0][0] = %p \n", &a, &a[0],&a[0][0]);
//     printf("&a+1 = %p \t&a[0]+1 = %p \t&a[0][0]+1= %p \n", &a+1,&a[0]+1, &a[0][0]+1);
//     printf("&a = %p \t&a[0] = %p \t&a[0][0]= %p \n", sizeof(a),sizeof(a[0]), sizeof(a[0][0]));
//     return 0;
// }

// int* get_array() {
//     static int array[1121];
//     for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
//     array[i] = i;
//     }
//     return array;
// }
// int main(int argc, char *argv[]) {
//     int *p = get_array();
// }

// int main(int argc, char *argv[]) {
//     char str[] = "XiyouLinuxGroup";
//     char *p = str;
//     char x[] = "XiyouLinuxGroup\t\106F\bamily";
//     printf("%zu %zu %zu %zu\n", sizeof(str), sizeof(p),sizeof(x), strlen(x));
//     return 0;
// }

// int add(int *x, int y) {
//     printf("%d %d\n",(*x^y),(*x&y)<<1);
//     return *x = (*x^y) + ((*x&y)<<1);
// }
// int a;
// int main(int argc, char *argv[]) {
//     int b = 2020;
//     if(add(&b, 1) || add(&a, 1)) {
//         printf("XiyouLinuxGroup%d\n", b);
//         printf("Waiting for y%du!\n", a);
//     }
//     if(add(&b, 1) && a++) {
//         printf("XiyouLinuxGroup%d\n", b);
//         printf("Waiting for y%du!\n", a);
//     }
// }

// void func() {
//     int a = 2020;
//     unsigned long c;
//     printf("%p\n", &a);
//     printf("我们想要修改的地址：");
//     scanf("%lx", &c);
//     printf("请随便输入一个数字：");
//     scanf("%d", (int *)c);
//     printf("a=%d\n",a);
// }
// int main(){
//     func();
//     return 0;
// }

// int main(){
//     puts((char*)(int const[]){
//     0X6F796958,0X6E694C75,0X72477875,
//     0X3270756F,0X313230,0X00000A
//     });
// }

// int main(int argc, char *argv[]) {
//     char str[1121];
//     int key;
//     char t;
//     fgets(str, 1121, stdin);
//     for(int i = 0; i < strlen(str) - 1; i++) {
//         key = i;
//         for(int j = i + 1; j < strlen(str); j++) {
//             if(str[key] > str[j]) {
//                 key = j;
//             }
//         }
//         t = str[key];
//         str[key] = str[i];
//         str[i] = t;
//     }
//     puts(str);
//     return 0;
// } 

// long recursive(int n){
//     if(n==1||n==2){
//         return 1;
//     }else{
//         return recursive(n-1)+recursive(n-2);
//     }
// }
// long loop(int n){
//     if(n == 1 || n == 2)    
//         return 1;
//     long a = 1, b = 1, temp;  
//     int i;
//     for(i = 3; i <= n; i++) {
//         temp = b;
//         b = a + b; 
//         a = temp;  
//     }
//     return b;
// }
// int main(){
//     int a=10;
//     scanf("%d",&a);
//     long int c=recursive(a);
//     printf("%ld\n",c);
//     long int b=loop(a);
//     printf("%ld\n",b);
//     return 0;
// }

// #include<stdio.h>
// #define max_n 1000
// int fib[3][max_n + 5] = {{0, 0}, {1, 1}, {1, 1}}; // 长度为3的二维数组
// int main(){
//     int n = 2;
//     while (fib[n % 3][0] < 1000) {
//         n += 1;
//         for (int i = 1; i <= fib[(n - 1) % 3][0]; ++i) { // 数组的第二个维度存的是每一项对应位上的数字,第二维的第一位当做基数器，存数字的位数
//             fib[n % 3][i] = fib[(n - 1) % 3][i] + fib[(n - 2) % 3][i]; // 对应位置上的数字相加
//         }
//         fib[n % 3][0] = fib[(n - 1) % 3][0];// 先用前面的一项的位数对当前项的位数进行初始化
//         for (int i = 1; i <= fib[n % 3][0]; ++i) { //处理进位
//             if (fib[n % 3][i] < 10) continue;
//             fib[n % 3][i + 1] += fib[n % 3][i] / 10;
//             fib[n % 3][i] %= 10;
//             fib[n % 3][0] += (i == fib[n % 3][0]);
//         }
//     }
//     printf("%d\n",n);
//     return 0;
// }


// int main(){   
//     int fib[3][1005]={{0,0},{1,1},{1,1}};//三个斐波那契数:f(n),f(n-1),f(n-2),各一维数组第一个位为位数计数。
//     int n=2;//n为第n位斐波那契数
//     while (n < 100) {
//         n += 1;
//         for(int i=1;i <= fib[(n - 1) % 3][0];i++){
//             fib[n%3][i]=fib[(n-1)%3][i]+fib[(n-2)%3][i];// 对应位置上的数字相加
//         }
//         fib[n%3][0]=fib[(n-1)%3][0];//将位数及时移动过来
//         for (int i = 1; i <= fib[n % 3][0]; ++i) { //处理进位
//                 if (fib[n % 3][i] < 10) continue;
//                 fib[n % 3][i + 1] += fib[n % 3][i] / 10;
//                 fib[n % 3][i] %= 10;
//                 fib[n % 3][0] += (i == fib[n % 3][0]);
//             }
//     }
//     for(int i=1;i<=fib[n % 3][0];i++){
//             printf("%d",fib[n%3][i]);
//     }
//     printf("\n");
// }

// int main(){

// }