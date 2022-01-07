#include<stdio.h>

int main(){
    int t=0;
    int n,k;
    int arr[100]={0};

    scanf("%d",&t);
    for(int i=0;i<t;i++){
        char s[400];
        int m=0;
        scanf("%d %d",&n,&k);
        for(int j=0;j<n;j++){
            int num=0;
            scanf("%d",&arr[j]);

            arr[j]=arr[j]^k;
            
            num=arr[j]%256;
            arr[j]>>=8;
            s[m]=num;

            num=arr[j]%256;
            arr[j]>>=8;
            s[m+1]=num;

            num=arr[j]%256;
            arr[j]>>=8;
            s[m+2]=num;

            num=arr[j];
            s[m+3]=num;

            m+=4;
        }
        printf("%s\n",s);
    }

    return 0;
}