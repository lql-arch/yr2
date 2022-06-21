#include "SalesAnalysis_UI.h"
#include "../Common/List.h"
#include "../Service/Account.h"
#include "../Service/Ticket.h"
#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Sale.h"
#include "../Service/SalesAnalysis.h"
#include<stdio.h>
#include <stdlib.h>

const int SALESANALYSIS_PAGE_SIZE = 5;
void SalesAnalysis_UI_MgtEntry ()//��ʾ��ĿƱ����Ϣ 
{
    int i, id;
	char choice;
	salesanalysis_list_t head;
	salesanalysis_node_t *pos;
	Pagination_t paging;

	List_Init(head, salesanalysis_node_t);
	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
 
	
	paging.totalRecords = SalesAnalysis_Srv_StaticSale(head);
	Paging_Locate_FirstPage(head, paging);

    
    
	do {
      
		printf(
				"\n===================================================================\n");
		printf(
				"************************** Ʊ����Ϣ *******************************\n");
		printf("%6s %20s  %8s  %5s  %20s  %5s %5s %5s\n", "��ĿID", "��Ŀ����", "��Ʒ����",
				"ʱ��", "��ӳʱ��","��������","Ʊ��","Ʊ��");
		printf(
				"-------------------------------------------------------------------\n");
            Paging_ViewPage_ForEach(head, paging, salesanalysis_node_t, pos, i)
			printf("%6d %20s  %8s  %5d  %d/%d/%d->%d/%d/%d  %5d %5d %5d\n", pos->data.play_id,pos->data.name,pos->data.area,pos->data.duration
            ,pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day,pos->data.totaltickets
			,pos->data.sales,pos->data.price);

		printf(
				"------- ��:%2dҳ ---------------------------------- ҳ�� :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        printf(
				"*******************************************************************\n");
		printf(
				"[P]��һҳ   |   [N]��һҳ   |   [R]�����ϲ�");
		printf(
				"\n\n\n\n===================================================================\n");
        printf("��������Ҫ���еĲ���:");
		fflush(stdin);
        setbuf(stdin,NULL);
		scanf("%c", &choice);
		setbuf(stdin,NULL);
        printf("choice = %c",choice);
		fflush(stdin);

		switch (choice) {
		case 'p':
		case 'P':
            
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
			}
			break;
		case 'n':
		case 'N':
            
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
			}
			break;
		}
	} while (choice == 'r'||choice == 'R');
	List_Destroy(head, salesanalysis_node_t);
}
