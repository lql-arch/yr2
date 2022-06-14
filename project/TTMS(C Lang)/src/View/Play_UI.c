//
// Created by bronya on 22-6-14.
//

#include "Play_UI.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include <stdio.h>

void Play_UI_MgtEntry(int argc){
    int i, id;
    char choice;
    char ch;

    play_list_t head;
    play_node_t *pos;
    Pagination_t paging;

    List_Init(head, play_node_t);
    paging.offset = 0;
    paging.pageSize = 5;

    //��������
    paging.totalRecords = Play_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head, paging);

    do {
        printf(
                "\n==================================================================\n");
        printf(
                "************************* Play Room List ***************************\n");
        printf("%5s  %20s  %10s  %5s  %10s  %10s  %10s  %10s  %6s\n", "ID", "Name", "type",
               "area", "rating","duration","start_date","end_date","price");
        printf(
                "------------------------------------------------------------------\n");
        //��ʾ����
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i){
            printf("%5d  %20s  %10u  %5s  %10u  %10d  %4d-%2d-%2d  %4d-%2d-%2d  %6d\n", pos->date.id,
                   pos->date.name, pos->date.type, pos->date.area,pos->date.rating,pos->date.duration,
                   pos->date.start_date.year,pos->date.start_date.month,pos->date.start_date.day,
                   pos->date.end_date.year,pos->date.start_date.month,pos->date.start_date.day,pos->date.price);
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

        switch (choice) {
            case 'a':
            case 'A':
                if (Play_UI_Add()) //����ӳɹ����������һҳ��ʾ
                {
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, play_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("Input the ID:");
                scanf("%d", &id);
                if (Play_UI_Delete(id)) {	//������������
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    List_Paging(head, paging, play_node_t);
                }
                break;
//            case 'u':
//            case 'U':
//                printf("Input the ID:");
//                scanf("%d", &id);
//                if (Play_UI_Modify(id)) {	//������������
//                    paging.totalRecords = Play_Srv_FetchAll(head);
//                    List_Paging(head, paging, play_node_t);
//                }
//                break;
//            case 's':
//            case 'S':
//                printf("Input the ID:");
//                scanf("%d", &id);
//                paging.totalRecords = Play_Srv_FetchAll(head);
//                List_Paging(head, paging, play_node_t);
//                break;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
                }
                break;
        }
    } while (choice != 'r' && choice != 'R');
    //�ͷ�����ռ�
    List_Destroy(head, play_node_t);
}

int Play_UI_Add(){
    play_t t;
    int NewCount = 0;
    char choice;

    do{
        fflush(stdin);
        printf("\n=======================================================\n");
        printf("****************  Add New Projection Room  ****************\n");
        printf("-------------------------------------------------------\n");
        printf("Play Name:");
        scanf("%s",t.name);
        printf("Type of Play:");
        scanf("%d", &(t.type));
        printf("Area of Play:");
        scanf("%s", t.area);
        printf("Duration of Play:");
        scanf("%d",&t.duration);
        printf("Start_date of Play(year-month-day):");
        scanf("%d-%d-%d",&t.start_date.year,&t.start_date.month,&t.start_date.day);
        printf("End_date of Play(year-month-day):");
        scanf("%d-%d-%d",&t.end_date.year,&t.end_date.month,&t.end_date.day);
        printf("=======================================================\n");

        if (Play_Srv_Add(&t)) {
            NewCount += 1;
            printf("The new room added successfully!\n");
        } else
            printf("The new room added failed!\n");
        printf("-------------------------------------------------------\n");
        printf("[A]dd more, [R]eturn:");
        fflush(stdin);
        scanf("%c", &choice);
    } while ('a' == choice || 'A' == choice);

    return NewCount;

}

void Play_UI_Modify(int id){

}

void Play_UI_Delete(int id){

}

void Play_UI_Query(){

}