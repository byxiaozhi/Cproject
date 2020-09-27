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
    SetConsoleTitle("�½��Һ�");
    printf("\n  ���ߣ�%s\n  ���ң�%s\n  ҽ����%s\n",p->name,getDepartment(d->department),d->name);
    printf("\n������yȷ�ϹҺţ�Ĭ��Ϊn����");
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
        printf("�Һųɹ���");
        system("pause");
    }
    else
    {
        clear();
        printf("������ȡ����");
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
        SetConsoleTitle("������Ϣ����");
    }
    while(selector(6,"�½��Һ�","���","��ҩ","סԺ","��¼��ѯ","����",recordRegister,check,medicine,hospitalized,recordList,NULL)!=6);
}
