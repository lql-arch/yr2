#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int time;
    char name[101];
}node; 

void _qsort(node *ke,int start,int end){
    if(start>end){
        return ;
    }
    node temp=ke[start];
    int i=start;
    int j=end;
    while(i!=j){
        while(ke[j].time>=temp.time&&j>i){
            j--;
        }
        while(ke[i].time<=temp.time&&j>i){
            i++;
        }
        if(j>i){
            node t=ke[i];
            ke[i]=ke[j];
            ke[j]=t;
        }
    }
    ke[start]=ke[i];
    ke[i]=temp;
    _qsort(ke,start,i-1);
    _qsort(ke,i+1,end);
}

int main(){
    int n=0;
    scanf("%d",&n);
    node kemmu[n];
    for(int i=0;i<n;i++){
        scanf("%s %d",&kemmu[i].name,&kemmu[i].time);
    }
    _qsort(kemmu,0,n-1);
    for(int i=0;i<n;i++){
        printf("%s\t",kemmu[i].name);
    }
    printf("\n");
    return 0;
}