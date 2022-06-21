#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/List.h"

#include "../Common/binary_Balance_tree.h"
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list)
{
	int cnt = 0;
	assert(NULL!=list);
	play_list_t playlist;
	play_node_t *pos;
	int sold;//�洢������ЧƱ��
	salesanalysis_list_t p;
	List_Free(list,salesanalysis_node_t);
	List_Init(playlist,play_node_t);
	Play_Srv_FetchAll(playlist);

	BiTree T=NULL;
	int tall=0;

	List_ForEach(playlist,pos)
	{
		p  =   (salesanalysis_list_t)malloc(sizeof(salesanalysis_node_t));
		strcpy(p->data.area,pos->data.area);
		p->data.duration = pos->data.duration;
		p->data.end_date = pos->data.end_date;
		strcpy(p->data.name,pos->data.name);
		p->data.play_id = pos->data.id;
		p->data.price = pos->data.price;
		p->data.start_date = pos->data.start_date;
		
		p->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&sold);//Ʊ��
		p->data.totaltickets = sold;//����

		InsertAVL(&T,p->data,&tall);

		cnt++;
	}

	PreOrderTraverse(T,list);
	return cnt;

}

int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount){
	return 0;

}

int Sale_Srv_FetchByTicketID(int ticket_id, sale_t *sale){
	return 0;

}
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list)
 { 
	salesanalysis_node_t *p;    
  	if(list == NULL) return ;   
    list->prev->next = NULL;//��ѭ���Ͽ�     
	salesanalysis_list_t listleft =  list->next;//listleftָ���һ�����ݽڵ� 
	list->next = list->prev = list;//�������������Ϊ��  
	while(listleft != NULL)    
	{   
		       p = listleft;     
			    listleft = listleft->next;       
    SalesAnalysis_Srv_addnode(list,p);//+    
	}     
	return ; 
} 
void SalesAnalysis_Srv_addnode(salesanalysis_list_t list,salesanalysis_node_t *p)
{ 	salesanalysis_node_t *cur;   
   if(list == NULL)  
    {         List_AddTail(list,p);     }     
	  
   else   
  	{        
	   cur = list->next;       
	     while(cur != list)      
		    {            
				 if(p->data.sales > cur->data.sales) break;  
				            cur = cur->next;      
		   }      
		      List_InsertBefore(cur,p);    
	}   
	  return ;
 }
