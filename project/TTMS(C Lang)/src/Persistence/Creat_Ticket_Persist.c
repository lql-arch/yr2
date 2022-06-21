//
// Created by bronya on 22-6-15.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include "Creat_Ticket_Persist.h"
#include "Schedule_Persist.h"
#include "Play.h"
#include "Play_Perst.h"
#include "EntityKey_Persist.h"

static const char TICKET_KEY_NAME[] = "Ticket";
static const char TICKET_DATA_FILE[] = "Ticket.dat";
static const char TICKET_DATA_TEMP_FILE[] = "TicketTmp.dat";


int Ticket_Perst_Insert(int schedule_id,int studio_id){
    schedule_t sch;
    seat_node_t *p;
    play_t play;
    FILE *fp;
    int seat_num;
    seat_list_t list;
    ticket_t data;

    List_Init(list,seat_node_t);


    if((fp = fopen(TICKET_DATA_FILE,"ab+")) == NULL) {
        printf("Failed:open %s", TICKET_DATA_FILE);
        return 0;
    }

    if (! Schedule_Srv_FetchByID(schedule_id,&sch)) {
        printf("The schedule does not exist!\nPress [Enter] key to return\n");
        setbuf(stdin,NULL);
        getchar();
        return 0;
    }

    if (! Play_Srv_FetchByID(sch.play_id,&play)) {
        printf("The play does not exist!\nPress [Enter] key to return\n");
        setbuf(stdin,NULL);
        getchar();
        return 0;
    }

    if(!Seat_Srv_FetchValidByRoomID(list,studio_id)){
        printf("The play does not exist!\nPress [Enter] key to return\n");
        setbuf(stdin,NULL);
        getchar();
        return 0;
    }


    List_ForEach(list,p)
    {
        data.id = EntKey_Perst_GetNewKeys(TICKET_KEY_NAME,1);
        data.price = play.price;
        data.schedule_id = schedule_id;
        data.seat_id = p->data.id;
        data.status = 0;
        printf("%d %d %d\n",data.id,data.seat_id,data.schedule_id);
        fwrite(&data,sizeof(ticket_t),1,fp);
        seat_num++;
    }



    fclose(fp);

    return seat_num;
}

int Ticket_Perst_Rem(int schedule_id){

    if(rename(TICKET_DATA_FILE, TICKET_DATA_TEMP_FILE)<0){
        printf("Cannot open file %s!\n", TICKET_DATA_FILE);
        return 0;
    }

    FILE *fpSour, *fpTarg;
    fpSour = fopen(TICKET_DATA_TEMP_FILE, "rb");
    if (NULL == fpSour ){
        printf("Cannot open file %s!\n", TICKET_DATA_TEMP_FILE);
        return 0;
    }

    fpTarg = fopen(TICKET_DATA_FILE, "wb");
    if ( NULL == fpTarg ) {
        printf("Cannot open file %s!\n", TICKET_DATA_FILE);
        return 0;
    }

    ticket_t buf;

    int found = 0;
    while (!feof(fpSour)) {
        if (fread(&buf, sizeof(ticket_t), 1, fpSour)) {
            if (schedule_id == buf.schedule_id) {
                found = 1;
                continue;
            }
            fwrite(&buf, sizeof(ticket_t), 1, fpTarg);
        }
    }

    fclose(fpTarg);
    fclose(fpSour);

    //删除临时文件
    remove(TICKET_DATA_TEMP_FILE);
    return found;
}

int Ticket_Perst_SelByID(int id, ticket_t *buf)
{

    int found = 0;
    assert(NULL!=buf);

    FILE *fp = fopen(TICKET_DATA_FILE, "rb+");
    if (NULL == fp)
    {
        printf("%s ERROR.\n",TICKET_DATA_FILE);
        return 0;
    }

    ticket_t data;

    while (!feof(fp))
    {
        if (fread(&data, sizeof(ticket_t), 1, fp))
        {
            if (id == data.id)
            {
                *buf = data;
                found = 1;
                break;
            }

        }
    }
    fclose(fp);

    return found;
}

int Ticket_Perst_FetchAll(ticket_list_t list){
    ticket_node_t *newNode;
    ticket_t data;
    int recCount = 0;

    assert(NULL!=list);

    printf("无法打开文件 %s!\n", TICKET_DATA_FILE);
    if (access(TICKET_DATA_FILE, 0))
        return 0;

    List_Free(list, ticket_node_t);

    FILE *fp = fopen(TICKET_DATA_FILE, "rb");
    if (NULL == fp){
        printf("无法打开文件 %s!\n", TICKET_DATA_FILE);
        return 0;
    }

    while (!feof(fp)){
        if (fread(&data, sizeof(ticket_t), 1, fp)){
            newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
            if (!newNode) {
                printf("错误！\n");
                break;
                }
                newNode->data = data;
                List_AddTail(list, newNode);
                recCount++;
            }
    }

    fclose(fp);
    return recCount;
}

int Ticket_Perst_SelectAll(ticket_list_t list)
{
    ticket_node_t *newNode;
    ticket_t data;
    int recCount = 0;

    assert(NULL!=list);

    printf("无法打开文件 %s!\n", TICKET_DATA_FILE);
    if (access(TICKET_DATA_FILE, 0))
        return 0;

    List_Free(list, ticket_node_t);

    FILE *fp = fopen(TICKET_DATA_FILE, "rb");
    if (NULL == fp)
    {
        printf("无法打开文件 %s!\n", TICKET_DATA_FILE);
        return 0;
    }

    while (!feof(fp))
    {
        if (fread(&data, sizeof(ticket_t), 1, fp)){
            newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
            if (!newNode) {
                printf("错误！\n");
                break;
            }
            newNode->data = data;
            List_AddTail(list, newNode);
            recCount++;
        }
    }
    fclose(fp);
    return recCount;
}