//
// Created by bronya on 22-6-20.
//

#include "Account_UI.h"
#include "../Service/Account.h"
#include "../Common/List.h"
#include <stdio.h>
#include <string.h>

#define ACCOUNT_PAGE_SIZE 5;

#ifdef linux
    #include <termio.h>
    int getch() {
        struct termios tm, tm_old;
        int fd = 0, ch;

        if (tcgetattr(fd, &tm) < 0) {//�������ڵ��ն�����
            return -1;
        }

        tm_old = tm;
        cfmakeraw(&tm);//�����ն�����Ϊԭʼģʽ����ģʽ�����е������������ֽ�Ϊ��λ������
        if (tcsetattr(fd, TCSANOW, &tm) < 0) {//�����ϸ���֮�������
            return -1;
        }

        ch = getchar();
        if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//��������Ϊ���������
            return -1;
        }

        return ch;
    }
#endif
#ifdef WIN32
    #include <conio.h>
#endif


void Account_UI_MgtEntry(int argc,char* name)
{
    int id,i;
    char ch;
    char choice;
    char usrName[31];
    account_list_t head;
    account_node_t *pos;
    Pagination_t paging;
    account_t test;

    List_Init(head, account_node_t);
    paging.offset = 0;
    paging.pageSize = ACCOUNT_PAGE_SIZE;

    //��������
    paging.totalRecords = Account_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head, paging);
    do{
        printf("\n====================================================================================================n");
        printf("--------------------------------------------------ϵͳ�û�����------------------------------------------\n");
        printf("%5s   %5s   %12s   %15s  \n", "ID","type","usrName","password");
        printf("------------------------------------------------------------------------------------------------------\n");
        //��ʾ����
        Paging_ViewPage_ForEach(head, paging, account_node_t, pos, i){
            printf("%5d   %5d   %12s  ",pos->data.id,pos->data.type,pos->data.username);
            if(argc == 9 || strcmp(pos->data.username,name) == 0){
                printf("%15s   \n",pos->data.password);
            }else{
                printf("***************   \n");
            }
        }
        printf("---------------- Total Records:%2d ------------------------------ Page %2d/%2d -------------------------\n",
                paging.totalRecords, Pageing_CurPage(paging),
                Pageing_TotalPages(paging));
        printf("********************************************************************************************************\n");
        printf("\t1.���ϵͳ�û�(a��A)    2.�޸�ϵͳ�û�(m��M)    \n");
        printf("\t3.ɾ��ϵͳ�û�(d��D)    4.��ѯϵͳ�û�(q��Q)    \n");
        printf("\t5.��λ����һҳ(p��P)    6.��λ����һҳ(n��N)    \n");
        printf("\t7.�˳�(r��R)    \n");
        printf("\n-----------------------------------------------------------------------------------------------------\n");

        char choice;
        //ѡ��Ҫʵ�ֵĹ���
        printf("Your Choice:");
        fflush(stdin);
        scanf("%c", &choice);

        switch (choice) {
            case 'a':
            case 'A':
                if (argc == 9 && Account_UI_Add(head)) //����ӳɹ����������һҳ��ʾ
                {
                    paging.totalRecords = Account_Srv_FetchAll(head);
                    Paging_Locate_LastPage(head, paging, account_node_t);
                }
                break;
            case 'd':
            case 'D':
                printf("��������Ҫɾ�����û���:");
                scanf("%s", usrName);
                setbuf(stdin, 0);
                if(argc == 9 || strcmp(name,usrName) == 0) {
                    if (Account_UI_Del(head, usrName)) {    //������������
                        paging.totalRecords = Account_Srv_FetchAll(head);
                        List_Paging(head, paging, account_node_t);
                    }
                }else{
                    fprintf(stdout,"��û��Ȩ��ɾ�����û���Ϣ.\n��[Enter]�˳�.\n");
                    getchar();
                }
                break;
            case 'm':
            case 'M':
                printf("��������Ҫ�޸ĵ��û�����:");
                scanf("%s", usrName);
                setbuf(stdin, 0);
                if(argc == 9 || strcmp(name,usrName) == 0) {
                    if (Account_UI_Modify(head, usrName,argc)) {    //������������
                        paging.totalRecords = Account_Srv_FetchAll(head);
                        List_Paging(head, paging, account_node_t);
                    }
                }else{
                    fprintf(stdout,"��û��Ȩ���޸ĸ��û���Ϣ.\n ��[Enter]�˳�.\n");
                    getchar();
                }
                break;
            case 'q':
            case 'Q':
                printf("��������Ҫ��ѯ���û�����:");
                scanf("%s", usrName);
                setbuf(stdin, 0);
                if(argc == 9 || strcmp(name,usrName) == 0) {
                    if (Account_UI_Que(head, usrName)) {
                        paging.totalRecords = Account_Srv_FetchAll(head);
                        List_Paging(head, paging, account_node_t);
                    }
                }else{
                    fprintf(stdout,"��û��Ȩ�޲�ѯ���û���Ϣ.\n��[Enter]�˳�.\n");
                    getchar();
                }
                break;
            case 'p':
            case 'P':
                if (!Pageing_IsFirstPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
                }
                break;
            case 'n':
            case 'N':
                if (!Pageing_IsLastPage(paging)) {
                    Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
                }
                break;
            case 'r':
            case 'R':
                while((ch = getchar()) != '\n')
                    continue;
                return ;
                break;
        }
    }while(choice != 'r' && choice != 'R');

    List_Destroy(head, account_node_t);

    while((ch = getchar()) != '\n')
        continue;

}

