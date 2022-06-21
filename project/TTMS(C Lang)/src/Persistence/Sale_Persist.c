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

	rtn = fwrite(data,sizeof(sale_t),1,fp);
	fclose(fp);
	return rtn;
}


int Ticket_Perst_Update(ticket_t *data){
	int rtn ;
	FILE *fp;

	if((fp = fopen(TICKET_DATA_FILE,"rb+")) == NULL){
		printf("Open FILE Failed %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	while(!feof(fp)){//指针  没有  指到 FILE 末尾的
		ticket_t rec;
		fread(&rec, sizeof(ticket_t), 1, fp);
		if(rec.id == data->id){
			fwrite(data,sizeof(ticket_t),1,fp);
			rtn=1;
			fclose(fp);
			return rtn;
		}
	}
	fclose(fp);
	return rtn;;
}


int Ticket_Srv_SelBySchID(int id,ticket_list_t list){
	List_Init(list, ticket_node_t);

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
			ticket_node_t newNode;
			List_AddTail(list, &newNode);
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













