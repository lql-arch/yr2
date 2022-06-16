//
// Created by bronya on 22-6-14.
//

#include "Play_UI.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "Schedule_UI.h"
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

    //载入数据
    paging.totalRecords = Play_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head, paging);

    do {
    #ifdef linux
            system("clear");
    #endif
    #ifdef WIN32
            system("cls");
    #endif
        printf("\n==========================================================================================================\n");
        printf(
                "*************************************** Play Room List ***************************************************\n");
        printf("%5s  %20s  %10s  %5s  %10s  %10s  %10s  %10s  %6s\n", "ID", "Name", "type",
               "area", "rating","duration","start_date","end_date","price");
        printf(
                "----------------------------------------------------------------------------------------------------------\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i){
            printf("%5d  %20s  %10u  %5s  %10u  %10d  %4d-%2d-%2d  %4d-%2d-%2d  %6d\n", pos->date.id,
                   pos->date.name, pos->date.type, pos->date.area,pos->date.rating,pos->date.duration,
                   pos->date.start_date.year,pos->date.start_date.month,pos->date.start_date.day,
                   pos->date.end_date.year,pos->date.start_date.month,pos->date.start_date.day,pos->date.price);
        }

        printf(
                "---------------- Total Records:%2d ------------------------------ Page %2d/%2d -----------------------------\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));
        printf(
                "**********************************************************************************************************\n");
        printf(
                "[P]revPage|[N]extPage | [A]dd|[D]elete|[U]pdate | [S]eat | [F]indSchedule | [R]eturn");
        printf("\n==========================================================================================================\n");
        printf("type: [1/file] [2/opear] [3/concert]           rating: [1/child] [2/teenage] [3/adult]");
        printf("\n==========================================================================================================\n");
        printf("Your Choice:");
        fflush(stdin);
        scanf("%c", &choice);
        while((ch = getchar()) != '\n')
            continue;

        switch (choice) {
            case 'a':
            case 'A':
                if (Play_UI_Add()) //新添加成功，跳到最后一页显示
                {
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, play_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("Input the ID:");
                scanf("%d", &id);
                while((ch = getchar()) != '\n')
                    continue;
                if (Play_UI_Delete(id)) {	//从新载入数据
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    List_Paging(head, paging, play_node_t);
                }
                break;
            case 'u':
            case 'U':
                printf("Input the ID:");
                scanf("%d", &id);
                while((ch = getchar()) != '\n')
                    continue;
                if (Play_UI_Modify(id)) {	//从新载入数据
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    List_Paging(head, paging, play_node_t);
                }
                break;
            case 's':
            case 'S':
                printf("Input the ID:");
                scanf("%d", &id);
                while((ch = getchar()) != '\n')
                    continue;
                if(Play_UI_Query(id,&paging)){
                    paging.totalRecords = Play_Srv_FetchAll(head);
                    List_Paging(head, paging, play_node_t);
                }
                break;
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
            case 'f':
            case 'F':
                printf("Input the ID:");
                scanf("%d", &id);
                while((ch = getchar()) != '\n')
                    continue;
                Schedule_UI_MgtEntry(id);
                break;
        }
    } while (choice != 'r' && choice != 'R');
    //释放链表空间
    List_Destroy(head, play_node_t);
}

int Play_UI_Add(){
    play_t t;
    int NewCount = 0;
    char choice;

    do{
        #ifdef linux
                system("clear");
        #endif
        #ifdef WIN32
                system("cls");
        #endif
        printf("\n====================================================================================\n");
        printf("********************************  Add New Projection Room  ***************************\n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("Play Name:");
        scanf("%s",t.name);
        printf("Type of Play([1/file] [2/opear] [3/concert]):");
        scanf("%d", &(t.type));
        printf("Area of Play:");
        scanf("%s", t.area);
        printf("rating of Play([1/child] [2/teenage] [3/adult]):");
        scanf("%d",&t.rating);
        printf("Duration of Play:");
        scanf("%d",&t.duration);
        printf("Start_date of Play(year-month-day):");
        scanf("%d-%d-%d",&t.start_date.year,&t.start_date.month,&t.start_date.day);
        printf("End_date of Play(year-month-day):");
        scanf("%d-%d-%d",&t.end_date.year,&t.end_date.month,&t.end_date.day);
        printf("Price of play:");
        scanf("%d",&t.price);
        printf("======================================================================================\n");

        if (Play_Srv_Add(&t)) {
            NewCount += 1;
            printf("The new room added successfully!\n");
        } else
            printf("The new room added failed!\n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("[A]dd more, [R]eturn:");
        fflush(stdin);
        scanf("%c", &choice);
    } while ('a' == choice || 'A' == choice);

    while((choice = getchar()) != '\n')
        continue;

    return NewCount;

}

int Play_UI_Modify(int id){
    play_t t;
    int rtn = 0;

    /*Load record*/
    if (!Play_Srv_FetchByID(id, &t)) {
        printf("The play does not exist!\n"
               "Press [Enter] key to return!\n");
        getchar();
        return 0;
    }


    #ifdef linux
        system("clear");
    #endif
    #ifdef WIN32
        system("cls");
    #endif

    printf("\n=======================================================\n");
    printf("**************** Modify %dth Projection Room  ****************\n",id);
    printf("-------------------------------------------------------\n");
    printf("Room ID:%d\n", t.id);
    printf("Room Name[%s]:", t.name);
    fflush(stdin);
    fgets(t.name,30,stdin);
    printf("Type of Play([1/file] [2/opear] [3/concert]):");
    scanf("%d", &(t.type));
    printf("Area of Play:");
    scanf("%s", t.area);
    printf("rating of Play([1/child] [2/teenage] [3/adult]):");
    scanf("%d",&t.rating);
    printf("Duration of Play:");
    scanf("%d",&t.duration);
    printf("Start_date of Play(year-month-day):");
    scanf("%d-%d-%d",&t.start_date.year,&t.start_date.month,&t.start_date.day);
    printf("End_date of Play(year-month-day):");
    scanf("%d-%d-%d",&t.end_date.year,&t.end_date.month,&t.end_date.day);
    printf("Price of play:");
    scanf("%d",&t.price);
    printf("=======================================================\n");

    if (Play_Srv_Modify(&t)) {
        rtn = 1;
        printf("The play data updated successfully!\nPress [Enter] key to return!\n");
    } else
        printf("The play data updated failed!\nPress [Enter] key to return!\n");

    getchar();
    return rtn;
}

int Play_UI_Delete(int id){
    int rtn = 0;

    if (Play_Srv_Deleteify(id)) {
       Schedule_srv_DeleteByID(id);
       printf("The play deleted successfully!\nPress [Enter] key to return!\n");
        rtn = 1;
    } else {
        printf("The play does not exist!\nPress [Enter] key to return!\n");
    }

    getchar();

    return rtn;
}

int Play_UI_Query(int id, Pagination_t *paging){
    return Play_SetOffset(id,paging);
}