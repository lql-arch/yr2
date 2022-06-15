//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__SCHEDULE_PERSIST_H
#define TTMS_C_LANG__SCHEDULE_PERSIST_H

#include "../Service/Schedule.h"

//功能：根据剧目ID载入演出计划
int Schedule_Perst_SeletByPlay(int id,schedule_t *buf);

//功能：存储演出计划
int Schedule_Perst_Insert(schedule_t *p);

//功能：更新演出计划
int Schedule_Perst_Update(schedule_t *data);

//功能：根据id去除演出计划
int Schedule_Perst_RemByID(int ID);

int Schedule_Persist_SetOffset(int id, Pagination_t *ptr);

int Schedule_Perst_SelectAll(schedule_list_t list);

//功能：获取实体主键
//int EntKey_Perst_GetNewKeys();

#endif //TTMS_C_LANG__SCHEDULE_PERSIST_H
