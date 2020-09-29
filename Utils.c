#include "utils.h"
#include "stdarg.h"
#include "stdio.h"
#include "windows.h"

//菜单选择器
int selector(int args, ...)
{
    void *parameter;
    int select;
    va_list vl;
    va_start(vl,args);
    printf("\n");
    fflush(stdin);
    for (int i = 1; i <= args; i++)
    {
        parameter = va_arg(vl, void*);
        printf("  %d.%s\n\n", i, (char*)parameter);
    }
    printf("  请选择：");
    scanf("%d",&select);
    clear();
    if(select > 0 && select <= args)
    {
        for(int i = 0; i < select; i++)
            parameter = va_arg(vl, void*);
        if(parameter)
            (*(void(*)(void))(parameter))();
    }
    va_end(vl);
    return select;
}

//计算这一年已经过的天数
int dayCount(time t)
{
    int sum = 0;
    switch(t.month)
    {
    case 1:
        sum = t.day;
        break;
    case 2:
        sum = 31 + t.day;
        break;
    case 3:
        sum = 59 + t.day;
        break;
    case 4:
        sum = 90 + t.day;
        break;
    case 5:
        sum = 120 + t.day;
        break;
    case 6:
        sum = 151 + t.day;
        break;
    case 7:
        sum = 181 + t.day;
        break;
    case 8:
        sum = 212 + t.day;
        break;
    case 9:
        sum = 243 + t.day;
        break;
    case 10:
        sum = 273 + t.day;
        break;
    case 11:
        sum = 304 + t.day;
        break;
    case 12:
        sum = 334 + t.day;
        break;
    }
    if(t.month > 2 && (((t.year % 4 == 0) && (t.year % 100 !=0)) || (t.year % 400) == 0))
        sum++;
    return sum;
}

//检查时间是否合法
bool timeCheck(time t)
{
    bool ly = ((t.year % 4 == 0) && (t.year % 100 !=0)) || (t.year % 400) == 0;
    if(t.month<1 || t.month>12)
        return false;
    if(t.day<1)
        return false;
    if(t.hour<0 || t.hour>23)
        return false;
    if(t.minute<0 || t.minute>59)
        return false;
    if((t.month == 1 || t.month == 3 || t.month == 5 || t.month == 7 || t.month == 8 || t.month == 10 || t.month == 12)&&t.month>31)
        return false;
    if((t.month == 2 || t.month==4 || t.month == 6 || t.month==9 || t.minute==11) && t.month>30)
        return false;
    if(!ly && t.month>28 || ly&& t.month>29)
        return false;
    return true;
}

//计算星期几
int weekCount(time t)
{
    if(t.month == 1 || t.month == 2)
    {
        t.month += 12;
        t.year --;
    }
    int week = (t.day + 2 * t.month + 3 * (t.month + 1) / 5 + t.year + t.year / 4 - t.year / 100 + t.year / 400) % 7;
    return week + 1;
}

void clear()
{
    system("cls");
    fflush(stdin);
}

void timeFlush()
{

    FILE *fp=fopen("time.txt", "r");
    fscanf(fp, "%d/%d/%d %d:%d",&nowTime.year,&nowTime.month,&nowTime.day,&nowTime.hour,&nowTime.minute);
    fclose(fp);
}


