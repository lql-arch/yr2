//
// Created by bronya on 22-6-15.
//

#include "Creat_Ticket_UI.h"
#include "Creat_Ticket.h"
#include "Play.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../Service/Creat_Ticket.h"
#include "../View/Schedule_UI.h"
#include "Play_UI.h"
#include "Sale.h"

const static int SCHEDULE_PAGE_SIZE = 5;
const static int PLAY_PAGE_SIZE = 5;

int Tick_UI_MgrEntry(int schedule_id){
    schedule_t rec;
    play_t rec2;
    char choice;
    char ch;

    if (! Schedule_Srv_FetchByID(schedule_id,&rec)) {
        printf("The schedule does not exist!\nPress [Enter] key to return\n");
        setbuf(stdin,NULL);
        getchar();
        return 0;
    }


    if (!Play_Srv_FetchByID(rec.play_id, &rec2)) {
        printf("The repertoire does not exist!\nPress [Enter] key to return\n");
        setbuf(stdin,NULL);
        getchar();
        return 0;
    }

    #ifdef linux
        system("clear");
    #endif
    #ifdef WIN32
        system("cls");
    #endif

    printf(
            "\n============================================================================\n");
    printf(
            "*********************** Show program information *****************************\n");
    printf("%8s %8s  %8s  %10s  %8s %8s\n", "schedule_ID", "play_ID", "studio_ID",
           "date", "time","seat_count");
    printf("-------------------------------------------------------------------------------\n");

    printf("%8d %8d  %8d  %04d-%02d-%02d  %02d-%02d-%02d %8d \n",rec.id,
       rec.play_id, rec.studio_id, rec.date.hour,
       rec.date.minute,rec.date.second,rec.time.hour,
       rec.time.minute,rec.time.second,rec.seat_count);
    printf("\n==============================================================================\n");

    printf("********************************** The Play information ***************************************************\n");
    printf("%5s  %20s  %10s  %5s  %10s  %10s  %10s  %10s  %6s\n", "ID", "Name", "type",
       "area", "rating","duration","start_date","end_date","price");
    printf("---------------------------------------------------------------------------------------------------------\n");
    //显示数据
    printf("%5d  %20s  %10u  %5s  %10u  %10d  %4d-%2d-%2d  %4d-%2d-%2d  %6d\n", rec2.id,
           rec2.name, rec2.type, rec2.area,rec2.rating,rec2.duration,
           rec2.start_date.year,rec2.start_date.month,rec2.start_date.day,
           rec2.end_date.year,rec2.start_date.month,rec2.start_date.day,rec2.price);
    printf("\n==========================================================================================================\n");
    printf("type: [1/file] [2/opera] [3/concert]           rating: [1/child] [2/teenage] [3/adult]");
    printf("\n==========================================================================================================\n");

    do {
        printf("**********************************************************************************************************\n");
        printf(
                "[G]Generate tickets for the show　　|　　r[E]generate the ticket 　　|　　 [R]return\n");
        printf(
                "==========================================================================================================\n");


        printf("Your Choice:");
        fflush(stdin);
        scanf("%s", &choice);
        while ((ch = getchar()) != '\n') {}
        fflush(stdin);

        switch (choice) {
            case 'g':
            case 'G':
                if(Ticket_Srv_GenBatch(schedule_id,rec.studio_id)){
                    printf("Succeed:Generate tickets for the show.\n");
                }else{
                    printf("Failed:Generate tickets for the show.\n");
                }
                break;
            case 'e':
            case 'E':
                if(Ticket_Srv_DeleteBatch(schedule_id)){
                    printf("Succeed:regenerate the ticket.\n");
                }else{
                    printf("Failed:regenerate the ticket.\n");
                }
                break;
            case 'r':
            case 'R':
                break;
            default:
                fprintf(stderr,"Error:Input error.\n");
                break;
        }
    }while(choice != 'r' && choice != 'R');


    setbuf(stdin,NULL);

    return 0;

}

