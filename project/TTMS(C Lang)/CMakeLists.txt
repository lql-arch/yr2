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
        src/View/Paly_UI.h
        src/View/Play_UI.c)
