/*
* Copyright(C), 2007-2008, XUPT Univ.
* ������ţ�TTMS_UC_02	 
* File name: Seat.h	  
* Description : ������λ�����־û���	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015��4��22��	
*/

#include "Seat_Persist.h"
#include "../Service/Seat.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#if linux
    #include <sys/io.h>
#include <unistd.h>

#endif
#if WIN32
    #include<io.h>
#endif

static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";
static const char SEAT_DATA_FILE[] = "Seat.dat";

//��Ӷ���������ʶ����
static const char SEAT_KEY_NAME[] = "Seat";

/*
�������ܣ��������ļ������һ������λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ��ӵ���λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��������λ�ı�־��
*/ 
int Seat_Perst_Insert(seat_t *data) {   
	assert(NULL!=data);
	FILE *fp = fopen(SEAT_DATA_FILE, "ab");
	int rtn = 0;

	if (NULL == fp)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(seat_t), 1, fp);

	fclose(fp);
	return rtn;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_InsertBatch
�������ܣ��������ļ������һ����λ���ݡ�
����˵����listΪseat_list_t���ͣ���ʾ��Ҫ��ӵ�һ����λ������ͷָ�롣
�� �� ֵ�����ͣ���ʾ�ɹ����һ����λ�ĸ�����
*/
int Seat_Perst_InsertBatch(seat_list_t list) {
	seat_node_t *p;
	assert(NULL!=list);
	FILE *fp = fopen(SEAT_DATA_FILE, "rb+");
	int rtn = 0;

	if (NULL == fp)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	List_ForEach(list,p)
	{
		fwrite(&(p->data), sizeof(seat_t), 1, fp);
		rtn++;
	}

	fclose(fp);
	return rtn;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_Update
�������ܣ��������ļ��и���һ����λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ���µ���λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��
*/
int Seat_Perst_Update(const seat_t *seatdata) {
	assert(NULL!=seatdata);
	FILE *fp = fopen(SEAT_DATA_FILE, "rb+");
	if (NULL == fp)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}
	seat_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(seat_t), 1, fp))
		{
			if (buf.id == seatdata->id)
			{
				fseek(fp, -((long)sizeof(seat_t)), SEEK_CUR);
				fwrite(seatdata, sizeof(seat_t), 1, fp);
				found = 1;
				break;
			}
		}
	}
	fclose(fp);
	return found;
}

/*
ʶ����TTMS_SCU_Seat_Perst_DelByID
�������ܣ����ڴ��ļ���ɾ��һ����λ�����ݡ�
����˵��������IDΪ���ͣ���ʾ��Ҫɾ������λID�� 
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��
*/
int Seat_Perst_DeleteByID(int ID) {
	FILE *fpSour, *fpTarg;

	if (rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE) < 0)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb");
	fpTarg = fopen(SEAT_DATA_FILE, "wb");

	if (NULL == fpTarg)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}
	if (NULL == fpSour)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_TEMP_FILE);
		return 0;
	}

	seat_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(seat_t), 1, fpSour))
		{
			if (ID == buf.id)
			{
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(seat_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//ɾ����ʱ�ļ�
	remove(SEAT_DATA_TEMP_FILE);

	return found;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_DelAllByID
�������ܣ����ݱ�����ڴ��ļ���ɾ����λ���ݡ�
����˵��������roomIDΪ���ͣ���ʾ�ݳ���ID�� 
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��
*/ 
int Seat_Perst_DeleteAllByRoomID(int roomID) {

	int found = 0;
	FILE *fpSour, *fpTarg;

	seat_t buf;
	fpSour = fopen(SEAT_DATA_FILE, "rb");
	fpTarg = fopen(SEAT_DATA_TEMP_FILE, "wb");

	if (NULL == fpTarg)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}
	if (NULL == fpSour)
	{
		fclose(fpTarg);
		printf("�޷����ļ� %s!\n", SEAT_DATA_TEMP_FILE);
		return 0;
	}
	while (!feof(fpSour))
	{
		if (fread(&buf, sizeof(seat_t), 1, fpSour))
		{
			if (roomID == buf.roomID)
			{
				found += 1;
				continue;
			}
			fwrite(&buf, sizeof(seat_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);
	//ɾ����ʱ�ļ�
	remove(SEAT_DATA_FILE);
	rename(SEAT_DATA_TEMP_FILE, SEAT_DATA_FILE);
	return found;
}
/*
��ʶ����TTMS_SCU_Studio_Perst_SelByID
�������ܣ����ڴ��ļ�������һ����λ�����ݡ�
����˵������һ������IDΪ���ͣ���ʾ��Ҫ�������ݵ���λID���ڶ�������bufΪseat_tָ�룬ָ��������λ���ݵ�ָ�롣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��
*/
int Seat_Perst_SelectByID(int ID, seat_t *buf) {
	assert(NULL!=buf);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	seat_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(seat_t), 1, fp))
		{
			if (ID == data.id)
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
/*
��ʶ����TTMS_SCU_Seat_Perst_SelAll
�������ܣ����ڴ��ļ�������������λ���ݡ�
����˵����listΪseat_list_t���ͣ���ʾ��Ҫ�������λ����ͷָ�롣
�� �� ֵ�����ͣ��ɹ�������λ�ĸ�����
*/
int Seat_Perst_SelectAll(seat_list_t list) {
	seat_node_t *newNode;
	seat_t data;
	int recCount = 0;

	assert(NULL!=list);

	if (access(SEAT_DATA_FILE, 0))
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	List_Free(list, seat_node_t);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	while (!feof(fp))
	{
		if (fread(&data, sizeof(seat_t), 1, fp))
		{
			newNode = (seat_node_t*) malloc(sizeof(seat_node_t));
			if (!newNode)
			{
				printf("�ڴ����!\n");
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
/*
��ʶ����TTMS_SCU_Seat_Perst_SelByRoomID
�������ܣ��������ļ��и����ݳ���ID����������λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ���ʾ��Ҫ�������λ����ͷָ�룬�ڶ�������roomIDΪ���ͣ���ʾ�ݳ���ID��
�� �� ֵ�����ͣ���ʾ�ɹ��������ݳ�����λ�ĸ�����
*/
int Seat_Perst_SelectByRoomID(seat_list_t* list, int roomID)
{
    List_Init(*list,seat_node_t);
	seat_t data;
	int recCount = 0;

	FILE *fp = fopen(SEAT_DATA_FILE, "rb+");
	if (NULL == fp)
	{
		printf("�޷����ļ� %s!\n", SEAT_DATA_FILE);
		return 0;
	}

    List_Free(*list,seat_node_t);

	while (!feof(fp))
	{
		if (fread(&data, sizeof(seat_t), 1, fp))
		{ 
			if (data.roomID == roomID)  //����λ�Ǳ���ӳ������λ�������
			{
                seat_node_t *newNode = (seat_node_t*) malloc(sizeof(seat_node_t));
				newNode->data = data;
				List_AddTail(*list, newNode);
				recCount++;
			}
		} 
	}
	fclose(fp);

    return recCount;
}
