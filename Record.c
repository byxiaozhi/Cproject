#include "Record.h"
#include "windows.h"
void recordManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("������Ϣ����");
    }
    while(selector(5,"�½��Һ�","���","��ҩ","סԺ","��¼��ѯ","����",NULL,NULL,NULL,NULL,NULL)!=6);
}
