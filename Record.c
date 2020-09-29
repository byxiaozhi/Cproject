#include "Record.h"
#include "Patient.h"
#include "Doctor.h"
#include "windows.h"
#include "Utils.h"
#include "stdio.h"
#include "Hospital.h"
void recordSave()
{

    FILE *fp=fopen("records.txt", "w+");
    for(int i=0; i<listSize(records); i++)
    {
        record  *temp=listGet(records,i);
        record_hospitalized *h=&(temp->data_hospitalized);
        fprintf(fp, "%d %s %d %d %d %d %d ",temp->id,temp->patientId,temp->docterId,temp->registeredOnly,temp->Bill_check,temp->Bill_medicine,temp->Bill_hospitalized);
        fprintf(fp, "%d %d %d %d %d ",temp->dateTime.year,temp->dateTime.month,temp->dateTime.day,temp->dateTime.hour,temp->dateTime.minute);
        fprintf(fp, "%d %d %d %d %d ",h->startTime.year,h->startTime.month,h->startTime.day,h->startTime.hour,h->startTime.minute);
        fprintf(fp, "%d %d %d %d %d ",h->endTime.year,h->endTime.month,h->endTime.day,h->endTime.hour,h->endTime.minute);
        fprintf(fp, "%d ",h->deposit);
        fprintf(fp, "%d ", listSize(temp->data_check));
        for(int i=0; i<listSize(temp->data_check); i++)
        {
            record_check *check = listGet(temp->data_check,i);
            fprintf(fp,"%s %d ",check->name,check->price);
        }
        fprintf(fp, "%d ", listSize(temp->data_medicine));
        for(int i=0; i<listSize(temp->data_medicine); i++)
        {
            record_medicine *medicine = listGet(temp->data_medicine,i);
            fprintf(fp,"%s %d %d ",medicine->name,medicine->price,medicine->num);
        }
    }
    fclose(fp);
    hospitalSave();
}

void recordRead()
{
    int n;
    FILE *fp=fopen("records.txt", "r");
    if(!fp)
    {
        return;
    }
    record *temp=(record*)malloc(sizeof(record));
    while(fscanf(fp, "%d %s %d %d %d %d %d ",&temp->id,temp->patientId,&temp->docterId,(int*)&temp->registeredOnly,&temp->Bill_check,&temp->Bill_medicine,&temp->Bill_hospitalized)==7)
    {
        record_hospitalized *h=&(temp->data_hospitalized);
        fscanf(fp, "%d %d %d %d %d ",&temp->dateTime.year,&temp->dateTime.month,&temp->dateTime.day,&temp->dateTime.hour,&temp->dateTime.minute);
        fscanf(fp, "%d %d %d %d %d ",&h->startTime.year,&h->startTime.month,&h->startTime.day,&h->startTime.hour,&h->startTime.minute);
        fscanf(fp, "%d %d %d %d %d ",&h->endTime.year,&h->endTime.month,&h->endTime.day,&h->endTime.hour,&h->endTime.minute);
        fscanf(fp, "%d ",&h->deposit);
        temp->data_check=listCreate();
        fscanf(fp, "%d ", &n);
        for(int i=0; i<n; i++)
        {
            record_check *check = (record_check*)malloc(sizeof(record_check));
            fscanf(fp,"%s %d ",check->name,&check->price);
            listAddLast(temp->data_check,check);
        }
        temp->data_medicine=listCreate();
        fscanf(fp, "%d ", &n);
        for(int i=0; i<n; i++)
        {
            record_medicine *medicine = (record_medicine*)malloc(sizeof(record_medicine));
            fscanf(fp,"%s %d %d ",medicine->name,&medicine->price,&medicine->num);
            listAddLast(temp->data_medicine,medicine);
        }
        listAddLast(records,temp);
        temp=(record*)malloc(sizeof(records));
    }
    free(temp);
    fclose(fp);
}

