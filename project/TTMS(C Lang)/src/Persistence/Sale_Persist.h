#ifndef TTMS_C_LANG__SALE_PERSIST_H_
#define TTMS_C_LANG__SALE_PERSIST_H_


#include "../Service/Sale.h"

/*�洢�¶�����Ϣ*/
int Sale_Perst_Insert(sale_t *data);

/*����Ʊ״̬*/
int Ticket_Perst_Update(ticket_t *data);

/*�����ݳ��ƻ�ID����Ʊ������*/
int Ticket_Srv_SelBySchID(int id,ticket_list_t list);

int Sale_Srv_FetchByTicketID(int ticket_id, sale_t* sale);

int Sale_Perst_SelectByTicketID(int ticket_id, sale_t* sale);

int Sale_Perst_SelectAll(sale_list_t list);

int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale);

//int Sale_Perst_SelectByName(sale_list_t list, char condt[]);

int Sale_Perst_SelectByID(int ticket_ID, sale_t *buf);

int Sale_Perst_Update( sale_t *data);

int Sale_Perst_RemByID(int ID);

int Sale_Perst_SelByUsrID(sale_list_t  saleList, int usrID);

int Sale_Perst_SelByID (sale_list_t list, int usrID);

#endif //TTMS_C_LANG__SALE_PERSIST_H_
