#include "Patient.h"
#include "windows.h"

const char *types[3]= {"检查","开药","住院"};

void patientManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("患者管理");
    }
    while(selector(5,"功能一","功能二","功能三","功能四","返回",NULL,NULL,NULL,NULL,NULL)!=5);
}
