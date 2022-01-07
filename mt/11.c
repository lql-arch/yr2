#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
// struct A {
//     long a;
//     int b;
// };
// int main(int argc, char* argv[])
// {
//     struct A num = {0x6e694c756f796978,0x7875};//,0x7875
//     printf("%p,%p\n",&num.a,&num.b);
//     char ch = '0';
//     for(int i = 0; ch; i++)
//     {
//         ch = *((char *)&num + i);
//         printf("%c ",ch);
//     }
//     printf("\n");
//     return 0;
// }
// int main(){
//     int num=0x690078;
//     char ch='0';
//     for(int i = 0; ch; i++)
//     {
//         ch = *((char *)&num + i);
//         printf("%c",ch);
//     }
// }

// int main(int argc, char* argv[])
// {
//     const int b = 10;

// //1。
//     int*p=&b;
//     *p=2;
//     printf("%d\n",b);

// //2.
//     int a=*&b;
//     a=2;
//     printf("%d\n",b);
    
// //...

//     return 0;
// }

// struct node {
//     char a;
//     int b;
//     short c;
// };
// struct n {
//     char a;
//     int b;
// };
// int main(int argc, char* argv[])
// {
//     struct node a[2] = {{1,2,3},{4,5,6}};
//     *(int *)((char *)a + 2 * sizeof(struct n)) = 100;
//     // printf("%p %p &%p\n",&a->a,&a->b,&a->c);
//     // printf("%d %d %d\n",a->a,a->b,a->c);
//     printf("%d\n",*(int *)((char *)a + 2 * sizeof(struct n)));
    
//     printf("%d\n",*(int *)((char *)a + 2 * sizeof(struct n)));

//     return 0;
// }

// void func(char* a)
// {
//     printf("%lu\n", sizeof(a)) ;
//     printf("%lu\n", strlen(a)) ;
// }
// int main(int argc, char* argv[])
// {
//     char a[] = "hello world";
//     char* b = "hello world";
//     printf("%s\n", b);
//     func(a);
//     printf("%lu\n", sizeof(a));
//     printf("%lu\n", strlen(a));
//     return 0;
// }

// #define f(a,b) a##b
// #define g(a) #a
// #define h(a) g(a)
// int main(int argc, char* argv[])
// {
//     printf("%s\n", h(f(1,2)));
//     printf("%s\n", g(f(1,2)));
//     return 0;
// }


// int isaccord(double avge,double nums[],int size);
// #define MAX 20
// int main(){
//     int n=0;
//     double nums[MAX];
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//         scanf("%lf",&nums[i]);
//     }
    
//     for(int gap=n/2;gap>0;gap/=2){
//         for(int i=gap;i<n;i++){
//             double t=nums[i];
//             int j=i-gap;
//             while(j>=0&&nums[j]>t){
//                 nums[j+gap]=nums[j];
//                 j-=gap;
//             }
//             nums[j+gap]=t;
//         }
//     }
//     double sum=0,avge=0; 
//     for(int i=0;i<n;i++){
//         sum+=nums[i];
//     }
//     avge=sum/2;
    
//     int flag=isaccord(avge,nums,n);
//     if(flag==1){
//         printf("符合");
//     }else{
//         printf("不符合");
//     }

//     return 0;
// }

// int isaccord(double avge,double nums[],int size){
//     int flag=0;
//     double sum=0;
//     for(int i=0;i<size-1;i++){
//         sum=0;
//         for(int j=i;j<size;j++){
//             sum+=nums[j];
//             if(fabs(sum-avge)<0.0001){
//                 flag=1;
//                 return flag;
//             }
//         }     
//     }
//     return flag;
// }

// #include <stdio.h>
// #include <stdlib.h>
 
// int cmp(int* p1,int* p2)
// {
//     return *p1-*p2;
// }
// int main(void)
// {
//     int dg[100]={1,2,3,1,4,5,645,75,75,87,5678,785,76,76,4};
//     int sum=0,i=0,p1,p2,p3,j,judge=0;
//     while(dg[i])
//     {
//         sum+=dg[i];
//         i++;
//     }//i is sum_count 
//     qsort(dg,i,4,cmp);
//     if(sum%2==1)
//     {
//         printf("No");
//         return 0;
//     }
//     sum=sum/2;
//     for(p1=0;p1<i-2;p1++)
//     {
//         p2=p1;
//         p3=i-1;
//         while(p2<p3)
//         {
//             int sum1=0;
//             for(j=p2;j<=p3;j++)
//             sum1+=dg[j];
//             if(sum==sum1)
//             {
//                 judge=1;
//                 goto here;
//             }
//             else if(sum1 < sum)
//                 p2++;
//             else
//                 p3--;
//         }
//     }here:
//         if(judge)
//         printf("Yes");
//         else
//         printf("No");
//     return 0;
//  } 


