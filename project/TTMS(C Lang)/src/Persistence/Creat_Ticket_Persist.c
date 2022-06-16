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


int Ticket_Perst_Insert(int schedule_id){
    schedule_t sch;
    seat_list_t seat_list;
    seat_node_t *p;
    play_t play;
    int cnt = 0;
    FILE *fp;


    if((fp = fopen(TICKET_DATA_FILE,"ab")) == NULL) {
        printf("Failed:open %s", TICKET_DATA_FILE);
        return 0;
    }

    if (! Schedule_Srv_FetchByID(schedule_id,&sch)) {
        printf("The schedule does not exist!\nPress [Enter] key to return\n");
        setbuf(stdin,NULL);
        getchar();
        return 0;
    }

    if (! Play_Srv_FetchByID(schedule_id,&play)) {
        printf("The play does not exist!\nPress [Enter] key to return\n");
        setbuf(stdin,NULL);
        getchar();
        return 0;
    }

    List_Init(seat_list,seat_node_t);
    Seat_Srv_FetchValidByRoomID(seat_list,sch.studio_id);

    ticket_t data;
    List_ForEach(seat_list,p)
    {
        data.id = EntKey_Perst_GetNewKeys(TICKET_KEY_NAME,1);
        data.price = play.price;
        data.schedule_id = schedule_id;
        data.seat_id = p->data.id;
        data.status = 0;
        fwrite(&data,sizeof(ticket_t),1,fp);
        cnt++;
    }
    fclose(fp);

    return cnt;
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

    //É¾³ýÁÙÊ±ÎÄ¼þ
    remove(TICKET_DATA_TEMP_FILE);
    return found;
}