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

//#define TEST

//憨批才用链表,问题根本没解决 --lql

//file-reverse?
typedef struct File_List {
        char *name;
        struct File_List *next;
} file_list;  

typedef struct temp{
    char* name;
    int size;
    long time;
    struct temp*next;
} f_temp;

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
int option=0;

//too many files will make mistakes.it seems that I should change my storage method.

char address[PATH_MAX];
char temp_path[PATH_MAX];
typedef struct _List{
	file_list* head;
}list_head;

f_temp start; 

typedef struct __List{
	f_temp *start; 
}temp_head;

list_head list;
temp_head list_t;

//file_free* first_ptr;
// char R_next_arr[100][PATH_MAX];
// int R_next_num=0;


//there's no comment.I suggest you dont't read it to protect your head.

//void ptr_collect(char* record);
//void end_free();
//void print(file_list *dir);
void my_ls(char* cata);
void showFile(char* file);
void transStr_Jur(struct stat *file_into,char *str,char*file);
void file_type(mode_t mode);
void L_show(char * file,struct stat *file_into);
void file_path(char* cata);
char* get_uid(uid_t uid);
char* get_gid(gid_t gid);
void R_option(temp_head* list_t,int size);
void l_option(temp_head* list_t,int size);
char file_collect(char* cata,list_head* path);
void join(file_list* node,list_head* f_path);
void join_temp(temp_head* f_head,char* d_name);
void t_sort(temp_head* f_head,char* d_name);
void s_sort(temp_head* f_head,char* d_name);
f_temp* r_sort(temp_head* f_head);
void filename_swap(int num,char (*R_arr)[PATH_MAX],file_list *head );
void temp_free();


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
                        option_a=1;
                        continue;
                    }else if(argv[i][k]=='F')
                    {
                        option_F=1;
                        continue;
                    }else if(argv[i][k]=='i')
                    {
                        option_i=1;
                        continue;
                    }else if(argv[i][k]=='d')
                    {
                        option_d=1;
                        continue;
                    }else if(argv[i][k]=='l')
                    {
                        option_l=1;
                        continue;
                    }else if(argv[i][k]=='R')
                    {
                        option_R=1;
                        continue;
                    }else if(argv[i][k]=='A')
                    {            
                        option_A=1;
                        continue;
                    }else if(argv[i][k]=='s')
                    {            
                        option_s=k;
                        continue;
                    }else if(argv[i][k]=='t')
                    {            
                        option_t=k;
                        continue;
                    }else if(argv[i][k]=='r')
                    {            
                        option_r=k;
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
//        printf("t:%d\ts:%d\n",option_t,option_s);


        for(int j=0;j<fileI-1;j++)
        {
            *argv++;
        }


        option=option_a+option_d+option_F+option_i              \
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
    if(option==0)
        printf("\n");

    free(path);
    return 0;

}

void file_path(char* cata)
{
    char arr[256];

    if(cata[0]=='.' && cata[1]=='/')
    {
        getcwd(arr,sizeof(arr));
        *cata++;
        strcat(arr,cata);
        strcpy(cata,arr);
        //printf("%s\n",cata);
    }
    //printf("%s:\n",cata);
    chdir(cata);//切换工作目录到对应的路径
    my_ls(cata);
    chdir("");//切换工作目录到当前目录
                
}

void my_ls(char* cata)
{
    char arr[256];
    DIR *ptr;
    struct dirent *dir_ptr;
    struct stat st_buf;

    

    //list.head =NULL;
    list_t.start =NULL;

    //char R_arr[256][PATH_MAX];
    int size=0;

    //file_collect(cata,&list);

#ifdef TEST
        char* t=NULL;
        t=getcwd(NULL,0);
        printf("test:%s\n",t);
        free(t);
#endif

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

            if(option_R!=0 || option_l!=0)//
            {
                while((dir_ptr=readdir(ptr))!=NULL)
                {
                    join_temp(&list_t,dir_ptr->d_name);
                    //printf("test:%s\n",dir_ptr->d_name);
                    if(stat(dir_ptr->d_name,&st_buf)==-1)
                    {
                        fprintf(stderr,"[Error]%s Error:%s .\n",dir_ptr->d_name,strerror(errno));
                        //exit(-1); 
                        continue;
                    }
                    if(option_a==0 && (strcmp(dir_ptr->d_name,".")==0 && strcmp(dir_ptr->d_name,"..")==0) )
                        continue;
                    else
                        size += st_buf.st_blocks/2; 
                }
            }

            while((dir_ptr=readdir(ptr))!=NULL)
            {
                showFile(dir_ptr->d_name);
            }

            if(option_R)
                R_option(&list_t,size);

            if(option_l!=0 && option_R==0)
                l_option(&list_t,size);
            
        }


    }
    if(closedir(ptr)==-1)
    {
        fprintf(stderr,"Error-cannot closedir %s:%s",cata,strerror(errno));
        exit(-1);
    }

}

