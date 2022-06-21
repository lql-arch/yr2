//
// Created by bronya on 22-6-20.
//

#ifndef TTMS_C_LANG__ACCOUNT_PERSIST_H
#define TTMS_C_LANG__ACCOUNT_PERSIST_H

#include "../Service/Account.h"

//�ж�ϵͳ�û��ļ��Ƿ����
int Account_perst_CheckAccFile();

//��data��ָ��ϵͳ�û������ļ�Account.dat��
int Account_Perst_Insert(account_t *data);

//��dataָ���ϵͳ�û����µ�ϵͳ�û��ļ���
int Account_Perst_Update(account_t *data);

//����ϵͳid����ƥ���ϵͳ�û���Ϣ�������ļ���ɾ��
int Account_Perst_RemByID(int id);

//������ȡ�ļ�������list����
int Account_Perst_SelectAll(account_list_t list);

int Account_Perst_Verify(char usrName[],char pwd[]);

#endif //TTMS_C_LANG__ACCOUNT_PERSIST_H
