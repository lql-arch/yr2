//
// Created by bronya on 22-6-15.
//

#ifndef TTMS_C_LANG__CREAT_TICKET_PERSIST_H
#define TTMS_C_LANG__CREAT_TICKET_PERSIST_H

#include "Schedule.h"
#include "Creat_Ticket.h"

//����id�����ݳ��ƻ�
int Schedule_Perst_SelectByID(int id , schedule_t *buf);

//�洢�ݳ�Ʊ
int Ticket_Perst_Insert(ticket_list_t list);

//����idȥ���ݳ�Ʊ
int Ticket_Perst_Rem(int schedule_id);

int Ticket_Perst_FetchAll(ticket_list_t list);


#endif //TTMS_C_LANG__CREAT_TICKET_PERSIST_H
