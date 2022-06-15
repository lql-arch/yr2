//
// Created by bronya on 22-6-15.
//

#ifndef TTMS_C_LANG__CREAT_TICKET_H
#define TTMS_C_LANG__CREAT_TICKET_H

#include "Schedule.h"

typedef enum{
    TICKET_AVL = 0,     // Ԥ��
    TICKET_SOLD = 1,    //����
    TICKET_RESV = 9     //����
}ticket_status_t;

typedef struct {
    int id;                 //Ʊid
    int schedule_id;        //�ݳ��ƻ�id
    int seat_id;            //��λid
    int price;              //Ʊ��
    ticket_status_t status; //Ʊ״̬
}ticket_t;

typedef struct ticket_node{
    ticket_t data;
    struct ticket_node *next,*prev;
}ticket_node_t,*ticket_list_t;


//����id��ȡ�ݳ��ƻ����������ݲ����е��ݳ��ƻ�id�����ó־ò㺯����ȡ��
// ���ƻ�������Ϣ�����ڵڶ�������buf��ָ���ڴ���
int Schedule_Srv_FetchByID(int id,schedule_t* buf);

//�����ļ���Ʊ����Ϣ
int Ticket_Srv_GenBatch(int schedule_id);

//����idɾ��Ʊ��Ϣ
int Ticket_Srv_DeleteBatch(int schedule_id);

int Ticket_Srv_FetchAll(ticket_list_t list);

#endif //TTMS_C_LANG__CREAT_TICKET_H