//��ȡ�Һż���ܼۣ�����Ϊ�ҺŴ�������
int recordGetPriceOfCheck(int index)
{
    record *temp = listGet(records,index);
    node *checks = temp->data_check;
    int i,total=0;
    for(i=0; i<listSize(checks); i++)
    {
        record_check *check=listGet(checks,i);
        total+=check->price;
    }
    return total;
}

//��ȡ�Һ�ҩ���ܼۣ�����Ϊ�ҺŴ�������
int recordGetPriceOfMedicine(int index)
{
    record *temp = listGet(records,index);
    node *medicines = temp->data_medicine;
    int i,total=0;
    for(i=0; i<listSize(medicines); i++)
    {
        record_medicine *medicine=listGet(medicines,i);
        total+=medicine->price*medicine->num;
    }
    return total;
}

int recordGetById(int id)
{
    for(int i=0; i<listSize(records); i++)
    {
        record *temp=listGet(records,i);
        if(temp->id==id)
            return i;
    }
    return -1;
}

int recordGetByUser()
{
    int id,i;
    clear();
    printf("������Һţ�");
    scanf("%d",&id);
    i = recordGetById(id);
    if(i==-1)
    {
        clear();
        printf("δ�ҵ��ùҺţ�");
        system("pause");
        return -1;
    }
    return i;
}

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
        temp->data_check=listCreate();
        temp->data_medicine=listCreate();
        if(listSize(records))
            temp->id = ((record*)listGet(records,listSize(records)-1))->id+1;
        else
            temp->id = 1;
        timeFlush();
        temp->dateTime=nowTime;
        listAddLast(records,temp);
        recordSave();
        clear();
        printf("�Һųɹ��������ǣ�%d\n",temp->id);
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
    int i = recordGetByUser();
    if(i==-1)
        return;
    SetConsoleTitle("���");
    record *temp = listGet(records,i);
    node *checks = temp->data_check;
    temp->registeredOnly = false;
    int select=0;
    int total0 = recordGetPriceOfCheck(i);
    while(select!=3)
    {
        clear();
        if(listSize(checks))
            printf("\n%-12s %-12s %-12s\n","���","����","�۸�");
        for(i=0; i<listSize(checks); i++)
        {
            record_check *check=listGet(checks,i);
            printf("%-12d %-12s %-12d\n",i,check->name,check->price);
        }

        switch(select)
        {
        case 1:
        {
            record_check *check = (record_check*)malloc(sizeof(record_check));
            printf("\n�����������ƣ�");
            scanf("%s",check->name);
            printf("��������۸�");
            scanf("%d",&check->price);
            listAddLast(checks,check);
            select = 0;
        }
        break;
        case 2:
            printf("\n������Ҫɾ������ţ�");
            scanf("%d",&select);
            listRemove(checks,select);
            select = 0;
            break;
        default:
            printf("\n������1.���Ӽ�¼ 2.ɾ����¼ 3.ȷ�ϱ���\n\n��ѡ��");
            scanf("%d",&select);
        }
    }

    //������仯
    int d_total = recordGetPriceOfCheck(i)-total0;
    temp->Bill_check+=d_total;
    turnover_check+=d_total;
    turnover_all+=d_total;

    recordSave();
}