// #define MAX 2 0
// int main(){
//     int n=0;
//     double nums[MAX];
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//         scanf("%lf",&nums[i]);
//     }
//     int sum=0,avge=0;

//     for(int i=0;i<n;i++){
//         sum+=nums[i];
//     }
//     avge=sum/2;



//     return 0;
// }

// void reversePrint(char*str);

// int main(){
//     char str[100];
//     //  hello  everyone, we are xiyou xiLinuxer 
//     gets(str);

//     reversePrint(str);

//     return 0;
// }

// void reversePrint(char*str){
//     int l=strlen(str);
//     for(int i=l-1;i>=0;i--){
//         if(str[i]!=' '){
//             str[i+1]='\0';
//             break;
//         }
//         l--;
//     }
//     for(int i=l-1;i>=0;i--){
//         if(str[i]==' '){
//             printf("%s",&str[i+1]);
//             if(str[i]!=str[i-1]){
//                 printf(" ");
//             }
//             if(str[i]==str[i-1]){
//                 str[i-1]='\0';
//             }
//             str[i]='\0';
//         }
//         if(i==0&&str[0]!=' '){
//             printf("%s\n",&str[i]);
//         }
//     }
// }

// int main(){
//   int i;
//   char str[81];
//   gets(str);
//   for (i = strlen(str) - 1; i >= 0; i--){
//   // 将所有的空格转化成打印字符穿的结束符
//     if (str[i] == ' '){
//       printf("%s", &str[i + 1]);
//       printf(" ");
//       str[i] = '\0';
//     }
//     // 当走到数组起始位置时候需要单独打印。
//     if (i == 0) printf("%s", &str[i]); 
//   }
//   return 0;
// }

// void func(char** p)
// {
//     *p = (char* )malloc(sizeof(char)*20);
//     if(p==NULL){
//         fprintf(stderr,"malloc error\n");
//         exit(2);
//     }
// }
// int main(int argc, char* argv[])
// {
//     char*s = NULL;
//     func(&s);
//     strcpy(s, "I love xiyou_linux");
//     puts(s);
//     return 0;
// }

// char* func(char* p)
// {
//     p = (char* )malloc(sizeof(char)*20);
//     if(p==NULL){
//         fprintf(stderr,"malloc error\n");
//         exit(2);
//     }
//     return p;
// }
// int main(int argc, char* argv[])
// {
//     char*s = NULL;
//     s=func(s);
//     strcpy(s, "I love xiyou_linux");
//     puts(s);
//     return 0;
// }


typedef struct node
{
    int val;
    struct node *next;
}Node;

// Node* reverse(Node*head){
//     if( head==NULL || head->next==NULL ){
//         return head;
//     }
//     Node* NewHead=reverse(head->next);

//     head->next->next=head;
//     head->next=NULL;//防止成环

//     return NewHead;
// }

// Node* reverse(Node*head){
//     //我想不到不用新节点的办法，最多是只使用中间变量。
//     Node*t1=NULL,*t2=NULL;
//     t1=head->next;
//     head->next=NULL;//截断
//     while(t1!=NULL){
//         t2=t1;
//         t1=t1->next;

//         t2->next=head;
//         head=t2;
//     }

//     return head;
// }

// void print(Node*head){
//     Node*d=head;
//     while(d!=0){
//         printf("%d ",d->val);
//         d=d->next;
//     }
//     printf("\n");
// }

// int main(){
//     Node*head=NULL;
//     Node*p;
//     Node*last=NULL;
//     int num=0;

//     do{
//         scanf("%d",&num);
//         if(num!=-1)
//         {
//             p=(Node*)malloc(sizeof(Node*));
//             p->val=num;
//             p->next=NULL;
//             if(head){
//                 last->next=p;
//             }
//             else{
//                 head=p;
//             }
//             last=p;
//         }
//     }while(num!=-1);

//     print(head);

//     head=reverse(head);
//     print(head);

//     return 0;
// }

// int main(int argc, char* argv[])
// {
//     char c = -1;
//     printf("%x\n", c);
//     printf("%x %d\n",(unsigned char)c, (unsigned char)c);
// }