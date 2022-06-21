//
// Created by bronya on 22-6-20.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Account_Persist.h"
#include "../Persistence/EntityKey_Persist.h"
#include "../Common/List.h"

static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";
static const char ACCOUNT_KEY_NAME[] = "Account";

int Account_perst_CheckAccFile(){
    FILE* fp;

    if((fp = fopen(ACCOUNT_DATA_FILE,"rb")) == NULL){
        return 0;
    }else{
        fclose(fp);
        return 1;
    }
}


int Account_Perst_Insert(account_t *data){
    FILE* fp;
    int rtn = 0;

    if((fp = fopen(ACCOUNT_DATA_FILE,"ab+")) == NULL){
        fprintf(stderr,"����δ�ܳɹ����ļ�%s",ACCOUNT_DATA_FILE);
        return 0;
    }

    long key = EntKey_Perst_GetNewKeys(ACCOUNT_KEY_NAME, 1); //Ϊ���ݳ��������ȡ
    if(key<=0)			//��������ʧ�ܣ�ֱ�ӷ���
        return 0;
    data->id = key;		//�����¶�����ص�UI��

    rtn = fwrite(data, sizeof(account_t), 1, fp);

    fclose(fp);
    return rtn;
}


int Account_Perst_Update(account_t *data){
    FILE *fp;
    account_t buf;
    int flag = 0;

    if((fp = fopen(ACCOUNT_DATA_FILE,"rb+")) == NULL){
        fprintf(stderr,"����δ�ܳɹ����ļ�%s\n",ACCOUNT_DATA_FILE);
        return 0;
    }

    while(!feof(fp)){
        if(fread(&buf, sizeof(account_t), 1, fp)){
            if(buf.id == data->id){
                fseek(fp,-(int)sizeof(account_t),SEEK_CUR);
                fwrite(data, sizeof(account_t), 1, fp);
                flag = 1;
                break;
            }
        }
    }

    fclose(fp);

//    if(flag == 0) {
//        char choice;
//        fprintf(stderr,"Warning:file no exist.\n"
//                       "Whether it needs to be added(y/n):");
//        scanf("%c",&choice);
//        if(choice == 'y' || choice == 'Y') {
//            Account_Perst_Insert(data);
//            flag = 1;
//        }
//        while((choice = getchar()) != '\n')
//            continue;
//    }

    return flag;
}


int Account_Perst_RemByID(int id){
    if(rename(ACCOUNT_DATA_FILE, ACCOUNT_DATA_TEMP_FILE)<0){
        printf("����δ�ܳɹ����ļ�%s!\n", ACCOUNT_DATA_FILE);
        return 0;
    }

    FILE *fpSour, *fpTarg;
    fpSour = fopen(ACCOUNT_DATA_TEMP_FILE, "rb");
    if (NULL == fpSour ){
        printf("����δ�ܳɹ����ļ�%s!\n", ACCOUNT_DATA_TEMP_FILE);
        return 0;
    }

    fpTarg = fopen(ACCOUNT_DATA_FILE, "wb");
    if ( NULL == fpTarg ) {
        printf("����δ�ܳɹ����ļ�%s!\n", ACCOUNT_DATA_FILE);
        return 0;
    }


    account_t buf;

    int found = 0;
    while (!feof(fpSour)) {
        if (fread(&buf, sizeof(account_t), 1, fpSour)) {
            if (id == buf.id) {
                found = 1;
                continue;
            }
            fwrite(&buf, sizeof(account_t), 1, fpTarg);
        }
    }

    fclose(fpTarg);
    fclose(fpSour);

    //ɾ����ʱ�ļ�
    remove(ACCOUNT_DATA_TEMP_FILE);
    return found;
}


int Account_Perst_SelectAll(account_list_t list){
    account_node_t *newNode;
    account_t data;
    int recCount = 0;

    assert(NULL != list);

    List_Free(list, account_node_t);

    FILE *fp = fopen(ACCOUNT_DATA_FILE, "rb");
    if (NULL == fp) { //�ļ�������
        return 0;
    }

    while (!feof(fp)) {
        if (fread(&data, sizeof(account_t), 1, fp)) {
            newNode = (account_node_t *) malloc(sizeof(account_node_t));
            if (!newNode) {
                printf(
                        "Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
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

int Account_Perst_Verify(char usrName[],char pwd[]){
    FILE* fp;
    account_t data;

    if((fp = fopen(ACCOUNT_DATA_FILE,"rb")) == NULL){
        fprintf(stderr,"����δ�ܳɹ����ļ�%s!\n", ACCOUNT_DATA_TEMP_FILE);
        return 0;
    }

    while (!feof(fp)) {
        if (fread(&data, sizeof(account_t), 1, fp)) {
            if(strcmp(data.password,pwd) == 0 && strcmp(data.username,usrName) == 0){
                return 1;
            }
        }
    }

    return 0;
}
