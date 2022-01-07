#include<stdio.h>
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int num[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&num[i][j]);
        }
    }
    int q=0;
    scanf("%d",&q);
    int arr[q][8];
    for(int i=0;i<q;i++){
        for(int j=0;j<8;j++){
            scanf("%d",&arr[i][j]);
        }
    }
    int sum=0;
    for(int k=0;k<q;k++){
        sum=0;
        for(int i=arr[k][0];i<=arr[k][2];i++){
            for(int j=arr[k][1];j<=arr[k][3];j++){
                sum+=num[i-1][j-1];
                num[i-1][j-1]=0;
            }
        }
        for(int i=arr[k][4];i<=arr[k][6];i++){
            for(int j=arr[k][5];j<=arr[k][7];j++){
                sum+=num[i-1][j-1];
            }
        }
        printf("%d\n",sum);
    }
    return 0;
}