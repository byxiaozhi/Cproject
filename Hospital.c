#include "Hospital.h"
#include "windows.h"

void hospitalManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("财务管理");
    }
    while(selector(5,"功能一","功能二","功能三","功能四","返回",NULL,NULL,NULL,NULL,NULL)!=5);
}
