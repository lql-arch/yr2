//
// Created by bronya on 22-6-14.
//

#include "Play_UI.h"
#include "Seat_UI.h"

static const int PLAY_PAGE_SIZE = 5;

void Play_UI_MgtEntry(int argc){
    int i, id;
    char choice;
    char ch;

    play_list_t head;
    play_node_t *pos;
    Pagination_t paging;
    play_t test;

    List_Init(head, play_node_t);
    paging.offset = 0;
    paging.pageSize = PLAY_PAGE_SIZE;

    //载入数据
    paging.totalRecords = Play_Srv_FetchAll(head);

    Paging_Locate_FirstPage(head, paging);



    do {

        while((ch = getchar()) != '\n')
            continue;

    #ifdef linux
            system("clear");
    #endif
    #ifdef WIN32
            system("cls");
    #endif
        printf("\n========================================================================================================================\n");
        printf(
                "*************************************** Play Room List *****************************************************************\n");
        printf("%5s   %15s   %5s   %15s   %10s    %10s     %10s    %10s   %8s\n", "ID", "Name", "type",
               "area", "rating","duration","start_date","end_date","price");
        printf(
                "------------------------------------------------------------------------------------------------------------------------\n");
        //显示数据
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i){
            printf("%5d   %15s   %5d   %15s   %10d    %10d   %04d-%02d-%02d   %04d-%02d-%02d   %8d\n", pos->date.id,
                   pos->date.name, pos->date.type, pos->date.area,pos->date.rating,pos->date.duration,
                   pos->date.start_date.year,pos->date.start_date.month,pos->date.start_date.day,
                   pos->date.end_date.year,pos->date.start_date.month,pos->date.start_date.day,pos->date.price);
        }

        printf(
                "---------------- Total Records:%2d ------------------------------ Page %2d/%2d --------------------------------------------\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));
        printf(
                "************************************************************************************************************************\n");
        printf(
                "[P]revPage|[N]extPage | [A]dd|[D]elete|[U]pdate | [S]eat | [F]indSchedule | [R]eturn");
        printf("\n========================================================================================================================\n");
        printf("type: [1/file] [2/opear] [3/concert]           rating: [1/child] [2/teenage] [3/adult]");
        printf("\n========================================================================================================================\n");
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
                while ((ch = getchar()) != '\n')
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
                while ((ch = getchar()) != '\n')
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
                while ((ch = getchar()) != '\n')
                    continue;
                Seat_UI_MgtEntry(id);
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
                while ((ch = getchar()) != '\n')
                    continue;
                if(!Play_Srv_FetchByID(id,&test)){
                    fprintf(stderr,"Error:%d does not exist.\nPress [Enter] key to return!\n",id);
                    getchar();
                    break;
                }
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
    char ch;
    int count = 0;

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
        while((ch = getchar()) != '\n' && count < 30 ){
            t.name[count++] = ch;
        }
        t.name[count] = '\0';
        printf("Type of Play([1/file] [2/opera] [3/concert]):");
        scanf("%d", &(t.type));
        printf("Area of Play:");
        scanf("%s", t.area);
        printf("rating of Play([1/child] [2/teenage] [3/adult]):");
        scanf("%d",&t.rating);
        printf("Duration of Play(minute):");
        scanf("%d",&t.duration);
        printf("Start_date of Play(year-month-day):");
        scanf("%d-%d-%d",&t.start_date.year,&t.start_date.month,&t.start_date.day);
        printf("End_date of Play(year-month-day):");
        scanf("%d-%d-%d", &t.end_date.year, &t.end_date.month, &t.end_date.day);
        while(!isTime(t)){
            fprintf(stderr,"start_date cannot be after end_date.\n");
            printf("End_date of Play(year-month-day):");
            scanf("%d-%d-%d", &t.end_date.year, &t.end_date.month, &t.end_date.day);
        }
        printf("Price of play:");
        scanf("%d",&t.price);
        printf("======================================================================================\n");
        printf("%5s   %15s   %5s   %15s   %10s    %10s     %10s    %10s   %8s\n", "ID", "Name", "type",
               "area", "rating","duration","start_date","end_date","price");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        //显示数据
            printf("%5d   %15s   %5d   %15s   %10d    %10d   %04d-%02d-%02d   %04d-%02d-%02d   %8d\n", t.id,
                   t.name, t.type, t.area,t.rating,t.duration,
                   t.start_date.year,t.start_date.month,t.start_date.day,
                   t.end_date.year,t.start_date.month,t.start_date.day,t.price);
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        while((choice = getchar()) != '\n')
            continue;
        printf("Canlcel:input \'R\' or \'r\',Press [Enter] to go tothenext step.\n");
        choice = getchar();
        if(choice == 'r' || choice == 'R' ){
            return 0;
        }

        if (Play_Srv_Add(&t)) {
            NewCount += 1;
            printf("The new room added successfully!\n");
        } else
            printf("The new room added failed!\n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("[A]add more, [R]return:");
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
    char ch;
    int count = 0;

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
    while((ch = getchar()) != '\n' && count < 30 ){
        t.name[count++] = ch;
    }
    t.name[count] = '\0';
    printf("Type of Play([1/file] [2/opera] [3/concert]):");
    scanf("%d", &(t.type));
    printf("Area of Play:");
    scanf("%s", t.area);
    printf("rating of Play([1/child] [2/teenage] [3/adult]):");
    scanf("%d",&t.rating);
    printf("Duration of Play(minute):");
    scanf("%d",&t.duration);
    printf("Start_date of Play(year-month-day):");
    scanf("%d-%d-%d",&t.start_date.year,&t.start_date.month,&t.start_date.day);
    printf("End_date of Play(year-month-day):");
    scanf("%d-%d-%d",&t.end_date.year,&t.end_date.month,&t.end_date.day);
    while(!isTime(t)){
        fprintf(stderr,"start_date cannot be after end_date.\n");
        printf("End_date of Play(year-month-day):");
        scanf("%d-%d-%d", &t.end_date.year, &t.end_date.month, &t.end_date.day);
    }
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
    char choice;
    int new_id;

    do {
        if (Play_Srv_Deleteify(id)) {
            Schedule_srv_DeleteByID(id);
            printf("The play deleted successfully!\n");
            rtn += 1;
        } else {
            printf("The play does not exist!\n");
        }
        printf("--------------------------------------------------------------------------------------\n");
        printf("[D]delete more, [R]return:");
        fflush(stdin);
        scanf("%c", &choice);
        printf("Id of be deleted:");
        scanf("%d",&new_id);
    } while ('d' == choice || 'D' == choice);


    printf("Press [Enter] key to return!\n");
    getchar();

    return rtn;
}

int Play_UI_Query(int id, Pagination_t *paging){
    play_t test;
    if(!Play_Srv_FetchByID(id,&test)){
        fprintf(stderr,"Error:%d does not exist.\nPress [Enter] key to return!\n",id);
        getchar();
        return 0;
    }
    return Play_SetOffset(id,paging);
}


int isTime(play_t t){
    if(t.start_date.year < t.end_date.year) {
        return 1;
    }
    else if(t.start_date.month < t.end_date.month) {
        return 1;
    }
    else if(t.start_date.day <= t.end_date.day) {
        return 1;
    }

    return 0;
}

void Play_UI_ShowList(play_list_t list,Pagination_t paging)//界面函数
{
    char ch;
    int i = 0,j;
    char choice;
    play_node_t *pos;

    do {
        while ((ch = getchar()) != '\n')
            continue;

    #ifdef linux
            system("clear");
    #endif
    #ifdef WIN32
            system("cls");
    #endif
        printf("\n\t\t\t\t=====================================================================================\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t*********剧目信息**********\n");
        printf("\n\t\t\t\t-------------------------------------------------------------------------------------\n");
        printf("\t\t\t\t%4s %12s %12s\t %8s %8s\t %8s %10s %6s",
               "ID", "名称", "出品地区", "类型", "等级", "时长(分钟)", "放映时间", "票价");
        printf("\n\t\t\t\t-------------------------------------------------------------------------------------\n");
        Paging_ViewPage_ForEach(list, paging, play_node_t, pos, i) {
            printf("\t\t\t\t%4d %12s %12s\t ", pos->date.id, pos->date.name, pos->date.area);
            j = pos->date.type;
            switch (j) {
                case 1:
                    printf("%8s ", "电影");
                    break;
                case 2:
                    printf("%8s ", "歌剧");
                    break;
                case 3:
                    printf("%8s ", "音乐会");
                    break;
            }
            j = pos->date.rating;
            switch (j) {
                case 1:
                    printf("%8s ", "儿童剧");
                    break;
                case 2:
                    printf("%8s ", "少年剧");
                    break;
                case 3:
                    printf("%8s ", "成人剧");
                    break;
                default:
                    printf("%8s ", "无");
                    break;
            }
            printf("\t%6d\t\t", pos->date.duration);
            printf("%04d/%02d/%02d ", pos->date.start_date.year, pos->date.start_date.month, pos->date.start_date.day);;
            printf("%6d \n ", pos->date.price);
        }
        printf("\t\t\t\t------- 共 %2d 项 ------------------------- 第 %2d/%2d 页 -------------------------------\n",
               paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
        printf(
                "************************************************************************************************************************\n");
        printf(
                "[P]revPage|[N]extPage | [S]ure");
        printf("\n========================================================================================================================\n");
        printf("Your Choice:");
        fflush(stdin);
        scanf("%c", &choice);
        while ((ch = getchar()) != '\n')
            continue;

        switch (choice) {
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
        }
    }while(choice != 's' && choice != 'S');
}//载入数据