#include "StaSales.h"
#include "../Common/List.h"
#include "../Common/common.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Account_Persist.h"
#include <stdio.h>


int StaSales_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate){
	int amount=0;//存放销售额
	sale_list_t saleList;
	sale_list_t p;
	
	List_Init(saleList,sale_node_t);
	Sale_Perst_SelByID(saleList,usrID);//saleList存储id对应的销售记录链表
	List_ForEach(saleList,p)
	{
		if( (p->data.date.year)*10000+(p->data.date.month)*100+(p->data.date.day)  >=  (stDate.year)*10000+(stDate.month)*100+(stDate.day)  &&  (p->data.date.year)*10000+(p->data.date.month)*100+(p->data.date.day)  <=  (endDate.year)*10000+(endDate.month)*100+(endDate.day) )
		{
			amount++;
		}
	}
	
	return amount;
}
