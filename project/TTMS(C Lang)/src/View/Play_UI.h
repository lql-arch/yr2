//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__PLAY_UI_H
#define TTMS_C_LANG__PLAY_UI_H

#include "List.h"

//�����Ŀ����
void Play_UI_MgtEntry(int argc);

//����¾�Ŀ����
int Play_UI_Add();

//�޸ľ�Ŀ����
int Play_UI_Modify(int id);

//ɾ����Ŀ����
int Play_UI_Delete(int id);

//��ѯ��Ŀ����
int Play_UI_Query(int id,Pagination_t *paging);


#endif //TTMS_C_LANG__PLAY_UI_H
