//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__SCHEDULE_H
#define TTMS_C_LANG__SCHEDULE_H

#include "List.h"

typedef struct {
    int  hour;
    int minute;
    int second;
}ttms_time_t;

typedef struct {
    int id;             // 演出计划id
    int play_id;        //上映剧目id
    int studio_id;      //演出厅id
    ttms_time_t date;   //放映日期
    ttms_time_t time;   //放映时间
    int seat_count;     //座位数
}schedule_t;

typedef struct schedule_node {
    schedule_t date;
    struct schedule_node *next;
    struct schedule_node *prev;
}schedule_node_t, *schedule_list_t;


//根据剧目id获取演出计划
int Schedule_Srv_FetchByPlay(int id,schedule_t *buf);

//添加新演出计划服务
int Schedule_Srv_Add(schedule_t *p);

//修改演出计划服务
int Schedule_Srv_Modify(schedule_t *data);

//根据id删除演出计划服务
int Schedule_srv_DeleteByID(int id);

int Schedule_SetOffset(int id, Pagination_t *ptr);

int Schedule_Srv_FetchAll(schedule_list_t head);

#endif //TTMS_C_LANG__SCHEDULE_PERSIST_H
