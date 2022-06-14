//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__PLAY_PERST_H
#define TTMS_C_LANG__PLAY_PERST_H

#include "../Service/Play.h"

//载入全部剧目
int Play_Perst_SelectAll(play_list_t date);

//存储新剧目
int Play_Perst_Insert(play_t *date);

//更新剧目
void Play_perst_Update();

//根据id去除剧目
void Play_Perst_RemByID();

//根据id载入剧目
void Play_Perst_SelectBYID();

//void EntKey_Perst_GetNewKeys();


#endif //TTMS_C_LANG__PLAY_PERST_H
