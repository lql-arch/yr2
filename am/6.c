#include<stdio.h>

int main(){
    int t=0;
    int n,c;
    int a,b;
    int max=0;
    int count=0;
    scanf("%d",&t);
    
    for(int k=0;k<t;k++){
        count=0;
        scanf("%d %d",&n,&c);
        for(a=0;a<=n/2;a++){
            b=n-a;
            if((a%c+b%c)==c){
                count++;
            }
        }
        count*=2;
        if(count==0){
            printf("-1\n");
        }else{
            printf("%d\n",count);
        }  
    }

    return 0;
}