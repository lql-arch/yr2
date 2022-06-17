//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__SCHEDULE_PERSIST_H
#define TTMS_C_LANG__SCHEDULE_PERSIST_H

#include "../Service/Schedule.h"

void Create_File_Name(char id);

//���ܣ����ݾ�ĿID�����ݳ��ƻ�
int Schedule_Perst_SeletByPlay(int id,schedule_list_t buf);

//���ܣ��洢�ݳ��ƻ�
int Schedule_Perst_Insert(schedule_t *p);

//���ܣ������ݳ��ƻ�
int Schedule_Perst_Update(schedule_t *data,int play_id);

//���ܣ�����idȥ���ݳ��ƻ�
int Schedule_Perst_RemByID(int ID);

int Schedule_Persist_SetOffset(int id, Pagination_t *ptr);

int Schedule_Perst_SelectAll(schedule_list_t list);

//���ܣ���ȡʵ������
//int EntKey_Perst_GetNewKeys();

#endif //TTMS_C_LANG__SCHEDULE_PERSIST_H
