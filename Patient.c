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
    SetConsoleTitle("增加患者");
    printf("请输入信息\n");

    printf("请输入姓名：");
    scanf("%s",temp->name);

    printf("请输入身份证号：");
    scanf("%s",temp->id);

    printf("请输入年龄：");
    scanf("%d",&temp->age);

    temp->bill_all=0;
    temp->bill_hospitalized=0;
    temp->bill_medicine=0;
    temp->deposit=0;

    clear();
    if(patientGetById(temp->id)!=-1)
    {
        free(temp);
        printf("该患者已存在，");
        system("pause");
        return false;
    }
    printf("请验证信息\n");
    printf("姓名：%s\n身份证号：%s\n年龄：%d",temp->name,temp->id,temp->age);

    printf("\n请输入y确认添加（默认为n）：");
    if(getchar()=='y')
    {
        listAddLast(patients,temp);
        patientSave();
        clear();
        printf("添加成功，");
        system("pause");
        return true;
    }
    else
    {
        clear();
        free(temp);
        printf("操作被取消，");
        system("pause");
        return false;
    }
}

int patientSelector(bool allowAdd)
{
    SetConsoleTitle("选择患者");
    clear();
    int select;
    if(allowAdd)
    {
        select = selector(3,"添加新患者","选择已有患者","取消挂号",NULL,NULL,NULL);
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
        printf("请输入患者姓名以检索：");
        char name[100];
        int i;
        scanf("%s",name);
        printf("\n%-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","姓名","身份证号","年龄","检查账单","开药账单","住院账单","总账单","剩余押金");
        for(i=0; i<listSize(patients); i++)
        {
            patient *temp=listGet(patients,i);
            if(strstr(temp->name,name))
                printf("%-12s %-12s %-12d %-12.2f %-12.2f %-12.2f %-12.2f %-12.2f\n",temp->name,temp->id,temp->age,temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->bill_all/100.0,temp->deposit/100.0);
        }
        printf("\n请输入身份证号以确认患者：");
        char id[100];
        scanf("%s",id);
        int r = patientGetById(id);
        clear();
        if(r!=-1)
            return r;
        printf("未找到该患者，");
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
    SetConsoleTitle("删除患者");
    printf("请输入身份证进行查询：");
    scanf("%s",id);
    i = patientGetById(id);
    if(i==-1)
    {
        clear();
        printf("未找到该患者，");
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
                printf("该患者还存在医疗记录，无法删除");
                system("pause");
                return;
            }
        }

        printf("请验证信息\n");
        printf("姓名：%s\n身份证号：%s\n年龄：%d\n检查账单：%d\n开药账单：%d\n住院账单：%d\n总账单：%d\n剩余押金：%d",temp->name,temp->id,temp->age,temp->bill_check,temp->bill_medicine,temp->bill_hospitalized,temp->bill_all,temp->deposit);

        printf("\n请输入y确认删除（默认为n）：");
        if(getchar()=='y')
        {
            listRemove(patients,i);
            patientSave();
            clear();
            printf("删除成功，");
            system("pause");
        }
        else
        {
            clear();
            printf("操作被取消，");
            system("pause");
        }
    }
}

void patientList()
{
    printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","姓名","身份证号","年龄","检查账单","开药账单","住院账单","总账单","剩余押金");
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
    SetConsoleTitle("查询患者信息");
    printf("请输入身份证进行查询：");
    scanf("%s",id);
    i = patientGetById(id);
    if(i==-1)
    {
        clear();
        printf("未找到该患者，");
        system("pause");
    }
    else
    {
        clear();
        temp=listGet(patients,i);
        printf("姓名：%s\n身份证号：%s\n年龄：%d\n检查账单：%.2f\n开药账单：%.2f\n住院账单：%.2f\n总账单：%.2f\n剩余押金：%.2f",temp->name,temp->id,temp->age,temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->bill_all/100.0,temp->deposit/100.0);
        printf("\n\n");
        system("pause");
    }
}

void patientManage()
{
    do
    {
        clear();
        SetConsoleTitle("患者管理");
    }
    while(selector(5,"增加患者","删除患者","列出所有患者","查询患者信息","返回",patientAdd,patientDelete,patientList,patientInfo,NULL)!=5);
}
