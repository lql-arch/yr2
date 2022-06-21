#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "Sale.h"
#include "../Service/Creat_Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/List.h"
#include "add.h"
#include "../Persistence/Sale_Persist.h"
//#include "../Common/binary_Balance_tree.h"

int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list)
{
    assert(list != NULL);

    int count = 0;
    int sold = 0;
    int total;
    play_list_t playList;
    play_node_t* pos;


    List_Free(list, salesanalysis_node_t);

    List_Init(playList, play_node_t);

    Play_Srv_FetchAll(playList);
    List_ForEach(playList, pos)
    {

        user_date_t curDate = DateNow();
        user_date_t tmp;
        tmp.year = pos->date.start_date.year;
        tmp.month = pos->date.start_date.month;
        tmp.day = pos->date.start_date.day;

        if (DateCmp(tmp, curDate) <= 0)	//找到上映剧目
        {
            salesanalysis_node_t* newNode =
                    (salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));//建立新块， 录入数据
            newNode->data.duration = pos->date.duration;

            newNode->data.start_date.day = pos->date.start_date.day;
            newNode->data.start_date.month = pos->date.start_date.month;
            newNode->data.start_date.year = pos->date.start_date.year;

            newNode->data.end_date.day = pos->date.end_date.day;
            newNode->data.end_date.year = pos->date.end_date.year;
            newNode->data.end_date.month = pos->date.end_date.month;


            strcpy(newNode->data.name, pos->date.name);

            newNode->data.price = pos->date.price;
            newNode->data.play_id = pos->date.id;
            strcpy(newNode->data.area, pos->date.area);
            //还差sales和totaltickets
            newNode->data.sales = Schedule_Srv_StatRevByPlay(pos->date.id, &sold);
            newNode->data.totaltickets = sold;

            //创建
            List_AddTail(list, newNode);
            count++;
        }
    }
    List_Destroy(playList, play_node_t);
    return count;
}


//int SalesAnalysis_Srv_StaticSale2(salesanalysis_list_t list)
//{
//	int cnt = 0;
//	assert(NULL!=list);
//	play_list_t playlist;
//	play_node_t *pos;
//	int sold;//存储已售有效票数
//	salesanalysis_list_t p;
//	List_Free(list,salesanalysis_node_t);
//	List_Init(playlist,play_node_t);
//	Play_Srv_FetchAll(playlist);
//
//	BiTree T = NULL;
//	int tall=0;
//
//	List_ForEach(playlist,pos)
//	{
//		p  =   (salesanalysis_list_t)malloc(sizeof(salesanalysis_node_t));
//		strcpy(p->data.area,pos->date.area);
//		p->data.duration = pos->date.duration;
//		p->data.end_date = pos->date.end_date;
//		strcpy(p->data.name,pos->date.name);
//		p->data.play_id = pos->date.id;
//		p->data.price = pos->date.price;
//		p->data.start_date = pos->date.start_date;
//
//		p->data.sales = Schedule_Srv_StatRevByPlay(pos->date.id,&sold);//票房
//		p->data.totaltickets = sold;//上座
//
//		InsertAVL(&T,p->data,&tall);
//
//		cnt++;
//	}
//
//	PreOrderTraverse(T,list);
//	return cnt;
//
//}


void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list)
{
	salesanalysis_node_t *p;

  	if(list == NULL)
          return ;
    list->prev->next = NULL;//将循环断开     
	salesanalysis_list_t listLeft = list->next;
    //listleft指向第一个数据节点
	list->next = list->prev = list;//将list链表置为空
	while(listLeft != NULL)
	{   
        p = listLeft;
        listLeft = listLeft->next;
        SalesAnalysis_Srv_addnode(list,p);
	}
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


int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate)
{
    int amount = 0;
    sale_list_t saleList;
    List_Init(saleList, sale_node_t);
    sale_node_t* pSale;
    Sale_Perst_SelByUsrID(saleList, usrID);
    List_ForEach(saleList, pSale)
    {
        user_date_t tmp ;
        tmp.day = pSale->data.date.day;
        tmp.month = pSale->data.date.month;
        tmp.year = pSale->data.date.year;

        if (DateCmp(tmp, stDate) >= 0 && DateCmp(tmp, endDate) <= 0)
            amount += pSale->data.value;
    }
    return amount;
}



int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list)
{
    assert(list != NULL);

    int count = 0;
    int sold = 0;
    int total;
    play_list_t playList;
    play_node_t* pos;


    List_Free(list, salesanalysis_node_t);

    List_Init(playList, play_node_t);

    Play_Srv_FetchAll(playList);
    List_ForEach(playList, pos)
    {

        user_date_t curDate = DateNow();
        user_date_t tmp ;
        tmp.day = pos->date.start_date.day;
        tmp.month = pos->date.start_date.month;
        tmp.year = pos->date.start_date.year;
        user_date_t tmp2 ;
        tmp2.day = pos->date.end_date.day;
        tmp2.month = pos->date.end_date.month;
        tmp2.year = pos->date.end_date.year;

        if (DateCmp(tmp, curDate) <= 0)	//找到上映剧目
        {
            salesanalysis_node_t* newNode =(salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));//建立新块， 录入数据
            newNode->data.duration = pos->date.duration;
            newNode->data.start_date = tmp;
            newNode->data.end_date = tmp2;
            strcpy(newNode->data.name, pos->date.name);

            newNode->data.price = pos->date.price;
            newNode->data.play_id = pos->date.id;
            strcpy(newNode->data.area, pos->date.area);
            //还差sales和totaltickets
            newNode->data.sales = Schedule_Srv_StatRevByPlay(pos->date.id, &sold);
            newNode->data.totaltickets = sold;

            //创建
            List_AddTail(list, newNode);
            count++;
        }
    }
    List_Destroy(playList, play_node_t);
    return count;
}

void SalesAnalysis_Srv_AddToSortedList(salesanalysis_list_t list, salesanalysis_node_t* node)
{
    if (list->next == list)
    {
        List_AddTail(list, node);
        return;
    }

    salesanalysis_node_t* curpos;
    List_ForEach(list, curpos)
    {
        if (node->data.sales > curpos->data.sales)
        {
            List_InsertBefore(curpos, node);
            return;
        }
    }
    if (curpos == list)
    {
        List_AddTail(list, node);
        return;
    }
}

