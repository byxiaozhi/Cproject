#pragma once
#include "DataHandler.h"
#define Mon (1<<1)
#define Tue (1<<2)
#define Wed (1<<3)
#define Thur (1<<4)
#define Fri (1<<5)
#define Sat (1<<6)
#define Sun (1<<7)
typedef struct
{
    int id;//����
    char name[100];//����
    int level;//����
    int department;//����
    int visitTime;//����ʱ��
} docter;

node* docters;
void docterRead();
