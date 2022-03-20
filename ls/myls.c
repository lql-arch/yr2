#include <stdio.h>       
#include <stdlib.h>
#include <string.h>
#include <errno.h>        
#include <sys/types.h>     
#include <dirent.h>         
#include <sys/stat.h>       
#include <unistd.h>         
#include <limits.h>         
#include <grp.h>            
#include <pwd.h>            
#include <time.h>           
#include <fcntl.h>          

int option_a=0;//显示隐藏文件
int option_F=0;//在不同类型的文件的文件名结尾追加一个字符以示区别。     //suspending
int option_i=0;//显示节点
int option_R=0;//迭代显示目录下所有的子目录。
int option_A=0;//all）显示所有文件，不包括以 .（自身目录）和 .. （父目录）。        //suspending
int option_d=0;//显示目录本身的信息，而不是列出目录下的文件。
int option_l=0;//显示文件类型、权限、硬链接的数目、文件拥有者、文件所在的组、大小、日期和文件名。
int option_s=0;                              //half
int option_t=0;                             //half
int option_r=0;                            //half



char address[PATH_MAX];
char temp_path[PATH_MAX];
// char R_next_arr[100][PATH_MAX];
// int R_next_num=0;

//there's no comment.I suggest you dont't read it to protect your head.

void my_ls(char* cata);
void showFile(char* file);
void transStr_Jur(struct stat *file_into,char *str,char*file);
void file_type(mode_t mode);
void L_option(char * file,struct stat *file_into);
void file_path(char* cata);
char* get_uid(uid_t uid);
char* get_gid(gid_t gid);
void R_option(char* arr,char (*R_arr)[PATH_MAX],int R_num);



int main(int argc,char **argv)
{
    int fileI=1;
    char *path = NULL;
    path = getcwd(NULL,0);//malloc() ,need free();
    strcpy(address,path);

    if(argc == 1)
    {
        my_ls(".");
    }else{
        int num=argc;
        for(int i=1;i<argc;i++)
        {
            if(argv[i][0]=='-')
            {

                for(int k=1;k<strlen(argv[i]);k++)
                {
                    if(argv[i][k]=='a')
                    {
                        option_a+=1;
                        continue;
                    }else if(argv[i][k]=='F')
                    {
                        option_F+=1;
                        continue;
                    }else if(argv[i][k]=='i')
                    {
                        option_i+=1;
                        continue;
                    }else if(argv[i][k]=='d')
                    {
                        option_d+=1;
                        continue;
                    }else if(argv[i][k]=='l')
                    {
                        option_l+=1;
                        continue;
                    }else if(argv[i][k]=='R')
                    {
                        option_R+=1;
                        continue;
                    }else if(argv[i][k]=='A')
                    {            
                        option_A+=1;
                        continue;
                    }else if(argv[i][k]=='s')
                    {            
                        option_s+=1;
                        printf("-s sort is not complete.\n");
                        continue;
                    }else if(argv[i][k]=='t')
                    {            
                        option_t+=1;
                        printf("-t sort is not complete.\n");
                        continue;
                    }else if(argv[i][k]=='r')
                    {            
                        option_r+=1;
                        printf("-r sort is not complete.\n");
                        continue;
                    }
                    else{
                        fprintf(stderr,"Error:please input correct parameters,for example:\"-a\".\n");
                    }

                }
                num--;
                fileI++;
            }
        }


        for(int j=0;j<fileI-1;j++)
        {
            *argv++;
        }


        int option=option_a+option_d+option_F+option_i              \
                    +option_l+option_R+option_A+option_s+option_t;
        
        if(num==1&&option!=0)
        {
            my_ls(".");
        }else{
            while(--num)
            {
                file_path(*++argv);
                
            }
        }
    }
    free(path);
    return 0;

}

