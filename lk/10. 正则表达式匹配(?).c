#include<stdbool.h>

// bool isMatch(char * s, char * p){
//     int plen = strlen(p);
//     int slen = strlen(s);

//     if (plen==2)
//     {
//         if (p[0]=='.' && p[1]=='*')
//         return true;
//     }
//     int status=0;
//     int k=0;
//     bool flag =true;
//     int i,j;
//     int count=1;

//     for (i=0,j=0;i<slen && j<plen;i++)
//     {
//         count=0;
//         if(s[i]!=p[j] && p[j]!='.')
//         {
//             if(j + 1 < plen && p[j+1]=='*' )
//             {
//                 k++;
//                 j+=2;
//                 i--;
//                 if(plen-j != slen-i)
//                     status=1;
//             }
//             else
//             {
//                 return false;
//             }
//         }
//         else
//         {
//             if(j + 1 < plen && p[j+1]=='*' )
//             {
//                 j+=2;
//                 while( i+1< slen && s[i]==s[i+1])
//                 {
//                     i++;
//                     count++;
//                 }
//                 while( j<plen && p[j] == p[j+1])
//                 {
//                     j++;
//                     count--;
//                     if(count<=1)
//                     {
//                         break;
//                     }
//                 }
//                 status=1;
//             }
//             else
//             {
//                 j++;
//             }
//         }

//     }
//     if(status == 0 && slen!=plen)
//     {
//         flag = false;
//     }

//     if(i>=slen-1 && j>=plen-1)
//         return flag;
//     else
//         return false;
// }