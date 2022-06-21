//
// Created by bronya on 22-6-20.
//

#include "Account_UI.h"
#include "../Service/Account.h"
#include "../Common/List.h"
#include <stdio.h>
#include <string.h>

#define ACCOUNT_PAGE_SIZE 5;

void Account_UI_MgtEntry(int argc,char* name)
{
    int id,i;
    char ch;
    char choice;
    char usrName[31];
    account_list_t head;
    account_node_t *pos;
    Pagination_t paging;
    account_t test;

    List_Init(head, account_node_t);
    paging.offset = 0;
    paging.pageSize = ACCOUNT_PAGE_SIZE;

    //载入数据
    paging.totalRecords = Account_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head, paging);
    do{
        printf("\n====================================================================================================n");
        printf("--------------------------------------------------系统用户管理------------------------------------------\n");
        printf("%5s   %5s   %12s   %15s  \n", "ID","type","usrName","password");
        printf("------------------------------------------------------------------------------------------------------\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, account_node_t, pos, i){
            printf("%5d   %5d   %12s  ",pos->data.id,pos->data.type,pos->data.username);
            if(argc == 9 || strcmp(pos->data.username,name) == 0){
                printf("%15s   \n",pos->data.password);
            }else{
                printf("***************   \n");
            }
        }
        printf("---------------- Total Records:%2d ------------------------------ Page %2d/%2d -------------------------\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));
        printf("********************************************************************************************************\n");
        printf("\t1.添加系统用户(a或A)    2.修改系统用户(m或M)    \n");
        printf("\t3.删除系统用户(d或D)    4.查询系统用户(q和Q)    \n");
        printf("\t5.定位到上一页(p或P)    6.定位到下一页(n和N)    \n");
        printf("\t7.退出(r或R)    \n");
        printf("\n-----------------------------------------------------------------------------------------------------\n");

        char choice;
        //选择要实现的功能
        printf("Your Choice:");
        fflush(stdin);
        scanf("%c", &choice);

        switch (choice) {
            case 'a':
            case 'A':
                if (argc == 9 && Account_UI_Add(head)) //新添加成功，跳到最后一页显示
                {
                    paging.totalRecords = Account_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, account_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("请输入需要删除的用户名:");
                scanf("%s", usrName);
                setbuf(stdin, 0);
                if(argc == 9 || strcmp(name,usrName) == 0) {
                    if (Account_UI_Del(head, usrName)) {    //从新载入数据
                        paging.totalRecords = Account_Srv_FetchAll(head);
                        List_Paging(head, paging, account_node_t);
                    }
                }else{
                    fprintf(stdout,"你没有权限删除该用户信息.\n按[Enter]退出.\n");
                    getchar();
                }
                break;
            case 'm':
            case 'M':
                printf("请输入需要修改的用户名称:");
                scanf("%s", usrName);
                setbuf(stdin, 0);
                if(argc == 9 || strcmp(name,usrName) == 0) {
                    if (Account_UI_Modify(head, usrName,argc)) {    //从新载入数据
                        paging.totalRecords = Account_Srv_FetchAll(head);
                        List_Paging(head, paging, account_node_t);
                    }
                }else{
                    fprintf(stdout,"你没有权限修改该用户信息.\n 按[Enter]退出.\n");
                    getchar();
                }
                break;
            case 'q':
            case 'Q':
                printf("请输入需要查询的用户名称:");
                scanf("%s", usrName);
                setbuf(stdin, 0);
                if(argc == 9 || strcmp(name,usrName) == 0) {
                    if (Account_UI_Que(head, usrName)) {
                        paging.totalRecords = Account_Srv_FetchAll(head);
                        List_Paging(head, paging, account_node_t);
                    }
                }else{
                    fprintf(stdout,"你没有权限查询该用户信息.\n按[Enter]退出.\n");
                    getchar();
                }
                break;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
                }
                break;
            case 'r':
            case 'R':
                while((ch = getchar()) != '\n')
                    continue;
                return ;
                break;
        }
    }while(choice != 'r' && choice != 'R');

    List_Destroy(head, account_node_t);

    while((ch = getchar()) != '\n')
        continue;

}

