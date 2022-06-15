//
// Created by bronya on 22-6-15.
//

#ifndef TTMS_C_LANG__CREAT_TICKET_PERSIST_H
#define TTMS_C_LANG__CREAT_TICKET_PERSIST_H

#include "Schedule.h"
#include "Creat_Ticket.h"

//根据id载入演出计划
int Schedule_Perst_SelectByID(int id , schedule_t *buf);

//存储演出票
int Ticket_Perst_Insert(ticket_list_t list);

//根据id去除演出票
int Ticket_Perst_Rem(int schedule_id);

int Ticket_Perst_FetchAll(ticket_list_t list);


#endif //TTMS_C_LANG__CREAT_TICKET_PERSIST_H
