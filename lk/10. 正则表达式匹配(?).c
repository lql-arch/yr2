#include<stdbool.h>

bool isMatch(char * s, char * p){
    int plen = strlen(p);
    int slen = strlen(s);

    if (plen==2)
    {
        if (p[0]=='.' && p[1]=='*')
        return true;
    }
    bool flag =true;
    int i,j;
    int count=0;

    for (i=0,j=0;i<slen && j<plen;i++)
    {
        count=0;
        if(s[i]!=p[j] && p[j]!='.')
        {
            if(j + 1 < plen && p[j+1]=='*' )
            {
                j+=2;
                i--;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(j + 1 < plen && p[j+1]=='*' )
            {
                j+=2;
                while(s[i]==s[i+1])
                {
                    i++;
                    count++;
                }
                if(count>=2)
                {
                    while (i<slen && s[i++] == s[i-1] && count>0)
                    {
                        count--;
                    }
                }
                flag = true;
            }
            else
            {
                j++;
            }
        }

    }
    if(i>=slen && j>=plen)
        return flag;
    else
        return false;
}