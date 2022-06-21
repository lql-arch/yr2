//
// Created by bronya on 22-6-20.
//

#ifndef TTMS_C_LANG__SALESANALYSIS_H
#define TTMS_C_LANG__SALESANALYSIS_H


#include "../Common/common.h"
#include "../Service/Play.h"
#include "../Service/Sale.h"
#include "../Common/List.h"

typedef struct {
    int play_id; 	//剧目编号
    char name[31]; 	//剧目名称
    char area[9]; 	//剧目区域
    int duration; 	//以分钟为单位
    long totaltickets; //剧目票销售数量
    long sales; 	//电影票房
    int price; 		//剧目票价
    user_date_t start_date; 	//剧目上映日期
    user_date_t end_date; 	//剧目下映日期
} salesanalysis_t;


typedef struct salesanalysis_node {
    salesanalysis_t data;
    struct salesanalysis_node *next, *prev;
} salesanalysis_node_t, *salesanalysis_list_t;

int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list);

int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount);

int Sale_Srv_FetchByTicketID(int ticket_id, sale_t *sale);

void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list);

void SalesAnalysis_Srv_addnode(salesanalysis_list_t list,salesanalysis_node_t *p);

int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate);

int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list);

void SalesAnalysis_Srv_AddToSortedList(salesanalysis_list_t list, salesanalysis_node_t* node);


#endif //TTMS_C_LANG__SALESANALYSIS_H
