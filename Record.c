#include "Record.h"
#include "windows.h"
const char *types[3]= {"���","��ҩ","סԺ"};
void recordManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("�ҺŹ���");
    }
    while(selector(5,"����һ","���ܶ�","������","������","����",NULL,NULL,NULL,NULL,NULL)!=5);
}
