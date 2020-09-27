#include "Record.h"
#include "windows.h"
void recordManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("诊疗信息管理");
    }
    while(selector(6,"新建挂号","检查","开药","住院","记录查询","返回",NULL,NULL,NULL,NULL,NULL)!=6);
}
