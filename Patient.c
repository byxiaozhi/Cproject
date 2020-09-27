#include "Patient.h"
#include "windows.h"
#include "stdio.h"




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


void patientAdd()
{
    char comfirm;
    patient *temp=(patient*)malloc(sizeof(patient));
    SetConsoleTitle("增加患者");

    clear();
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
    }
    else
    {
        clear();
        free(temp);
        printf("操作被取消，");
        system("pause");
    }
}

void patientDelete()
{
    char id[100];
    int i;
    patient *temp;
    clear();
    printf("请输入身份证进行查询：");
    scanf("%s",id);
    for(i=0; i<listSize(patients); i++)
    {
        temp=listGet(patients,i);
        if(strcmp(temp->id,id)==0)
            break;
    }
    if(i==listSize(patients))
    {
        clear();
        printf("未找到该患者，");
        system("pause");
    }
    else
    {
        clear();
        printf("请验证信息\n");
        printf("姓名：%s\n身份证号：%s\n年龄：%d\n检查账单：%d\n开药账单：%d\n住院账单：%d\n总账单：%d\n剩余押金：%d",temp->name,temp->id,temp->age,temp->bill_all,temp->bill_check,temp->bill_medicine,temp->bill_hospitalized,temp->deposit);

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
    clear();
    printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","姓名","身份证号","年龄","检查账单","开药账单","住院账单","总账单","剩余押金");
    for(int i=0; i<listSize(patients); i++)
    {
        patient *temp=listGet(patients,i);
        printf("%-12s %-12s %-12d %-12d %-12d %-12d %-12d %-12d\n",temp->name,temp->id,temp->age,temp->bill_all,temp->bill_check,temp->bill_medicine,temp->bill_hospitalized,temp->deposit);
    }
    system("pause");
}

void PatientInfo()
{

}

void patientManage()
{
    do
    {
        clear();
        SetConsoleTitle("患者管理");
    }
    while(selector(5,"增加患者","删除患者","列出所有患者","查询患者信息","返回",patientAdd,patientDelete,patientList,PatientInfo,NULL)!=5);
}
