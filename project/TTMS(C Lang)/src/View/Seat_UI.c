/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* ������ţ�TTMS_UC_02
* File name: Seat_UI.c			  
* Description : ������λ���������	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015��4��22��	
*/

#include "Seat_UI.h"
#include "../Service/Seat.h"

#include "../Service/Studio.h"
#include "../Common/List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Service/EntKey.h"

/*
��ʶ����TTMS_SCU_Seat_UI_S2C 
�������ܣ�������λ״̬��ȡ������ʾ���š�
����˵����statusΪseat_status_t���ͣ���ʾ��λ״̬��
�� �� ֵ���ַ��ͣ���ʾ��λ�Ľ�����ʾ���š�
*/

inline char Seat_UI_Status2Char(seat_status_t status) {
	char statusChar;
	switch (status) {
	case SEAT_GOOD:		//����λ
		statusChar = '#';
		break;
	case SEAT_BROKEN:	//�𻵵���λ
		statusChar = 'x';
		break;
	case SEAT_NONE:
	default:
		statusChar = ' ';
		break;
	}
	return statusChar;
}

/*
��ʶ����TTMS_SCU_Seat_UI_C2S
�������ܣ�����������Ż�ȡ��λ״̬��
����˵����statusCharΪ�ַ��ͣ���ʾ������λ��������š�
�� �� ֵ��seat_status_t���ͣ���ʾ��λ��״̬��
*/
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	seat_status_t status;
	switch (statusChar) {
	case '#':		//����λ
		status = SEAT_GOOD;
		break;			
	case '~':	//�𻵵���λ
		status = SEAT_BROKEN;
		break;
	default:
		status = SEAT_NONE;
		break;
	}
	return status;
}

