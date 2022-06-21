#include<stdio.h>

#include"../Service/Play.h"							//MgtEnt
#include"../Service/Seat.h"
#include"../Common/List.h"
#include "./Sale_UI.h"
#include"../Persistence/Play_Perst.h"	//无对应函数所进行取代引入
#include"../Service/Schedule.h"						//ShowTicket
#include"../Service/Creat_Ticket.h"
#include"../Service/Account.h"						//SellTicket
#include "../Service/Sale.h"
#include "EntKey.h"
#include "Schedule_UI.h"
#include "../Service/Sale.h"
#include "../Service/Seat.h"

static const int SALESANALYSIS_PAGE_SIZE = 5;
static const int PLAY_PAGE_SIZE = 5;
static const int SCHEDULE_PAGE_SIZE = 5;
static const int TICKET_PAGE_SIZE = 5;

account_t User;

void GetUser(account_t* t){
    User = *t;
}

/*管理售票界面*/
void Sale_UI_MgtEntry(void){
    int i;
    char ch;
	play_list_t list;		//创建	剧目 	链表
	play_node_t* pos;
	List_Init(list,play_node_t);//初始化

	Pagination_t paging;	//设置分页器
	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;

	paging.totalRecords = Play_Srv_FetchAll(list);//调用函数获取总记录数
	Paging_Locate_FirstPage(list, paging);//页面定位到链表第一页


	char choice;
	do{				//设置长度为83个字符

//        while((ch = getchar()) != '\n')
//            continue;
        setbuf(stdin,NULL);

        printf(
	            "\n =========================================================================================================\n");
	    printf(
	            " ********************************LIST OF PLAYS**************************************************************\n");
	    printf(
	            " %2s %10s %10s %13s %9s %9s %14s %12s %10s\n",
	            "id","name","type","area","rating","duration","star_date","end_date","price");
        Paging_ViewPage_ForEach(list, paging, play_node_t, pos, i) {
            printf(" %2d %16s %4d %13s %6d %10d %10d.%2d.%2d %8d.%2d.%2d %7d\n",
                   pos->date.id, pos->date.name, pos->date.type, pos->date.area, pos->date.rating, pos->date.duration,
                   pos->date.start_date.year, pos->date.start_date.month, pos->date.start_date.day,
                   pos->date.end_date.year, pos->date.end_date.month, pos->date.end_date.day,
                   pos->date.price);
        }
	    printf(
				" ---------------- Total Records:%2d ------------------------------ Page %2d/%2d ----------------------------\n",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
	    printf(
				" ***********************************************************************************************************\n");

	    printf(
				" [C]ShowScheduler  [S]earchByName  [F]ilterByName  [P]revPage   [N]extPage   [R]eturn\n");

	    printf(
				" ===========================================================================================================\n");

		printf("YOUR CHOICE:");
        fflush(stdout);
		scanf("%c",&choice);

		char name[30];
		switch(choice){
		case'c':			//通过id寻找演出计划
		case'C':
			printf("Please input the ID you want to search:");
			int id;
			scanf("%d",&id);
            Sale_UI_ShowScheduler(id);	//
			break;

		case's':			//查询剧目名称
		case'S':
			printf("Please input the name you want to search:");
			scanf("%s",name);
                setbuf(stdin,NULL);
			paging.totalRecords = Play_Perst_SelectByName(list,name);
			Paging_Locate_FirstPage(list, paging);
			break;

		case'f':
		case'F':
			printf("Please input the name you want to filter:");
			scanf("%s",name);

//			assert(list != NULL);		//根据名称筛选剧目
			int t = 0;
			play_node_t* p;
			play_node_t* temp;
			List_ForEach(list, p) {
                if (!strcmp(p->date.name, name)) {
                    temp = p;
                    p = p->prev;
                    List_FreeNode(temp);
                    t++;
                }
            }

			paging.totalRecords -= t;
			Paging_Locate_FirstPage(list, paging);
			break;

		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, -1, play_node_t);
			}
			break;

		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
			}
			break;
        case 'r':
        case 'R':
            break;
		}
	}while(choice !='r' && choice !='R');

	//释放空间
	List_Destroy(list, play_node_t);

    setbuf(stdin,NULL);
}