void Ticket_UI_Query(void)
{
    ticket_list_t ticket_list;
//初始化演出票链表
    List_Init(ticket_list,ticket_node_t);

//调用逻辑层函数获取所有演出票信息
    Ticket_Srv_FetchAll(ticket_list);

    ticket_list_t pos;
    //= (ticket_list_t) malloc( sizeof(ticket_node_t));
    int choice,id;

    do
    {
        system("clear");
        printf("====================================================\n");
        printf("[S]how   |   [Q]uery   |   [R]eturn");
        printf("\n====================================================\n");

        printf("\n\n\n");


        fflush(stdin);
        printf("请输入：");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);


        switch(choice)
        {
            case 'S':
            case 's':
    #ifdef linux
                system("clear");
    #endif
    #ifdef WIN32
                system("cls");
    #endif
                Ticket_UI_ShowTicket(ticket_list->data.id);
                break;
            case 'Q':
            case 'q':
                system("clear");
                printf("输入你想查找的票的id");
                scanf("%d",&id);
                Ticket_Srv_FetchByID(id,&(pos->data));
                printf(
                        "\n=======================================================\n");
                printf(
                        "*********************** 票的信息 **********************\n");
                printf("%5s  %5s  %5s %5s %5s","票id","演出计划id","座位id","价格","状态");
                printf(
                        "\n-------------------------------------------------------\n");
                printf("%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);
                printf("\n\n\n\n提示：输入任意键返回。");
                setbuf(stdin,NULL);
                getchar();
                break;
        }
    }
    while(choice != 'R'&& choice != 'r');
}
int Ticket_UI_ShowTicket(int ID)
{
    char choice;
    schedule_list_t scheduleList;
    List_Init(scheduleList, schedule_node_t);
    play_list_t playList;
    List_Init(playList, play_node_t);
    Pagination_t paging;
    int play_id;
    int schedule_id;
    play_t play;
    schedule_t schedule;
    ticket_list_t ticketList;
    seat_list_t seatList;

    List_Init(seatList, seat_node_t);
    List_Init(ticketList, ticket_node_t);
    paging.totalRecords = Play_Srv_FetchAll(playList);
    paging.pageSize = PLAY_PAGE_SIZE;
    Paging_Locate_FirstPage(playList, paging);

    do{
#ifdef WIN32
        system("cls");
#endif
#ifdef linux
        system("clear");
#endif
        Play_UI_ShowList(playList, paging);
        printf("\t\t\t\t\t[E]选择剧目 ?[P]上一页 ?[N]下一页 ?[R]退出\n\t\t\t\t");
        choice = toupper(getchar());
        while (getchar() != '\n')
            continue;
        switch (choice){
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                Paging_Locate_OffsetPage(playList, paging, -1, play_node_t);
                break;
            case 'N':
                if (!Pageing_IsLastPage(paging))
                Paging_Locate_OffsetPage(playList, paging, 1, play_node_t);
                break;
            case 'R':
                return 0;
                break;
        }
    } while (choice != 'E');
    printf("\t\t\t\t请输入剧目ID:");
    scanf("%d", &play_id);
    while (getchar() != '\n')
        continue;
    while (Play_Srv_FetchByID(play_id, &play) == 0)
    {
        printf("\t\t\t\t输入ID错误, 请重新输入：");
        scanf("%d", &play_id);
        while (getchar() != '\n')
         continue;
    }
    paging.totalRecords = Schedule_Srv_FetchByPlay( play_id,scheduleList);
    paging.pageSize = SCHEDULE_PAGE_SIZE;
    Paging_Locate_FirstPage(scheduleList, paging);
    do{
#ifdef WIN32
        system("cls");
#endif
#ifdef linux
        system("clear");
#endif
        Schedule_UI_ShowList(scheduleList, paging);
         printf("\t\t\t\t[E]选择计划 ?[P]上一页 ?[N]下一页 ?[R]退出\n\t\t\t\t");
        choice = toupper(getchar());
        while (getchar() != '\n')
        continue;
        switch (choice) {
            case 'P':
                if (!Pageing_IsFirstPage(paging))
                    Paging_Locate_OffsetPage(scheduleList, paging, -1, schedule_node_t);
            case 'N':
                if (!Pageing_IsLastPage(paging))
                    Paging_Locate_OffsetPage(scheduleList, paging, 1, schedule_node_t);
            case 'R':
                return 0;
            default:
                break;
        }

        } while (choice != 'E');
    printf("\t\t\t\t请输入演出计划ID:");
    scanf("%d", &schedule_id);
    while (getchar() != '\n')
        continue;
    while (Schedule_Srv_FetchByID(schedule_id, &schedule) == 0)
     {
        printf("\t\t\t\t输入ID错误, 请重新输入：");
        scanf("%d", &schedule_id);
         while (getchar() != '\n')
        continue;
        }
    Ticket_Srv_FetchBySchID(schedule_id,ticketList );
    Seat_Srv_FetchByRoomID(seatList, schedule.studio_id);
    Ticket_UI_ListBySch(&schedule, ticketList, seatList);
    List_Destroy(scheduleList, schedule_node_t);
    List_Destroy(seatList, seat_node_t);
    List_Destroy(playList, play_node_t);
    List_Destroy(ticketList, ticket_node_t);
    return 0;

}

