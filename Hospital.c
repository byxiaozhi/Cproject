#include "Hospital.h"
#include "windows.h"

void hospitalManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("�������");
    }
    while(selector(5,"����һ","���ܶ�","������","������","����",NULL,NULL,NULL,NULL,NULL)!=5);
}