int Account_UI_Add(account_list_t list) {//����Ϊϵͳ�û�����ͷָ��
    account_t t;
    int NewCount = 0;
    char choice;

    do {
        #ifdef linux
                system("clear");
        #endif
        #ifdef WIN32
                system("cls");
        #endif
        printf("---------------------------------------------------------------------------\n");

        printf("*****************************�����ϵͳ�û�********************************\n");

        printf("---------------------------------------------------------------------------\n");

        printf("�������û�����");
        scanf("%s", t.username);
        printf("���������룺");
        scanf("%s", t.password);
        printf("��ѡ���ʺ�����([����Ա/1]��[����/2]��[ϵͳ����Ա/9])��");
        scanf("%d", &t.type);

        if (Account_Srv_Add(&t)) {
            NewCount += 1;
            printf("�µ��ʺ��ѱ��ɹ�����\n");
        } else
            printf("�����ʺ�ʧ��\n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("[A]��Ӹ���, [R]����\n");
        fflush(stdin);
        scanf("%c", &choice);

    }while('a' == choice || 'A' == choice);

    setbuf(stdin,0);

    return NewCount;

}

int Account_UI_Del(account_list_t list,char usrName[]) {
    //�����û�����ѯ���û�,����ɾ����ϵͳ�û�

    account_list_t t;
    int rtn = 0;
    char choice;
    char name[31];

    /*Load record*/
    do{
        if ((t = Account_Srv_FindByUsrName(list,usrName)) == NULL) {
            printf("%s������!\n"
                   "����[Enter]�����ϲ�!\n",usrName);
            getchar();
            return 0;
        }

        #ifdef linux
            system("clear");
        #endif
        #ifdef WIN32
            system("cls");
        #endif

        printf("-----------------------------------------------------------------------------\n");

        printf("*****************************ɾ��ϵͳ�û���Ϣ********************************\n");

        printf("-----------------------------------------------------------------------------\n");

        if (Account_Srv_DelByID(t->data.id)) {
            printf("�ʺ��ѱ��ɹ�ɾ��!\n");
            rtn += 1;
        } else {
            printf("�ʺ�ɾ��ʧ��!\n");
            break;
        }
        printf("--------------------------------------------------------------------------------------\n");
        printf("[D]ɾ������, [R]����:");
        scanf("%c", &choice);
        printf("��Ҫɾ�����ʺ��û���:");
        scanf("%s",name);
        setbuf(stdin,NULL);
    } while ('d' == choice || 'D' == choice);

    printf("����[Enter]�����ϲ�!\n");
    getchar();

    return rtn;

}

int Account_UI_Modify(account_list_t list,char usrName[],int argc){
    account_list_t t;
    int rtn = 0;
    int count = 0;
    char pow[31];
    int i = 0;

    /*Load record*/
    if ((t = Account_Srv_FindByUsrName(list,usrName)) == NULL) {
        printf("%s������!\n"
               "����[Enter]�����ϲ�!\n",usrName);
        getchar();
        return 0;
    }

    #ifdef linux
        system("clear");
    #endif
    #ifdef WIN32
        system("cls");
    #endif

    printf("-----------------------------------------------------------------------------\n");

    printf("*****************************�޸�ϵͳ�û���Ϣ********************************\n");

    printf("-----------------------------------------------------------------------------\n");

    if(argc != 9) {
        while( i <= 3) {
            printf("������ԭʼ���룺");
            scanf("%s", pow);
            if (strcmp(pow, t->data.password) != 0) {
                printf("�������(ʣ����᣺%d)\n",i);
            } else {
                printf("�����������룺");
                scanf("%s", t->data.password);
                break;
            }
            i++;
        }
        if(i == 4){
            fprintf(stderr,"�޸�ʧ��.\n");
            setbuf(stdin,NULL);
            return 0;
        }
    }else{
        printf("�����������룺");
        scanf("%s", t->data.password);
    }

    if (Account_Srv_Insert(&(t->data))) {
        rtn = 1;
        printf("�ʺ��޸ĳɹ���\n����[Enter]�����ϲ�!\n");
    } else
        printf("�ʺ��޸�ʧ��!\n����[Enter]�����ϲ�!\n");

    getchar();
    return rtn;
}


int Account_UI_Que(account_list_t list,char usrName[]) {
    account_list_t t;
    int rtn = 0;
    int count = 0;

    /*Load record*/
    if ((t = Account_Srv_FindByUsrName(list,usrName)) == NULL) {
        printf("%s������!\n"
               "����[Enter]�����ϲ�!\n",usrName);
        getchar();
        return 0;
    }

    #ifdef linux
        system("clear");
    #endif
    #ifdef WIN32
        system("cls");
    #endif


    //�����û���ƥ��ϵͳ�û�
    printf("-----------------------------------------------------------------------------\n");

    printf("*****************************��ѯϵͳ�û���Ϣ********************************\n");

    printf("-----------------------------------------------------------------------------\n");

    printf("\n====================================================================================================n");
    printf("--------------------------------------------------ϵͳ�û�����------------------------------------------\n");
    printf("%5s   %5s   %12s   %15s  \n", "ID","type","usrName","password");
    printf("------------------------------------------------------------------------------------------------------\n");
    //��ʾ����
    printf("%5d   %5d   %12s  %15s   \n",t->data.id,t->data.type,t->data.username,t->data.password);
    printf("------------------------------------------------------------------------------------------------------\n");

    fprintf(stdout,"����[Enter]�˳�.\n");

    getchar();

    return 1;
}

int SysLogin(account_t* t) {
    char ch;
    int choice;

    do {
        printf("----------------------------------------------------------\n");
        printf("*                                                        *\n");
        printf("*                       1.�û���¼                         *\n");
        printf("*                       2.ע���û�                         *\n");
        printf("*                       3.������¼                         *\n");
        printf("*                       4.�˳�                            *\n");
        printf("*                                                        *\n");
        printf("----------------------------------------------------------\n");

        printf("������ѡ��:");
        scanf("%d",&choice);

        switch(choice) {

            case 1:
                slg(t);
                if(t->type != -1) {
                    setbuf(stdin,NULL);
                    return t->type;
                }else{
                    fprintf(stderr,"�������������࣬������ѡ��.\n");
                }
                break;
            case 2:
                reg();
                break;
            case 3:
                setbuf(stdin,NULL);
                return 0;
                break;
            case 4:
                break;
            default:
                fprintf(stderr,"�����������������.\n");
                break;
        }
    }while(choice != 4);


    setbuf(stdin,NULL);

    return -1;
}

int slg(account_t* ans){
    account_t t;
    char ch;
    int i = 0,count = 0;
    account_list_t list;
    account_list_t head;

    List_Init(head, account_node_t);
    Account_Srv_FetchAll(head);

    printf("�������û�����");
    scanf("%s", t.username);
    while ((ch = getchar()) != '\n')
        continue;

    while (i <= 3) {
        printf("���������룺");
        while((ch = getch()) != '\n'){
            if(ch == '\r')
                break;
            if(ch == '\b'){
                printf("\b \b");
                count--;
            }else{
                printf("*");
                t.password[count++] = ch;
            }
        }
        t.password[count] = '\0';
        //scanf("%s",t.password);

        if (Account_Srv_Verify(t.username, t.password)) {
            list = Account_Srv_FindByUsrName(head,t.username);
            ans->type = list->data.type;
            strcpy(ans->password , list->data.password);
            strcpy(ans->username , list->data.username);
            return ans->type;
        }else{
            i++;
            fprintf(stderr,"(ʣ���������������%d)",4-i);
        }
    }

    return -1;
}

void reg(){
    account_t t;
    printf("�������û�����");
    scanf("%s", t.username);
    printf("���������룺");
    scanf("%s",t.password);
    printf("��ѡ���ʺ�����([����Ա/1]��[����/2]��[ϵͳ����Ա/9])��" );
    scanf("%d",&t.type);

    Account_Srv_Add(&t);

    fprintf(stdout,"ע����ɣ���[Enter]�˳�.\n");

    getchar();
}

