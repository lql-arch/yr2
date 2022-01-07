#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int a;
    int b;
}Node;

int cmp(const void *p1,const void *p2){
    Node *m=(Node*)p1;
    Node *n=(Node*)p2;
    return m->b - n->b;
}

int main(){
    int n=0;
    scanf("%d",&n);
    Node node[n];

    for(int i=0;i<n;i++){
        scanf("%d %d",&node[i].a,&node[i].b);
    }
    qsort(node,n,sizeof(node[0]),cmp);
    int cnt=0;
    int tine=0;
    for(int i=0;i<n;i++){
        if(node[i].a>time){
            cnt++;
            time=node[i].b;
        }
    }

    printf("%d\n",cnt);

    return 0;
}