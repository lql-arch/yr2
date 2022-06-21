#ifndef SALE_H_
#define SALE_H_


#include "../Common/common.h"
#include "../Service/Schedule.h"
#include "../Service/Seat.h"
#include "../Service/Creat_Ticket.h"
#include "../Service/Play.h"
//												08
typedef enum
{
	SALE_SELL = 1,  	//
	SALE_REFOUND = -1   //
}sale_type_t;

typedef struct
{
	long id;    	 		//
	int user_id;    		//
	int ticket_id;    		//
	ttms_date_t date;    	//
	ttms_time_t time;    	//
	int value;      		//
	sale_type_t type;     	//
}sale_t;


typedef struct sale_node
{
	sale_t data;
	struct sale_node *next;
	struct sale_node *prev;
}sale_node_t,*sale_list_t;


/*添加新订单信息*/
int Sale_Srv_Add(const sale_t *data);


/*修改票状态*/
int Ticket_Srv_Modify(const ticket_t *data);

/*根据演出计划ID获取票的数据*/
int Ticket_Srv_FetchBySchID(int ID, ticket_list_t *list);

/*根据ID获取票*/
ticket_node_t * Ticket_Srv_FetchBySeatID(ticket_list_t list , int seat_id);


void Ticket_UI_ShowList(ticket_list_t ticket, Pagination_t paging);



#endif
