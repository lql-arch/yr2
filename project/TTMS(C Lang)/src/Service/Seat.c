/*
* Copyright(C), 2007-2008, XUPT Univ.	
* ������ţ�TTMS_UC_02 
* File name: Seat.c		  
* Description : ������λ����ҵ���߼���	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015��4��22��	
*/

#include <stdlib.h>
#include <stdio.h>
#include "../Common/List.h"
#include "../Persistence/Seat_Persist.h"
#include "Seat.h"
#include "../Service/Creat_Ticket.h"
#include "../Service/EntKey.h"

/*
�������ܣ��������һ������λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ��ӵ���λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��������λ�ı�־��
*/
int Seat_Srv_Add(seat_t *data){
    return Seat_Perst_Insert(data);
}

/*
�������ܣ����������λ���ݡ�
����˵����listΪseat_list_t����ָ�룬��ʾ��Ҫ��ӵ�������λ�����γɵ�����
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ������������λ�ı�־��
*/
int Seat_Srv_AddBatch(seat_list_t list){
	return Seat_Perst_InsertBatch(list);
}

/*
�������ܣ������޸�һ����λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ�޸ĵ���λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��޸�����λ�ı�־��
*/
int Seat_Srv_Modify(const seat_t *data){
	return Seat_Perst_Update(data);
}

/*
�������ܣ�������λIDɾ��һ����λ��
����˵����IDΪ���ͣ���ʾ��Ҫɾ������λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��
*/
int Seat_Srv_DeleteByID(int ID)
{
	return Seat_Perst_DeleteByID(ID);
}

/*
�������ܣ�������λID��ȡ��λ���ݡ�
����˵������һ������IDΪ���ͣ���ʾ��λID���ڶ�������bufΪseat_tָ�룬ָ�����ȡ����λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ȡ����λ�ı�־��
*/
int Seat_Srv_FetchByID(int ID, seat_t *buf){
	return Seat_Perst_SelectByID(ID, buf);
}

/*
�������ܣ������ݳ���IDɾ��������λ��
����˵����roomIDΪ���ͣ���ʾ��Ҫɾ��������λ���ݳ���ID��
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ�����ݳ���������λ�ı�־��
*/
int Seat_Srv_DeleteAllByRoomID(int roomID){
	return Seat_Perst_DeleteAllByRoomID(roomID);
}

/*
�������ܣ����ݸ����ݳ������С�������ʼ���ݳ�����������λ���ݣ�����ÿ����λ��㰴�в�����λ����
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ʼ�����ݳ�����������λ��
*/
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID)
{
    //�����ݳ���ID������λ
	int SeatCount=Seat_Perst_SelectByRoomID(list, roomID);
	//����λ��������

	Seat_Srv_SortSeatList(list);
	return SeatCount;
}

