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
        SetConsoleTitle("�������");
        printf("\n  ҽԺ�������\n");
        printf("  ҽԺ�����룺%.2f Ԫ\n",turnover_all/100.0);
        printf("  ҽԺ������룺%.2f Ԫ\n",turnover_check/100.0);
        printf("  ҽԺҩƷ���룺%.2f Ԫ\n",turnover_medicine/100.0);
        printf("  ҽԺסԺ���룺%.2f Ԫ\n",turnover_hospitalized/100.0);
    }
    while(selector(2,"����������Ϣ","����",NULL,NULL)!=2);
}