void file_path(char* cata)
{
    char arr[100];

    if(cata[0]=='.' && cata[1]=='/')
    {
        getcwd(arr,sizeof(arr));
        *cata++;
        strcat(arr,cata);
        strcpy(cata,arr);
        //printf("%s\n",cata);
    }
    printf("%s:\n",cata);
    chdir(cata);//切换工作目录到对应的路径
    my_ls(cata);
    chdir("");//切换工作目录到当前目录
                
}

void my_ls(char* cata)
{
    char arr[100];
    DIR *ptr;
    struct dirent *dir_ptr;
    struct stat st_buf;

    char R_arr[100][PATH_MAX];
    int R_num=0;

    if((ptr=opendir(cata))==NULL)
    {
        fprintf(stderr,"Warning:%s is not a directory,%s.\n",cata,strerror(errno));
        showFile(cata);
    }
    else
    {
        if(option_d)
        {
            if(cata == ".")
            {
                // getcwd(arr,sizeof(arr));
                // printf("%s\n",arr);
                printf(".\n");
            }else{
                showFile(cata);
            }
            return ;
        }
        else{

            if(option_R!=0)//
            {
                strcpy(arr,".");

                if(cata[0]=='.')
                    printf("%s:\n",cata);

                while((dir_ptr=readdir(ptr))!=NULL)
                {
                    showFile(dir_ptr->d_name);

                    if(stat(dir_ptr->d_name,&st_buf)==-1)
                    {
                        fprintf(stderr,"%s Error:%s .\n",dir_ptr->d_name,strerror(errno));
                        exit(-1);
                    }else{
                        if(S_ISDIR(st_buf.st_mode))
                        {
                            strcpy(R_arr[R_num++],dir_ptr->d_name);
                        }
                    }
                }
            }

            while((dir_ptr=readdir(ptr))!=NULL)
            {
                showFile(dir_ptr->d_name);
            }
            if(option_R)
                R_option(arr,R_arr,R_num);
            
        }


    }
    if(closedir(ptr)==-1)
    {
        fprintf(stderr,"Error-cannot closedir %s:%s",cata,strerror(errno));
        exit(-1);
    }

}

void R_option(char* arr,char (*R_arr)[PATH_MAX],int R_num)
{
    int num=0;
    char r_arr[100][PATH_MAX];
    int i=2;// jump up . and .. ;
    while(i<R_num)
    {
        if( R_arr[i][0]=='.'&&(option_a==0) )//不处理隐藏目录
        {
            i++;
            continue;
        }else{
            DIR* next_cata_ptr;
            DIR* temp_ptr;
            struct dirent* next_dir_ptr;

            char temp[PATH_MAX];
            char temp_address[PATH_MAX];

            strcpy(temp,arr);
            getcwd(temp_address,sizeof(temp_address));

            int len=strlen(temp_address);
            strcpy(temp_path,temp_address);

            if(temp_address[len]!='/')
            {
                strcat(temp_path,"/");
                //printf("%s\n",temp);
            }
            strcat(temp_path,R_arr[i]);

            if(arr[strlen(arr)]!='/')
            {
                strcat(arr,"/");
            }
            strcat(arr,R_arr[i]);

            if((next_cata_ptr=opendir(temp_path))==NULL)
            {
                fprintf(stderr,"Error:cannot open next cata %s:%s\n",temp_path,strerror(errno));
            
            }else{
                chdir(temp_path);
                printf("\n%s:\n",arr);
                while((next_dir_ptr=readdir(next_cata_ptr))!=NULL)
                {
                    showFile(next_dir_ptr->d_name);

                    char file[100];
                    strcpy(file,next_dir_ptr->d_name);
                    struct stat file_into;
                    if( stat(file,&file_into)==-1)
                    {
                        fprintf(stderr,"Error-%s get failled:%s\n",file,strerror(errno));
                        exit(-1);
                    }
                    if(S_ISDIR(file_into.st_mode))
                    {
                        strcpy(r_arr[num++],file);
                    }

                }

                R_option(arr,r_arr,num);
                num=0;

                chdir(temp_address);
                strcpy(arr,temp);

            }
            i++;
        }
    }
}