int Account_UI_Add(account_list_t list) {//参数为系统用户链表头指针
    account_t t;
    int NewCount = 0;
    char choice;

    do {
        #ifdef linux
                system("clear");
        #endif
        #ifdef WIN32
                system("cls");
        #endif
        printf("---------------------------------------------------------------------------\n");

        printf("*****************************添加新系统用户********************************\n");

        printf("---------------------------------------------------------------------------\n");

        printf("请输入用户名：");
        scanf("%s", t.username);
        printf("请输入密码：");
        scanf("%s", t.password);
        printf("请选择帐号种类([销售员/1]，[经理/2]，[系统管理员/9])：");
        scanf("%d", &t.type);

        if (Account_Srv_Add(&t)) {
            NewCount += 1;
            printf("新的帐号已被成功生成\n");
        } else
            printf("生成帐号失败\n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("[A]添加更多, [R]返回\n");
        fflush(stdin);
        scanf("%c", &choice);

    }while('a' == choice || 'A' == choice);

    setbuf(stdin,0);

    return NewCount;

}

int Account_UI_Del(account_list_t list,char usrName[]) {
    //根据用户名查询到用户,并且删除该系统用户

    account_list_t t;
    int rtn = 0;
    char choice;
    char name[31];

    /*Load record*/
    do{
        if ((t = Account_Srv_FindByUsrName(list,usrName)) == NULL) {
            printf("%s不存在!\n"
                   "按下[Enter]返回上层!\n",usrName);
            getchar();
            return 0;
        }

        #ifdef linux
            system("clear");
        #endif
        #ifdef WIN32
            system("cls");
        #endif

        printf("-----------------------------------------------------------------------------\n");

        printf("*****************************删除系统用户信息********************************\n");

        printf("-----------------------------------------------------------------------------\n");

        if (Account_Srv_DelByID(t->data.id)) {
            printf("帐号已被成功删除!\n");
            rtn += 1;
        } else {
            printf("帐号删除失败!\n");
            break;
        }
        printf("--------------------------------------------------------------------------------------\n");
        printf("[D]删除更多, [R]返回:");
        scanf("%c", &choice);
        printf("需要删除的帐号用户名:");
        scanf("%s",name);
        setbuf(stdin,NULL);
    } while ('d' == choice || 'D' == choice);

    printf("按下[Enter]返回上层!\n");
    getchar();

    return rtn;

}

int Account_UI_Modify(account_list_t list,char usrName[],int argc){
    account_list_t t;
    int rtn = 0;
    int count = 0;
    char pow[31];
    int i = 0;

    /*Load record*/
    if ((t = Account_Srv_FindByUsrName(list,usrName)) == NULL) {
        printf("%s不存在!\n"
               "按下[Enter]返回上层!\n",usrName);
        getchar();
        return 0;
    }

    #ifdef linux
        system("clear");
    #endif
    #ifdef WIN32
        system("cls");
    #endif

    printf("-----------------------------------------------------------------------------\n");

    printf("*****************************修改系统用户信息********************************\n");

    printf("-----------------------------------------------------------------------------\n");

    if(argc != 9) {
        while( i <= 3) {
            printf("请输入原始密码：");
            scanf("%s", pow);
            if (strcmp(pow, t->data.password) != 0) {
                printf("输入错误。(剩余机会：%d)\n",i);
            } else {
                printf("请输入新密码：");
                scanf("%s", t->data.password);
                break;
            }
            i++;
        }
        if(i == 4){
            fprintf(stderr,"修改失败.\n");
            setbuf(stdin,NULL);
            return 0;
        }
    }else{
        printf("请输入新密码：");
        scanf("%s", t->data.password);
    }

    if (Account_Srv_Insert(&(t->data))) {
        rtn = 1;
        printf("帐号修改成功！\n按下[Enter]返回上层!\n");
    } else
        printf("帐号修改失败!\n按下[Enter]返回上层!\n");

    getchar();
    return rtn;
}


int Account_UI_Que(account_list_t list,char usrName[]) {
    account_list_t t;
    int rtn = 0;
    int count = 0;

    /*Load record*/
    if ((t = Account_Srv_FindByUsrName(list,usrName)) == NULL) {
        printf("%s不存在!\n"
               "按下[Enter]返回上层!\n",usrName);
        getchar();
        return 0;
    }

    #ifdef linux
        system("clear");
    #endif
    #ifdef WIN32
        system("cls");
    #endif


    //根据用户名匹配系统用户
    printf("-----------------------------------------------------------------------------\n");

    printf("*****************************查询系统用户信息********************************\n");

    printf("-----------------------------------------------------------------------------\n");

    printf("\n====================================================================================================n");
    printf("--------------------------------------------------系统用户管理------------------------------------------\n");
    printf("%5s   %5s   %12s   %15s  \n", "ID","type","usrName","password");
    printf("------------------------------------------------------------------------------------------------------\n");
    //显示数据
    printf("%5d   %5d   %12s  %15s   \n",t->data.id,t->data.type,t->data.username,t->data.password);
    printf("------------------------------------------------------------------------------------------------------\n");

    fprintf(stdout,"按下[Enter]退出.\n");

    getchar();

    return 1;
}

int SysLogin(account_t* t) {
    char ch;
    int choice;

    do {
        printf("----------------------------------------------------------\n");
        printf("*                                                        *\n");
        printf("*                       1.用户登录                         *\n");
        printf("*                       2.注册用户                         *\n");
        printf("*                       3.匿名登录                         *\n");
        printf("*                       4.退出                            *\n");
        printf("*                                                        *\n");
        printf("----------------------------------------------------------\n");

        printf("请输入选项:");
        scanf("%d",&choice);

        switch(choice) {

            case 1:
                slg(t);
                if(t->type != -1) {
                    setbuf(stdin,NULL);
                    return t->type;
                }else{
                    fprintf(stderr,"密码错误次数过多，请重新选择.\n");
                }
                break;
            case 2:
                reg();
                break;
            case 3:
                setbuf(stdin,NULL);
                return 0;
                break;
            case 4:
                break;
            default:
                fprintf(stderr,"输入错误，请重新输入.\n");
                break;
        }
    }while(choice != 4);


    setbuf(stdin,NULL);

    return -1;
}

int slg(account_t* ans){
    account_t t;
    char ch;
    int i = 0,count = 0;
    account_list_t list;
    account_list_t head;

    List_Init(head, account_node_t);
    Account_Srv_FetchAll(head);

    printf("请输入用户名：");
    scanf("%s", t.username);
    while ((ch = getchar()) != '\n')
        continue;

    while (i <= 3) {
        printf("请输入密码：");
        scanf("%s",t.password);

        if (Account_Srv_Verify(t.username, t.password)) {
            list = Account_Srv_FindByUsrName(head,t.username);
            ans->type = list->data.type;
            strcpy(ans->password , list->data.password);
            strcpy(ans->username , list->data.username);
            return ans->type;
        }else{
            i++;
            fprintf(stderr,"(剩余输入密码次数：%d)",4-i);
        }
    }

    return -1;
}

void reg(){
    account_t t;
    printf("请输入用户名：");
    scanf("%s", t.username);
    printf("请输入密码：");
    scanf("%s",t.password);
    printf("请选择帐号种类([销售员/1]，[经理/2]，[系统管理员/9])：" );
    scanf("%d",&t.type);

    Account_Srv_Add(&t);

    fprintf(stdout,"注册完成，按[Enter]退出.\n");

    getchar();
}