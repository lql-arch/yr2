// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>

// typedef struct{
//     int u;
//     int v;
//     int w;
// }node; 

// int cmp(const void *p1,const void *p2){
//     node* n=(node*)p1;
//     node* m=(node*)p2;
//     return n->u - m->u;
// }

// int main(){
//     int t=0;
//     scanf("%d",&t);
//     for(int k=0;k<t;k++){
//         int n=0;
//         scanf("%d",&n);
//         node lu[1000];
//         int city[1000];
//         for(int i=0;i<n-1;i++){
//             scanf("%d %d %d",&lu[i].u,&lu[i].v,&lu[i].w);           
//         }
//         int lujin=0;
//         int cnt=0;
//         qsort(lu,n-1,sizeof(lu[0]),cmp);
        
//         int i=0;
//         while(lu[i].u==1){
//             int next=lu[i].v;
            
//             i++;
//         }
        
//     }

    
// }