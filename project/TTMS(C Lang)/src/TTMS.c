/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* File name: TTMS.c			  
* Description : Main in C, Ansi-style	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015??4??22??	
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef linux
	#include <sys/io.h>
#endif
#ifdef WIN32
	#include <io.h>
#endif

#include "./View/Main_Menu.h"
#include "./View/Account_UI.h"
#include "./View/Sale_UI.h"


//系统运行入口函数main
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
    account_t t;
    GetUser(&t);

    Account_Srv_InitSys();//tmp_admin默认666666

    int ans = SysLogin(&t);
    if(ans == 1)
    {
        Main_Menu1(t.username);
    }else if(ans == 0){
        Main_Menu0(t.username);
    }else if(ans == 2){
        Main_Menu2(t.username);
    }else if(ans == 9){
        Main_Menu9(t.username);
    }
	return EXIT_SUCCESS;
}
