#include<stdio.h>
#include <time.h>

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
#include "Seat_UI.h"

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

    while((ch = getchar()) != '\n')
        continue;

	char choice;
	do{				//设置长度为83个字符

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
			Sale_UI_ShowTicket(tk_id);
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
void Sale_UI_ShowTicket(int schedule_id){
    schedule_t schedule_buf;
    Schedule_Srv_FetchByID(schedule_id,&schedule_buf);//根据演出计划id，找出演出计划的节点信息  演出计划理由剧目id


    ticket_list_t buf;//buf保存着某演出计划的所有票      票理由演出计划id
    List_Init(buf,ticket_node_t);
    ticket_list_t pos;

    Pagination_t paging;
    paging.offset = 0;
    paging.pageSize = 5;
    int i;
    int choice;

    seat_list_t flag;//flag保存演出计划的所有座位      座位里由演出计划id
    List_Init(flag,seat_node_t);
    Seat_Srv_FetchByRoomID(flag,schedule_buf.studio_id);//根据剧目id找到座位链表


    List_Init(buf,ticket_node_t);
    paging.totalRecords=Ticket_Srv_FetchBySchID(schedule_id,buf);
    Paging_Locate_FirstPage(buf,paging);

//    ticket_node_t *p;
//    List_ForEach(buf,p){
//        printf("%d %d\n",p->data.status,p->data.id);
//    }


    do {
#ifdef WIN32
        system("cls");//清屏
#endif
#ifdef linux
        system("clear");//清屏
#endif

        printf(
                "\n=======================================================\n");
        printf(
                "********************** 票的信息 ***********************\n");
        printf("%5s  %5s  %5s  %5s  %5s","票id","演出计划id","座位id","价格","状态\n");
        printf(
                "-------------------------------------------------------\n");
        Paging_ViewPage_ForEach(buf, paging, ticket_node_t, pos, i){
            printf("%5d  %5d  %7d  %5d  ",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price);
            printf("%5s\n",(pos->data.status == 0 ? "预售" : (pos->data.status == 1 ? "已售" : "待售")));
        }


        printf(
                "------- 共:%2d条 --------------------- 页数 :%2d/%2d ----\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));

        printf("\n*******************************************************\n");
        printf("[1]购票|[2]查看seat|[0]返回|[3]上一页|[4]下一页\n");
        printf("=======================================================\n");



        fflush(stdin);
        printf("请输入：");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        switch(choice)
        {
            case 1:
                if(!Sale_UI_SellTicket(buf,flag)){
                    fprintf(stderr,"Error:Sell ticket failed.\n");
                }else{
                    paging.totalRecords=Ticket_Srv_FetchBySchID(schedule_id,buf);
                    List_Paging(buf,paging,ticket_node_t);
                }
                break;
            case 2:
                Seat_UI_MgtEntry(schedule_buf.studio_id);
                break;
            case 3://system("clear");
                if (!Pageing_IsFirstPage(paging)) {
                    Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
                }
                break;
            case 4://system("clear");
                if (!Pageing_IsLastPage(paging)) {
                    Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
                }
                break;
        }
    }while(choice != 0);
    List_Destroy(flag, seat_node_t);
    List_Destroy(buf, ticket_node_t);
}


/*售票界面*/
int Sale_UI_SellTicket(ticket_list_t tickList,seat_list_t seatList){
    int x,y;
    printf("输入你想要买的票的行号：");
    scanf("%d",&x);
    printf("输入列号：");
    scanf("%d",&y);
    printf("\n");

    seat_node_t *b;
    if(!(b = Seat_Srv_FindByRowCol(seatList,x,y))){
        printf("该座位不存在!");
        return 0;
    }

    ticket_t flag;
    //根据座位id，找到票的信息，，flag存储票信息链表节点
    if(!Ticket_Srv_FetchByID(b->data.id,&flag)){
        printf("该票不存在！\n");
        return 0;
    }else
    {
        printf("找到该票！\n");
    }

    if(flag.status==0)
    {
        printf("该票等待售出！\n");

        flag.status = 1;

        if(Ticket_Srv_Modify(&flag)){
            printf("Ticket_modify success!\n");
        }else{
            return 0;
        }

        FILE *fp;
        ticket_t rec;
        if((fp = fopen("Ticket.dat","rb+")) == NULL){
            printf("Open FILE Failed !\n");
            return 0;
        }
        while(!feof(fp)){//指针  没有  指到 FILE 末尾的
            fread(&rec, sizeof(ticket_t), 1, fp);
            if(rec.id == flag.id){
                printf("%d %d\n",rec.status,rec.id);
            }
        }
        fclose(fp);


        sale_t buf;//保存这次售票的销售记录

        long key = EntKey_Perst_GetNewKeys("Sale", 1); //获取主键

        if(key<=0) {
            fprintf(stderr,"Error:key.\n");
            return 0;
        }
        buf.id = key;
        printf("\n");
        printf("输入你的id");
        scanf("%d",&buf.user_id);

        buf.ticket_id = flag.id;

        struct tm *local;
        time_t t;

        t=time(&t);
        local=localtime(&t);  //当前日期

        printf("%d年%d月%d日\n",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
        buf.date.year=local->tm_year+1900;
        buf.date.month=local->tm_mon+1;
        buf.date.day=local->tm_mday;

        printf("%d时%d分%d秒\n",local->tm_hour,local->tm_min,local->tm_sec);
        buf.time.hour=local->tm_hour;
        buf.time.minute=local->tm_min;
        buf.time.second=local->tm_sec;
        buf.type=1;//买票

        if(Sale_Srv_Add(&buf)){
            printf("Sale_add success!\n");
        }else{
            flag.status = 0;
            Ticket_Srv_Modify(&flag);
            return 0;
        }


        return 1;
    }
    else if(flag.status==1)
    {
        printf("该票已售出！");
        return 0;
    }
    else
    {
        printf("该票已被预定，不可购买！");

        return 0;
    }
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
		printf("Wrong Play_ID ! Repeat Again :");
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
		printf("Wrong Schedule_ID ! Repeat Again :");
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
    printf("Your ticket_id:");
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
            printf("Refund Success !\n");

            List_Destroy(tlist, ticket_node_t);
            setbuf(stdin,NULL);
            return;
            break;
        }
		default:
			printf("No Such Choice !\n");
		}
	}while(choice !='r' && choice !='R');
}