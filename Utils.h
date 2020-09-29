#pragma once
#include "stdbool.h"

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
}time;
time nowTime;
void clear();
void timeFlush();
int dayCount(time t);
int weekCount(time t);
int selector(int args, ...);
bool timeCheck();