/*
��ʶ����TTMS_SCU_Seat_UI_MgtEnt
�������ܣ�����������λ����ں�������ʾ��ǰ����λ���ݣ����ṩ��λ������ӡ��޸ġ�ɾ�����ܲ�������ڡ�
����˵����roomIDΪ���ͣ�����Ҫ������λ���ݳ���ID��
�� �� ֵ���ޡ�
*/ 
void Seat_UI_MgtEntry(int roomID)
{
	int i, j;
	char choice;
	int seatCount;
	int changedCount = 0;
	studio_t studioRec;

    #ifdef WIN32
        system("cls");//����
    #endif
    #ifdef linux
        system("clear");//����
    #endif

	if (!Studio_Srv_FetchByID(roomID, &studioRec)) {  //��ö�Ӧid��ӳ������Ϣ
		printf("\t\t\tû�иüƻ�\n���س�����\n");
		while(getchar() != '\n')
            continue;
		return;
	}

	seat_list_t list;
	seat_node_t *p;

	List_Init(list, seat_node_t);
	//ѡ���ӳ����������λ
	seatCount = Seat_Srv_FetchByRoomID(list, roomID);

//    List_ForEach(list,p)
//    {
//        printf("%d %d %d\n",p->data.id,p->data.column,p->data.row);
//    }
    printf("Seat:%d\n",seatCount);

	do {

#ifdef WIN32
        system("cls");//����
#endif
#ifdef linux
        system("clear");//����
#endif

		printf("\n\t\t\t\t==================================================================\n");
		printf("\n\t\t\t\t*************************  %s��ӳ������λ  *************************\n",studioRec.name);
		printf("\t\t\t\t%5c",' ');
		for (i = 1; i <= studioRec.colsCount; i++) {
			printf("%3d", i);
		}

		printf(
				"\n\t\t\t\t------------------------------------------------------------------\n");
		//��ʾ����
		for (i = 1; i <= studioRec.rowsCount; i++){
			j = 1;
			printf("\t\t\t\t%2d��:%c", i, ' ');

			List_ForEach(list,p)
			{
				if(p->data.row == i) {
					while (p->data.column != j) {
						printf("%3c", ' ');
						j++;
					}
					printf("%3c", Seat_UI_Status2Char(p->data.status));
					j++;
				}
			}
			printf("\n");
		}

		printf("\t\t\t\t[A]���  |  [D]ɾ��  |  [U]����  |  [R]����\n");
		printf("\n\t\t\t\t===================================================================\n");
		printf("\t\t\t\t���������ѡ��");
		fflush(stdin);
		choice = toupper(getchar());
		fflush(stdin);

		switch (choice) {
		case 'a':
		case 'A':
			changedCount = Seat_UI_Add(list, roomID,studioRec.rowsCount,
                                       studioRec.colsCount);
			if (changedCount > 0) {
				seatCount += changedCount;
				//�޸��ݳ��������λ����
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'd':
		case 'D':
			changedCount = Seat_UI_Delete(list, studioRec.rowsCount,
                                          studioRec.colsCount);
			if (changedCount > 0) {
				seatCount -= changedCount;
				//�޸��ݳ��������λ����
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'u':
		case 'U':
			Seat_UI_Modify(list, studioRec.rowsCount, studioRec.colsCount);
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//�ͷ�����ռ�
	List_Destroy(list, seat_node_t);
}

/*
ʶ����TTMS_SCU_Seat_UI_Add
�������ܣ��������һ���µ���λ���ݡ�
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬
         �ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��������λ�ı�־��
*/
int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) {  //����һ����λ
	seat_t rec;
	seat_node_t *p;
	int newRecCount = 0;
	char choice;
	do {
#ifdef WIN32
        system("cls");//����
#endif
#ifdef linux
        system("clear");//����
#endif
		printf("\n\t\t\t\t==================================================================\n");
		printf("\n\t\t\t\t**************************  �������λ  **************************\n");
		printf("------------------------------------------------------------------\n");

		do {
			printf("�в��ɳ� %d and �в��ɳ� %d!\n",
					row, column);
			printf("�ڼ��У� ");
			scanf("%d", &(rec.row));
			printf("�ڼ��У� ");
			scanf("%d", &(rec.column));
			while (getchar() != '\n')
				continue;
		} while (rec.row > row || rec.column > column);

		p = Seat_Srv_FindByRowCol(list, rec.row, rec.column);
		if (p) {						//����������к�����Ӧ����λ�Ѵ��ڣ����ܲ���
			printf("��λ�Ѵ���\n");
			printf("�����������");
			
			while (getchar() != '\n')
				continue;
			return 0;
		}

		rec.id = EntKey_Srv_CompNewKey("Seat");		//������λid
		rec.roomID = roomID;
		rec.status = SEAT_GOOD;    //���������λ��״̬Ĭ��Ϊ����λ
		printf("==================================================================\n");

		if (Seat_Srv_Add(&rec)) {
			newRecCount++;
			printf("����λ��ӳɹ�\n");
			p = (seat_node_t*) malloc(sizeof(seat_node_t));
			p->data = rec;
			Seat_Srv_AddToSoftedList(list, p); //������������λ�������list
		} else
			printf("����λ���ʧ��\n");
		printf("------------------------------------------------------------------\n");
		printf("[A]�������, [R]����");
		fflush(stdin);
		choice = toupper(getchar());
		while (getchar() != '\n')
			continue;
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

/*
��ʶ����TTMS_SCU_Seat_UI_Mod 
�������ܣ������޸�һ����λ���ݡ�
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��޸�����λ�ı�־��
*/
int Seat_UI_Modify(seat_list_t list, int row, int column) {
	int rtn = 0;
	int newrow, newcolumn;
	char choice;
	seat_node_t *p;

	printf("\n\t\t\t\t==================================================================\n");
	printf("\n\t\t\t\t***************************  ������λ  ***************************\n");
	printf("\t\t\t\t------------------------------------------------------------------\n");
	do {
		do {				//���µ���λ������Ϣ���ܳ�����ӳ����������
			printf("\t\t\t\t�в��ɳ� %d and �в��ɳ� %d!\n",
					row, column);
			printf("\t\t\t\t��λ�кţ� ");
			scanf("%d", &newrow);
			printf("\t\t\t\t��λ�кţ� ");
			scanf("%d", &newcolumn);
			while (getchar() != '\n')
				continue;
		} while (newrow > row || newcolumn > column);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p) {
			printf("\t\t\t\t�޸���λ��Ϣ[%d,%d]:[%c]Ϊ('#': ��λ����; '~':��λ��; ����:��λ������):", newrow, newcolumn,
					Seat_UI_Status2Char(p->data.status));
			choice = toupper(getchar());
			while (getchar() != '\n')
				continue;
			p->data.status = Seat_UI_Char2Status(choice);
		printf("\t\t\t\t------------------------------------------------------------------\n");
			if (Seat_Srv_Modify(&(p->data))) {
				rtn = 1;
				printf("\t\t\t\t��λ���³ɹ�\n");
			} else
				printf("\t\t\t\t��λ����ʧ��\n");
		} else
			printf("\t\t\t\t��λ������\n");
		printf("\t\t\t\t------------------------------------------------------------------\n");
		printf("\t\t\t\t[U]�������, [R]����");
		choice = toupper(getchar());
		while (getchar() != '\n')
			continue;
	} while ('u' == choice || 'U' == choice);
	return rtn;
}

/*
��ʶ����TTMS_SCU_Seat_UI_Del
�������ܣ�����ɾ��һ����λ�����ݡ�
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��
*/
int Seat_UI_Delete(seat_list_t list, int row, int column) {
	int delSeatCount = 0;
	int newrow, newcolumn;
	seat_node_t *p;
	char choice;

	do {
#ifdef WIN32
        system("cls");//����
#endif
#ifdef linux
        system("clear");//����
#endif
		printf("\n==================================================================\n");
		printf("\n***************************  ɾ����λ  ***************************\n");
		printf("------------------------------------------------------------------\n");
		do {
			fflush(stdin);
			printf("�в��ɳ� %d �в��ɳ� %d!\n",
					row, column);
			printf("��λ�кţ� ");
			scanf("%d", &(newrow));
			printf("��λ�кţ� ");
			scanf("%d", &(newcolumn));
			fflush(stdin);
		} while (newrow > row || newcolumn > column);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p) {
			printf("\n\t\t\t\t==================================================================\n");
			if (Seat_Srv_DeleteByID(p->data.id)) {
				printf("��λɾ���ɹ�\n");
				delSeatCount++;
				List_FreeNode(p);	//�ͷŽ����λ���p
			}
		} else {
			printf("��λ������\n");
		}

		printf("\t\t\t\t------------------------------------------------------------------\n");
		printf("[D]����ɾ��, [R]����");
		fflush(stdin);
		choice = toupper(getchar());
		fflush(stdin);
	} while ('d' == choice || 'D' == choice);
	return delSeatCount;
}

