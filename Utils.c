#include "utils.h"
#include "stdarg.h"

int selector(int args, ...)
{
    void *result;
    int select;
    va_list vl;
    va_start(vl,args);
    printf("²Ëµ¥£º\n");
    for (int i = 1; i <= args; i++)
    {
        result = va_arg(vl, void *);
        printf("%d.%s\n", i, result);
    }
    printf("ÇëÑ¡Ôñ£º");
    scanf("%d",&select);
    if(select>0 && select<=args)
    {
        for(int i=0; i<select; i++)
            result = va_arg(vl, void *);
        if(result)
            (*(void(*)(void))(result))();
    }
    va_end(vl);
    return select;
}
