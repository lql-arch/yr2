/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* File name: Main_Menu.c			 	 
* Description : TTMS 
* Author:   XUPT  		 
* Version:  v.1 	 
* Da
*/

#include "../View/Main_Menu.h"

#include <stdio.h>
#include <stdlib.h>

#include "../View/Studio_UI.h"
#include "../View/Account_UI.h"
#include "../View/Play_UI.h"
#include "../View/Sale_UI.h"

void Main_Menu1(char *name) {
	char choice;
    char ch;
	do {
    #ifdef linux
            system("clear");
    #endif
    #ifdef WIN32
            system("cls");
    #endif

        setbuf(stdin,0);

		printf("\n=============================1====================================\n");
		printf("**************** Theater Ticket Management System ****************\n");
		printf("[S]tudio Management.\n");
		printf("[P]lay Management.\n");
		printf("[T]icket Sale.\n");
		printf("[R]eturn Ticket.\n");
		printf("[Q]ueries\n");
		printf("Ra[n]king and Statistics.\n");
		printf("[A]ccount Management.\n");
		printf("[E]xist.\n");
		printf("\n==================================================================\n");
		printf("Please input your choice:");
		fflush(stdin);
		choice = getchar();

		switch (choice) {
		case 'S':
		case 's':
			Studio_UI_MgtEntry();
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(0);
			break;
//		case 'Q':
//		case 'q':
//			Queries_Menu();
//			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket();
			break;
//		case 'N':
//		case 'n':
//			SalesAanalysis_UI_MgtEntry();
//			break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry(1,name);
			break;
		}
	} while ('E' != choice && 'e' != choice);

    setbuf(stdin,0);

}

void Main_Menu9(char *name){
    char choice;
    char ch;
    do {
#ifdef linux
        system("clear");
#endif
#ifdef WIN32
        system("cls");
#endif

        setbuf(stdin,NULL);

        printf("\n============================9=====================================\n");
        printf("**************** Theater Ticket Management System ****************\n");
        printf("[S]tudio Management.\n");
        printf("[P]lay Management.\n");
        printf("[T]icket Sale.\n");
        printf("[R]eturn Ticket.\n");
        printf("[Q]ueries\n");
        printf("Ra[n]king and Statistics.\n");
        printf("[A]ccount Management.\n");
        printf("[E]xist.\n");
        printf("\n==================================================================\n");
        printf("Please input your choice:");
        fflush(stdin);
        choice = getchar();

        switch (choice) {
            case 'S':
            case 's':
                Studio_UI_MgtEntry();
                break;
            case 'P':
            case 'p':
                Play_UI_MgtEntry(0);
                break;
//		case 'Q':
//		case 'q':
//			Queries_Menu();
//			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket();
			break;
//		case 'N':
//		case 'n':
//			SalesAanalysis_UI_MgtEntry();
//			break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry(9,name);
			break;
        }
    } while ('E' != choice && 'e' != choice);

    setbuf(stdin,NULL);
}

void Main_Menu0(char *name){
    char choice;
    char ch;
    do {
#ifdef linux
        system("clear");
#endif
#ifdef WIN32
        system("cls");
#endif

        setbuf(stdin,0);

        printf("\n================================0=================================\n");
        printf("**************** Theater Ticket Management System ****************\n");
        printf("[S]tudio Management.\n");
        printf("[P]lay Management.\n");
        printf("[T]icket Sale.\n");
        printf("[R]eturn Ticket.\n");
        printf("[Q]ueries\n");
        printf("Ra[n]king and Statistics.\n");
        printf("[A]ccount Management.\n");
        printf("[E]xist.\n");
        printf("\n==================================================================\n");
        printf("Please input your choice:");
        choice = getchar();


        switch (choice) {
            case 'S':
            case 's':
                Studio_UI_MgtEntry();
                break;
            case 'P':
            case 'p':
                Play_UI_MgtEntry(0);
                break;
//		case 'Q':
//		case 'q':
//			Queries_Menu();
//			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket();
			break;
//		case 'N':
//		case 'n':
//			SalesAanalysis_UI_MgtEntry();
//			break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry(0,name);
			break;
        }
    } while ('E' != choice && 'e' != choice);

    setbuf(stdin,NULL);

}

void Main_Menu2(char *name){
    char choice;
    char ch;
    do {
#ifdef linux
        system("clear");
#endif
#ifdef WIN32
        system("cls");
#endif

        setbuf(stdin,0);

        printf("\n===============================2==================================\n");
        printf("**************** Theater Ticket Management System ****************\n");
        printf("[S]tudio Management.\n");
        printf("[P]lay Management.\n");
        printf("[T]icket Sale.\n");
        printf("[R]eturn Ticket.\n");
        printf("[Q]ueries\n");
        printf("Ra[n]king and Statistics.\n");
        printf("[A]ccount Management.\n");
        printf("[E]xist.\n");
        printf("\n==================================================================\n");
        printf("Please input your choice:");
        fflush(stdin);
        choice = getchar();

        switch (choice) {
            case 'S':
            case 's':
                Studio_UI_MgtEntry();
                break;
            case 'P':
            case 'p':
                Play_UI_MgtEntry(0);
                break;
//		case 'Q':
//		case 'q':
//			Queries_Menu();
//			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket();
			break;
//		case 'N':
//		case 'n':
//			SalesAanalysis_UI_MgtEntry();
//			break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry(2,name);
			break;
        }
    } while ('E' != choice && 'e' != choice);

    setbuf(stdin,NULL);
}