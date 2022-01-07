#include<stdio.h>

int main(){
    int n=0;
    int num[1001];
    int sum=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&num[i]);
        sum^=num[i];
    }
    printf("%d\n",sum);
    return 0;
}