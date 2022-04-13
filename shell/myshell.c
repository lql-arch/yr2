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

// file name: " "
// >> and | again
//free
//^C(2)

void print_prompt(); 
void get_user_input(char *buf);
void second_and_mycmd(char** para,int pararnum);
void ex_input(char* buf,char** para,int* paranum);
void mycd(char *optiton);
int command(char *arg);

char temp[4] = "";
int back_sleep = 0;

typedef void (*signal_handler)(int);

void signal_handler_fun(int signum) {
   strcpy(temp,"^C");
}


int main(int argc, char **argv)
{
    char *first=NULL;
    first = getcwd(NULL,0);
    int count=0;
    char* m_buf = NULL;
    char **para=NULL;
    int paraNum = 0;
    para = (char**)malloc(sizeof(char*)*100);

    m_buf = (char*)malloc(sizeof(char) * 512);

    if(m_buf == NULL)
    {
        perror("Error:buf malloc");
        exit(-1);
    }

    while(1)
    {
        if(back_sleep == 1)
        {
            back_sleep = 0;
            sleep(1);
        }
        memset(m_buf,0,512);
        fflush(stdout);
        print_prompt();
        get_user_input(m_buf);
        if(strcmp(temp,"^C") == 0)
        {
            strcpy(temp,"\0");
            continue;
        }
        if( strcmp(m_buf, "exit\n") == 0 )
        {
            break;
        }
        paraNum = 0;
        if(strcmp(m_buf,"\n"))
        {
            ex_input(m_buf,para,&paraNum);
            second_and_mycmd(para,paraNum);
        }
    }
    
    chdir(first);

    for(int i=0;i<100;i++)
    {
        if(para[i] != NULL)
            free(para[i]);
    }
    free(para);
    free(first);
    free(m_buf);

    return 0;
}

void print_prompt()
{
    char *path=NULL;
    path = getcwd(NULL,0);
    char *address;
    char *temp,*p;
    struct passwd *user;
	user = getpwuid(getuid());

    if(strcmp(path,"/home")!=0 && strcmp(path,"/")!=0)
    {
        p = strtok_r(path,"/",&temp);
        while(p!=NULL)
        {
            if((p = strtok_r(NULL,"/",&temp))!=NULL)
                address = p;
        }

        //printf("[%s@MiWiFi-R4CM-srv %s]:$ ",user->pw_name,address);
        if(strcmp(user->pw_name,address)!=0)
            printf("[%s@archLinux(temp) %s]:$ ",user->pw_name,address);
        else   
            printf("[%s@archLinux(temp) ~]:$ ",user->pw_name);

        free(p);
    }
    else{
        printf("[%s@archLinux(temp) %s]:$ ",user->pw_name,path);
    }
    
    free(path);
    
}

void get_user_input(char *buf)
{
    int len = 0;
    int ch;

    memset(buf, 0, 512);
    signal(SIGINT, signal_handler_fun);
    if(strcmp(temp,"^C") == 0)
    {
        return ;
    }
    else{
        ch = getchar();
    }
    while(len<511 && ch != '\n')
    {
        buf[len++] = ch;
        ch = getchar();
    }

    buf[len++] = '\n';
    buf[len] = '\0';

    return ;
}

void ex_input(char* buf,char **para,int* pararnum)
{
    char *t1 = buf;
    char *t2 = buf;
    int num=0;
    while(t1)
    {
        if(t1[0]=='\n' || t1[0] == '\0')
            break;
        if(t1[0]==' ')
        {
            t1++;
        }
        else
        {
            t2 = t1;
            num=0;
            while(t2[0] !=' ' && t2[0] != '\n' && t2[0] != '\0')
            {
                if(t2[0] == '\\')
                {
                    t1++;
                    t2++;
                }else{
                    num++;
                    t2++;
                }

            }
            if(t1[0] != ' ' && t1[0] != '\n' && t1[0] != '\0')
            {
                if(para[*pararnum] == NULL)
                    para[*pararnum] = (char*)malloc(sizeof(char)*num+1);
                else   
                    para[*pararnum] = (char*)realloc(para[*pararnum],sizeof(char)*num+1);
                memcpy(para[*pararnum],t1,num+1);
                para[*pararnum][num] = '\0';
                // printf("para[%d]:%s\n",*pararnum,para[*pararnum]);
                *pararnum +=1;
            }
            t1 = t2;    
        }
    }
}

