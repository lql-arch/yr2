//
// Created by bronya on 22-6-15.
//

#ifndef TTMS_C_LANG__CREAT_TICKET_PERSIST_H
#define TTMS_C_LANG__CREAT_TICKET_PERSIST_H

#include "Schedule.h"
#include "Creat_Ticket.h"
#include "Seat.h"


//����id�����ݳ��ƻ�
int Schedule_Perst_SelectByID(int id , schedule_t *buf);

//�洢�ݳ�Ʊ
int Ticket_Perst_Insert(int schedule_id,int studio_id);

//����idȥ���ݳ�Ʊ
int Ticket_Perst_Rem(int schedule_id);

int Ticket_Perst_FetchAll(ticket_list_t list);

int Ticket_Perst_SelByID(int id, ticket_t *buf);

int Ticket_Perst_SelectAll(ticket_list_t list);

#endif //TTMS_C_LANG__CREAT_TICKET_PERSIST_H
