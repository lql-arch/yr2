//
// Created by bronya on 22-6-14.
//

#include "Play.h"
#include "../Persistence/Play_Perst.h"

//
int Play_Srv_FetchAll(play_list_t list){
    return Play_Perst_SelectAll(list);
}

int Play_Srv_Add(play_t *date){
    return Play_Perst_Insert(date);
}


void Play_Srv_Modify(){

}


void Play_Srv_Deleteify(){

}

void Play_Srv_FetchBYID(){

}