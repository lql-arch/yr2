//
// Created by bronya on 22-6-15.
//

#include "Creat_Ticket_UI.h"
#include "Creat_Ticket.h"
#include "Play.h"
#include <stdio.h>

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
            "*********************** Show program information *****************************\n",schedule_id);
    printf("%8s %8s  %8s  %10s  %8s %8s\n", "schedule_ID", "play_ID", "studio_ID",
           "date", "time","seat_count");
    printf(
            "-------------------------------------------------------------------------------\n");
    //显示数据
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
                if(Ticket_Srv_GenBatch(schedule_id)){
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