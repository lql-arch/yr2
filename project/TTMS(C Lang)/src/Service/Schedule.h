//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__SCHEDULE_H
#define TTMS_C_LANG__SCHEDULE_H

typedef struct {
    int  hour;
    int minute;
    int second;
}ttms_time_t;

typedef struct {
    int id;             // �ݳ��ƻ�id
    int play_id;        //��ӳ��Ŀid
    int studio_id;      //�ݳ���id
    ttms_time_t date;   //��ӳ����
    ttms_time_t time;   //��ӳʱ��
    int seat_count;     //��λ��
}schedule_t;

typedef struct schedule_node {
    schedule_t date;
    struct schedule_node *next;
    struct schedule_node *prev;
}schedule_node_t, *schedule_list_t;


//���ݾ�Ŀid��ȡ�ݳ��ƻ�
int Schedule_Srv_FetchByPlay();

//������ݳ��ƻ�����
int Schedule_Srv_Add();

//�޸��ݳ��ƻ�����
int Schedule_Srv_Modify();

//����idɾ���ݳ��ƻ�����
int Schedule_srv_DeleteByID();



#endif //TTMS_C_LANG__SCHEDULE_PERSIST_H
