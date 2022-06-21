//
// Created by bronya on 22-6-15.
//

#ifndef TTMS_C_LANG__CREAT_TICKET_UI_H
#define TTMS_C_LANG__CREAT_TICKET_UI_H

#include<stdio.h>
#include "../Service/Schedule.h"
#include "../Service/Creat_Ticket.h"
#include "../Service/Seat.h"


//显示与演出计划id相对应的演出计划信息，并提供生成演出票和重新生成票功能的入口
int Tick_UI_MgrEntry(int schedule_id);

void Ticket_UI_Query(void);

int Ticket_UI_ShowTicket(int ticket_id);

void Queries_Menu(void);

void Ticket_UI_ListBySch(const schedule_t *sch, ticket_list_t tickList, seat_list_t seatList);

void  Ticket_UI_Qry();

char Ticket_UI_Status2Char(ticket_status_t status);

#endif //TTMS_C_LANG__CREAT_TICKET_UI_H
