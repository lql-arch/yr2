//
// Created by bronya on 22-6-20.
//

#ifndef TTMS_C_LANG__ACCOUNT_H
#define TTMS_C_LANG__ACCOUNT_H

typedef enum {
    USR_ANOMY = 0,
    USR_CLERK = 1,
    USR_MANG = 2,
    USR_ADMIN = 9
} account_type_t;

typedef struct {
    int id;
    account_type_t type;
    char username[30];
    char password[30];
}account_t;


typedef struct account_node {
    account_t data;
    struct account_node *next, *prev;

} account_node_t,*account_list_t;


void Account_Srv_InitSys();
//如果系统文件不存在则创建ttms系统admin匿名系统用户，权限为系统管理员

int Account_Srv_Verify(char usrName[],char pwd[]);
//验证是否存在用户

//添加新用户
int Account_Srv_Add(account_t *data);

//修改系统用户的密码
int Account_Srv_Insert(account_t *data);

//根据用户id删除系统用户
int Account_Srv_DelByID(int usrID);

//获取所有系统用户的信息
int Account_Srv_FetchAll(account_list_t list);

//根据用户名获取系统用户指针
account_node_t* Account_Srv_FindByUsrName(account_list_t list,char usrName[]);

int Account_Srv_FetchByName(char* username,account_t* user);

#endif //TTMS_C_LANG__ACCOUNT_H
