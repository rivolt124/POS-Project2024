cmake_minimum_required(VERSION 3.20)
project(hadik C)

set(CMAKE_C_STANDARD 99) # Nastavuje štandard C99

add_executable(hadik main.c map.c
        Menu.h
        Menu.c
) # Pridaj všetky svoje .c súbory
