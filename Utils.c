#include "utils.h"
#include "stdarg.h"

int selector(int args, ...)
{
    void *parameter;
    int select;
    va_list vl;
    va_start(vl,args);
    printf("\n  ²Ëµ¥\n");
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
