//
// Created by bronya on 22-6-13.
//

#include "Schedule_UI.h"
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include "Creat_Ticket_UI.h"
#include "Schedule_Persist.h"
#include "Creat_Ticket.h"
#include "Creat_Ticket_Persist.h"
#include <stdio.h>
#include <string.h>



void Schedule_UI_MgtEntry(int play_id){
    int i,id;
    char choice;
    char ch;
    Create_File_Name((char)play_id);

    schedule_list_t head;
    schedule_node_t *pos;
    Pagination_t paging;

    List_Init(head, schedule_node_t);
    paging.offset = 0;
    paging.pageSize = 5;

    //载入数据
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
                "\n==================================================================\n");
        printf(
                "*********************** %dth Play  List *****************************\n",play_id);
        printf("%8s  %5s  %10s  %10s  %8s  %5s\n", "play_id", "ID", "studio_id",
               "time", "date","seat_count");
        printf(
                "------------------------------------------------------------------\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
            printf("%8d  %5d  %10d  %04d-%02d-%02d  %02d-%02d-%02d  %5d\n", pos->date.play_id,pos->date.id,pos->date.studio_id,
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
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, schedule_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("Input the ID:");
                scanf("%d", &id);
                while ((ch = getchar()) != '\n') {}
                if (Schedule_UI_Delete(id)) {	//从新载入数据
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    List_Paging(head, paging, schedule_node_t);
                }
                break;
            case 'u':
            case 'U':
                printf("Input the ID:");
                scanf("%d", &id);
                while ((ch = getchar()) != '\n') {}
                if (Schedule_UI_Modify(id)) {	//从新载入数据
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    List_Paging(head, paging, schedule_node_t);
                }
                break;
            case 's':
            case 'S':
                printf("Input the ID:");
                scanf("%d", &id);
                while ((ch = getchar()) != '\n') {}
                if(Schedule_SetOffset(id,&paging)){
                    paging.totalRecords = Schedule_Srv_FetchAll(head);
                    List_Paging(head, paging, schedule_node_t);
                }
                paging.totalRecords = Schedule_Srv_FetchAll(head);
                List_Paging(head, paging, schedule_node_t);
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
                printf("Input the ID:");
                scanf("%d", &id);
                while((ch = getchar()) != '\n')
                    continue;
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
        printf("Date of screening(year-month-second):");
        scanf("%d-%d-%d",&t.date.hour,&t.date.minute,&t.date.second);
        printf("Time of screening(hour-minute-second):");
        scanf("%d-%d-%d",&t.time.hour,&t.time.minute,&t.time.second);
        printf("Number of seat:");
        scanf("%d",&t.seat_count);
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
    printf("studio_id[%d]:",t.studio_id);
    scanf("%d", &(t.studio_id));
    printf("Date of screening(year-month-second):");
    scanf("%d-%d-%d",&t.date.hour,&t.date.minute,&t.date.second);
    printf("Time of screening(hour-minute-second):");
    scanf("%d-%d-%d",&t.time.hour,&t.time.minute,&t.time.second);
    printf("Number of seat:");
    scanf("%d",&t.seat_count);
    printf("=======================================================\n");

    if (Schedule_Srv_Modify(&t, play_id)) {
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