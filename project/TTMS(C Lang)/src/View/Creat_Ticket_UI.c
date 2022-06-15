//
// Created by bronya on 22-6-15.
//

#include "Creat_Ticket_UI.h"
#include "Creat_Ticket.h"
#include <stdio.h>

void Tick_UI_MgrEntry(int schedule_id){
    int i,id;
    char choice;
    char ch;

    ticket_list_t head;
    ticket_node_t *pos;
    Pagination_t paging;

    List_Init(head, ticket_node_t);
    paging.offset = 0;
    paging.pageSize = 5;

    //载入数据
    //未完成：不同多个数据
    paging.totalRecords = Ticket_Srv_FetchAll(head);
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
                "*********************** %dth Schedule List *****************************\n",schedule_id);
        printf("%5s  %8s  %8s  %6s  %5s  \n", "ID", "schedule_id", "seat_id",
               "price", "status");
        printf(
                "------------------------------------------------------------------\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
            printf("%5d  %8d  %8d  %6d  %5d\n", pos->data.id,pos->data.schedule_id,pos->data.seat_id,
                   pos->data.price,pos->data.status);
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
//            case 'a':
//            case 'A':
//                if (Schedule_UI_Add()) //新添加成功，跳到最后一页显示
//                {
//                    paging.totalRecords = Schedule_Srv_FetchAll(head);
//                    Paging_Locate_LastPage(head, paging, schedule_node_t);
//                }
//                break;
//            case 'd':
//            case 'D':
//                printf("Input the ID:");
//                scanf("%d", &id);
//                if (Schedule_UI_Delete(id)) {	//从新载入数据
//                    paging.totalRecords = Schedule_Srv_FetchAll(head);
//                    List_Paging(head, paging, schedule_node_t);
//                }
//                break;
//            case 'u':
//            case 'U':
//                printf("Input the ID:");
//                scanf("%d", &id);
//                if (Schedule_UI_Modify(id)) {	//从新载入数据
//                    paging.totalRecords = Schedule_Srv_FetchAll(head);
//                    List_Paging(head, paging, schedule_node_t);
//                }
//                break;
//            case 's':
//            case 'S':
//                printf("Input the ID:");
//                scanf("%d", &id);
//                while((ch = getchar()) != '\n')
//                    continue;
//                if(Schedule_SetOffset(id,&paging)){
//                    paging.totalRecords = Schedule_Srv_FetchAll(head);
//                    List_Paging(head, paging, schedule_node_t);
//                }
//                paging.totalRecords = Schedule_Srv_FetchAll(head);
//                List_Paging(head, paging, schedule_node_t);
//                break;
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
        }
    } while (choice != 'r' && choice != 'R');
    //释放链表空间
    List_Destroy(head, schedule_node_t);
}