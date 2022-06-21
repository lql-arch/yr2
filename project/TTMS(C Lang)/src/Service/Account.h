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
//���ϵͳ�ļ��������򴴽�ttmsϵͳadmin����ϵͳ�û���Ȩ��Ϊϵͳ����Ա

int Account_Srv_Verify(char usrName[],char pwd[]);
//��֤�Ƿ�����û�

//������û�
int Account_Srv_Add(account_t *data);

//�޸�ϵͳ�û�������
int Account_Srv_Insert(account_t *data);

//�����û�idɾ��ϵͳ�û�
int Account_Srv_DelByID(int usrID);

//��ȡ����ϵͳ�û�����Ϣ
int Account_Srv_FetchAll(account_list_t list);

//�����û�����ȡϵͳ�û�ָ��
account_node_t* Account_Srv_FindByUsrName(account_list_t list,char usrName[]);

int Account_Srv_FetchByName(char* username,account_t* user);

#endif //TTMS_C_LANG__ACCOUNT_H
