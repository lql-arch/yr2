#include<stdio.h>

int main(){
    int t=0;
    scanf("%d",&t);

    for(int i=0;i<t;i++){
        long long a,b,sum;
        scanf("%lld %lld",&a,&b);
        sum=a+b;
        printf("%lld\n",sum);
    }

    return 0;
}