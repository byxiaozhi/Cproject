#include "Record.h"
#include "Patient.h"
#include "Doctor.h"
#include "windows.h"
#include "Utils.h"
#include "stdio.h"

void recordRegister()
{
    int pi = patientSelector();
    if(pi==-1)
        return;
    int di = docterSelector();
    if(di==-1)
        return;
    patient *p = listGet(patients,pi);
    docter *d = listGet(docters,di);
    clear();
    SetConsoleTitle("新建挂号");
    printf("\n  患者：%s\n  科室：%s\n  医生：%s\n",p->name,getDepartment(d->department),d->name);
    printf("\n请输入y确认挂号（默认为n）：");
    if(getchar()=='y')
    {
        record *temp = (record*)malloc(sizeof(record));
        strcpy(temp->patientId,p->id);
        temp->docterId=d->id;
        temp->registeredOnly=true;
        if(listSize(records))
            temp->id = ((record*)listGet(records,listSize(records)-1))->id+1;
        else
            temp->id = 1;
        listAddLast(records,temp);
        clear();
        printf("挂号成功，");
        system("pause");
    }
    else
    {
        clear();
        printf("操作被取消，");
        system("pause");
    }
}

void check()
{


}

void medicine()
{


}

void hospitalized()
{


}

void recordList()
{



}


void recordManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("诊疗信息管理");
    }
    while(selector(6,"新建挂号","检查","开药","住院","记录查询","返回",recordRegister,check,medicine,hospitalized,recordList,NULL)!=6);
}
