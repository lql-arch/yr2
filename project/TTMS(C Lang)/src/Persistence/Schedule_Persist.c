//
// Created by bronya on 22-6-14.
//

#include "Schedule_Persist.h"
#include "../Service/Schedule.h"
#include "EntityKey_Persist.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include <string.h>
#include "../View/Schedule_UI.h"

static const char SCHEDULE_KEY_NAME[] = "Schedule"; //�ݳ��ƻ���
static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";//�ݳ��ƻ��ļ���
static const char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat"; //�ݳ��ƻ���ʱ�ļ�������


//static char SCHEDULE_KEY_NAME[24]; //�ݳ��ƻ���
//static char SCHEDULE_DATA_FILE[24];//�ݳ��ƻ��ļ���
//static char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat"; //�ݳ��ƻ���ʱ�ļ�������

void Create_File_Name(char play_id){
    strcpy(SCHEDULE_DATA_FILE,"Schedule");
    strcat(SCHEDULE_DATA_FILE,&play_id);
    strcpy(SCHEDULE_KEY_NAME,SCHEDULE_DATA_FILE);
    strcat(SCHEDULE_DATA_FILE,".dat");
}

//���ܣ�����ID�����ݳ��ƻ�
int Schedule_Perst_SelectByID(int id , schedule_t *buf){
    assert(NULL != buf);

    FILE *fp;
    if (NULL == (fp = fopen(SCHEDULE_DATA_FILE, "rb"))) {
        return 0;
    }

    schedule_t data;
    int found = 0;

    while (!feof(fp)) {
        if (fread(&data, sizeof(schedule_t), 1, fp)) {
            if (id == data.id) {
                *buf = data;
                found = 1;
                break;
            };
        }
    }
    fclose(fp);

    return found;
}


//���ܣ����ݾ�ĿID�����ݳ��ƻ�,schedule_list_t
int Schedule_Perst_SeletByPlay(int play_id,schedule_list_t list){

    schedule_node_t *newNode;
    schedule_t data;
    int recCount = 0;

    assert(NULL != list);

    List_Free(list, schedule_node_t);

    FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
    if (NULL == fp) { //�ļ�������
        return 0;
    }

    while (!feof(fp)) {
        if (fread(&data, sizeof(schedule_t), 1, fp)) {
            if(data.play_id == play_id){
                newNode = (schedule_node_t *) malloc(sizeof(schedule_node_t));
                if (!newNode) {
                    printf(
                            "Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
                    break;
                }
                newNode->date = data;
                List_AddTail(list, newNode);
                recCount++;
            }
        }
    }

    fclose(fp);
    return recCount;
}


//���ܣ��洢�ݳ��ƻ�
int Schedule_Perst_Insert(schedule_t *date){
    assert(NULL!=date);

    long key = EntKey_Perst_GetNewKeys(SCHEDULE_KEY_NAME, 1);
    if(key<=0)			//��������ʧ�ܣ�ֱ�ӷ���
        return 0;
    date->id = key;		//�����¶�����ص�UI��

    FILE *fp = fopen(SCHEDULE_DATA_FILE, "ab");
    int rtn = 0;
    if (NULL == fp) {
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }

    rtn = fwrite(date, sizeof(schedule_t), 1, fp);

    fclose(fp);
    return rtn;
}

//���ܣ������ݳ��ƻ�
int Schedule_Perst_Update(schedule_t *data,int play_id){
//    int flag = 0;
//    int new_id = data->play_id;
//    int old_id = play_id;
//
//    if(new_id != old_id) {
//        Create_File_Name((char) new_id);
//    }
//    if(Schedule_Perst_Insert(data)){
//        flag ++;
//    }else{
//        return 0;
//    }
//    if(new_id != old_id) {
//        Create_File_Name((char) old_id);
//    }
//    if(Schedule_Perst_RemByID(data->id)){
//        flag ++;
//    }else {
//        return 0;
//    }
//    return flag;

    if(rename(SCHEDULE_DATA_FILE, SCHEDULE_DATA_TEMP_FILE)<0){
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }

    FILE *fpSour, *fpTarg;
    fpSour = fopen(SCHEDULE_DATA_TEMP_FILE, "rb");
    if (NULL == fpSour ){
        printf("Cannot open file %s!\n", SCHEDULE_DATA_TEMP_FILE);
        return 0;
    }

    fpTarg = fopen(SCHEDULE_DATA_FILE, "wb");
    if ( NULL == fpTarg ) {
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }


    schedule_t buf;

    int found = 0;
    while (!feof(fpSour)) {
        if (fread(&buf, sizeof(schedule_t), 1, fpSour)) {
            if (play_id == buf.id) {
                found = 1;
                continue;
            }
            fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
        }
    }

    fclose(fpTarg);
    fclose(fpSour);

    //ɾ����ʱ�ļ�
    remove(SCHEDULE_DATA_TEMP_FILE);
    return found;
}

//���ܣ�����idȥ���ݳ��ƻ�
int Schedule_Perst_RemByID(int id){
    if(rename(SCHEDULE_DATA_FILE, SCHEDULE_DATA_TEMP_FILE)<0){
        printf("Cannot open file %s!\n", SCHEDULE_DATA_FILE);
        return 0;
    }

    FILE *fpSour, *fpTarg;
    fpSour = fopen(SCHEDULE_DATA_TEMP_FILE, "rb");
    if (NULL == fpSour ){
        printf("Cannot open file %s!\n", SCHEDULE_DATA_TEMP_FILE);
        return 0;
    }

    fpTarg = fopen(SCHEDULE_DATA_FILE ,"wb");
    if ( NULL == fpTarg ) {
        printf("Cannot open file %s!\n",SCHEDULE_DATA_FILE);
        return 0;
    }


    schedule_t buf;

    int found = 0;
    while (!feof(fpSour)) {
        if (fread(&buf, sizeof(schedule_t), 1, fpSour)) {
            if (id == buf.id) {
                found = 1;
                continue;
            }
            fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
        }
    }

    fclose(fpTarg);
    fclose(fpSour);

    //ɾ����ʱ�ļ�
    remove(SCHEDULE_DATA_TEMP_FILE);
    return found;
}

int Schedule_Persist_SetOffset(int id, Pagination_t *ptr){
    FILE *fp;
    schedule_t buf;
    int flag = 0;
    ptr->offset = 0;


    if((fp = fopen(SCHEDULE_DATA_FILE,"rb+")) == NULL){
        fprintf(stderr,"Cannot open file %s\n",SCHEDULE_DATA_FILE);
        return 0;
    }

    while(!feof(fp)){
        if(fread(&buf, sizeof(schedule_t), 1, fp)){
            ptr->offset++;
            if(buf.id == id){
                flag = 1;
                break;
            }
        }
    }

    fclose(fp);

    return 1;
}

int Schedule_Perst_SelectAll(schedule_list_t list){
    schedule_node_t *newNode;
    schedule_t data;
    int recCount = 0;

    assert(NULL != list);

    List_Free(list, schedule_node_t);

    FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
    if (NULL == fp) { //�ļ�������
        return 0;
    }

    while (!feof(fp)) {
        if (fread(&data, sizeof(schedule_t), 1, fp)) {
            newNode = (schedule_node_t *) malloc(sizeof(schedule_node_t));
            if (!newNode) {
                printf(
                        "Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
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