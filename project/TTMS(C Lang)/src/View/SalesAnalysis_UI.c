#include <ctype.h>
#include "SalesAnalysis_UI.h"

//剧院销售排行榜函数,降序显示截止目前剧院电影票房排行榜
void SalesAnalysis_UI_MgtEntry()
{
	int i;
	char choice;

	salesanalysis_list_t head;
	salesanalysis_node_t* pos;
	Pagination_t paging;

	List_Init(head, salesanalysis_node_t);
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);
	SalesAnalysis_Srv_SortBySale(head);   //根据票房排序
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
		printf("\t\t\t\t\t\t\t\t[P]上一页	|	[N]下一页	|	[R]返回\n");
		printf("\n\t\t\t\t=========================================================================\n");
		printf("\t\t\t\t请选择功能：");
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
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t票房图表\n");
	printf("\t\t\t\t-------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t剧目名\t\t区域\t\t售票数\t\t票房\t\t上映时间\t\t\t下映时间\n");

	Paging_ViewPage_ForEach(list, paging, salesanalysis_node_t, pos, i)
	{
		printf("\t\t\t\t\t%-10s\t%-10s\t%-5ld\t%-5ld\t%d-%d-%d\t\t%d-%d-%d\t\n",
			pos->data.name, pos->data.area, pos->data.totaltickets, pos->data.sales,
			pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day,
			pos->data.end_date.year, pos->data.end_date.month, pos->data.end_date.day);
	}
	printf("\t\t\t\t---------- 共 %2d 项 --------------------------- 第 %2d/%2d 页 --------\n",
		paging.totalRecords, Pageing_CurPage(paging),
		Pageing_TotalPages(paging));
}
