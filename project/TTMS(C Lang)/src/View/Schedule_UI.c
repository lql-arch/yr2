//
// Created by bronya on 22-6-13.
//

#include "Schedule_UI.h"
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include <stdio.h>


void Schedule_UI_MgtEntry(int argc){
    int i,id;
    char choice;
    char ch;

    schedule_node_t *head;
    schedule_node_t *pos;
    Pagination_t paging;

    List_Init(head, schedule_node_t);
    paging.offset = 0;
    paging.pageSize = 5;

    //载入数据
    paging.totalRecords = Schedule_Srv_FetchByPlay(head);
    Paging_Locate_FirstPage(head, paging);


    do {
        printf(
                "\n==================================================================\n");
        printf(
                "*********************** Play Room List *****************************\n");
        printf("%5s  %8s  %10s  %8s  %10s  %5s\n", "ID", "play_id", "studio_id",
               "time", "date","seat_count");
        printf(
                "------------------------------------------------------------------\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
            printf("%5d  %8d  %10d  %2d-%2d-%2d  %4d-%2d-%2d  %5d\n", pos->date.id,pos->date.play_id,pos->date.studio_id,
                   pos->date.time.hour,pos->date.time.minute,pos->date.time.second, pos->date.date.hour,pos->date.date.minute,pos->date.date.second, pos->date.seat_count);
        }

        printf(
                "------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));
        printf(
                "******************************************************************\n");
        printf(
                "[P]revPage|[N]extPage | [A]dd|[D]elete|[U]pdate | [S]eat | [R]eturn");
        printf(
                "\n==================================================================\n");
        printf("Your Choice:");
        fflush(stdin);
        scanf("%c", &choice);
        while((ch = getchar()) != '\n'){}
        fflush(stdin);

//        switch (choice) {
//            case 'a':
//            case 'A':
//                if (Schedule_UI_Add()) //新添加成功，跳到最后一页显示
//                {
//                    paging.totalRecords = Schedule_Srv_FetchByPlay(head);
//                    Paging_Locate_LastPage(head, paging, schedule_node_t);
//                }
//                break;
//            case 'd':
//            case 'D':
//                printf("Input the ID:");
//                scanf("%d", &id);
//                if (Schedule_UI_Delete(id)) {	//从新载入数据
//                    paging.totalRecords = Schedule_Srv_FetchByPlay(head);
//                    List_Paging(head, paging, schedule_node_t);
//                }
//                break;
//            case 'u':
//            case 'U':
//                printf("Input the ID:");
//                scanf("%d", &id);
//                if (Schedule_UI_Modify(id)) {	//从新载入数据
//                    paging.totalRecords = Schedule_Srv_FetchByPlay(head);
//                    List_Paging(head, paging, schedule_node_t);
//                }
//                break;
//            case 's':
//            case 'S':
//                printf("Input the ID:");
//                scanf("%d", &id);
//                paging.totalRecords = Schedule_Srv_FetchByPlay(head);
//                List_Paging(head, paging, schedule_node_t);
//                break;
//            case 'p':
//            case 'P':
//                if (!Pageing_IsFirstPage(paging)) {
//                    Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
//                }
//                break;
//            case 'n':
//            case 'N':
//                if (!Pageing_IsLastPage(paging)) {
//                    Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
//                }
//                break;
//        }
    } while (choice != 'r' && choice != 'R');
    //释放链表空间
    List_Destroy(head, schedule_node_t);
}

int Schedule_UI_Add(){
//    int id;
//    schedule_t t;
//    char choice;
//
//    do{
//        fflush(stdin);
//        printf("\n=======================================================\n");
//        printf("********************  Add New Play Room  ****************\n");
//        printf("-------------------------------------------------------\n");
//        printf("Play Name:");
//        scanf("%d", &(t.play_id));
//        printf("Projection Room:");
//        scanf("%d", &(t.studio_id));
//        printf(" ");
//        printf("=======================================================\n");
//
//
//
//
//    }while();

}

void Schedule_UI_Modify(){

}

void Schedule_UI_Delete(){

}