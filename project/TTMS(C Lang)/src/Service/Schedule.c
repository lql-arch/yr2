//
// Created by bronya on 22-6-14.
//
#include "Schedule.h"
#include "../Persistence/Schedule_Persist.h"
#include "List.h"

//根据剧目id获取演出计划
int Schedule_Srv_FetchByPlay(int play_id,schedule_list_t buf){
    return Schedule_Perst_SeletByPlay(play_id, buf);
}

//添加新演出计划服务
int Schedule_Srv_Add(schedule_t *p){
    return Schedule_Perst_Insert(p);
}

//修改演出计划服务
int Schedule_Srv_Modify(schedule_t *data) {
    return Schedule_Perst_Update(data);
}

//根据id删除演出计划服务
int Schedule_srv_DeleteByID(int id){
    return Schedule_Perst_RemByID(id);
}

int Schedule_SetOffset(int id, Pagination_t *ptr) {
    return Schedule_Persist_SetOffset(id,ptr);
}

int Schedule_Srv_FetchAll(schedule_list_t list){
    return Schedule_Perst_SelectAll(list);
}