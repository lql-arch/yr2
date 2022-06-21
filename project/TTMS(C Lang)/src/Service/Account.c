//
// Created by bronya on 22-6-20.
//

#include <stdio.h>
#include <string.h>
#include "Account.h"
#include "../Persistence/Account_Persist.h"

account_t gl = {0,USR_ANOMY,"Anonymous","123456"};

void Account_Srv_InitSys(){
    if(!Account_perst_CheckAccFile()){
        account_t t = {0,USR_ADMIN,"tmp_admin","123456"};
        Account_Srv_Add(&t);
    }
}

int Account_Srv_Verify(char usrName[],char pwd[]){
    if(Account_perst_CheckAccFile() == 0){
        return 0;
    }
    return Account_Perst_Verify(usrName,pwd);
}

int Account_Srv_Add(const account_t *data){
    return Account_Perst_Insert(data);
}

int Account_Srv_Insert(const account_t *data){
    return Account_Perst_Update(data);
}

int Account_Srv_DelByID(int usrID){
    return Account_Perst_RemByID(usrID);
}

int Account_Srv_FetchAll(account_list_t list){
    return Account_Perst_SelectAll(list);
}

account_node_t* Account_Srv_FindByUsrName(account_list_t list,char usrName[]){
    account_node_t *p = list->next;
    int flag = 0;
    while(p != list){
        if(strcmp(p->data.username,usrName) == 0){
            flag = 1;
            break;
        }
        p = p->next;
    }

    return flag == 1 ? p : NULL;
}