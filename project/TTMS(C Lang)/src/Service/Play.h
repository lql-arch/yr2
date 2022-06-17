//
// Created by bronya on 22-6-13.
//

#ifndef TTMS_C_LANG__PLAY_H
#define TTMS_C_LANG__PLAY_H

#include "List.h"

//剧目类型
typedef enum{
    PLAY_TYPE_FILE = 1,
    PLAY_TYPE_OPEAR = 2,
    PLAY_TYPE_CONCERT = 3
}play_type_t;

//剧目分级类别
typedef enum{
    PLAY_PATE_CHILD = 1,
    PLAY_PATE_TEENAGE = 2,
    PLAY_PATE_ADULT = 3,
}play_rating_t;

//日期定义
typedef struct {
    int year;
    int month;
    int day;
}ttms_date_t;

typedef struct {
    int id;                 //剧目id
    char name[31];          //剧目名称
    play_type_t type;       //剧目类型
    char area[20];           //剧目出品地区
    play_rating_t rating;   //剧目等级
    int duration;           //时长，以分钟为单位
    ttms_date_t start_date; //开始放映日期
    ttms_date_t end_date;   //放映结束日期
    int price;              //票价
}play_t;

typedef struct play_node{
    play_t date;            //实体数据
    struct play_node *next; //向后指针
    struct play_node *prev; //前驱指针
}play_node_t,*play_list_t;

//获取全部剧目服务
int Play_Srv_FetchAll(play_list_t list);

//添加新剧目服务
int Play_Srv_Add(play_t *date);

//修改剧目服务
int Play_Srv_Modify(play_t *t);

//根据id删除剧目服务
int Play_Srv_Deleteify(int id);

//根据id获取剧目服务
int Play_Srv_FetchByID(int id,play_t *date);

//修改偏移量
int Play_SetOffset(int id,Pagination_t *paging);

#endif //TTMS_C_LANG__PLAY_H
