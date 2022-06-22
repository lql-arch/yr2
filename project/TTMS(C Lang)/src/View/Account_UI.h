//
// Created by bronya on 22-6-20.
//

#ifndef TTMS_C_LANG__ACCOUNT_UI_H
#define TTMS_C_LANG__ACCOUNT_UI_H

#include "../Service/Account.h"
#include "../Persistence/Account_Persist.h"

void Account_UI_MgtEntry(int argc,char* name);

int Account_UI_Add(account_list_t list);

int Account_UI_Del(account_list_t list,char usrName[]);

int Account_UI_Modify(account_list_t list,char usrName[],int argc);

int Account_UI_Que(account_list_t list,char usrName[]);

int SysLogin(account_t* t);

int slg(account_t* t);

void reg();

#ifdef linux
    int getch(void);
#endif


#endif //TTMS_C_LANG__ACCOUNT_UI_H
