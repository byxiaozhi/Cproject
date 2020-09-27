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
int dayCount(int year,int month,int day)
{
    int sum = 0;
    switch(month)
    {
    case 1:
        sum = day;
        break;
    case 2:
        sum = 31 + day;
        break;
    case 3:
        sum = 59 + day;
        break;
    case 4:
        sum = 90 + day;
        break;
    case 5:
        sum = 120 + day;
        break;
    case 6:
        sum = 151 + day;
        break;
    case 7:
        sum = 181 + day;
        break;
    case 8:
        sum = 212 + day;
        break;
    case 9:
        sum = 243 + day;
        break;
    case 10:
        sum = 273 + day;
        break;
    case 11:
        sum = 304 + day;
        break;
    case 12:
        sum = 334 + day;
        break;
    }
    if(month > 2 && (((year % 4 == 0) && (year % 100 !=0)) || (year % 400) == 0))
        sum++;
    return sum;
}

void clear()
{
    system("cls");
    fflush(stdin);
}

