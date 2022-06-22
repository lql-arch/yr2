//
// Created by bronya on 22-6-13.
//

#include "Schedule_UI.h"
#include "Play.h"
#include "Seat_UI.h"

const static int SCHEDULE_PAGE_SIZE = 5;

void Schedule_UI_MgtEntry(int play_id){
    int i,id;
    char choice;
    char ch;
    //Create_File_Name((char)play_id);

    schedule_t buf;
    schedule_list_t head;
    schedule_node_t *pos;
    Pagination_t paging;

    List_Init(head, schedule_node_t);
    paging.offset = 0;
    paging.pageSize = SCHEDULE_PAGE_SIZE;

    //载入数据
    //paging.totalRecords = Schedule_Srv_FetchAll(head);
    paging.totalRecords = Schedule_Srv_FetchByPlay(play_id,head);
    Paging_Locate_FirstPage(head, paging);


    do {
        setbuf(stdin,NULL);
        #ifdef linux
                system("clear");
        #endif
        #ifdef WIN32
                system("cls");
        #endif

        printf(
                "\n==================================================================\n");
        printf(
                "*********************** %dth Play  List *****************************\n",play_id);
        printf("%8s  %5s  %10s  %10s  %8s  %5s\n", "play_id", "ID", "studio_id",
               "time", "date","seat_count");
        printf(
                "------------------------------------------------------------------\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
            printf("%8d  %5d  %10d  %02d:%02d:%02d  %04d-%02d-%02d  %5d\n", pos->date.play_id,pos->date.id,pos->date.studio_id,
                   pos->date.time.hour,pos->date.time.minute,pos->date.time.second,pos->date.date.hour,pos->date.date.minute,pos->date.date.second, pos->date.seat_count);
        }

        printf(
                "------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));
        printf(
                "******************************************************************\n");
        printf(
                "[P]revPage|[N]extPage | [A]dd|[D]elete | [U]pdate | [S]eat | [T]icket_creating | [R]eturn");
        printf(
                "\n==================================================================\n");
        printf("Your Choice:");
        fflush(stdin);
        scanf("%c", &choice);
        while((ch = getchar()) != '\n'){}
        fflush(stdin);

        switch (choice) {
            case 'a':
            case 'A':
                if (Schedule_UI_Add(play_id)) //新添加成功，跳到最后一页显示
                {
                    //paging.totalRecords = Schedule_Srv_FetchAll(head);
                    paging.totalRecords = Schedule_Srv_FetchByPlay(play_id,head);
                    Paging_Locate_LastPage(head, paging, schedule_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("Input the ID:");
                scanf("%d", &id);
                while ((ch = getchar()) != '\n') {}
                if (Schedule_UI_Delete(id)) {	//从新载入数据
                    //paging.totalRecords = Schedule_Srv_FetchAll(head);
                    paging.totalRecords = Schedule_Srv_FetchByPlay(play_id,head);
                    List_Paging(head, paging, schedule_node_t);
                }
                break;
            case 'u':
            case 'U':
                printf("Input the ID:");
                scanf("%d", &id);
                while ((ch = getchar()) != '\n') {}
                if (Schedule_UI_Modify(id)) {	//从新载入数据
                    //paging.totalRecords = Schedule_Srv_FetchAll(head);
                    paging.totalRecords = Schedule_Srv_FetchByPlay(play_id,head);
                    List_Paging(head, paging, schedule_node_t);
                }
                break;
            case 's':
            case 'S':
                printf("Input the ID:");
                scanf("%d", &id);
                while ((ch = getchar()) != '\n') {}
                Seat_UI_MgtEntry(id);
                if(!Schedule_Srv_FetchByID(id,&buf)){
                    fprintf(stderr,"Error:%d does not exist.\n",id);
                    break;
                }
                if(Schedule_SetOffset(id,&paging)){
                    //paging.totalRecords = Schedule_Srv_FetchAll(head);
                    paging.totalRecords = Schedule_Srv_FetchByPlay(play_id,head);
                    List_Paging(head, paging, schedule_node_t);
                }
                break;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
                }
                break;
            case 't':
            case 'T':
                printf("Input the schedule_ID:");
                scanf("%d", &id);
                while((ch = getchar()) != '\n')
                    continue;
                if(!Schedule_Srv_FetchByID(id,&buf)){
                    fprintf(stderr,"Error:%d does not exist.\n",id);
                    break;
                }
                Tick_UI_MgrEntry(id);
                break;
        }
    } while (choice != 'r' && choice != 'R');
    //释放链表空间
    List_Destroy(head, schedule_node_t);
}


int Schedule_UI_Add(int play_id){
    int NewCount;
    schedule_t t;
    char choice;
    studio_t buf1;

    do{
        #ifdef linux
                system("clear");
        #endif
        #ifdef WIN32
                system("cls");
        #endif
        printf("\n===============================================================\n");
        printf("********************  Add New Schedule Of Plan ****************\n");
        printf("---------------------------------------------------------------\n");
        printf("Projection Room:");
        scanf("%d", &(t.studio_id));
        while(!Studio_Srv_FetchByID(t.studio_id,&buf1)){
            fprintf(stderr,"Error:%d no exist.\n",t.studio_id);
            printf("Stdio_id:");
            scanf("%d", &(t.studio_id));
        }
        printf("Date of screening(year:month:day):");
        scanf("%d:%d:%d",&t.date.hour,&t.date.minute,&t.date.second);
        printf("Time of screening(hour-minute-second):");
        scanf("%d-%d-%d",&t.time.hour,&t.time.minute,&t.time.second);
        t.seat_count = buf1.seatsCount;
        t.play_id = play_id;
        printf("=================================================================\n");

        if (Schedule_Srv_Add(&t)) {
            NewCount += 1;
            printf("The new room added successfully!\n");
        } else
            printf("The new room added failed!\n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("[A]dd more, [R]eturn:");
        fflush(stdin);
        scanf("%c", &choice);
    } while ('a' == choice || 'A' == choice);

    return NewCount;
}

int Schedule_UI_Modify(int id){
    schedule_t t;
    int play_id ;
    int rtn = 0;
    studio_t buf1;
    play_t buf2;

    /*Load record*/
    if (!Schedule_Srv_FetchByID(id, &t)) {
        printf("The play does not exist!\n"
               "Press [Enter] key to return!\n");
        getchar();
        return 0;
    }

    play_id = t.play_id;

    #ifdef linux
        system("clear");
    #endif
    #ifdef WIN32
        system("cls");
    #endif

    printf("\n=======================================================\n");
    printf("**************** Modify %dth Projection Room  ****************\n",id);
    printf("-------------------------------------------------------\n");
    printf("Schedule ID:%d\n", t.id);
    printf("Play_id[%d]:", t.play_id);
    scanf("%d",&t.play_id);
    while(play_id != t.play_id){
        fprintf(stderr,"Error:%d does not exist.\n",t.play_id);
        printf("Play_id:");
        scanf("%d", &(t.play_id));
    }
    printf("studio_id[%d]:",t.studio_id);
    scanf("%d", &(t.studio_id));
    while(!Studio_Srv_FetchByID(t.studio_id,&buf1)){
        fprintf(stderr,"Error:%d no exist.\n",t.studio_id);
        printf("Studio_id:");
        scanf("%d", &(t.studio_id));
    }
    printf("Date of screening(year-month-day):");
    scanf("%d-%d-%d",&t.date.hour,&t.date.minute,&t.date.second);
    printf("Time of screening(hour:minute:second):");
    scanf("%d:%d:%d",&t.time.hour,&t.time.minute,&t.time.second);
    t.seat_count = buf1.seatsCount;
    printf("=======================================================\n");

    if (Schedule_Srv_Modify(&t)) {
        rtn = 1;
        printf("The play data updated successfully!\nPress [Enter] key to return!\n");
    } else
        printf("The play data updated failed!\nPress [Enter] key to return!\n");

    getchar();
    return rtn;
}

int Schedule_UI_Delete(int id){
    int rtn = 0;

    if (Schedule_srv_DeleteByID(id)) {
        printf("The play deleted successfully!\nPress [Enter] key to return!\n");
        rtn = 1;
    } else {
        printf("The play does not exist!\nPress [Enter] key to return!\n");
    }

    getchar();

    return rtn;
}

void Schedule_UI_ShowList(schedule_list_t list, Pagination_t paging)
{
    int i = 0;
    schedule_node_t* p;
    play_t play;
    studio_t studio;
    char choice,ch;

    Play_Srv_FetchByID(list->next->date.play_id, &play);

    do{
#ifdef linux
        system("clear");
#endif
#ifdef WIN32
        system("cls");
#endif
        printf("\n\t\t\t\t==================================================================\n");
        printf("\t\t\t\t\t\t\t*********演出计划*********\n");
        printf("\t\t\t\t------------------------------------------------------------------\n");
        printf("\t\t\t\t%4s\t%10s\t%8s\t%10s\t%5s \t%5s\n", "ID", "剧目", "演出厅", "放映日期", "放映时间", "座位数");
        //显示数据
        Paging_ViewPage_ForEach(list, paging, schedule_node_t, p, i)
        {
            Play_Srv_FetchByID(p->date.play_id, &play);
            Studio_Srv_FetchByID(p->date.studio_id, &studio);
            printf("\t\t\t\t%4d\t %10s\t %8s\t", p->date.id, play.name, studio.name);
            printf("%4d-%02d-%02d \t", p->date.date.hour, p->date.date.minute, p->date.date.second);
            printf("%2d:%02d \t", p->date.time.hour, p->date.time.minute);
            printf("\t%5d\n", p->date.seat_count);
            }
        printf("\n\t\t\t\t-------- 共 %2d 项 --------------------------- %2d/%2d 页 --------\n",
        paging.totalRecords, Pageing_CurPage(paging),
        Pageing_TotalPages(paging));
        printf(" ***********************************************************************************\n");
        printf("    		[P]revPage       			 [N]extPage   				  [C]ontinue    \n");

        printf("Your Choice:");
        fflush(stdin);
        scanf("%c", &choice);
        while ((ch = getchar()) != '\n')
            continue;

        switch (choice)
        {
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                Paging_Locate_OffsetPage(list, paging, -1, schedule_node_t);
                break;

            case 'N':
                if (!Pageing_IsLastPage(paging))
                Paging_Locate_OffsetPage(list, paging, 1, schedule_node_t);
                break;
            default:
                break;
        }
    }while(choice !='c' && choice !='C');

    setbuf(stdin,NULL);
}

int Schedule_UI_Query(char *play_name)
{
    play_list_t list_p;
    schedule_list_t list_s;
    List_Init(list_p,play_node_t);
    List_Init(list_s,schedule_node_t);


    Play_Srv_FetchByName(list_p,play_name);

    play_node_t* p;
    List_ForEach(list_p,p)
    {
        Schedule_Srv_FetchByPlay(p->date.id,list_s);
    }


    int len = 0,i;
    schedule_list_t s;
    List_ForEach(list_s,s)
    {
        len++;
    }

    schedule_node_t *pos;
    Pagination_t paging;


    paging.offset = 0;
    paging.pageSize = SCHEDULE_PAGE_SIZE;

    paging.totalRecords = len;
    Paging_Locate_FirstPage(list_s, paging);

    printf(
            "\n==================================================================\n");
    printf(
            "********************** Play  List **********************\n");
    printf("%8s  %5s  %10s  %10s  %8s  %5s\n", "play_id", "ID", "studio_id",
           "time", "date","seat_count");
    printf(
            "------------------------------------------------------------------\n");

    Paging_ViewPage_ForEach(list_s, paging, schedule_node_t, pos, i){
        printf("%8d  %5d  %10d  %02d:%02d:%02d  %04d-%02d-%02d  %5d\n", pos->date.play_id,pos->date.id,pos->date.studio_id,
               pos->date.time.hour,pos->date.time.minute,pos->date.time.second,pos->date.date.hour,pos->date.date.minute,pos->date.date.second, pos->date.seat_count);

    }

    printf(
            "------- Total Records:%2d ----------------------- Page :%2d/%2d ----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));
    printf(
            "******************************************************************\n");
    setbuf(stdin,NULL);
    getchar();
#ifdef linux
    system("clear");
#endif
#ifdef WIN32
    system("cls");
#endif
    return 1;
}

void Schedule_UI_ListAll(void)
{
    int i,id;
    char choice;
    char play_name[64];
    schedule_list_t head;
    schedule_node_t *pos;
    Pagination_t paging;

    List_Init(head, schedule_node_t);
    paging.offset = 0;
    paging.pageSize = SCHEDULE_PAGE_SIZE;


    paging.totalRecords = Schedule_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head, paging);
    do {
#ifdef linux
        system("clear");
#endif
#ifdef WIN32
        system("cls");
#endif
        printf(
                "\n==========================================================\n");
        printf(
                "********************** Play  List **********************\n");
        printf("%8s  %5s  %10s  %10s  %8s  %5s\n", "play_id", "ID", "studio_id",
               "time", "date","seat_count");
        printf(
                "----------------------------------------------------------\n");

        Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
            printf("%8d  %5d  %10d  %02d:%02d:%02d  %04d-%02d-%02d  %5d\n", pos->date.play_id,pos->date.id,pos->date.studio_id,
                   pos->date.time.hour,pos->date.time.minute,pos->date.time.second,pos->date.date.hour,pos->date.date.minute,pos->date.date.second, pos->date.seat_count);

        }

        printf(
                "------- Total Records:%2d ------------------------- Page :%2d/%2d ----\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));
        printf(
                "**********************************************************\n");
        printf(
                "[P]revPage  |  [N]extPage   |  [Q]uery | [R]eturn  |");
        printf(
                "\n\n\n\n==========================================================\n");
        printf("Your Choice:");
        fflush(stdin);
        setbuf(stdin,NULL);
        scanf("%c", &choice);
        setbuf(stdin,NULL);
        fflush(stdin);



        switch (choice) {
            case 'Q':
            case 'q':
                printf("Input your play_name:");
                scanf("%s", play_name);
                if (Schedule_UI_Query(play_name))
                {
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, schedule_node_t);
                }
                break;

            case 'P':
            case 'p':
                system("clear");
                if (!Pageing_IsFirstPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
                }
                break;
            case 'N':
            case 'n':
                system("clear");
                if (!Pageing_IsLastPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
                }
                break;
        }
    } while ((choice != 'r')&&(choice!='R'));
    system("clear");
    List_Destroy(head, schedule_node_t);
}