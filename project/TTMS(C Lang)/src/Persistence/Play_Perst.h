//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__PLAY_PERST_H
#define TTMS_C_LANG__PLAY_PERST_H


#include "../Service/Play.h"
#include "EntityKey_Persist.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include "../View/Play_UI.h"

//����ȫ����Ŀ
int Play_Perst_SelectAll(play_list_t date);

//�洢�¾�Ŀ
int Play_Perst_Insert(play_t *date);

//���¾�Ŀ
int Play_perst_Update(play_t *t);

//����idȥ����Ŀ
int Play_Perst_RemByID(int id);

//����id�����Ŀ
int Play_Perst_SelectByID(int id,play_t *date);

int Play_Perst_SetOffset(int id, Pagination_t *paging);

//void EntKey_Perst_GetNewKeys();


#endif //TTMS_C_LANG__PLAY_PERST_H
