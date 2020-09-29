#include "Patient.h"
#include "windows.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "Utils.h"
#include "Record.h"
void recordListByPatient();


void patientSave()
{
    FILE *fp=fopen("patients.txt", "w+");
    for(int i=0; i<listSize(patients); i++)
    {
        patient *temp=listGet(patients,i);
        fprintf(fp, "%s %s %d %d %d %d %d %d\n",temp->name,temp->id,temp->age,temp->bill_all,temp->bill_check,temp->bill_medicine,temp->bill_hospitalized,temp->deposit);
    }

    fclose(fp);
}

void patientRead()
{
    FILE *fp=fopen("patients.txt", "r");

    if(!fp)
    {
        return;
    }
    patient *temp=(patient*)malloc(sizeof(patient));
    while(fscanf(fp,"%s %s %d %d %d %d %d %d\n",temp->name,temp->id,&temp->age,&temp->bill_all,&temp->bill_check,&temp->bill_medicine,&temp->bill_hospitalized,&temp->deposit)==8)
    {
        listAddLast(patients,temp);
        temp=(patient*)malloc(sizeof(patient));
    }
    free(temp);

    fclose(fp);
}

int patientGetById(char *id)
{
    for(int i=0; i<listSize(patients); i++)
    {
        patient *temp=listGet(patients,i);
        if(strcmp(temp->id,id)==0)
            return i;
    }
    return -1;
}


bool patientAdd()
{
    patient *temp=(patient*)malloc(sizeof(patient));
    SetConsoleTitle("���ӻ���");
    printf("��������Ϣ\n");

    printf("������������");
    scanf("%s",temp->name);

    printf("���������֤�ţ�");
    scanf("%s",temp->id);

    printf("���������䣺");
    scanf("%d",&temp->age);

    temp->bill_all=0;
    temp->bill_hospitalized=0;
    temp->bill_medicine=0;
    temp->deposit=0;

    clear();
    if(patientGetById(temp->id)!=-1)
    {
        free(temp);
        printf("�û����Ѵ��ڣ�");
        system("pause");
        return false;
    }
    printf("����֤��Ϣ\n");
    printf("������%s\n���֤�ţ�%s\n���䣺%d",temp->name,temp->id,temp->age);

    printf("\n������yȷ����ӣ�Ĭ��Ϊn����");
    if(getchar()=='y')
    {
        listAddLast(patients,temp);
        patientSave();
        clear();
        printf("��ӳɹ���");
        system("pause");
        return true;
    }
    else
    {
        clear();
        free(temp);
        printf("������ȡ����");
        system("pause");
        return false;
    }
}

int patientSelector(bool allowAdd)
{
    SetConsoleTitle("ѡ����");
    clear();
    int select;
    if(allowAdd)
    {
        select = selector(3,"����»���","ѡ�����л���","ȡ���Һ�",NULL,NULL,NULL);
    }
    else
    {
        select = 2;
    }
    switch(select)
    {
    case 1:
        if(patientAdd())
            return listSize(patients)-1;
        break;
    case 2:
        clear();
        printf("�����뻼�������Լ�����");
        char name[100];
        int i;
        scanf("%s",name);
        printf("\n%-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","����","���֤��","����","����˵�","��ҩ�˵�","סԺ�˵�","���˵�","ʣ��Ѻ��");
        for(i=0; i<listSize(patients); i++)
        {
            patient *temp=listGet(patients,i);
            if(strstr(temp->name,name))
                printf("%-12s %-12s %-12d %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f\n",temp->name,temp->id,temp->age,temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->bill_all/100.0,temp->deposit/100.0);
        }
        printf("\n���������֤����ȷ�ϻ��ߣ�");
        char id[100];
        scanf("%s",id);
        int r = patientGetById(id);
        clear();
        if(r!=-1)
            return r;
        printf("δ�ҵ��û��ߣ�");
        system("pause");
        break;
    }
    return -1;
}

void patientDelete()
{
    char id[100];
    int i;
    patient *temp;
    SetConsoleTitle("ɾ������");
    printf("���������֤���в�ѯ��");
    scanf("%s",id);
    i = patientGetById(id);
    if(i==-1)
    {
        clear();
        printf("δ�ҵ��û��ߣ�");
        system("pause");
    }
    else
    {
        clear();
        temp=listGet(patients,i);

        for(int i=0; i<listSize(records); i++)
        {
            record *t=listGet(records,i);
            if(strcmp(temp->id,t->patientId)==0)
            {
                printf("�û��߻�����ҽ�Ƽ�¼���޷�ɾ��");
                system("pause");
                return;
            }
        }

        printf("����֤��Ϣ\n");
        printf("������%s\n���֤�ţ�%s\n���䣺%d\n����˵���%d\n��ҩ�˵���%d\nסԺ�˵���%d\n���˵���%d\nʣ��Ѻ��%d",temp->name,temp->id,temp->age,temp->bill_check,temp->bill_medicine,temp->bill_hospitalized,temp->bill_all,temp->deposit);

        printf("\n������yȷ��ɾ����Ĭ��Ϊn����");
        if(getchar()=='y')
        {
            listRemove(patients,i);
            patientSave();
            clear();
            printf("ɾ���ɹ���");
            system("pause");
        }
        else
        {
            clear();
            printf("������ȡ����");
            system("pause");
        }
    }
}

void patientList()
{
    printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","����","���֤��","����","����˵�","��ҩ�˵�","סԺ�˵�","���˵�","ʣ��Ѻ��");
    for(int i=0; i<listSize(patients); i++)
    {
        patient *temp=listGet(patients,i);
        printf("%-12s %-12s %-12d %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f\n",temp->name,temp->id,temp->age,temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->bill_all/100.0,temp->deposit/100.0);
    }
    system("pause");
}

void patientInfo()
{
    char id[100];
    int i;
    patient *temp;
    SetConsoleTitle("��ѯ������Ϣ");
    printf("���������֤���в�ѯ��");
    scanf("%s",id);
    i = patientGetById(id);
    if(i==-1)
    {
        clear();
        printf("δ�ҵ��û��ߣ�");
        system("pause");
    }
    else
    {
        clear();
        temp=listGet(patients,i);
        printf("������%s\n���֤�ţ�%s\n���䣺%d\n����˵���%.2f\n��ҩ�˵���%.2f\nסԺ�˵���%.2f\n���˵���%.2f\nʣ��Ѻ��%.2f",temp->name,temp->id,temp->age,temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->bill_all/100.0,temp->deposit/100.0);
        printf("\n\n");
        system("pause");
    }
}

void patientManage()
{
    do
    {
        clear();
        SetConsoleTitle("���߹���");
    }
    while(selector(5,"���ӻ���","ɾ������","�г����л���","��ѯ������Ϣ","����",patientAdd,patientDelete,patientList,patientInfo,NULL)!=5);
}
