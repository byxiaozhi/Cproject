#include "Patient.h"
#include "windows.h"

const char *types[3]= {"���","��ҩ","סԺ"};

void patientManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("���߹���");
    }
    while(selector(5,"����һ","���ܶ�","������","������","����",NULL,NULL,NULL,NULL,NULL)!=5);
}