void second_and_mycmd(char** para,int paranum)
{
    int flag=0;
    char *choice=NULL;
    int pip=0; // 管道
    int back=0; //后台
    int din=0; //标准输入
    int dout=0; //标准输出
    char* file;
    int fd;
    char ch;
    char *buf=(char*)malloc(sizeof(char)*512);
    pid_t pid;
    int num[100];
    int number=1;
    int state;
    memset(num,0,100);
    num[0] = 0;
    int len = 0; 
    char** pro=NULL;
    pro = (char**)malloc(sizeof(char*)*paranum);

    for(int i=0;i<paranum;i++)
    {
        if(strcmp(para[i],"cd")==0)
        {
            flag++;
        }
        if(strcmp(para[i],"|")==0)
        {
            if(i == 0 )
            {
                fprintf(stderr,"|”附近有语法错误\n");
                return ;
            }
            else if(para[i+1] == NULL)
            {
                while(1)
                {
                    int len=0;
                    printf(">");
                    memset(buf,0,sizeof(char)*512);
                    ch = getchar();
                    while(len<511 && ch != '\n')
                    {
                        buf[len++] = ch;
                        ch = getchar();
                    }

                    buf[len] = '\0';
                    if(buf[0] != '\0')
                    {
                        ex_input(buf,para,&paranum);
                        pip += 1;
                        break;
                    }
                }
            }
            else{
                pip += 1;
            }
        }
    }

    for(int i=0;i<paranum;i++)
    {
        if(strncmp(para[i],"&",1)==0)
        {
            if(i == paranum-1)
            {
                back = 1;
                back_sleep = 1;
                int t_len = strlen(para[i]);
                // memmove(para[i],para[i]+1,t_len-1);
                // para[i][t_len-1] = '\0'; 
                if(t_len >= 2)
                {
                    printf("bash:%s:未找到命令 \n",para[i]+1);
                }
                break;
            }else{
                fprintf(stderr,"&”附近有语法错误\n");
                return ;
             }
        }
    }

    for(int i=0;i<paranum;i++)
    {
        //printf("para[%d]:%s\n",i,para[i]);
        if(strncmp(para[i],"<<",2)==0)
        {
            if( para[i+1] == NULL)
            {
                fprintf(stderr,"<<”附近有语法错误\n");
                return ;
            }
            else{
                din += 100;
            }
        }
        else if(strncmp(para[i],"<",1)==0 )//&& ((strlen(para[i])>=2 && strncmp(para[i],"<",2)!=0) || strlen(para[i]) < 2)
        {
            if(i == 0)
            {
                fprintf(stderr,"<”附近有语法错误\n");
                return ;
            }
            else{
                din += 1;
            }
        }

        if(strncmp(para[i],">>",2)==0)
        {
            if(i == 0 || para[i+1] == NULL)
            {
                fprintf(stderr,">>”附近有语法错误\n");
                return ;
            }
            else{
                dout += 100;
            }
        }
        else if(strncmp(para[i],">",1)==0 )//&& ((strlen(para[i]) >= 2 && strncmp(para[i],">",2)!=0) || strlen(para[i]) < 2) 
        {
            if(para[i+1] == NULL)
            {
                fprintf(stderr,">”附近有语法错误\n");
                return ;
            }
            else{
                dout += 1;
            }
        }
    }

    if(strcmp(para[0],"cd") == 0)
    {
        if(paranum < 2)
        {
            mycd(NULL);
        }
        else if( paranum > 2 && strcmp(para[2],"|")!=0 )
        {
            fprintf(stderr,"bash: cd: 参数太多\n");
        }
        else
        {
            if( flag==1 && paranum < 2 )
            {
                mycd(para[1]);
            }  
        }
    }

    for(int i=0;i < paranum;i++)
    {
        if(strcmp(para[i],"|")==0 || strcmp(para[i],"&")==0)
        {
            num[number++] = i;
        }

        if(i == paranum - 1)
        {
            num[number++] = i + 1;
        }
    }

    for(int i=0;i < num[1] ;i++)
    {
        pro[i] = (char*)malloc(sizeof(char)*100);
        strcpy(pro[i],para[i]);
        len++;
    }
    pro[num[1]] = NULL;

    int k=2;
    int fd2,fd5;
    int fd2_flag = 0;
    int pip_flag = 0;
    if(pip > 0)
        pip_flag += 1;

    fd5 = open("/tmp/shell_flag.txt",O_RDONLY|O_WRONLY|O_CREAT|O_TRUNC, 0644);
    write(fd5,"123456\n",7);
    close(fd5);

    while(pip >= 0)
    {
        if((pid = fork()) < 0)
        {
            printf("Error:fork error\n");
            exit(-1);
        }
        if(pid == 0)
        {
            if(din == 0 && dout == 0)
            {
                if(!command(pro[0]))
                {
                    printf("bash: %s:未找到命令\n", pro[0]);
                    exit(0);
                }
            }
            if(din > 0)// 输入重定向<
            {
                int d_flag = 0;
                for(int i = 0 ;i < len ;i++)
                {
                    if(strncmp(pro[i], "<<",2) == 0)
                    {
                        d_flag = 1;
                        file = pro[i+1];
                        pro[i] = NULL;
                        break;
                    }
                    else if(strncmp(pro[i], "<",1) == 0)
                    {
                        file = pro[i+1];
                        pro[i] = NULL;
                        break;
                    }
                }
                if(!command(pro[0]))
                {
                    printf("bash: %s:未找到命令\n", pro[0]);
                    exit(0);
                }
                if(d_flag == 1)
                {
                    lseek(fd,0,SEEK_END);
                }
                fd = open(file, O_RDONLY);
                dup2(fd, 0);
            }
            if(dout > 0) // 输出重定向符>
            {
                int d_flag = 0;
                for(int i = 0 ;i < len ;i++)
                {
                    if(strncmp(pro[i], ">>",2) == 0)
                    {
                        d_flag = 1;
                        file = pro[i+1];
                        pro[i] = NULL;
                        break;
                    }
                    else if(strncmp(pro[i], ">",1) == 0  )
                    {
                        file = pro[i+1];
                        pro[i] = NULL;
                        break;
                    }       
                }
                if(!command (pro[0]))
                {
                    printf("bash: %s:未找到命令\n", pro[0]);
                    exit(0);
                }
                if(d_flag == 1)
                {
                    //lseek(fd,0,SEEK_END);
                    fd = open(file, O_RDWR|O_CREAT|O_APPEND, 0644);
                }else{
                    fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 0644);
                }
                dup2(fd, 1);
            }
            if(pip_flag > 0)
            {
                fd5 = open("/tmp/shell_flag.txt",O_RDONLY);
                char temp_buf[7];
                int fd5_len = read(fd5,temp_buf,6);
                temp_buf[6] = '\0';
                if( strcmp(temp_buf,"111111") != 0 )
                {
                    fd2 = open("/tmp/temp_shell.txt",O_WRONLY|O_CREAT|O_TRUNC, 0644);
                    dup2(fd2,1);

                    if(pip == 1)
                    {        
                        fd5 = open("/tmp/shell_flag.txt",O_WRONLY|O_CREAT|O_TRUNC, 0644);
                        write(fd5,"111111\n",7);
                        close(fd5);
                    }
                }else{
                    fd2 = open("/tmp/temp_shell.txt",O_RDONLY);
                    dup2(fd2,0);
                }
            }
            execvp(pro[0],pro);
            fflush(stdout);
            exit(0);
        }
        //printf("pid:%d ppid:%d\n",getpid(),getppid());

        if(back == 1 )
        {
            printf("[pid] %d \n", pid);
            return ;
        }

        if(waitpid(pid,&state, 0) == -1)
        {
            printf("wait for child process error.\n");
        }
        

        if(k <= number)
        {
            len = 0;
            for(int count=0,i=num[k-1] + 1 ; i < num[k] ;count++,i++)
            {
                if(pro[count]!=NULL)
                    pro[count] = (char*)realloc(pro[count],sizeof(char)*100);
                else 
                    pro[count] = (char*)malloc(sizeof(char)*100);
                strcpy(pro[count],para[i]);
                len++;
                //printf("(temp)pro[%d]:%s\n",count,pro[count]);
            }
            pro[ num[k] - num[k-1] - 1] = NULL;
            k++;
        }

        pip--;
    }

    remove("/tmp/shell_flag.txt");
    remove("/tmp/temp_shell.txt");


    free(buf);
    free(pro);

    return ;
}


