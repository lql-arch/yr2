#pragma once

#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"
#include "../Common/List.h"
#include  <stdio.h> 

#define SALESANALYSIS_PAGE_SIZE 5

void SalesAnalysis_UI_MgtEntry();


void SalesAnalysis_UI_ShowList(salesanalysis_list_t list, Pagination_t paging);
