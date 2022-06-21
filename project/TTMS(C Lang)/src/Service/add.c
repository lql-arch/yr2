
#include "Schedule.h"
#include "Schedule_Persist.h"
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include "../Service/Creat_Ticket.h"
#include "../View/Creat_Ticket_UI.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
    #include <io.h>
#endif
#ifdef linux
    #include <sys/io.h>
#endif
#include <assert.h>
#include <unistd.h>
#include "Sale.h"
#include "../Persistence/Sale_Persist.h"


static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";//保存演出计划信息
static const char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat";////删除或更新时，暂时保存演出计划信息

int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id)
{
    schedule_node_t* newNode;
    schedule_t data;
    int recCount = 0;

    assert(NULL != list);

    if (access(SCHEDULE_DATA_FILE, 0x00))
    {
        printf("无法打开文件 %s!\n", SCHEDULE_DATA_FILE);
        while (getchar() != '\n')
            continue;
        return 0;
    }

    List_Free(list, schedule_node_t);

    FILE* fp = fopen(SCHEDULE_DATA_FILE, "rb");
    if (NULL == fp)
    {
        printf("无法打开文件 %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }

    while (!feof(fp))
    {
        if (fread(&data, sizeof(schedule_t), 1, fp) && data.play_id == play_id)
        {
            newNode = (schedule_node_t*)malloc(sizeof(schedule_node_t));
            if (!newNode)
            {
                printf("文件打开失败\n");
                break;
            }
            newNode->date = data;
            List_AddTail(list, newNode);
            recCount++;
        }
    }
    fclose(fp);
    return recCount;
}

int Ticket_Srv_StatRevBySchID(int schedule_id, int* soldCount)
{
    int value = 0;
    *soldCount = 0;
    sale_t sale;
    ticket_list_t list;
    ticket_node_t* pos;

    List_Init(list, ticket_node_t);

    *soldCount = Ticket_Srv_FetchBySchID(schedule_id,list);
    List_ForEach(list, pos)
    {
        if (Sale_Srv_FetchByTicketID(pos->data.id, &sale) == 0)
            continue;
       // printf("type:%d\n", sale.type);
        if (pos->data.status == TICKET_SOLD && sale.type == SALE_SELL)
        {
            //printf("test");
            (*soldCount)++;
            value += pos->data.price;
        }
    }
    List_Destroy(list, ticket_node_t);
    return value;
}









int Schedule_Srv_StatRevByPlay(int play_id, int* soldCount)
{
    *soldCount = 0;
    int value = 0;
    int sold = 0;
    schedule_list_t list;
    schedule_node_t* pos;

    List_Init(list, schedule_node_t);

    Schedule_Perst_SelectByPlay(list, play_id);
    List_ForEach(list, pos)
    {
        value += Ticket_Srv_StatRevBySchID(pos->date.id, &sold);
        (*soldCount) += sold;
    }
    List_Destroy(list, schedule_node_t);
    return value;
}

