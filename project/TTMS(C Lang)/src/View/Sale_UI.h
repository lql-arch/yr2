#ifndef SALE_UI_H_
#define SALE_UI_H_

#include "../Service/Creat_Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Account.h"
//												08
/*������Ʊ����*/
void GetUser(account_t* t);

void Sale_UI_MgtEntry(void);


/*��Ʊ����*/
int Sale_UI_SellTicket(ticket_list_t ticketList,seat_list_t seatList);


/*��ʾ�ݳ�Ʊ����*/
void Sale_UI_ShowTicket(int scheduleID , int play_id);


/*���ݾ�Ŀ��ʾ�ݳ��ƻ�����*/
void Sale_UI_ShowScheduler(int id);

//												09
/*��Ʊ����*/
void Sale_UI_ReturnTicket();


#endif
