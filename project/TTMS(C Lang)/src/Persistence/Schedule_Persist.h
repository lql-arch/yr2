//
// Created by bronya on 22-6-14.
//

#ifndef TTMS_C_LANG__SCHEDULE_PERSIST_H
#define TTMS_C_LANG__SCHEDULE_PERSIST_H

#include "../Service/Schedule.h"

//���ܣ����ݾ�ĿID�����ݳ��ƻ�
int Schedule_Perst_SeletByPlay();

//���ܣ��洢�ݳ��ƻ�
int Schedule_Perst_Insert();

//���ܣ������ݳ��ƻ�
int Schedule_Perst_Update();

//���ܣ�����idȥ���ݳ��ƻ�
int Schedule_Perst_RemByID(int ID);

//���ܣ���ȡʵ������
//int EntKey_Perst_GetNewKeys();

#endif //TTMS_C_LANG__SCHEDULE_PERSIST_H
