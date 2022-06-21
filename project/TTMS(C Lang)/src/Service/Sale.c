#include"Sale.h"
#include"../Persistence/Sale_Persist.h"
#include"../Service/Creat_Ticket.h"
#include "../Persistence/Creat_Ticket_Persist.h"
#include <stdio.h>
//添加新订单信息
int Sale_Srv_Add(const sale_t *data)
{
	return Sale_Perst_Insert(data);
}

int Ticket_Srv_Modify(const ticket_t *data){
	return Ticket_Perst_Update(data);
}

int Ticket_Srv_FetchBySchID(int ID, ticket_list_t *list){
	return Ticket_Srv_SelBySchID(ID,list);
}

ticket_node_t * Ticket_Srv_FetchBySeatID(ticket_list_t list , int seat_id){
	ticket_node_t *pos;
	List_ForEach(list, pos){
		if(pos->data.id == seat_id )
		{
			return pos;
		}
	}
	return NULL;
}

int Sale_Srv_FetchByTicketID(int ticket_id, sale_t* sale)
{
	return Sale_Perst_SelectByTicketID(ticket_id, sale);
}
