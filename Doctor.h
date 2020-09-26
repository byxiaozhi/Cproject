#pragma once
#include "DataHandler.h"
typedef struct
{
    int id;//工号
    char name[100];//姓名
    int level;//级别
    int department;//科室
} docter;

node* docters;
