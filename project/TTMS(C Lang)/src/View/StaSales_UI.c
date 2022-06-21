#include "StaSales_UI.h"

#include "../Common/List.h"
#include "../Service/Sale.h"
#include "../Service/Account.h"
#include "../Service/StaSales.h"
#include <stdio.h>
#include <time.h>

extern account_t gl_CurUser;

void StaSales_UI_MgtEntry ()
{

    if(gl_CurUser.type==USR_CLERK)//��ƱԱ
    {
        StaSales_UI_Self();//ͳ�Ƹ������۶�
    }
    else if(gl_CurUser.type==USR_MANG ||gl_CurUser.type== 0  )//����
    {
        StaSales_UI_Clerk();//ͳ����ƱԱ���۶�
    }
    else
    {
        printf("�˺�û��Ȩ�ޣ�");
        printf("��{ENTER}�����ϲ�!\n");
        getchar();
        
    }
    system("clear");
    return ;
}


void StaSales_UI_Self(){
    int id;
    id=gl_CurUser.id;//����Աid

    user_date_t curdate;//��ǰ����
    user_date_t startdate;//���µ�һ��
    user_date_t enddate;//�������һ��

    struct tm *local;
    time_t t;
    t=time(&t);
    local=localtime(&t); //��ǰ����
    
    curdate.year=local->tm_year+1900;
    curdate.month=local->tm_mon+1;
    curdate.day=local->tm_mday;

    startdate.year=local->tm_year+1900;
    startdate.month=local->tm_mon+1;
    startdate.day=1;

    startdate.year=local->tm_year+1900;
    startdate.month=local->tm_mon+1;
    startdate.day=31;

    int choice;
    do
    {
        system("clear");
    printf("=======================================\n");
    printf("[D]�������۶� | [M]�������۶� | [0]����\n");
    printf("---------------------------------------\n");

    printf("��ѡ�������ѯ��ѡ�");
    setbuf(stdin,NULL);
    scanf("%d",&choice);
    setbuf(stdin,NULL);
    system("clear");

    int count;
    switch(choice)
    {
        case 'd':
		case 'D': 
            system("clear");
            count=StaSales_Srv_CompSaleVal(id,curdate,curdate);
            printf("===========================================\n");
            printf("%5s  %5s  %5s","ID","����","����\n");
            printf("%5d  %5d  %5s\n",gl_CurUser.id,gl_CurUser.type,gl_CurUser.username);
            printf("�����ܶ�Ϊ��%5d\n",count);
            printf("******************************************\n");
            break;
        case 'm':
        case 'M':
            system("clear");
            count=StaSales_Srv_CompSaleVal(id,startdate,enddate);
            printf("===========================================\n");
            printf("%5s  %5s  %5s","ID","����","����\n");
            printf("%5d  %5d  %5s\n",gl_CurUser.id,gl_CurUser.type,gl_CurUser.username);
            printf("�����ܶ�Ϊ��%5d\n",count);
            printf("******************************************\n");
            break;
    }
    }while(choice != 0);
}


void StaSales_UI_Clerk()
{
    int id;
    char username[100];
    user_date_t startdate;
    user_date_t enddate;
    system("clear");
    printf("��������ƱԱ������");
    setbuf(stdin,NULL);
    scanf("%s",username);
    setbuf(stdin,NULL);
    system("clear");

    account_t user;//�洢�û���Ϣ
    int i;
    i = Account_Srv_FetchByName(username,&user);
    id=user.id;
    if(i==0)
    {
        printf("���û������ڣ�");
        return;
    }
    printf("������Ҫ��ѯ�Ŀ�ʼ����(x/y/z):");
    setbuf(stdin,NULL);
    scanf("%d/%d/%d",&startdate.year,&startdate.month,&startdate.day);
    setbuf(stdin,NULL);
    printf("����Ҫ��ѯ�Ľ�������(x/y/z)��");
    setbuf(stdin,NULL);
    scanf("%d/%d/%d",&enddate.year,&enddate.month,&enddate.day);

    int count;
    count=StaSales_Srv_CompSaleVal(id,startdate,enddate);
    printf("\n\n\n\n");
    printf("===========================================\n");
    printf("%5s  %5s  %5s","ID","����","����\n");
    printf("%5d  %5d  %5s\n",user.id,user.type,user.username);
    printf("�����ܶ�Ϊ��%5d\n",count);
    printf("*******************************************\n");
    setbuf(stdin,NULL);
    getchar();

}
