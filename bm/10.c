#include<stdio.h>

int main(){
    int t=0;
    int num[2000];
    scanf("%d",&t);
    for(int k=0;k<t;k++){
        int n=0;
        int flag=0;
        scanf("%d",&n);
        for(int j=0;j<n;j++){
            scanf("%d",&num[j]);
        }
        for(int i=0;i<n-1;i++){
            if(num[i]<=num[i+1]){
                flag=1;
                break;
            }
        }
        if(flag) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}