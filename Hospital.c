#include "Hospital.h"
#include "windows.h"
#include "stdio.h"
#include "Utils.h"
#include "Record.h"
#include "Patient.h"
#include "Doctor.h"


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

void revokeRecord()
{
    int id,i;
    SetConsoleTitle("撤销诊疗信息");
    printf("\n  请输入挂号进行查询：");
    scanf("%d",&id);
    i = recordGetById(id);
    if(i==-1)
    {
        clear();
        printf("\n  未找到该挂号，");
        system("pause");
        return;
    }
    record *temp=listGet(records,i);
    patient *temp2=listGet(patients,patientGetById(temp->patientId));
    docter *temp3=listGet(docters,docterGetById(temp->docterId));


    if(temp->data_hospitalized.startTime.year!=0 && temp->data_hospitalized.endTime.year==0)
    {
        printf("\n  该挂号的患者正在住院，撤销记录前请登记出院，");
        system("pause");
        return;
    }
    clear();
    printf("\n  请验证信息\n");
    printf("\n  挂号：%d \n  姓名：%s\n  科室：%s\n  医生：%s\n  检查花费：%.2f\n  开药花费：%.2f\n  住院花费：%.2f\n\n",
           temp->id,temp2->name,getDepartment(temp3->department),temp3->name,
           temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0);
    printf("  1.撤销记录并退款  2.撤销记录但不退款  3.返回\n\n  请选择：");
    int select;
    scanf("%d",&select);
    if(select == 1 || select == 2)
    {
        recordRemove(i,select == 1);
        clear();
        printf("记录撤销成功，");
        system("pause");

    }
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
    while(selector(2,"撤销诊疗信息","返回",revokeRecord,NULL)!=2);
}
