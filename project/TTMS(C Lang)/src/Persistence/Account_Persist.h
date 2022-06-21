//
// Created by bronya on 22-6-20.
//

#ifndef TTMS_C_LANG__ACCOUNT_PERSIST_H
#define TTMS_C_LANG__ACCOUNT_PERSIST_H

#include "../Service/Account.h"

//判断系统用户文件是否存在
int Account_perst_CheckAccFile();

//将data所指的系统用户插入文件Account.dat里
int Account_Perst_Insert(account_t *data);

//将data指向的系统用户更新到系统用户文件里
int Account_Perst_Update(account_t *data);

//根据系统id查找匹配的系统用户信息，并从文件里删除
int Account_Perst_RemByID(int id);

//遍历读取文件，构建list链表
int Account_Perst_SelectAll(account_list_t list);

int Account_Perst_Verify(char usrName[],char pwd[]);

#endif //TTMS_C_LANG__ACCOUNT_PERSIST_H
