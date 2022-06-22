//
// Created by bronya on 22-6-14.
//

#include "Play_Perst.h"


static const char PLAY_DATA_FILE[] = "Play.dat";//��Ŀ�ļ�������
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat"; //��Ŀ��ʱ�ļ�������
static const char PLAY_KEY_NAME[] = "Play"; //��Ŀ������

static const int PLAY_PAGE_SIZE = 5;

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
                printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
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
//    printf("%5d   %15s   %5d   %15s   %10d    %10d   %04d-%02d-%02d   %04d-%02d-%02d   %8d\n", date->id,
//          date->name, date->type,date->area,date->rating,date->duration,
//          date->start_date.year,date->start_date.month,date->start_date.day,
//          date->end_date.year,date->start_date.month,date->start_date.day,date->price);


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
                fseek(fp,-((int)sizeof(play_t)),SEEK_CUR);
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
    int count = 0;


    if((fp = fopen(PLAY_DATA_FILE,"rb+")) == NULL){
        fprintf(stderr,"Cannot open file %s\n",PLAY_DATA_FILE);
        return 0;
    }

    while(!feof(fp)){
        if(fread(&buf, sizeof(play_t), 1, fp)){
            count++;
            if(count == PLAY_PAGE_SIZE + 1){
                count = 0;
                paging->offset++;
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

int Play_Perst_SelectByName(play_list_t list, char condt[])
{
    int recCount = 0;

    assert(NULL!=list);

    FILE *fp = fopen(PLAY_DATA_FILE, "rb");
    if (NULL == fp)
    {
        return 0;
    }

    play_t data;
    play_list_t p;
    List_Free(list, play_node_t);

    while (!feof(fp))
    {
        p = (play_list_t)malloc(sizeof(play_node_t));
        if (fread(&data, sizeof(play_t), 1, fp))
        {
            if (strstr(data.name,condt))
            {
                p->date = data;
                recCount++;
                List_AddTail(list,p);
            }
            else
            {
                free(p);
            }
        }
    }
    fclose(fp);

    return recCount;
}