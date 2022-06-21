#include "SaleAnalysis_Persist.h"
#include "../Service/Sale.h"
#include "../Common/List.h"
#include "../Persistence/EntityKey_Persist.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include <string.h>

static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";
static const char SALE_KEY_NAME[]="Sale";

int Sale_Perst_Insert( sale_t *data)
{
	 assert(NULL!=data);

                
	long key = EntKey_Perst_GetNewKeys(SALE_KEY_NAME, 1);
	if(key<=0)			
		return 0;
	data->id = key;	



	FILE *fp = fopen(SALE_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SALE_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(sale_t), 1, fp);

	fclose(fp);
	return rtn;
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

int Sale_Perst_SelectAll(sale_list_t list)
{
	sale_node_t *newNode;
	sale_t data;
	int recCount = 0;

	assert(NULL!=list);

    List_Free(list,sale_node_t);

	FILE *fp = fopen(SALE_DATA_FILE, "rb");
	if (NULL == fp) { 
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(sale_t), 1, fp)) {
			newNode = (sale_t*) malloc(sizeof(sale_node_t));
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


int Sale_Perst_SelectByName(sale_list_t list, char condt[]) 
{
	assert(NULL!=list);

	FILE *fp = fopen(SALE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	sale_t data;
	int found = 0;
	sale_list_t p;
	while (!feof(fp)) 
	{
		p = (sale_list_t)malloc(sizeof(sale_node_t));
		if (fread(&data, sizeof(sale_t), 1, fp)) {
			if (strstr(data.name,condt))
			 {
				p->data = data;
				found++;
				List_AddTail(list,p);
			}
			else
			{
				free(p);
			}
			

		}
	}
	fclose(fp);

	return found;
}


