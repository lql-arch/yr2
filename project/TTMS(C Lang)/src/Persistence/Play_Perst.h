//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__PLAY_PERST_H
#define TTMS_C_LANG__PLAY_PERST_H

#include "../Service/Play.h"

//����ȫ����Ŀ
int Play_Perst_SelectAll(play_list_t date);

//�洢�¾�Ŀ
int Play_Perst_Insert(play_t *date);

//���¾�Ŀ
void Play_perst_Update();

//����idȥ����Ŀ
void Play_Perst_RemByID();

//����id�����Ŀ
void Play_Perst_SelectBYID();

//void EntKey_Perst_GetNewKeys();


#endif //TTMS_C_LANG__PLAY_PERST_H
