#include<stdio.h>
#include<stdlib.h>
// int main(int argc, char *argv[]) {
//     for (unsigned int i = 3; i >= 0; i--)
//     putchar('=');
// }

// int main(){
//     int c = a; a = b ; b = c;
//     //a = a - b; b = b + a; a = b - a;
//     //a ^= b ; b ^= a ; a ^= b;
// }

// int main() {
//     static int a = 0;
//     int b = 0;
//     printf("%d, %d\n", ++a, ++b);
// }

// int main(void) {
//     printf("%d\n", printf("Xiyou Linux Group2%d", printf("")));
// }

// int main(int argc, char *argv[]) {
//     char ch = 128;
//     int d = 'a' + 1;
//     printf("%c %d", ch, d);
// }

// int main(int argc, char *argv[]) {
//     char x = -2, y = 3;
//     int a=0,b=0;
//     int c=(++a) || (b++);
//     char t = (++x) | (y++);
//     printf("%d\n",c);
//     printf("x = %d, y = %d, t = %d\n", x, y, t);
//     t = (++x) || (y++);
//     printf("x = %d, y = %d, t = %d\n", x, y, t);
// }

// int main(){
//     int val = 2018;
//     int *pi = 2019;
//     printf("%p\n",pi);
//     pi = &val;
//     *pi = 0;
//     printf("%d\n",val);
// }

// int main(int argc, char *argv[]) {
//     char *p = (char *)malloc(sizeof(char) * 20),
//     *q = p;
//     scanf("%s %s", p, q);
//     printf("%s %s\n", p, q);
// }

// int main(int argc, char *argv[]) {
//  int a[4] = { 2, 0, 1, 9 };
//  printf("%p, %p\n", a, &a);
//  printf("%p, %p\n", a + 1, &a + 1);
// }

// int fb(int num){
//     if(num==1||num==2){
//         return 1;
//     }
//     if(num>2){
//         return fb(num-1)+fb(num-2);
//     }
// }

// int main(){
//     int num=0;
//     scanf("%d",&num);
//     num=fb(num);
//     printf("%d",num);
//
//     return 0;
// }

// int main(int argc, char *argv[]) {
//     int nums[6] = { 6, 3, 2, 4, 5, 1 };
//     for (int i = 0; i < 6; i++) {
//         for (int j = i; j < 6; j++) {
//             if (nums[i] > nums[j]) {
//                 int c = nums[i];
//                 nums[i] = nums[j];
//                 nums[j] = c;
//             }
//         }
//     }
// }

// int main(int argc, char *argv[]) {
//     int nums[6] = { 6, 3, 2, 4, 5, 1 };
//     for(int i=0;i<6-1;i++){
//         int max=i;
//         for(int j=i+1;j<6;j++){
//             if(nums[j]>nums[max]){
//                 max=j;
//             }
//         }
//         if(max!=i){
//             // int temp=nums[max];
//             // nums[max]=nums[i];
//             // nums[i]=temp;
//             nums[max]^=nums[i];
//             nums[i]^=nums[max];
//             nums[max]^=nums[i];
//         }
//     }
//     for(int i=0;i<6;i++){
//         printf("%d ",nums[i]);
//     }
//     printf("\n");
// }

// int main(){
//     int nums[6] = { 6, 3, 2, 4, 5, 1 };
//     for(int i=1;i<6;i++){
//         for(int j=i-1;j>=0&&nums[j]<nums[j+1];j--){
//             nums[j]^=nums[j+1];
//             nums[j+1]^=nums[j];
//             nums[j]^=nums[j+1];
//         }
//     }
// }

// int main(){
//     int nums[6] = { 6, 3, 2, 4, 5, 1 };
//     int l=sizeof(nums)/sizeof(int);
//     for(int i=l/2;i>0;i/=2){
//         for(int j=i;j<l;j++){
//             int temp=nums[j];
//             int k=j-i;
//             while(k>=0&&nums[k]>temp){
//                 nums[k+i]=nums[k];
//                 k=k-i;
//             }
//             nums[k+i]=temp;
//         }
//     }
//     for(int i=0;i<6;i++){
//         printf("%d ",nums[i]);
//     }
//     printf("\n");
// }

