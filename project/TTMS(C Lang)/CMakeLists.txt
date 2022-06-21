cmake_minimum_required(VERSION 3.22)
project(TTMS_C_Lang_ C)

set(CMAKE_C_STANDARD 11)

include_directories(src/Common)
include_directories(src/Persistence)
include_directories(src/Service)
include_directories(src/View)

add_executable(TTMS_C_Lang_
        src/Common/common.c
        src/Common/common.h
        src/Common/List.h
        src/Common/listTestDrv.c
        src/Common/listTestDrv.h
        src/Persistence/EntityKey_Persist.c
        src/Persistence/EntityKey_Persist.h
        src/Persistence/Seat_Persist.c
        src/Persistence/Seat_Persist.h
        src/Persistence/Studio_Persist.c
        src/Persistence/Studio_Persist.h
        src/Service/Seat.c
        src/Service/Seat.h
        src/Service/Studio.c
        src/Service/Studio.h
        src/View/Main_Menu.c
        src/View/Main_Menu.h
        src/View/Seat_UI.c
        src/View/Seat_UI.h
        src/View/Studio_UI.c
        src/View/Studio_UI.h
        src/TTMS.c
        src/View/Schedule_UI.h
        src/View/Schedule_UI.c
        src/Service/Play.h
        src/Service/Play.c
        src/Persistence/Play_Perst.h
        src/Persistence/Play_Perst.c
        src/Service/Schedule.c
        src/Service/Schedule.h
        src/View/Play_UI.c
        src/View/Play_UI.h
        src/Persistence/Schedule_Persist.c
        src/Persistence/Schedule_Persist.h
        src/Persistence/Creat_Ticket_Persist.c
        src/Persistence/Creat_Ticket_Persist.h
        src/Service/Creat_Ticket.c
        src/Service/Creat_Ticket.h
        src/View/Creat_Ticket_UI.c
        src/View/Creat_Ticket_UI.h
        src/View/Account_UI.c
        src/View/Account_UI.h
        src/Service/Account.h
        src/Service/Account.c
        src/Persistence/Account_Persist.c
        src/Persistence/Account_Persist.h
#        src/View/SalesAnalysis_UI.c
#        src/View/SalesAnalysis_UI.h
#        src/View/StaSales_UI.c
#        src/View/StaSales_UI.h
#        src/View/SalesAnalysis_UI.h
#        src/View/SalesAnalysis_UI.c
#        src/View/StaSales_UI.h
#        src/View/StaSales_UI.c
#        src/Service/SalesAnalysis.h
#        src/Service/SalesAnalysis.c
#        src/Persistence/SalesAnalysis_persist.h
#        src/Persistence/SalesAnalysis_persist.c
#        src/Persistence/StaSales_Persist.h
#        src/Persistence/StaSales_Persist.c
#        src/Service/StaSales.h
#        src/Service/StaSales.c
        src/View/Sale_UI.c
        src/View/Sale_UI.h
        src/Service/Sale.c
        src/Service/Sale.h
        src/Persistence/Sale_Persist.c
        src/Persistence/Sale_Persist.h
        src/Service/EntKey.c src/Service/EntKey.h
        )
