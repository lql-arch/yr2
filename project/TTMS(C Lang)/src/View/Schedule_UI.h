//
// Created by bronya on 22-6-13.
//
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include "Creat_Ticket_UI.h"
#include "Schedule_Persist.h"
#include "Creat_Ticket.h"
#include "Creat_Ticket_Persist.h"
#include <stdio.h>
#include <string.h>
#include "../Service/Studio.h"
//安排演出界面
//管理剧目界面，列表显示
void Schedule_UI_MgtEntry(int argc);

//添加新演出计划界面
int Schedule_UI_Add(int play_id);

//修改演出计划界面
int  Schedule_UI_Modify(int id);

//删除演出计划界面
int Schedule_UI_Delete(int id);

//生成演出票界面
//void Ticket_UI_MgtEntry();