/*根据剧目显示演出计划界面*/
void Sale_UI_ShowScheduler(int id){

    int tk_id;
    char ch;
    int i = 0;
	schedule_list_t list;		//创建	演出厅		链表
	schedule_node_t *pos;

    play_t play_temp;			//根据ID判断是否存在剧目
    if(!Play_Srv_FetchByID(id,&play_temp)){
        fprintf(stderr,"Error:%d does not exist.\nPress [Enter] key to return!\n",id);
        getchar();
        return ;
    }

	List_Init(list,schedule_node_t);//初始化

	Pagination_t paging;	//设置分页器
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = Schedule_Srv_FetchByPlay(id,list);//调用函数获取总记录数
	Paging_Locate_FirstPage(list,paging);//页面定位到链表第一页


	char choice;
	do{
#ifdef linux
        system("clear");
#endif
#ifdef WIN32
        system("cls");
#endif

        setbuf(stdin,NULL);

	    printf(
		        "\n ===================================================================================\n");
	    printf(
	            " ************************************LIST OF PLAYS**********************************\n");
	    printf(
	            " %10s %15s %15s %10s %10s %15s\n","id","play_id","studio_id","date","time","seat_count");
	    if(!List_IsEmpty(list)){		//判断剧目演出厅是否为空
	    	Paging_ViewPage_ForEach(list,paging,schedule_node_t,pos,i)
	    	{		printf( " %10d %12d %13d %13d/%02d/%02d %5dh%02dm%02ds %9d\n",
						pos->date.id,pos->date.play_id,pos->date.studio_id,
						pos->date.date.hour,pos->date.date.minute,pos->date.date.second,
						pos->date.time.hour,pos->date.time.minute,pos->date.time.second,
						pos->date.seat_count);}
	    }
	    else{
	    	printf("COULD NOT FIND ANY PLAYS !\n");
	    }
	    printf(" ---------------- Total Records:%2d ------------------------------ Page %2d/%2d ----\n",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
	    printf(" ***********************************************************************************\n");
	    printf("         Show[T]icket         [P]revPage        [N]extPage      [R]eturn      \n");
	    printf(" ===================================================================================\n");

	    printf("Your Choice:");
	    scanf("%c",&choice);

        while((ch = getchar()) != '\n')
            continue;

		switch(choice){
		case 't':
		case 'T':
			printf("\nPlease Input The Schedule_ID:");
			scanf("%d",&tk_id);
			Sale_UI_ShowTicket(tk_id,id);
			break;

		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, -1, schedule_node_t);
			}
			break;

		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, 1, schedule_node_t);
			}
			break;
		}
	}while(choice !='r' && choice !='R');

	List_Destroy(list,schedule_node_t);
}

/*显示演出票界面*/
void Sale_UI_ShowTicket(int scheduleID , int play_id){
	schedule_t sch;
	play_t pla;
    studio_t studioRec;
	seat_list_t sea;
	ticket_list_t tic;


	while(!Schedule_Srv_FetchByID(scheduleID,&sch))		//判断 演出计划ID 是否存在
	{
		printf("Schedule_ID is Wrong !\nRepeat:");
		scanf("%d",&scheduleID);
	}

    if(!Studio_Srv_FetchByID(sch.studio_id, &studioRec)){
        fprintf(stdout,"Room does not exist!\n按下[Enter]返回.\n");
        getchar();
        return;
    }

	if(!Seat_Srv_FetchByRoomID(sea , sch.studio_id)){
        fprintf(stdout,"Studio_ID is Wrong !\n按下[Enter]返回.\n");
        getchar();
        return;
    }

	if(!Ticket_Srv_FetchBySchID(scheduleID,&tic)){
        fprintf(stdout,"票务获取失败!\n按下[Enter]返回.\n");
        getchar();
        return;
    }

    printf("tic:\n");
    ticket_node_t* pow ;
    List_ForEach(tic,pow){
        printf("%d %d %d\n",pow->data.id,pow->data.schedule_id,pow->data.seat_id);
    }


    char choice;
     printf("              [R]返回上一页 						  [B]购票:");
     scanf("%s",&choice);
     if(choice == 'r' || choice == 'R'){
         return ;
     }
     Sale_UI_SellTicket(tic, sea);


	List_Destroy(tic, ticket_node_t);
	List_Destroy(sea, seat_node_t);
}


/*售票界面*/
int Sale_UI_SellTicket(ticket_list_t tickList,seat_list_t seatList){

	int row,col;
	printf("Please Input The   row    About This Seat: ");
	scanf("%d",&row);
	printf("Please Input The   col    About This Seat: ");
	scanf("%d",&col);
    while (getchar() != '\n')
        continue;

    schedule_t sch;
    seat_node_t* seat;
    ticket_node_t* ticket;
    sale_t sale;
    seat_t tseat;
    ticket_t tticket;
    Schedule_Srv_FetchByID(tickList->next->data.schedule_id, &sch); //获取安排信息
    Ticket_UI_ListBySch(&sch,tickList,seatList);

    if ((seat = Seat_Srv_FindByRowCol(seatList, row, col)) == NULL || seat->data.status != SEAT_GOOD)
    {
		printf("Wrong ROW and COL !\n");
        while (getchar() != '\n')
            continue;
        return 0;
	}

    if (seat->data.status == SEAT_NONE)
    {
        printf("Not For Useing !");
        while (getchar() != '\n')
            continue;
        return 0;
    }


    if (seat->data.status == SEAT_BROKEN)
    {
        printf("Seat Broken !");
        while (getchar() != '\n')
            continue;
        return 0;
    }

    if ((ticket = Ticket_Srv_FetchBySeatID(tickList, seat->data.id)) == NULL)
    {
        printf("Get Ticket Failed");
        while (getchar() != '\n')
            continue;
        return 0;
    }

    if (TICKET_SOLD == ticket->data.status)
    {
        printf("Ticket has been Sold !");
        while (getchar() != '\n')
            continue;
        return 0;
    }

    sale.date.year = DateNow().year; //设置销售数据
    sale.date.day = DateNow().day ;
    sale.date.month = DateNow().month;

    sale.time.second = TimeNow().second;
    sale.time.minute = TimeNow().minute;
    sale.time.hour = TimeNow().hour;

    sale.user_id = User.id;
    sale.id = EntKey_Srv_CompNewKey("Sale");
    sale.ticket_id = ticket->data.id;
    sale.value = ticket->data.price;
    sale.type = SALE_SELL;
    while (getchar() != '\n')
        continue;

    ticket->data.status = TICKET_SOLD;

    tticket = ticket->data;

    Ticket_Srv_Modify(&tticket);

    Sale_Srv_Add(&sale);
    printf("Ticket Sell Success!");
    Ticket_UI_ShowTicket(ticket->data.id);
    while (getchar() != '\n')
        continue;
    return 1;

}

