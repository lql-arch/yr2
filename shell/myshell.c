#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void print_prompt(); 
void get_user_input(char *buf);
void mycd(char* buf);
void ex_input(char* buf);


int main(int argc, char **argv)
{
    int count=0;
    char* m_buf = NULL;

    m_buf = (char*)malloc(512);

    if(m_buf == NULL)
    {
        perror("Error:buf malloc");
        exit(-1);
    }

    while(1)
    {
        memset(m_buf, 0, 512);
        print_prompt();
        get_user_input(m_buf);
        if( strcmp(m_buf, "exit\n") == 0 )
        {
            break;
        }
        ex_input(m_buf);
        mycd(m_buf);

    }

    return 0;
}

void print_prompt()
{
    char *path=NULL;
    path = getcwd(NULL,0);
    int len = strlen(path);
    int i=len;
    char ch;
    struct passwd *user;
	user = getpwuid(getuid());

    do{
        --i;
        ch=path[i];
        if(len == 1)
        {   
            break;
        }
    }while(ch!='/');

    //printf("[%s@MiWiFi-R4CM-srv %s]:$ ",user->pw_name,&path[i]);
    if(strcmp(user->pw_name,&path[i+1])!=0)
        printf("[%s@archLinux %s]:$ ",user->pw_name,&path[i]);
    else   
        printf("[%s@archLinux ~]:$ ",user->pw_name);
    
    free(path);
}

void get_user_input(char *buf)
{
    int len = 0;
    int ch;

    ch = getchar();
    while(len<511 && ch != '\n')
    {
        buf[len++] = ch;
        ch = getchar();
    }

    buf[len++] = '\n';
    buf[len] = '\0';

    return ;
}

void ex_input(char* buf)
{
    
}

void mycd(char* buf)
{
    

}