#include "Record.h"
#include "windows.h"

void recordManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("�ҺŹ���");
    }
    while(selector(5,"����һ","���ܶ�","������","������","����",NULL,NULL,NULL,NULL,NULL)!=5);
}
