//
// Created by bronya on 22-6-13.
//
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include "Creat_Ticket_UI.h"
#include "Schedule_Persist.h"
#include "Creat_Ticket.h"
#include "Creat_Ticket_Persist.h"
#include <stdio.h>
#include <string.h>
#include "../Service/Studio.h"
//�����ݳ�����
//�����Ŀ���棬�б���ʾ
void Schedule_UI_MgtEntry(int argc);

//������ݳ��ƻ�����
int Schedule_UI_Add(int play_id);

//�޸��ݳ��ƻ�����
int  Schedule_UI_Modify(int id);

//ɾ���ݳ��ƻ�����
int Schedule_UI_Delete(int id);

//�����ݳ�Ʊ����
//void Ticket_UI_MgtEntry();

void  Schedule_UI_ListAll(void);

void Schedule_UI_ShowList(schedule_list_t list, Pagination_t paging);