void showFile(char* file)
{
    struct stat file_into;//

    if( stat(file,&file_into)==-1)
    {
        fprintf(stderr,"Error-%s get failled:%s\n",file,strerror(errno));
        exit(-1);
    }
    
    //未-a的隐藏文件
    if( option_a==0 && file[0]=='.')
    {
        return ;
    }

    if(option_s)
    {
        printf("%-4ld ",file_into.st_blocks/2);
    }

    if(option_i){
        printf("%-10d ",(int)file_into.st_ino);
    }

    if(option_l)
    {
        L_option(file,&file_into);
    }

    printf("%s",file);

    // if(option_F)
    // {
    //     file_type(file_into->st_mode);
    // }

    printf("\n");
}

void L_option(char * file,struct stat *file_into)
{
    char str[11]="";

    transStr_Jur(file_into,str,file);


    printf("%s ",str);
    printf("%4d ",(int)file_into->st_nlink);
    printf("%-6s ",get_uid(file_into->st_uid));
    printf("%-6s ",get_gid(file_into->st_gid));
    printf("%6d ",file_into->st_size);
    printf("%.12s ",4+ctime(&file_into->st_mtime));
    
}

void transStr_Jur(struct stat *file_into,char *str,char*file)
{
    switch (file_into->st_mode & S_IFMT) {
           case S_IFBLK:
               str[0]='b';
               break;
           case S_IFCHR:
               str[0]='c';
               break;
            case S_IFSOCK:
               str[0]='s';
               break;
           case S_IFDIR:
               str[0]='d';
               break;
           case S_IFIFO:
               str[0]='p';
               break;
           case S_IFLNK:
               str[0]='s';
               break;
           case S_IFREG:
               str[0]='-';
               break;
           default:
               fprintf(stderr,"Error:%s unknow.\n",file);
               break;
    }

//文件属主权限,组权限,其他用户权限
    if(file_into->st_mode & S_IRUSR){
        str[1]='r';
    }else{
        str[1]='-';
    }
    if(file_into->st_mode & S_IWUSR){
        str[2]='w';
    }else{
        str[2]='-';
    }
    if(file_into->st_mode & S_IXUSR){
        str[3]='x';
    }else{
        str[3]='-';
    }
    if(file_into->st_mode & S_IRGRP){
        str[4]='r';
    }else{
        str[4]='-';
    }
    if(file_into->st_mode & S_IWGRP){
        str[5]='w';
    }else{
        str[5]='-';
    }
    if(file_into->st_mode & S_IXGRP){
        str[6]='x';
    }else{
        str[6]='-';
    }
    if(file_into->st_mode & S_IROTH){
        str[7]='r';
    }else{
        str[7]='-';
    }
    if(file_into->st_mode & S_IWOTH){
        str[8]='w';
    }else{
        str[8]='-';
    }
    if(file_into->st_mode & S_IXOTH){
        str[9]='x';
    }else{
        str[9]='-';
    }

}

// void file_type(mode_t mode)//不能判断文件是否为可执行文件,割了.
// {
//     if((mode&S_IFMT)==S_IFDIR)
//     {
//         printf("/");
//     }

//     if( mode & S_IXUSR)
//     {
//         printf("*");
//     }

//     if(  mode & S_IFIFO)
//     {
//         printf("|");
//     }

//     if(  mode & S_IFSOCK)
//     {
//         printf("=");
//     }

// }

char* get_uid(uid_t uid)
{
    char *name;
    struct passwd * user;

    name=(char*)malloc(sizeof(char)*20);

    if((user=getpwuid(uid))==NULL)
        sprintf(name,"%d",uid);
    else
        sprintf(name,"%s",user->pw_name);

    return name;
}

char* get_gid(gid_t gid)
{
    char *name;
    struct group * user;

    name=(char*)malloc(sizeof(char)*20);

    if((user=getgrgid(gid))==NULL)
        sprintf(name,"%d",gid);
    else
        sprintf(name,"%s",user->gr_name);

    return name;
}
