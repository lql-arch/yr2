//
// Created by bronya on 22-6-15.
//

#include <stdio.h>
#include "Creat_Ticket.h"
#include "Play.h"
#include "../Persistence/Creat_Ticket_Persist.h"
#include "Seat.h"
#include "Studio.h"


int Schedule_Srv_FetchByID(int id,schedule_t* buf){
    return Schedule_Perst_SelectByID(id,buf);
}

int Ticket_Srv_GenBatch(int schedule_id,int studio_id){

    return Ticket_Perst_Insert(schedule_id,studio_id);
}

int Ticket_Srv_DeleteBatch(int schedule_id){
    return Ticket_Perst_Rem(schedule_id);
}

int Ticket_Srv_FetchByID(int id,ticket_t *buf)
{
    return Ticket_Perst_SelByID(id,buf);
}

int Ticket_Srv_FetchSold(ticket_list_t list, ticket_list_t listSold)
{
    int retval = 0;
    ticket_node_t* node;
    List_ForEach(list, node)
    {
        if (node->data.status == TICKET_SOLD)
        {
            ticket_node_t* newNode = (ticket_node_t*)malloc(sizeof(ticket_node_t));
            newNode->data = node->data;
            List_AddTail(listSold, newNode);
            retval++;
        }
    }
    return retval;
}

int Ticket_Srv_FetchAll(ticket_list_t list)
{
    return Ticket_Perst_SelectAll(list);
}