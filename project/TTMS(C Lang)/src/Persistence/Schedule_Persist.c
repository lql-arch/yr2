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

static const char SCHEDULE_KEY_NAME[] = "Schedule"; //演出计划名
static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";//演出计划文件名
static const char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat"; //演出计划临时文件名常量

static const int SCHEDULE_PAGE_SIZE = 5;

//static char SCHEDULE_KEY_NAME[24]; //演出计划名
//static char SCHEDULE_DATA_FILE[24];//演出计划文件名
//static char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat"; //演出计划临时文件名常量
//void Create_File_Name(char play_id){
//    strcpy(SCHEDULE_DATA_FILE,"Schedule");
//    strcat(SCHEDULE_DATA_FILE,&play_id);
//    strcpy(SCHEDULE_KEY_NAME,SCHEDULE_DATA_FILE);
//    strcat(SCHEDULE_DATA_FILE,".dat");
//}

//功能：根据ID载入演出计划
int Schedule_Perst_SelectByID(int id , schedule_t *buf){
    assert(NULL != buf);

    FILE *fp;
    if (NULL == (fp = fopen(SCHEDULE_DATA_FILE, "rb"))) {
        fprintf(stderr,"Error:file %s does not exist.\n",SCHEDULE_DATA_FILE);
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


//功能：根据剧目ID载入演出计划,schedule_list_t
int Schedule_Perst_SeletByPlay(int play_id,schedule_list_t list){

    schedule_node_t *newNode;
    schedule_t data;
    int recCount = 0;

    assert(NULL != list);

    List_Free(list, schedule_node_t);

    FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
    if (NULL == fp) { //文件不存在
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


//功能：存储演出计划
int Schedule_Perst_Insert(schedule_t *date){
    assert(NULL!=date);

    long key = EntKey_Perst_GetNewKeys(SCHEDULE_KEY_NAME, 1);
    if(key<=0)			//主键分配失败，直接返回
        return 0;
    date->id = key;		//赋给新对象带回到UI层

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

//功能：更新演出计划
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

    //删除临时文件
    remove(SCHEDULE_DATA_TEMP_FILE);
    return found;
}

//功能：根据id去除演出计划
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

    //删除临时文件
    remove(SCHEDULE_DATA_TEMP_FILE);
    return found;
}

int Schedule_Persist_SetOffset(int id, Pagination_t *ptr){
    FILE *fp;
    schedule_t buf;
    int flag = 0;
    ptr->offset = 0;
    int count= 0;


    if((fp = fopen(SCHEDULE_DATA_FILE,"rb+")) == NULL){
        fprintf(stderr,"Cannot open file %s\n",SCHEDULE_DATA_FILE);
        return 0;
    }

    while(!feof(fp)){
        if(fread(&buf, sizeof(schedule_t), 1, fp)){
            count++;
            if(count == SCHEDULE_PAGE_SIZE + 1){
                count = 0;
                ptr->offset++;
            }
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
    if (NULL == fp) { //文件不存在
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