void R_option(temp_head* list_t,int size)
{
    f_temp* p = list_t->start; 
    char path[PATH_MAX];
    struct stat st_buf;
    list.head = NULL;
    int num=0;
    char *s_getpath = NULL;
    s_getpath = getcwd(NULL,0);
    
    printf("%s:\n",s_getpath);
    printf("总用量 %d\n",size);
    size=0;

    if(option_r)
    {
        p = r_sort(list_t);
    }

    while(p)
    {
        showFile(p->name);

        if(stat(p->name,&st_buf)==-1)
        {
            if(lstat(p->name,&st_buf)==-1)
            {
                fprintf(stderr,"[Error]%s Error:%s .\n",p->name,strerror(errno));
                //exit(-1);
                p = p->next;
                continue;
            }
        }else{
            if(S_ISDIR(st_buf.st_mode))
            {
                if(option_a==0 && p->name[0]=='.')
                {
                }else{
                    static file_list * node ;
                    node = (file_list*)malloc(sizeof(file_list));
                    node -> name = (char*)malloc(strlen(p->name)+1);
                    strcpy(node->name,p->name);
                    join(node,&list);
                    if(strcmp(p->name,".")!=0 && strcmp(p->name,"..")!=0)
                        num++;
                }
            }
        }

        p = p->next;
    }
    temp_free();

#ifdef TEST
        file_list *t = list.head ;
        while(t)
        {
            printf("text:%s\n",t->name);
            t = t->next;
        }
#endif
    char R_arr[num][PATH_MAX];


    filename_swap(num,R_arr,list.head);
#ifdef TEST
        char* t=NULL;
        t=getcwd(NULL,0);
        printf("test:%s\n",t);
        free(t);
#endif

    int i=0;
    while(i<num)
    {
        if(strcmp(R_arr[i],".")==0 && strcmp(R_arr[i],"..")==0)
        {
            continue;
        }

        DIR *ptr;
        struct dirent *dir_ptr;
        struct stat buf;
        int flag=0;

        char *getpath = NULL;
        getpath = getcwd(NULL,0);
        strcpy(path,getpath);
        //printf("test1:%s\n",path);

        if(path[strlen(path)-1]!='/')
            strcat(path,"/");
        strcat(path,R_arr[i]);

        chdir(path);
#ifdef TEST
        char* t=NULL;
        t=getcwd(NULL,0);
        printf("t-test:%s\n",t);
        free(t);
#endif
        if( (ptr=opendir(path))==NULL)
        {
            flag=1;
            fprintf(stderr,"(root)Warning:%s is not a directory,%s.\n",path,strerror(errno));
            showFile(path);
        }
        else{
            while((dir_ptr=readdir(ptr))!=NULL)
            {
                //printf("%s\n",dir_ptr->d_name);
                join_temp(list_t,dir_ptr->d_name);
                if(stat(dir_ptr->d_name,&buf) == -1 )
                {
                    //if(lstat(p->name,&st_buf)<0)
                    {
                        fprintf(stderr,"[Error]%s-%s Error:%s .\n",path,dir_ptr->d_name,strerror(errno));
                        //exit(-1);
                        continue;
                    }
                }
                if((strcmp(dir_ptr->d_name,".")!=0 && strcmp(dir_ptr->d_name,"..")!=0) )
                    size += buf.st_blocks/2;
            }
            
        }
        R_option(list_t,size);
        size=0;
        if(flag==0)
            if(closedir(ptr)==-1 )
            {
            fprintf(stderr,"Error-cannot closedir %s:%s",path,strerror(errno));
            exit(-1);
            }

        chdir(getpath);
        i++;

        free(getpath);
    }
    

    return ;
}

void l_option(temp_head* list_t,int size)
{
    f_temp* p = list_t->start; 
    char path[PATH_MAX];
    struct stat st_buf;
    list.head = NULL;
    int num=0;
    char *s_getpath = NULL;
    s_getpath = getcwd(NULL,0);
    
    printf("%s:\n",s_getpath);
    printf("总用量 %d\n",size);
    size=0;

    if(option_r)
    {
        p = r_sort(list_t);
    }

    while(p)
    {
        showFile(p->name);
        p = p->next;
    }
    //printf("\n");
    temp_free();

    return ;
}