void medicine()
{
    int i = recordGetByUser();
    if(i==-1)
        return;
    SetConsoleTitle("��ҩ");
    record *temp = listGet(records,i);
    node *medicines = temp->data_medicine;
    temp->registeredOnly = false;
    int select=0;
    int total0 = recordGetPriceOfMedicine(i);
    while(select!=3)
    {
        clear();
        if(listSize(medicines))
            printf("\n%-12s %-12s %-12s %-12s %-12s\n","���","����","����","����","�ܼ�");
        for(i=0; i<listSize(medicines); i++)
        {
            record_medicine *medicine=listGet(medicines,i);
            printf("%-12d %-12s %-12d %-12d %-12d\n",i,medicine->name,medicine->num,medicine->price,medicine->num*medicine->price);
        }
        printf("�ϼƣ�%d",recordGetPriceOfMedicine(i));

        switch(select)
        {
        case 1:
        {
            record_medicine *medicine = (record_medicine*)malloc(sizeof(record_medicine));
            printf("\n������ҩƷ���ƣ�");
            scanf("%s",medicine->name);
            printf("������ҩƷ���ۣ�");
            scanf("%d",&medicine->price);
            printf("������ҩƷ������");
            scanf("%d",&medicine->num);
            listAddLast(medicines,medicine);
            select = 0;
        }
        break;
        case 2:
            printf("\n������Ҫɾ������ţ�");
            scanf("%d",&select);
            listRemove(medicines,select);
            select = 0;
            break;
        default:
            printf("\n������1.���Ӽ�¼ 2.ɾ����¼ 3.ȷ�ϱ���\n\n��ѡ��");
            scanf("%d",&select);
        }
    }

    //������仯
    int d_total = recordGetPriceOfMedicine(i)-total0;
    temp->Bill_medicine+=d_total;
    turnover_medicine+=d_total;
    turnover_all+=d_total;
    recordSave();
}

//��ȡʣ��Ѻ��
int getOverDeposit(int index){
    record *temp = listGet(records,i);

    //���뿪ʼסԺ�Ѿ���ȥ������
    int pastDays = dayCount(nowTime) - dayCount(temp->data_hospitalized.startTime)

    //�����8�㣬������һ��ķ���
    if(temp->data_hospitalized.startTime.hour>=8)
        pastDays++;

    //ʣ��Ѻ��Ϊ���ɵ�Ѻ���ȥÿ���סԺ����
    return temp->data_hospitalized.deposit-pastDays*200;

}

void hospitalized()
{
    timeFlush();
    int i = recordGetByUser();
    if(i==-1)
        return;
    SetConsoleTitle("סԺ");
    record *temp = listGet(records,i);
    if(temp->data_hospitalized.startTime.year==0)
    {
        time tempTime;
        printf("סԺ�Ǽ�\n");
        printf("��ʼסԺʱ�䣺%d/%d/%d %d:%d",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
        printf("������Ԥ�Ƴ�Ժʱ��\n");
        tempTime.year=2020;
        printf("�£�");
        scanf("%d",&tempTime.month);
        printf("�գ�");
        scanf("%d",&tempTime.day);
        printf("ʱ��");
        scanf("%d",&tempTime.hour);
        printf("�֣�");
        scanf("%d",&tempTime.minute);
        clear();

        printf("��ʼסԺʱ�䣺%d/%d/%d %d:%d\n",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
        printf("Ԥ�Ƴ�Ժʱ�䣺%d/%d/%d %d:%d",tempTime.year,tempTime.month,tempTime.day,tempTime.hour,tempTime.minute);
        int days=dayCount(tempTime)-dayCount(nowTime);
        int deposit=1000+days*200;
        printf("��Ҫ����Ѻ��1000 + Ԥ��סԺ���� X 200����%d",deposit);

        printf("\n������yȷ�Ͽ�ʼסԺ��Ĭ��Ϊn����");
        if(getchar()=='y')
        {
            temp->data_hospitalized.startTime=nowTime;
            temp->data_hospitalized.deposit=deposit;
            clear();
            printf("ȷ�ϳɹ���");
            system("pause");
        }
        else
        {
            clear();
            printf("������ȡ����");
            system("pause");
        }
    }
    else
    {
        switch(selector(2,"����Ѻ��","��Ժ�Ǽ�",NULL,NULL)){
        case 1:
            break;
        case 2:
            break;
        }
    }
    recordSave();
}

void recordList()
{
    clear();
    printf("%-10s %-12s %-12s %-12s\n","�Һ�","����","����","ҽ��");
    for(int i=0; i<listSize(records); i++)
    {
        record *temp=listGet(records,i);
        patient *temp2=listGet(patients,patientGetById(temp->patientId));
        docter *temp3=listGet(docters,docterGetById(temp->docterId));
        printf("%-10d %-12s %-12s %-12s",temp->id,temp2->name,getDepartment(temp3->department),temp3->name);
        printf("\n");
    }
    system("pause");
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
