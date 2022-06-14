//
// Created by bronya on 22-6-14.
//

#include "Play_Perst.h"
#include "../Service/Play.h"
#include "EntityKey_Persist.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>

static const char PLAY_DATA_FILE[] = "Play.dat";//演出计划文件名常量
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat"; //演出计划临时文件名常量
static const char PLAY_KEY_NAME[] = "Play"; //演出计划名常量


int Play_Perst_SelectAll(play_list_t  list){
    play_node_t *newNode;
    play_t data;
    int recCount = 0;

    assert(NULL != list);

    List_Free(list, play_node_t);

    FILE *fp = fopen(PLAY_DATA_FILE, "rb");
    if (NULL == fp) { //文件不存在
        return 0;
    }

    while (!feof(fp)) {
        if (fread(&data, sizeof(play_t), 1, fp)) {
            newNode = (play_node_t*) malloc(sizeof(play_node_t));
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

int Play_Perst_Insert(play_t* date){
    assert(NULL!=date);

    long key = EntKey_Perst_GetNewKeys(PLAY_KEY_NAME, 1); //为新演出厅分配获取
    if(key<=0)			//主键分配失败，直接返回
        return 0;
    date->id = key;		//赋给新对象带回到UI层

    FILE *fp = fopen(PLAY_DATA_FILE, "ab");
    int rtn = 0;
    if (NULL == fp) {
        printf("Cannot open file %s!\n", PLAY_DATA_FILE);
        return 0;
    }

    rtn = fwrite(date, sizeof(play_t), 1, fp);

    fclose(fp);
    return rtn;
}

void Play_perst_Update(){

}

void Play_Perst_RemByID(){

}

void Play_Perst_SelectBYID(){

}