/*
�������ܣ������ݳ���ID��ø��ݳ�������Ч��λ��
����˵������һ������listΪseat_list_t���ͣ���ʾ��ȡ������Ч��λ����ͷָ�룬�ڶ�������roomIDΪ���ͣ���ʾ��Ҫ��ȡ��Ч��λ���ݳ���ID��
�� �� ֵ�����ͣ���ʾ�ݳ�������Ч��λ������
*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
    //�����ݳ���ID������λ
	int SeatCount=Seat_Perst_SelectByRoomID(list, roomID);
	seat_node_t* temp;
	seat_node_t *p;
	//ȥ����Ч��λ
	List_ForEach(list, p)
	{
		if(p->data.status!=SEAT_GOOD)
		{
			temp = p;
			p = p->prev;
			List_FreeNode(temp);
			SeatCount--;
		}
	}

	//����λ��������
	Seat_Srv_SortSeatList(list);
	return SeatCount;
}

/*
�������ܣ����ݸ����ݳ������С�������ʼ���ݳ�����������λ���ݣ�����ÿ����λ��㰴�в�����λ����
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ʼ�����ݳ�����������λ��
*/
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,
		int colsCount) 
{
	int i, j;
	seat_node_t *p;
	//������ȡ����
	long seatID=EntKey_Srv_CompNewKeys("Seat", rowsCount*colsCount);

	//�Ȱ�����������Ĭ����λ���γ�����
	for (i = 1; i <= rowsCount; i++){
		for (j = 1; j <= colsCount; j++) {
			p = (seat_node_t *) malloc(sizeof(seat_node_t));
			p->data.id = seatID;
			p->data.roomID = roomID;
			p->data.row = i;
			p->data.column = j;
			p->data.status = SEAT_GOOD;
			seatID++;
			List_AddTail(list, p);
		}
	}
	return Seat_Perst_InsertBatch(list);
}
/*
�������ܣ�����λ����list����λ�кš��кŽ�������
����˵����listΪseat_list_t���ͣ���ʾ��������λ����ͷָ�롣
�� �� ֵ���ޡ�
*/
void Seat_Srv_SortSeatList(seat_list_t list) {
    seat_node_t *p, *listLeft;
	assert(list!=NULL);

	if(List_IsEmpty(list))
		return ;

	//��nextָ�빹�ɵ�ѭ����������һ�����Ͽ�
	list->prev->next = NULL;

	//listLeftָ���һ�����ݽڵ�
	listLeft = list->next;

	//��list������Ϊ��
	list->next = list->prev = list;

	while (listLeft != NULL ) {
		//ȡ����һ�����
		p = listLeft;
		listLeft = listLeft->next;

		//�����p���뵽����������list��
		Seat_Srv_AddToSoftedList(list, p);
	}
}

/*
�������ܣ���һ����λ�����뵽���������λ�����С�
����˵������һ������listΪseat_list_t���ͣ���ʾ�����������λ����ͷָ�룬�ڶ�������nodeΪseat_node_tָ�룬��ʾ��Ҫ�������λ���ݽ�㡣
�� �� ֵ���ޡ�
*/
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
    seat_node_t *p;

	assert(list!=NULL && node!=NULL);

	if(List_IsEmpty(list))	{
		List_AddTail(list, node);
	}else{
		//Ѱ�Ҳ���λ��
		p=list->next;

		while(p!=list && (p->data.row<node->data.row ||
				(p->data.row==node->data.row && p->data.column<node->data.column))){
			p=p->next;
		}

		//�����node���뵽p֮ǰ
		List_InsertBefore(p, node);
	}
}
/*
�������ܣ�������λ���С��кŻ�ȡ��λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ���ʾ��λ����ͷָ�룬
         �ڶ�������rowΪ���ͣ���ʾ����ȡ��λ���кţ�����������columnΪ���ͣ���ʾ����ȡ��λ���кš�
�� �� ֵ��Ϊseat_node_tָ�룬��ʾ��ȡ������λ���ݡ�
*/
seat_node_t* Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
    assert(NULL!=list);
	seat_node_t *p;

	List_ForEach(list,p)
		if (p->data.row == row && p->data.column == column)
			return p;
	return NULL ;
}

int Seat_Srv_FindTheByRowCol(seat_t*buf,int row, int column){
    FILE *fp;
    seat_t data;
    int recCount = 0;

    if((fp = fopen("Seat.dat","rb+")) == NULL){
        fprintf(stderr,"Error:Seat.dat ������.\n");
        return 0;
    }

    while (!feof(fp)) {
        if (fread(&data, sizeof(seat_t), 1, fp)) {
            if(data.row == row && data.column == column){
                *buf = data;
                recCount++;
                break;
            }
        }
    }
    return recCount;
}



/*
�������ܣ�������λID�������л�ȡ��λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ�ָ����λ���������ڶ�������IDΪ���ͣ���ʾ��λID��
�� �� ֵ��seat_node_t���ͣ���ʾ��ȡ����λ���ݡ�
*/
seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) 
{
    
	assert(NULL!=list);
	seat_node_t *p;

	List_ForEach(list,p)
		if (p->data.id==rowID)
			return p;
	return NULL ;
}