int command(char *arg)
{
    // char *pass = NULL;
    // pass = getcwd(NULL,0);
    DIR *d;
    struct dirent *dir;
    char *path[]={"./","/usr/local/bin","/usr/bin","/usr/local/sbin","/usr/bin/site_perl","/usr/bin/vendor_perl","/usr/bin/core_perl","NULL"};
    //printf("arg:%s\n",arg);

    if( strncmp(arg, "./", 2) == 0 )
    {
        arg += 2;
    }

    for(int i=0;path[i] != NULL;i++)
    {
        if( (d= opendir(path[i])) == NULL )
        {
            printf("bash:%s:没有那个文件或目录.\n",arg);
        }
        while( (dir = readdir(d)) != NULL )
        {
            if(strcmp(dir->d_name, arg) == 0)
            {
                if(closedir(d) == -1)
                {
                    fprintf(stderr,"%s closedir error.\n",path[i]);
                }
                //free(pass);
                return 1;
            }
        }
    }
    //chdir(pass);
    if(closedir(d) == -1)
    {
        fprintf(stderr,"file closedir error.\n");
    }

    //free(pass);

    return 0;
}

void mycd(char *optiton)
{
    char *pass;
    char *address = (char*)malloc(sizeof(char)*512);
    pass = getcwd(NULL,0);
    int len = strlen(address);
    struct passwd *user;
	user = getpwuid(getuid());

    if(optiton == NULL)
    {
        memcpy(address,"/home/",6);
        strcat(address,user->pw_name);
        strcat(address,"\0");
    }
    else if(strcmp(optiton,"..") == 0 || strcmp(optiton,"../") == 0 || strcmp(optiton,".") == 0)
    {
        strcpy(address,pass);
        strcat(address,"/");
        strcat(address,optiton);
        strcat(address,"\0"); 
    }
    else if(strncmp(optiton,"./",2)==0)
    {
        strcpy(address,pass);
        optiton++;
        strcat(address,optiton);
        strcat(address,"\0");
        optiton--;
    }
    else 
    {
        strcpy(address,optiton);
    }
    if(chdir(address))
    {
        fprintf(stderr,"bash: cd: \"%s\": 没有那个文件或目录\n",optiton);
    }


    //chroot(address);

    free(address);
    free(pass);
}