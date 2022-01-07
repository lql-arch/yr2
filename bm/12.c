#include<stdio.h>

int main(){
    int t=0;
    scanf("%d",&t);
    int n,k;
    for(int i=0;i<t;i++){
        scanf("%d %d",&n,&k);  
        if(n<=k){
            printf("%d\n",k-n);
        }
        if(n>k){
            if((n-k)%2==0){//(n-k)&1==0
                printf("0\n");
            }else{
                printf("1\n");
            }
        }
    }
    return 0;
}