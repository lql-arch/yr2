//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__PLAY_UI_H
#define TTMS_C_LANG__PLAY_UI_H

#include "List.h"
#include "Play.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "Schedule_UI.h"
#include <stdio.h>

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

//�жϿ�ʼ�ͽ���ʱ���Ƿ�����
int isTime(play_t t);

void Play_UI_ShowList(play_list_t list,Pagination_t paging);//���溯��

#endif //TTMS_C_LANG__PLAY_UI_H