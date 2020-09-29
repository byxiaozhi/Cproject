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
    SetConsoleTitle("����������Ϣ");
    printf("\n  ������ҺŽ��в�ѯ��");
    scanf("%d",&id);
    i = recordGetById(id);
    if(i==-1)
    {
        clear();
        printf("\n  δ�ҵ��ùҺţ�");
        system("pause");
        return;
    }
    record *temp=listGet(records,i);
    patient *temp2=listGet(patients,patientGetById(temp->patientId));
    docter *temp3=listGet(docters,docterGetById(temp->docterId));


    if(temp->data_hospitalized.startTime.year!=0 && temp->data_hospitalized.endTime.year==0)
    {
        printf("\n  �ùҺŵĻ�������סԺ��������¼ǰ��Ǽǳ�Ժ��");
        system("pause");
        return;
    }
    clear();
    printf("\n  ����֤��Ϣ\n");
    printf("\n  �Һţ�%d \n  ������%s\n  ���ң�%s\n  ҽ����%s\n  ��黨�ѣ�%.2f\n  ��ҩ���ѣ�%.2f\n  סԺ���ѣ�%.2f\n\n",
           temp->id,temp2->name,getDepartment(temp3->department),temp3->name,
           temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0);
    printf("  1.������¼���˿�  2.������¼�����˿�  3.����\n\n  ��ѡ��");
    int select;
    scanf("%d",&select);
    if(select == 1 || select == 2)
    {
        recordRemove(i,select == 1);
        clear();
        printf("��¼�����ɹ���");
        system("pause");

    }
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
    while(selector(2,"����������Ϣ","����",revokeRecord,NULL)!=2);
}
