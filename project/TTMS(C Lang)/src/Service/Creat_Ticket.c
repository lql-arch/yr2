//
// Created by bronya on 22-6-15.
//

#include <stdio.h>
#include "Creat_Ticket.h"
#include "Play.h"
#include "../Persistence/Creat_Ticket_Persist.h"
#include "Seat.h"


int Schedule_Srv_FetchByID(int id,schedule_t* buf){
    return Schedule_Perst_SelectByID(id,buf);
}

int Ticket_Srv_GenBatch(int schedule_id){
    return Ticket_Perst_Insert(schedule_id);
}

int Ticket_Srv_DeleteBatch(int schedule_id){
    return Ticket_Perst_Rem(schedule_id);
}

//int Ticket_Srv_FetchAll(ticket_list_t list){
//
//}