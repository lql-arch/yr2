#include"Sale_Persist.h"
#include"Creat_Ticket_Persist.h"
#include "../Service/Sale.h"
#include "Studio_Persist.h"
#include "../Service/Studio.h"
#include "EntityKey_Persist.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

static const char SALE_DATA_FILE[] = "Sale.dat"; //文件名常量
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat"; //临时文件名常量
static const char TICKET_DATA_FILE[] = "Ticket.dat";
static const char SALE_DATA_NAME[] = "sale";

int Sale_Perst_Insert(sale_t *data){
	assert(NULL!=data);

    data->id = EntKey_Perst_GetNewKeys(SALE_DATA_NAME , 1);

	FILE *fp=fopen(SALE_DATA_FILE,"ab");
	int rtn;

	if (NULL==fp)
	{
		printf("Open FILE Failed %s!\n", SALE_DATA_FILE);
		return 0;
	}

	rtn = (int)fwrite(data,sizeof(sale_t),1,fp);
	fclose(fp);
	return rtn;
}


int Ticket_Perst_Update(ticket_t *data){
	int rtn ;
	FILE *fp;
    ticket_t rec;

	if((fp = fopen(TICKET_DATA_FILE,"rb+")) == NULL){
		printf("Open FILE Failed %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	while(!feof(fp)){//指针  没有  指到 FILE 末尾的
		fread(&rec, sizeof(ticket_t), 1, fp);
		if(rec.id == data->id){
            fseek(fp,-(int)sizeof(ticket_t),SEEK_CUR);
			fwrite(data,sizeof(ticket_t),1,fp);
			rtn=1;
			break;
		}
	}

	fclose(fp);
	return rtn;;
}


int Ticket_Srv_SelBySchID(int id,ticket_list_t list){
	//List_Init_pd(list, ticket_node_t);

	int count = 0;
	FILE *fp;
	if((fp = fopen(TICKET_DATA_FILE,"rb+") ) == NULL){
		printf("Open FILE Failed %s!\n", TICKET_DATA_FILE);
		return 0;
	}

    List_Free(list,ticket_node_t);

	while(!feof(fp)){//指针  没有  指到 FILE 末尾的
		ticket_t data;
		fread(&data, sizeof(ticket_t), 1, fp);
		if(data.schedule_id == id){
			ticket_node_t *newNode = (ticket_list_t)malloc(sizeof(ticket_node_t));
            newNode->data = data;
			List_AddTail(list, newNode);
			count++;
		}
	}
	fclose(fp);
	return count;
}

int Sale_Perst_SelectByTicketID(int ticket_id, sale_t* sale)
{
    int found = 0;
    FILE* fp;
    sale_t temp;
    if (access(SALE_DATA_FILE, 0x00))
    {
        printf("无法打开文件%s！", SALE_DATA_FILE);
        return 0;
    }
    if ((fp = fopen(SALE_DATA_FILE, "rb")) == NULL)
    {
        printf("无法打开文件%s！", SALE_DATA_FILE);
        return 0;
    }
    while (!feof(fp))
    {
        fread(&temp, sizeof(sale_t), 1, fp);
        if (temp.ticket_id == ticket_id)
        {
            found = 1;
            *sale = temp;
        }
    }
    fclose(fp);
    return found;
}

int Sale_Perst_SelectAll(sale_list_t list) {

    sale_node_t *newNode;
    sale_t data;
    int recCount = 0;

    assert(NULL!=list);

    List_Free(list, sale_node_t);

    FILE *fp = fopen("Account.dat", "rb");
    if (NULL == fp) {
        return 0;
    }

    while (!feof(fp)) {
        if (fread(&data, sizeof(sale_t), 1, fp)) {
            newNode = (sale_node_t*) malloc(sizeof(sale_node_t));
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

int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale)
{
    assert(NULL != sale);

    FILE *fp = fopen(SALE_DATA_FILE, "rb");
    if (NULL == fp) {
        return 0;
    }

    sale_t data;
    int found = 0;

    while (!feof(fp)) {
        if (fread(&data, sizeof(sale_t), 1, fp)) {
            if (ticket_id == data.ticket_id) {
                *sale =  data;
                found = 1;
                break;
            };

        }
    }
    fclose(fp);

    return found;
}

int Sale_Perst_SelectByID(int ticket_ID, sale_t *buf)
{
    assert(NULL != buf);

    FILE *fp = fopen(SALE_DATA_FILE, "rb");
    if (NULL == fp) {
        return 0;
    }

    sale_t data;
    int found = 0;

    while (!feof(fp)) {
        if (fread(&data, sizeof(sale_t), 1, fp)) {
            if (ticket_ID == data.id) {
                *buf = data;
                found = 1;
                break;
            }

        }
    }
    fclose(fp);

    return found;
}

int Sale_Perst_Update( sale_t *data)
{
    assert(NULL!=data);

    FILE *fp = fopen(SALE_DATA_FILE, "rb+");
    if (NULL == fp) {
        printf("Cannot open file %s!\n", SALE_DATA_FILE);
        return 0;
    }

    sale_t buf;
    int found = 0;

    while (!feof(fp)) {
        if (fread(&buf, sizeof(sale_t), 1, fp)) {
            if (buf.id == data->id) {
                fseek(fp, -((int)sizeof(sale_t)), SEEK_CUR);
                fwrite(data, sizeof(sale_t), 1, fp);
                found = 1;
                break;
            }

        }
    }
    fclose(fp);

    return found;
}

int Sale_Perst_RemByID(int ID)
{
    if(rename(SALE_DATA_FILE, SALE_DATA_TEMP_FILE)<0){
        printf("Cannot open file %s!\n", SALE_DATA_FILE);
        return 0;
    }

    FILE *fpSour, *fpTarg;
    fpSour = fopen(SALE_DATA_TEMP_FILE, "rb");
    if (NULL == fpSour ){
        printf("Cannot open file %s!\n", SALE_DATA_FILE);
        return 0;
    }

    fpTarg = fopen(SALE_DATA_FILE, "wb");
    if ( NULL == fpTarg ) {
        printf("Cannot open file %s!\n", SALE_DATA_TEMP_FILE);
        return 0;
    }

    sale_t buf;

    int found = 0;
    while (!feof(fpSour)) {
        if (fread(&buf, sizeof(sale_t), 1, fpSour)) {
            if (ID == buf.id) {
                found = 1;
                continue;
            }
            fwrite(&buf, sizeof(sale_t), 1, fpTarg);
        }
    }

    fclose(fpTarg);
    fclose(fpSour);


    remove(SALE_DATA_TEMP_FILE);
    return found;
}

int Sale_Perst_SelByID (sale_list_t list, int usrID){
    sale_node_t *newNode;
    sale_t data;
    int recCount = 0;

    assert(NULL!=list);

    FILE *fp = fopen("Sale.dat", "rb+");
    if (NULL == fp) {
        return 0;
    }

    while (!feof(fp)) {
        if (fread(&data, sizeof(sale_t), 1, fp)) {
            newNode = (sale_node_t*) malloc(sizeof(sale_node_t));
            if (!newNode) {
                printf(
                        "Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
                break;
            }
            if(data.user_id==usrID)
            {
                newNode->data = data;
                List_AddTail(list, newNode);
                recCount++;
            }
        }
    }
    fclose(fp);
    return recCount;

}

int Sale_Perst_SelByUsrID(sale_list_t saleList, int usrID){
    FILE* fp;
    List_Init(saleList,sale_node_t);
    sale_t data;
    sale_node_t *buf;
    int flag = 0;

    if((fp = fopen(SALE_DATA_FILE,"rb+")) == NULL){
        fprintf(stderr,"Error:%s does nit exist.\n",SALE_DATA_FILE);
        return 0;
    }

    while(!feof(fp)){
        if(fread(&data,sizeof(sale_t),1,fp)){
            if(usrID == data.user_id){
                flag = 1;
                buf = (sale_list_t)malloc(sizeof(sale_node_t));
                buf->data = data;
                List_AddTail(saleList,buf);
            }
        }
    }

    fclose(fp);

    return flag;

}



//
//int Sale_Perst_SelectByName(sale_list_t list, char condt[])
//{
//    assert(NULL!=list);
//
//    FILE *fp = fopen(SALE_DATA_FILE, "rb");
//    if (NULL == fp) {
//        return 0;
//    }
//
//    sale_t data;
//    int found = 0;
//    sale_list_t p;
//    while (!feof(fp))
//    {
//        p = (sale_list_t)malloc(sizeof(sale_node_t));
//        if (fread(&data, sizeof(sale_t), 1, fp)) {
//            if (strstr(data.name,condt))
//            {
//                p->data = data;
//                found++;
//                List_AddTail(list,p);
//            }
//            else
//            {
//                free(p);
//            }
//
//
//        }
//    }
//    fclose(fp);
//
//    return found;
//}





