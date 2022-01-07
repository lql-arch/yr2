#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// 5 5
// Z****
// *****
// **#**
// *****    
// ****W

//2 2
//ZW
//**

// 6 6 
// **Z***
// ******
// ******
// ******
// ******
// ***W**


int dirs[4][2]={{1,1},{1,-1},{-1,1},{-1,-1}};
int count=1;


//dfs(question)
// int k=0;

// int  find(int num[][1002],int *pos,int *end,int *lastp){
//     if(pos[0]==end[0] && pos[1]==end[1]){
//         return 1;
//     }
//     for(int i=0;i<4;i++){//四个方向,小心死循环
//         int nextp[2]={pos[0]+dirs[i][0],pos[1]+dirs[i][1]};
//         if(lastp[0]==nextp[0]&&lastp[1]==nextp[1]){
//             //还要判断是否走了四方
//             //if()
//             num[lastp[0]][lastp[1]]=0;//封闭死路 
//         }
//         if(num[nextp[0]][nextp[1]]==1){//判断是否可行
//             if (find(num,nextp,end,pos)==1){
//                 count++;
//                 return 1;
//             }
//         }
//     }
//     return 0;
// }

//bfs

typedef struct {
    int x,y,bits;
}node; 

int find(int num[][1002],int *start,int *end){
    
}

int main(){
    int n,m;
    int a,b;
    int z,d;
    scanf("%d %d",&n,&m);

    char s[n][m];
    for(int i=0;i<m;i++){
        scanf("%s",&s[i]);
    }
    int num[1002][1002];//四周围一圈0
    memset(num,0,sizeof(num));
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            switch (s[i][j]){
                case 'Z':
                    num[i+1][j+1]=1;
                    a=i+1;
                    b=j+1;
                    break;
                case '#':
                    num[i+1][j+1]=0;
                    break;
                case '*':
                    num[i+1][j+1]=1;
                    break;
                case 'W':
                    num[i+1][j+1]=1;
                    z=i;
                    d=j;
                    break;
                default :
                    break;
            }
        }
    }
    // for(int i=0;i<n+2;i++){
    //     for(int j=0;j<m+2;j++){
    //         printf("%d ",num[i][j]);
    //     }
    //     printf("\n");
    // }
    int start[2]={a,b};
    int end[2]={z,d};
    find(num,start,end);
    
    // if(flag==0)
    //     printf("-1\n");
    // else
    //     printf("%d\n",count);

    return 0;
}
 