/*退票界面*/
void Sale_UI_ReturnTicket(void){

//退票的   剧目   选择界面
    char ch;
	int play_id;
	play_list_t plist;		//创建	剧目 	链表
	List_Init(plist,play_node_t);//初始化

	Pagination_t paging;	//设置分页器
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;
	paging.totalRecords = Play_Srv_FetchAll(plist);//调用函数获取总记录数
	Paging_Locate_FirstPage(plist,paging);//页面定位到链表第一页

	Play_UI_ShowList(plist,paging);

    printf("Please Input The Play_ID :");
	scanf("%d",&play_id);
    getchar();
	play_t play;
	while (Play_Srv_FetchByID(play_id, &play) == 0)
	{
		printf("Wrong Play_ID ! Reapeat Again :");
		scanf("%d", &play_id);
	}

	List_Destroy(plist, play_node_t);


//退票的  演出厅计划   选择
	int schedule_id;
	schedule_list_t slist;		//创建	演出厅		链表
	List_Init(slist,schedule_node_t);//初始化

	paging.pageSize = SCHEDULE_PAGE_SIZE;
	paging.totalRecords = Schedule_Srv_FetchByPlay(play_id,slist);//调用函数获取总记录数
	Paging_Locate_FirstPage(slist,paging);//页面定位到链表第一页

    setbuf(stdin,NULL);

    Schedule_UI_ShowList(slist,paging);


	printf("Please Input The Schedule_id :");
	scanf("%d",&schedule_id);

	schedule_t schedule;
	while (Schedule_Srv_FetchByID(schedule_id, &schedule) == 0)
	{
		printf("Wrong Schedule_ID ! Reapeat Again :");
		scanf("%d", &schedule_id);
	}
	List_Destroy(slist, schedule_node_t);


//正式退票区
	ticket_list_t tlist;
    ticket_t ticket;
	List_Init(tlist,ticket_node_t);

	paging.pageSize = TICKET_PAGE_SIZE;
	paging.totalRecords = Ticket_Srv_FetchBySchID( schedule_id,tlist);
	Paging_Locate_FirstPage(tlist, paging);

	int ticket_id;
    char choice;
	scanf("%d",&ticket_id);
	while (Ticket_Srv_FetchByID(ticket_id, &ticket) == 0 || ticket.status == TICKET_AVL)
	{
		printf("Wrong Ticket_ID ! Reapeat Again :");
		scanf("%d", &ticket_id);
	}

	printf("\n ===================================================================================\n");
	printf(" ******************************  RETURN           TICKETS  ***************************\n");

	Ticket_UI_ShowList(tlist, paging);

	printf(
			" *************************************************************************************\n");
	printf("								[Q]uit              [R]eturn");


	do{
		printf("YOUR CHOICE :");
		scanf("%c",&choice);
		switch(choice){
		case'Q':
		case'q': {
            ticket.status = TICKET_AVL;
            sale_t data;
            data.id = EntKey_Srv_CompNewKey("Sale");

            data.user_id = User.id;
            data.ticket_id = ticket_id;


            data.date.year = DateNow().year;
            data.date.month = DateNow().month;
            data.date.day = DateNow().day;

            data.time.hour = TimeNow().hour;
            data.time.minute = TimeNow().minute;
            data.time.second = TimeNow().second;

            data.value = ticket.price;
            data.type = SALE_REFOUND;

            Sale_Srv_Add(&data);
            Ticket_Srv_Modify(&ticket);
            printf("Retfund Success !\n");

            List_Destroy(tlist, ticket_node_t);
            return;
            break;
        }
		default:
			printf("No Such Choice !\n");
		}
	}while(choice !='r' && choice !='R');
}