void Queries_Menu()
{
    char choice;
    do{
        printf("\n==================================================================\n");
        printf("[S]chedule_UI_ListAll.\n");
        printf("[T]icket_UI_Qry.\n");
        printf("[R]eturn.\n");
        printf("\n==================================================================\n");
        printf("Please input your choice:");
        fflush(stdin);
        choice=getchar();
        switch(choice)
        {
            //查询演出界面
            case 'S':
            case 's':
                Schedule_UI_ListAll();
                break;
                //查询演出票界面
            case 'T':
            case 't':
                Ticket_UI_Qry();
                break;
        }
    }
    while (choice != 'r' && choice != 'R');
}



void Ticket_UI_ShowList(ticket_list_t ticket, Pagination_t paging)
{
    ticket_list_t list;
    List_Init(list, ticket_node_t);
    paging.totalRecords = Ticket_Srv_FetchSold(ticket, list);
    // printf("%d", paging.totalRecords);
    Paging_Locate_FirstPage(list, paging);
    int i = 0;
    ticket_node_t* node;
    printf("\n\t\t\t\t==========================订票信息==============================\n");
    printf("\t\t\t\t%4s\t%12s  %8s  %4s\n", "ID", "演出计划ID", "座位ID", "价格");
    Paging_ViewPage_ForEach(list, paging, ticket_node_t, node, i)
    {
        if(node->data.status == TICKET_SOLD)
        printf("\t\t\t\t%4d\t%10d  %8d  %4d\n",
        node->data.id, node->data.schedule_id, node->data.seat_id, node->data.price);
         }
    printf("\t\t\t\t================================================================\n");
    List_Destroy(list, ticket_node_t);

}

void Ticket_UI_ListBySch(const schedule_t *sch, ticket_list_t tickList, seat_list_t seatList)
{
    assert(NULL!=sch && NULL!=tickList && NULL!=seatList);
    int i, j;

    studio_t studioRec;
    play_t playRec;
    ticket_node_t *pTicket;
    seat_node_t *pSeat;

    printf("%d\n",sch->studio_id);
    if (!Studio_Srv_FetchByID(sch->studio_id, &studioRec)) { //获得对应id放映厅的信息
        printf("\t\t\t\tstudio_id不存在\n");
        while(getchar() != '\n')continue;
        return;
    }

    if (!Play_Srv_FetchByID(sch->play_id, &playRec)) { //获得对应id剧目的信息
        printf("\t\t\t\tplay_id不存在\n");
        while(getchar() != '\n')continue;
        return;
    }
    system("cls");
    printf("\t\t\t\t********************** Ticket List for %s ***********************\n", playRec.name);
    printf("\t\t\t\t%5c", ' ');
    for (i = 1; i <= studioRec.colsCount; i++) {
        printf("%3d", i);
    }

    printf("\n\t\t\t\t------------------------------------------------------------------\n");
    //显示数据
    for (i = 1; i <= studioRec.rowsCount; i++)
    {
        j = 1;
        printf("\t\t\t\t%2d:%c", i, '|');
        List_ForEach(tickList, pTicket){
            pSeat = Seat_Srv_FindByID(seatList, pTicket->data.seat_id);
            if (NULL != pSeat && pSeat->data.row == i){
                if (pSeat->data.column != j || pSeat->data.status != SEAT_GOOD)
                {
                    printf("%3c", ' ');
                    j++;
                }
                printf("%3c", Ticket_UI_Status2Char(pTicket->data.status));
                j++;
            }
        }
        printf("\n");
    }
    printf("\t\t\t\t-----------------------------------------------\n");
    while (getchar() != '\n')
        continue;
}

char Ticket_UI_Status2Char(ticket_status_t status) {
    char statusChar;
    switch (status) {
        case TICKET_AVL: //待售座位
            statusChar = '#';
            break;
        case TICKET_SOLD:
            statusChar = '@';
            break;
        case TICKET_RESV:
            statusChar = '%';
        default:
            statusChar = '~';
            break;
    }
}

void  Ticket_UI_Qry(){
    Ticket_UI_ShowTicket(0);
}