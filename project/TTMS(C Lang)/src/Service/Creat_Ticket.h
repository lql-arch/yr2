//
// Created by bronya on 22-6-15.
//

#ifndef TTMS_C_LANG__CREAT_TICKET_H
#define TTMS_C_LANG__CREAT_TICKET_H

#include "Schedule.h"

typedef enum{
    TICKET_AVL = 0,     // 预售
    TICKET_SOLD = 1,    //已售
    TICKET_RESV = 9     //待售
}ticket_status_t;

typedef struct {
    int id;                 //票id
    int schedule_id;        //演出计划id
    int seat_id;            //座位id
    int price;              //票价
    ticket_status_t status; //票状态
}ticket_t;

typedef struct ticket_node{
    ticket_t data;
    struct ticket_node *next,*prev;
}ticket_node_t,*ticket_list_t;


//根据id获取演出计划函数，根据参数中的演出计划id，调用持久层函数获取演
// 出计划，将信息保存在第二个参数buf所指的内存中
int Schedule_Srv_FetchByID(int id,schedule_t* buf);

//增加文件中票的信息
int Ticket_Srv_GenBatch(int schedule_id);

//根据id删除票信息
int Ticket_Srv_DeleteBatch(int schedule_id);

int Ticket_Srv_FetchAll(ticket_list_t list);

#endif //TTMS_C_LANG__CREAT_TICKET_H
