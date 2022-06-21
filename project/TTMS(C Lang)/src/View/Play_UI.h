//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__PLAY_UI_H
#define TTMS_C_LANG__PLAY_UI_H

#include "List.h"
#include "Play.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "Schedule_UI.h"
#include <stdio.h>

//管理剧目界面
void Play_UI_MgtEntry(int argc);

//添加新剧目界面
int Play_UI_Add();

//修改剧目界面
int Play_UI_Modify(int id);

//删除剧目界面
int Play_UI_Delete(int id);

//查询剧目界面
int Play_UI_Query(int id,Pagination_t *paging);

//判断开始和结束时间是否正常
int isTime(play_t t);

void Play_UI_ShowList(play_list_t list,Pagination_t paging);//界面函数

#endif //TTMS_C_LANG__PLAY_UI_H