void showFile(char* file)
{
    struct stat file_into;//
    char *path=NULL;
    path=getcwd(NULL,0);

    if( stat(file,&file_into)==-1)
    {
        if(lstat(file,&file_into)==-1)
        {
            fprintf(stderr,"Error:%s/%s get failled:%s\n",path,file,strerror(errno));
            exit(-1);
            //return ;
        }
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
        L_show(file,&file_into);
    }

    if(option!=0)
    {
        struct stat buf;
        char *out=NULL;
        out=(char *)malloc(PATH_MAX);
        memset(out,0,PATH_MAX);
        
        if(S_ISLNK(file_into.st_mode))        
        {
            printf("%s ",file);
            printf(" -> "); 
            if((readlink(file,out,PATH_MAX)<0))
            {
                fprintf(stderr,"(%s/%s)Error:readlink error\n",path,file);
                exit(-1);
            }
            strcat(out,"\0");
            printf("%4s",out);
        }else{
                printf("%s ",file);
        }
        //printf("%s ",file);
        printf("\n");
        free(out);
    }
    else 
    {
        printf("%-8s  ",file);
    }

    // if(option_F)
    // {
    //     file_type(file_into->st_mode);
    // }

    free(path);
}

void L_show(char * file,struct stat *file_into)
{
    char str[11]="";

    transStr_Jur(file_into,str,file);


    printf("%s ",str);
    printf("%4d ",(int)file_into->st_nlink);
    printf("%-6s ",get_uid(file_into->st_uid));
    printf("%-6s ",get_gid(file_into->st_gid));
    printf("%6d ",file_into->st_size);
    printf("%.20s ",4+ctime(&file_into->st_mtime));
    //printf("%ld ",file_into->st_mtime);
    
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
               str[0]='l';
               break;
           case S_IFREG:
               str[0]='-';
               break;
           default:
               fprintf(stderr,"Error:%s unknow.\n",file);
               break;
    }
    //获取字符串的属性：普通文件-、目录d、字符设备c、块设备b、
    //管道文件p、连接文件l、套接字文件s

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


char file_collect(char* cata,list_head* path)
{
    DIR* dir;
    if((dir = opendir(cata)) == NULL)
    {
        fprintf(stderr,"Error(file_collect):cannot open next cata %s:%s\n",cata,strerror(errno));
        //exit(-1);
    }

    struct dirent *rent;
    while((rent = readdir(dir)) != NULL)
    {
        //if(rent->d_name[0]=='.')
        if(strcmp(rent->d_name,".")==0 || strcmp(rent->d_name,"..")==0)
        {
            continue;
        }
        file_list* node = (file_list*)malloc(sizeof(file_list));
        if(node == NULL)
        {
            fprintf(stderr,"Error(%s): malloc error",cata);
            exit(-1);
        }
        memset(node,0,sizeof(file_list));
        node->name = (char*)malloc(strlen(rent->d_name)+1);
        if (node->name == NULL)
        {
            free(node);
            fprintf(stderr,"Error(%s): filename is not stored.");
            exit(-1);
        }
        
        strcpy(node->name,rent->d_name);

        join(node,path);

    }
    closedir(dir);
}

void join(file_list* node,list_head* path){
    if (path->head == NULL) { 
        path->head = node;
        return ;
    }
    node->next = path->head;
    path->head = node;
    return; 

}

void join_temp(temp_head* f_head,char* d_name){

    if(option_t!=0 || option_s!=0 )
    {
        if(option_t > option_s)
            t_sort(f_head,d_name);
        else
            s_sort(f_head,d_name);
        return ;
    }

    static f_temp *node ;
    node= (f_temp*)malloc(sizeof(f_temp));
    static f_temp* last;

    node->name = (char*)malloc(strlen(d_name)+1);
    strcpy(node->name,d_name);

	
	node->next=NULL;

	if(f_head->start){
		last->next=node;
	}
	else{
		f_head->start=node;
	}
	last=node;
    return ;
}

void t_sort(temp_head* f_head,char* d_name)
{
    struct stat n_buf;
    static f_temp *node ;
    node= (f_temp*)malloc(sizeof(f_temp));

    node->name = (char*)malloc(strlen(d_name)+1);
    strcpy(node->name,d_name);

    if(stat(d_name,&n_buf)==-1)
    {
        fprintf(stderr,"[Error]%s t-sort Error:%s .\n",d_name,strerror(errno));
        free(node->name);
        free(node);
        return ;
    }else{
        node->time = n_buf.st_mtim.tv_sec;
    }

    if(f_head->start == NULL)
    {
        f_head->start = node ;
        return ;
    }

    if(node->time > f_head->start->time)
    {
        node->next = f_head->start;
        f_head->start = node;
        return ;
    }

    f_temp * temp = f_head->start;
    while(temp->next != NULL)
    {
        if(temp->next->time < node->time)
        {
            node->next = temp->next;
            temp->next = node ;
            return ;
        }
        temp = temp->next;
    }
    temp->next = node;
    return ;

}

