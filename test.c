#include<stdio.h>
#include<string.h>
// #include<stdlib.h>
// int main()
// {
//     const char *str="dasfasf";
//     //str=(char*)malloc(8);
//     int i=strlen(str);
//     while(i>0)
//     {
//         char ch=str[1];
//         printf("%c\t%c\n",ch,*str);
//         str ++;
//         i--;
//     }
// }

 #include<string.h>
#include<stdio.h>
int main(void)
{
    char input[16]="   abc d";
    char*p;
    /*strtok places a NULL terminator
    infront of the token,if found*/
    p=strtok(input," ");
    while(p)
    {
        printf("%s\n",p);
        /*Asecond call to strtok using a NULL
        as the first parameter returns a pointer
        to the character following the token*/
    p=strtok(NULL," ");
    }
    return 0;
 
}

// #include <stdio.h>  
// #include <stdlib.h>  
// #include <string.h>  
  
// int main()  
// {  
//     char str[]="ab,cd,ef";  
//     char *ptr;  
//     char *p;  
//     printf("before strtok:  str=%s\n",str);  
//     printf("begin:\n");  
//     ptr = strtok_r(str, ",", &p);  
//     while(ptr != NULL){  
//         printf("str=%s\n",str);  
//         printf("ptr=%s\n",ptr);  
//         ptr = strtok_r(NULL, ",", &p);  
//     }  
//     return 0;  
// }