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
        printf("\n  医院收入概览\n");
        printf("  医院总收入：%.2f 元\n",turnover_all/100.0);
        printf("  医院检查收入：%.2f 元\n",turnover_check/100.0);
        printf("  医院药品收入：%.2f 元\n",turnover_medicine/100.0);
        printf("  医院住院收入：%.2f 元\n",turnover_hospitalized/100.0);
    }
    while(selector(2,"撤销诊疗信息","返回",NULL,NULL)!=2);
}
