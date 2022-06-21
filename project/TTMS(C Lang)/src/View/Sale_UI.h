#ifndef SALE_UI_H_
#define SALE_UI_H_

#include "../Service/Creat_Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Account.h"
//												08
/*管理售票界面*/
void GetUser(account_t* t);

void Sale_UI_MgtEntry(void);


/*售票界面*/
int Sale_UI_SellTicket(ticket_list_t ticketList,seat_list_t seatList);


/*显示演出票界面*/
void Sale_UI_ShowTicket(int scheduleID );


/*根据剧目显示演出计划界面*/
void Sale_UI_ShowScheduler(int id);

//												09
/*退票界面*/
void Sale_UI_ReturnTicket();


#endif
