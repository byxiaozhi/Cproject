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
    SetConsoleTitle("���ӻ���");

    clear();
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
    }
    else
    {
        clear();
        free(temp);
        printf("������ȡ����");
        system("pause");
    }
}

void patientDelete()
{
    char id[100];
    int i;
    patient *temp;
    clear();
    printf("���������֤���в�ѯ��");
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
        printf("δ�ҵ��û��ߣ�");
        system("pause");
    }
    else
    {
        clear();
        printf("����֤��Ϣ\n");
        printf("������%s\n���֤�ţ�%s\n���䣺%d\n����˵���%d\n��ҩ�˵���%d\nסԺ�˵���%d\n���˵���%d\nʣ��Ѻ��%d",temp->name,temp->id,temp->age,temp->bill_all,temp->bill_check,temp->bill_medicine,temp->bill_hospitalized,temp->deposit);

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
    clear();
    printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","����","���֤��","����","����˵�","��ҩ�˵�","סԺ�˵�","���˵�","ʣ��Ѻ��");
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
        SetConsoleTitle("���߹���");
    }
    while(selector(5,"���ӻ���","ɾ������","�г����л���","��ѯ������Ϣ","����",patientAdd,patientDelete,patientList,PatientInfo,NULL)!=5);
}
