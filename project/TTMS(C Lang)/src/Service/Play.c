//
// Created by bronya on 22-6-14.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include "Play.h"
#include "../Persistence/Play_Perst.h"
#include "List.h"


int Play_Srv_FetchAll(play_list_t list){
    return Play_Perst_SelectAll(list);
}

int Play_Srv_Add(play_t *date){
    return Play_Perst_Insert(date);
}


int Play_Srv_Modify(play_t *t){
    return Play_perst_Update(t);
}


int Play_Srv_Deleteify(int id){
    return Play_Perst_RemByID(id);
}


int Play_Srv_FetchByID(int id,play_t *date){
    return Play_Perst_SelectByID(id,date);
}


int Play_SetOffset(int id, Pagination_t *paging){
    return Play_Perst_SetOffset(id,paging);
}