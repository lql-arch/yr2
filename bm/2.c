#include<stdio.h>

void find(int n,int m,int num[n][m],int h);

int main(){
    int n,m,h;
    int a,b,z,d;
    scanf("%d %d %d",&n,&m,&h);
    char s[n][m];
    for(int i=0;i<m;i++){
        scanf("%s",&s[n]);
    }
    int num[n][m];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            switch(s[i][j]){
            case '*':
                num[i][j]=1;
                break;
            case '#':
                num[i][j]=0;
                break;
            case 's':
                num[i][j]=1;
                a=i;
                b=j;
                break;
            case 'e':
                num[i][j]=1;
                z=i;
                d=j;
                break;
            case 'm':
                num[i][j]=-1;
                break;
            case '0':
                num[i][j]=3;
                break;
            case '1':
                num[i][j]=4;
                break;
            case '2':
                num[i][j]=5;
                break;
            case '3':
                num[i][j]=6;
                break;
            case '4':
                num[i][j]=7;
                break;
            case '5':
                num[i][j]=8;
                break;
            case '6':
                num[i][j]=9;
                break;
            case '7':
                num[i][j]=10;
                break;
            case 'A':
                num[i][j]=-3;
                break;
            case 'B':
                num[i][j]=-4;
                break;
            case 'C':
                num[i][j]=-5;
                break;
            case 'D':
                num[i][j]=-6;
                break;
            case 'E':
                num[i][j]=-7;
                break;
            case 'F':
                num[i][j]=-8;
                break;
            case 'G':
                num[i][j]=-9;
                break;
            case 'H':
                num[i][j]=-10;
                break;
            default:
                break;
            }
        }        
    }
    find(n,m,num,h);

    return 0;
}

void find(int n,int m,int num[n][m],int h){
    int 
}