#include <ctype.h>
#include "SalesAnalysis_UI.h"

//��Ժ�������а���,������ʾ��ֹĿǰ��Ժ��ӰƱ�����а�
void SalesAnalysis_UI_MgtEntry()
{
	int i;
	char choice;

	salesanalysis_list_t head;
	salesanalysis_node_t* pos;
	Pagination_t paging;

	List_Init(head, salesanalysis_node_t);
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;

	//��������
	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);
	SalesAnalysis_Srv_SortBySale(head);   //����Ʊ������
	Paging_Locate_FirstPage(head, paging);

	do
	{
#ifdef linux
        system("clear");
#endif
#ifdef WIN32
        system("cls");
#endif

		SalesAnalysis_UI_ShowList(head, paging);
		printf("\t\t\t\t*************************************************************************\n");
		printf("\t\t\t\t\t\t\t\t[P]��һҳ	|	[N]��һҳ	|	[R]����\n");
		printf("\n\t\t\t\t=========================================================================\n");
		printf("\t\t\t\t��ѡ���ܣ�");
		choice = toupper(getchar());
		while (getchar() != '\n')
			continue;

		switch (choice)
		{
            case 'P':
            case 'p':
                if (1 < Pageing_CurPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
                }
                break;
            case 'N':
            case 'n':
                if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
                }
                break;
		}
	} while (choice != 'R' && choice != 'r');
	List_Destroy(head, salesanalysis_node_t);
}

void SalesAnalysis_UI_ShowList(salesanalysis_list_t list, Pagination_t paging)
{
	int i = 0;
	salesanalysis_node_t* pos;
	printf("\t\t\t\t=========================================================================\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\tƱ��ͼ��\n");
	printf("\t\t\t\t-------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t��Ŀ��\t\t����\t\t��Ʊ��\t\tƱ��\t\t��ӳʱ��\t\t\t��ӳʱ��\n");

	Paging_ViewPage_ForEach(list, paging, salesanalysis_node_t, pos, i)
	{
		printf("\t\t\t\t\t%-10s\t%-10s\t%-5ld\t%-5ld\t%d-%d-%d\t\t%d-%d-%d\t\n",
			pos->data.name, pos->data.area, pos->data.totaltickets, pos->data.sales,
			pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day,
			pos->data.end_date.year, pos->data.end_date.month, pos->data.end_date.day);
	}
	printf("\t\t\t\t---------- �� %2d �� --------------------------- �� %2d/%2d ҳ --------\n",
		paging.totalRecords, Pageing_CurPage(paging),
		Pageing_TotalPages(paging));
}
