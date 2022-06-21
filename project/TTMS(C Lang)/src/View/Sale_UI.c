#include<stdio.h>
#include <time.h>

#include"../Service/Play.h"							//MgtEnt
#include"../Service/Seat.h"
#include"../Common/List.h"
#include "./Sale_UI.h"
#include"../Persistence/Play_Perst.h"	//�޶�Ӧ����������ȡ������
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

/*������Ʊ����*/
void Sale_UI_MgtEntry(void){
    int i;
    char ch;
	play_list_t list;		//����	��Ŀ 	����
	play_node_t* pos;
	List_Init(list,play_node_t);//��ʼ��

	Pagination_t paging;	//���÷�ҳ��
	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;

	paging.totalRecords = Play_Srv_FetchAll(list);//���ú�����ȡ�ܼ�¼��
	Paging_Locate_FirstPage(list, paging);//ҳ�涨λ�������һҳ

    while((ch = getchar()) != '\n')
        continue;

	char choice;
	do{				//���ó���Ϊ83���ַ�

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
		case'c':			//ͨ��idѰ���ݳ��ƻ�
		case'C':
			printf("Please input the ID you want to search:");
			int id;
			scanf("%d",&id);
            Sale_UI_ShowScheduler(id);	//
			break;

		case's':			//��ѯ��Ŀ����
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

//			assert(list != NULL);		//��������ɸѡ��Ŀ
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

	//�ͷſռ�
	List_Destroy(list, play_node_t);

    setbuf(stdin,NULL);
}





/*���ݾ�Ŀ��ʾ�ݳ��ƻ�����*/
void Sale_UI_ShowScheduler(int id){

    int tk_id;
    char ch;
    int i = 0;
	schedule_list_t list;		//����	�ݳ���		����
	schedule_node_t *pos;

    play_t play_temp;			//����ID�ж��Ƿ���ھ�Ŀ
    if(!Play_Srv_FetchByID(id,&play_temp)){
        fprintf(stderr,"Error:%d does not exist.\nPress [Enter] key to return!\n",id);
        getchar();
        return ;
    }

	List_Init(list,schedule_node_t);//��ʼ��

	Pagination_t paging;	//���÷�ҳ��
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = Schedule_Srv_FetchByPlay(id,list);//���ú�����ȡ�ܼ�¼��
	Paging_Locate_FirstPage(list,paging);//ҳ�涨λ�������һҳ


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
	    if(!List_IsEmpty(list)){		//�жϾ�Ŀ�ݳ����Ƿ�Ϊ��
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

/*��ʾ�ݳ�Ʊ����*/
void Sale_UI_ShowTicket(int schedule_id){
    schedule_t schedule_buf;
    Schedule_Srv_FetchByID(schedule_id,&schedule_buf);//�����ݳ��ƻ�id���ҳ��ݳ��ƻ��Ľڵ���Ϣ  �ݳ��ƻ����ɾ�Ŀid


    ticket_list_t buf;//buf������ĳ�ݳ��ƻ�������Ʊ      Ʊ�����ݳ��ƻ�id
    List_Init(buf,ticket_node_t);
    ticket_list_t pos;

    Pagination_t paging;
    paging.offset = 0;
    paging.pageSize = 5;
    int i;
    int choice;

    seat_list_t flag;//flag�����ݳ��ƻ���������λ      ��λ�����ݳ��ƻ�id
    List_Init(flag,seat_node_t);
    Seat_Srv_FetchByRoomID(flag,schedule_buf.studio_id);//���ݾ�Ŀid�ҵ���λ����


    List_Init(buf,ticket_node_t);
    paging.totalRecords=Ticket_Srv_FetchBySchID(schedule_id,buf);
    Paging_Locate_FirstPage(buf,paging);

//    ticket_node_t *p;
//    List_ForEach(buf,p){
//        printf("%d %d\n",p->data.status,p->data.id);
//    }


    do {
#ifdef WIN32
        system("cls");//����
#endif
#ifdef linux
        system("clear");//����
#endif

        printf(
                "\n=======================================================\n");
        printf(
                "********************** Ʊ����Ϣ ***********************\n");
        printf("%5s  %5s  %5s  %5s  %5s","Ʊid","�ݳ��ƻ�id","��λid","�۸�","״̬\n");
        printf(
                "-------------------------------------------------------\n");
        Paging_ViewPage_ForEach(buf, paging, ticket_node_t, pos, i){
            printf("%5d  %5d  %7d  %5d  ",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price);
            printf("%5s\n",(pos->data.status == 0 ? "Ԥ��" : (pos->data.status == 1 ? "����" : "����")));
        }


        printf(
                "------- ��:%2d�� --------------------- ҳ�� :%2d/%2d ----\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));

        printf("\n*******************************************************\n");
        printf("[1]��Ʊ|[2]�鿴seat|[0]����|[3]��һҳ|[4]��һҳ\n");
        printf("=======================================================\n");



        fflush(stdin);
        printf("�����룺");
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


/*��Ʊ����*/
int Sale_UI_SellTicket(ticket_list_t tickList,seat_list_t seatList){
    int x,y;
    printf("��������Ҫ���Ʊ���кţ�");
    scanf("%d",&x);
    printf("�����кţ�");
    scanf("%d",&y);
    printf("\n");

    seat_node_t *b;
    if(!(b = Seat_Srv_FindByRowCol(seatList,x,y))){
        printf("����λ������!");
        return 0;
    }

    ticket_t flag;
    //������λid���ҵ�Ʊ����Ϣ����flag�洢Ʊ��Ϣ����ڵ�
    if(!Ticket_Srv_FetchByID(b->data.id,&flag)){
        printf("��Ʊ�����ڣ�\n");
        return 0;
    }else
    {
        printf("�ҵ���Ʊ��\n");
    }

    if(flag.status==0)
    {
        printf("��Ʊ�ȴ��۳���\n");

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
        while(!feof(fp)){//ָ��  û��  ָ�� FILE ĩβ��
            fread(&rec, sizeof(ticket_t), 1, fp);
            if(rec.id == flag.id){
                printf("%d %d\n",rec.status,rec.id);
            }
        }
        fclose(fp);


        sale_t buf;//���������Ʊ�����ۼ�¼

        long key = EntKey_Perst_GetNewKeys("Sale", 1); //��ȡ����

        if(key<=0) {
            fprintf(stderr,"Error:key.\n");
            return 0;
        }
        buf.id = key;
        printf("\n");
        printf("�������id");
        scanf("%d",&buf.user_id);

        buf.ticket_id = flag.id;

        struct tm *local;
        time_t t;

        t=time(&t);
        local=localtime(&t);  //��ǰ����

        printf("%d��%d��%d��\n",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
        buf.date.year=local->tm_year+1900;
        buf.date.month=local->tm_mon+1;
        buf.date.day=local->tm_mday;

        printf("%dʱ%d��%d��\n",local->tm_hour,local->tm_min,local->tm_sec);
        buf.time.hour=local->tm_hour;
        buf.time.minute=local->tm_min;
        buf.time.second=local->tm_sec;
        buf.type=1;//��Ʊ

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
        printf("��Ʊ���۳���");
        return 0;
    }
    else
    {
        printf("��Ʊ�ѱ�Ԥ�������ɹ���");

        return 0;
    }
}


/*��Ʊ����*/
void Sale_UI_ReturnTicket(void){

//��Ʊ��   ��Ŀ   ѡ�����
    char ch;
	int play_id;
	play_list_t plist;		//����	��Ŀ 	����
	List_Init(plist,play_node_t);//��ʼ��

	Pagination_t paging;	//���÷�ҳ��
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;
	paging.totalRecords = Play_Srv_FetchAll(plist);//���ú�����ȡ�ܼ�¼��
	Paging_Locate_FirstPage(plist,paging);//ҳ�涨λ�������һҳ

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


//��Ʊ��  �ݳ����ƻ�   ѡ��
	int schedule_id;
	schedule_list_t slist;		//����	�ݳ���		����
	List_Init(slist,schedule_node_t);//��ʼ��

	paging.pageSize = SCHEDULE_PAGE_SIZE;
	paging.totalRecords = Schedule_Srv_FetchByPlay(play_id,slist);//���ú�����ȡ�ܼ�¼��
	Paging_Locate_FirstPage(slist,paging);//ҳ�涨λ�������һҳ

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


//��ʽ��Ʊ��
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