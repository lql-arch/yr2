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

static const char PLAY_DATA_FILE[] = "Play.dat";//��Ŀ�ļ�������
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat"; //��Ŀ��ʱ�ļ�������
static const char PLAY_KEY_NAME[] = "Play"; //��Ŀ������


int Play_Perst_SelectAll(play_list_t  list){
    play_node_t *newNode;
    play_t data;
    int recCount = 0;

    assert(NULL != list);

    List_Free(list, play_node_t);

    FILE *fp = fopen(PLAY_DATA_FILE, "rb");
    if (NULL == fp) { //�ļ�������
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

    long key = EntKey_Perst_GetNewKeys(PLAY_KEY_NAME, 1); //Ϊ���ݳ��������ȡ
    if(key<=0)			//��������ʧ�ܣ�ֱ�ӷ���
        return 0;
    date->id = key;		//�����¶�����ص�UI��

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

int Play_perst_Update(play_t *play){
    FILE *fp;
    play_t buf;
    int flag = 0;

    if((fp = fopen(PLAY_DATA_FILE,"rb+")) == NULL){
        fprintf(stderr,"Cannot open file %s\n",PLAY_DATA_FILE);
        return 0;
    }

    while(!feof(fp)){
        if(fread(&buf, sizeof(play_t), 1, fp)){
            if(buf.id == play->id){
                fseek(fp,-(int)sizeof(play_t),SEEK_CUR);
                fwrite(play, sizeof(play_t), 1, fp);
                flag = 1;
                break;
            }
        }
    }

    fclose(fp);

    if(flag == 0) {
        char choice;
        fprintf(stderr,"Warning:file no exist.\n"
                       "Whether it needs to be added(y/n):");
        scanf("%c",&choice);
        if(choice == 'y' || choice == 'Y') {
            Play_Perst_Insert(play);
            flag = 1;
        }
        while((choice = getchar()) != '\n')
            continue;
    }

    return flag;
}

int Play_Perst_RemByID(int id){
    //��ԭʼ�ļ���������Ȼ���ȡ��������д�뵽�����ļ��У�����Ҫɾ����ʵ����˵���

    //��ԭʼ�����ļ�������
    if(rename(PLAY_DATA_FILE, PLAY_DATA_TEMP_FILE)<0){
        printf("Cannot open file %s!\n", PLAY_DATA_FILE);
        return 0;
    }

    FILE *fpSour, *fpTarg;
    fpSour = fopen(PLAY_DATA_TEMP_FILE, "rb");
    if (NULL == fpSour ){
        printf("Cannot open file %s!\n", PLAY_DATA_TEMP_FILE);
        return 0;
    }

    fpTarg = fopen(PLAY_DATA_FILE, "wb");
    if ( NULL == fpTarg ) {
        printf("Cannot open file %s!\n", PLAY_DATA_FILE);
        return 0;
    }


    play_t buf;

    int found = 0;
    while (!feof(fpSour)) {
        if (fread(&buf, sizeof(play_t), 1, fpSour)) {
            if (id == buf.id) {
                found = 1;
                continue;
            }
            fwrite(&buf, sizeof(play_t), 1, fpTarg);
        }
    }

    fclose(fpTarg);
    fclose(fpSour);

    //ɾ����ʱ�ļ�
    remove(PLAY_DATA_TEMP_FILE);
    return found;
}

int Play_Perst_SelectByID(int id,play_t *date){
    FILE *fp;
    play_t buf;
    int flag = 0;

    if((fp = fopen(PLAY_DATA_FILE,"rb+")) == NULL){
        fprintf(stderr,"Cannot open file %s\n",PLAY_DATA_FILE);
        return 0;
    }

    while(!feof(fp)){
        if(fread(&buf, sizeof(play_t), 1, fp)){
            if(buf.id == id){
                fseek(fp,-(int)sizeof(play_t),SEEK_CUR);
                fread(date, sizeof(play_t), 1, fp);
                flag = 1;
                break;
            }
        }
    }
    fclose(fp);

    return flag;
}

int Play_Perst_SetOffset(int id, Pagination_t *paging){
    FILE *fp;
    play_t buf;
    int flag = 0;
    paging->offset = 0;


    if((fp = fopen(PLAY_DATA_FILE,"rb+")) == NULL){
        fprintf(stderr,"Cannot open file %s\n",PLAY_DATA_FILE);
        return 0;
    }

    while(!feof(fp)){
        if(fread(&buf, sizeof(play_t), 1, fp)){
            paging->offset++;
            if(buf.id == id){
                flag = 1;
                break;
            }
        }
    }

    fclose(fp);

    return 1;
}