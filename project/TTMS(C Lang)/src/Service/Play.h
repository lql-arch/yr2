//
// Created by bronya on 22-6-13.
//

#ifndef TTMS_C_LANG__PLAY_H
#define TTMS_C_LANG__PLAY_H

//��Ŀ����
typedef enum{
    PLAY_TYPE_FILE = 1,
    PLAY_TYPE_OPEAR = 2,
    PLAY_TYPE_CONCERT = 3
}play_type_t;

//��Ŀ�ּ����
typedef enum{
    PLAY_PATE_CHILD = 1,
    PLAY_PATE_TEENAGE = 2,
    PLAY_PATE_ADULT = 3,
}play_rating_t;

//���ڶ���
typedef struct {
    int year;
    int month;
    int day;
}ttms_date_t;

typedef struct {
    int id;                 //��Ŀid
    char name[31];          //��Ŀ����
    play_type_t type;       //��Ŀ����
    char area[9];           //��Ŀ��Ʒ����
    play_rating_t rating;   //��Ŀ�ȼ�
    int duration;           //ʱ�����Է���Ϊ��λ
    ttms_date_t start_date; //��ʼ��ӳ����
    ttms_date_t end_date;   //��ӳ��������
    int price;              //Ʊ��
}play_t;

typedef struct play_node{
    play_t date;            //ʵ������
    struct play_node *next; //���ָ��
    struct play_node *prev; //ǰ��ָ��
}play_node_t,*play_list_t;

//��ȡȫ����Ŀ����
int Play_Srv_FetchAll();

//�����¾�Ŀ����
int Play_Srv_Add(play_t *date);

//�޸ľ�Ŀ����
void Play_Srv_Modify();

//����idɾ����Ŀ����
void Play_Srv_Deleteify();

//����id��ȡ��Ŀ����
void Play_Srv_FetchBYID();

#endif //TTMS_C_LANG__PLAY_H