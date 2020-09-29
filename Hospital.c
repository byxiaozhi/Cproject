#include "Hospital.h"
#include "windows.h"
#include "stdio.h"


void hospitalSave()
{
    FILE *fp=fopen("hospital.txt", "w+");
    fprintf(fp,"%d %d %d %d",turnover_all,turnover_check,turnover_medicine,turnover_hospitalized);
    fclose(fp);
}

void hospitalRead()
{
    FILE *fp=fopen("hospital.txt", "r");
    fscanf(fp,"%d %d %d %d",&turnover_all,&turnover_check,&turnover_medicine,&turnover_hospitalized);
    fclose(fp);
}

void hospitalManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("财务管理");
    }
    while(selector(5,"功能一","功能二","功能三","功能四","返回",NULL,NULL,NULL,NULL,NULL)!=5);
}
