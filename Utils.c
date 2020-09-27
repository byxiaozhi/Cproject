#include "utils.h"
#include "stdarg.h"
#include "stdio.h"

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
        printf("  %d.%s\n", i, parameter);
    }
    printf("  ÇëÑ¡Ôñ£º");
    scanf("%d",&select);
    if(select>0 && select<=args)
    {
        for(int i=0; i<select; i++)
            parameter = va_arg(vl, void*);
        if(parameter)
            (*(void(*)(void))(parameter))();
    }
    va_end(vl);
    return select;
}



char weekDayCount(int year, int month, int day)
{
    int weekday = 0;
    if ((month == 1) || (month == 2))
    {
        month += 12;
        year--;
    }
    weekday = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7 + 1;
    return weekday;
}

void clear()
{
    system("cls");
    fflush(stdin);
}