void s_sort(temp_head* f_head,char* d_name)
{

    struct stat n_buf;
    static f_temp *node ;
    node= (f_temp*)malloc(sizeof(f_temp));

    node->name = (char*)malloc(strlen(d_name)+1);
    strcpy(node->name,d_name);

    if(stat(d_name,&n_buf)==-1)
    {
        fprintf(stderr,"[Error]%s t-sort Error:%s .\n",d_name,strerror(errno));
        free(node->name);
        free(node);
        return ;
    }else{
        node->size = n_buf.st_blocks/2;
    }

    if(f_head->start == NULL)
    {
        f_head->start = node ;
        return ;
    }

    if(node->size > f_head->start->size)
    {
        node->next = f_head->start;
        f_head->start = node;
        return ;
    }

    f_temp * temp = f_head->start;
    while(temp->next != NULL)
    {
        if(temp->next->size < node->size)
        {
            node->next = temp->next;
            temp->next = node ;
            return ;
        }
        temp = temp->next;
    }
    temp->next = node;
    return ;

}

f_temp* r_sort(temp_head* f_head)
{
	f_temp *newHead = NULL;
	f_temp*node;
	while (f_head->start!= NULL) {
		node = f_head->start;
		f_head->start = f_head->start->next;
		
		node->next = newHead;
		newHead = node;
	}

	return newHead;
}

void filename_swap(int num,char (*R_arr)[PATH_MAX],file_list *head )
{
    file_list* p ;
    int r=0;
    p = head;
    while(p && r<num)
    {
        strcpy(R_arr[r],p->name);
#ifdef TEST
        printf("text:%s\t",R_arr[r]);
#endif
        p = p->next;
        r++;
    }

}

void temp_free()
{
    while(list_t.start !=NULL)
    {
        f_temp *node = list_t.start->next;
        free(list_t.start->name);
        free(list_t.start);
        list_t.start = node;
    }
    return ;
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

// void ptr_collect(char* record)
// {
//     file_free* node = (file_free*)malloc(sizeof(file_free));
//     if(node == NULL)
//     {
//         fprintf(stderr,"Error(%s):file_ptr.",record);
//         exit(-1);
//     }
//     memset(node,0,sizeof(file_free));

//     node->name_ptr = record;
//     node->next = first_ptr;
//     first_ptr = node;

// }

// void end_free()
// {
        // while (first_ptr != NULL) { 
        //     file_free *last = first_ptr->next;
        //     free(first_ptr->name_ptr);
        //     free(first_ptr);
        //     first_ptr = last;
        // }
    
//         return;
// }

// void print(file_list *dir)
// {

// }


// void R_option(char* arr,f_temp* head,int size)
// {
    
    // int num=0;
    // char r_arr[100][PATH_MAX];
    // int i=2;// jump up . and .. ;
    // while(i<R_num)
    // {
    //     if( R_arr[i][0]=='.'&&(option_a==0) )//不处理隐藏目录
    //     {
    //         i++;
    //         continue;
    //     }else{
    //         DIR* next_cata_ptr;
    //         DIR* temp_ptr;
    //         struct dirent* next_dir_ptr;

    //         char temp[PATH_MAX];
    //         char temp_address[PATH_MAX];

    //         strcpy(temp,arr);
    //         getcwd(temp_address,sizeof(temp_address));

    //         int len=strlen(temp_address);
    //         strcpy(temp_path,temp_address);

    //         if(temp_address[len]!='/')
    //         {
    //             strcat(temp_path,"/");
    //             //printf("%s\n",temp);
    //         }
    //         strcat(temp_path,R_arr[i]);

    //         if(arr[strlen(arr)]!='/')
    //         {
    //             strcat(arr,"/");
    //         }
    //         strcat(arr,R_arr[i]);

    //         if((next_cata_ptr=opendir(temp_path))==NULL)
    //         {
    //             fprintf(stderr,"Error:cannot open next cata %s:%s\n",temp_path,strerror(errno));
            
    //         }else{
    //             chdir(temp_path);
    //             printf("\n%s:\n",arr);
    //             while((next_dir_ptr=readdir(next_cata_ptr))!=NULL)
    //             {
    //                 showFile(next_dir_ptr->d_name);

    //                 char file[256];
    //                 strcpy(file,next_dir_ptr->d_name);

    //                 struct stat file_into;
    //                 if( stat(file,&file_into)==-1)
    //                 {
    //                     fprintf(stderr,"Error-%s get failled:%s\n",file,strerror(errno));
    //                     exit(-1);
    //                 }
    //                 if(S_ISDIR(file_into.st_mode))
    //                 {
    //                     strcpy(r_arr[num++],file);
    //                 }

    //             }

    //             R_option(arr,r_arr,num);
    //             num=0;

    //             chdir(temp_address);
    //             strcpy(arr,temp);

    //         }
    //         i++;
    //     }
    // }
//}