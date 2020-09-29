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
        fprintf(fp, "%d %s %d %d %d %d %d ",temp->id,temp->patientId,temp->docterId,temp->registeredOnly,temp->bill_check,temp->bill_medicine,temp->bill_hospitalized);
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
        fprintf(fp,"\n");
    }
    fclose(fp);
    hospitalSave();
    patientSave();
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
    while(fscanf(fp, "%d %s %d %d %d %d %d ",&temp->id,temp->patientId,&temp->docterId,(int*)&temp->registeredOnly,&temp->bill_check,&temp->bill_medicine,&temp->bill_hospitalized)==7)
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
        temp=(record*)malloc(sizeof(record));
    }
    free(temp);
    fclose(fp);
}

//��¼�����仯
void recordChangeCheck(int index,int money)
{
    record *temp = listGet(records,index);
    patient *temp2 = listGet(patients,patientGetById(temp->patientId));

    temp->bill_check+=money;
    temp2->bill_check+=money;
    temp2->bill_all+=money;
    turnover_all+=money;
    turnover_check+=money;
}

//��¼ҩ����仯
void recordChangeMedicine(int index,int money)
{
    record *temp = listGet(records,index);
    patient *temp2 = listGet(patients,patientGetById(temp->patientId));

    temp->bill_medicine+=money;
    temp2->bill_medicine+=money;
    temp2->bill_all+=money;
    turnover_all+=money;
    turnover_medicine+=money;
}

//��¼סԺ���仯
void recordChangeHospitalized(int index,int money)
{
    record *temp = listGet(records,index);
    patient *temp2 = listGet(patients,patientGetById(temp->patientId));

    temp->bill_hospitalized+=money;
    temp2->bill_hospitalized+=money;
    temp2->bill_all+=money;
    turnover_all+=money;
    turnover_hospitalized+=money;
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

//��ȡ�Һ�ҩ������������Ϊ�ҺŴ�������
int recordGetCountOfMedicine(int index)
{
    record *temp = listGet(records,index);
    node *medicines = temp->data_medicine;
    int i,total=0;
    for(i=0; i<listSize(medicines); i++)
    {
        record_medicine *medicine=listGet(medicines,i);
        total+=medicine->num;
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

bool recordRemove(int index,bool refund)
{
    record *temp=listGet(records,index);
    if(temp==NULL)
    {
        return false;
    }
    if(refund)
    {
        recordChangeCheck(index,-temp->bill_check);
        recordChangeMedicine(index,-temp->bill_medicine);
        recordChangeHospitalized(index,-temp->bill_hospitalized);
    }
    listDelete(temp->data_check);
    listDelete(temp->data_medicine);
    listRemove(records,index);
    recordSave();
    return true;
}

int recordGetByUser()
{
    int id,i;
    clear();
    printf("\n  ������Һţ�");
    scanf("%d",&id);
    i = recordGetById(id);
    if(i==-1)
    {
        clear();
        printf("\n  δ�ҵ��ùҺţ�");
        system("pause");
        return -1;
    }
    return i;
}

void recordRegister()
{
    int t1=0,t2=0;
    timeFlush();
    //������ҽԺ�Ƿ�Һų���500
    for(int i=0; i<listSize(records); i++)
    {
        record *t=listGet(records,i);
        if(t->dateTime.day==nowTime.day)
            t1++;
    }
    if(t1>=500)
    {
        printf("\n  ����ҽԺ����Һ��������޷��Һţ�");
        system("pause");
        return;
    }

    //��ʼѡ����
    int pi = patientSelector(true);
    if(pi==-1)
        return;
    patient *p = listGet(patients,pi);

    //��黼���Ƿ�Һų���5��
    t1=0;
    for(int i=0; i<listSize(records); i++)
    {
        record *t=listGet(records,i);
        if(t->dateTime.day==nowTime.day && strcmp(t->patientId,p->id)==0)
            t1++;
    }
    if(t1>=5)
    {
        printf("\n  ���߽����Ѿ��Һ�5�����޷��ٹҺţ�");
        system("pause");
        return;
    }

    //��ʼѡ��ҽ��
    int di = docterSelector();
    if(di==-1)
        return;
    docter *d = listGet(docters,di);


    //��黼���Ƿ���ͬһ���ҹҹ��ţ�ҽ���Һ��Ƿ�ﵽ20
    for(int i=0; i<listSize(records); i++)
    {
        record *t=listGet(records,i);
        if(t->dateTime.day==nowTime.day && d->id==t->docterId)
            t1++;
        docter *td=listGet(docters,docterGetById(t->docterId));
        if(t->dateTime.day==nowTime.day && strcmp(t->patientId,p->id)==0 && td->department==d->department)
            t2++;
    }

    if(t1>=20)
    {
        clear();
        printf("\n  ���ҽ����������ҺŴﵽ20�����޷��ٹҺ�");
        system("pause");
        return;
    }
    if(t2>=1)
    {
        clear();
        printf("\n  ���߽����Ѿ���������ҹҹ��ţ��޷��ٹҺţ�");
        system("pause");
        return;
    }
    if(!(1<<weekCount(nowTime) & d->visitTime))
    {
        clear();
        printf("\n  ���ҽ�����첻����޷��Һ�");
        system("pause");
        return;
    }


    SetConsoleTitle("�½��Һ�");
    printf("\n  ���ߣ�%s\n  ���ң�%s\n  ҽ����%s\n",p->name,getDepartment(d->department),d->name);
    printf("\n  ������yȷ�ϹҺţ�Ĭ��Ϊn����");
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
        temp->dateTime=nowTime;
        listAddLast(records,temp);
        recordSave();
        clear();
        printf("\n  �Һųɹ��������ǣ�%d\n\n  ",temp->id);
        system("pause");
    }
    else
    {
        clear();
        printf("\n  ������ȡ����");
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
            printf("\n  %-12s %-12s %-12s\n","���","����","�۸�Ԫ��");
        for(int i=0; i<listSize(checks); i++)
        {
            record_check *check=listGet(checks,i);
            printf("  %-12d %-12s %-12.2f\n",i,check->name,check->price/100.0);
        }
        printf("\n  �ϼƣ�%.2fԪ",recordGetPriceOfCheck(i)/100.0);
        switch(select)
        {
        case 1:
        {
            select = 0;
            record_check *check = (record_check*)malloc(sizeof(record_check));
            printf("\n\n  �����������ƣ�");
            scanf("%s",check->name);
            printf("  ��������۸�Ԫ����");
            float price;
            scanf("%f",&price);
            check->price = price*100;
            if(recordGetPriceOfCheck(i)+check->price>10*10000*100)
            {
                printf("\n  ����ܼ۲��ܳ���10��");
                system("pause");
                continue;
            }

            listAddLast(checks,check);

        }
        break;
        case 2:
            select = 0;
            printf("\n\n  ������Ҫɾ������ţ�");
            scanf("%d",&select);
            listRemove(checks,select);
            break;
        default:
            printf("\n\n  ������1.���Ӽ�¼ 2.ɾ����¼ 3.ȷ�ϱ���\n\n  ��ѡ��");
            scanf("%d",&select);
        }
    }

    //������仯
    int d_total = recordGetPriceOfCheck(i)-total0;
    recordChangeCheck(i,d_total);
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
            printf("\n  %-12s %-12s %-12s %-12s %-12s\n","���","����","����","����","�ܼ�");
        for(int i=0; i<listSize(medicines); i++)
        {
            record_medicine *medicine=listGet(medicines,i);
            printf("  %-12d %-12s %-12d %-12.2f %-12.2f\n",i,medicine->name,medicine->num,medicine->price/100.0,medicine->num*medicine->price/100.0);
        }
        printf("\n  �ϼƣ�%.2f Ԫ",recordGetPriceOfMedicine(i)/100.0);

        switch(select)
        {
        case 1:
        {
            select = 0;
            record_medicine *medicine = (record_medicine*)malloc(sizeof(record_medicine));
            printf("\n\n  ������ҩƷ���ƣ�");
            scanf("%s",medicine->name);
            printf("  ������ҩƷ���ۣ�");
            float price;
            scanf("%f",&price);
            medicine->price = price*100;
            printf("  ������ҩƷ������");
            scanf("%d",&medicine->num);
            if(recordGetPriceOfMedicine(i)+medicine->price*medicine->num>10*10000*100)
            {
                printf("\n  ҩƷ�ܼ۲��ܳ���10��");
                system("pause");
                continue;
            }
            if(recordGetCountOfMedicine(i)+medicine->num>100)
            {
                printf("\n  ҩƷ������һ�β��ܳ��� 100 ��");
                system("pause");
                continue;
            }
            listAddLast(medicines,medicine);

        }
        break;
        case 2:
            select = 0;
            printf("\n\n  ������Ҫɾ������ţ�");
            scanf("%d",&select);
            listRemove(medicines,select);
            break;
        default:
            printf("\n\n  ������1.���Ӽ�¼ 2.ɾ����¼ 3.ȷ�ϱ���\n\n  ��ѡ��");
            scanf("%d",&select);
        }
    }

    //������仯
    int d_total = recordGetPriceOfMedicine(i)-total0;
    recordChangeMedicine(i,d_total);
    recordSave();
}

//��ȡסԺ��ȥ������
int getPastDays(int index)
{
    record *temp = listGet(records,index);

    //���뿪ʼסԺ�Ѿ���ȥ������
    int pastDays = dayCount(nowTime) - dayCount(temp->data_hospitalized.startTime);

    //�����8�㣬������һ��ķ���
    if(nowTime.hour>=8)
        pastDays++;

    //ʣ��Ѻ��Ϊ���ɵ�Ѻ���ȥÿ���סԺ����
    return pastDays;
}

//��ȡʣ��Ѻ��
int getOverDeposit(int index)
{
    record *temp = listGet(records,index);
    //ʣ��Ѻ��Ϊ���ɵ�Ѻ���ȥÿ���סԺ����
    return temp->data_hospitalized.deposit-getPastDays(index)*20000;
}

void hospitalized()
{
    timeFlush();
    int i = recordGetByUser();
    if(i==-1)
        return;
    SetConsoleTitle("סԺ");
    record *temp = listGet(records,i);
    patient *p = listGet(patients,patientGetById(temp->patientId));
    if(temp->data_hospitalized.startTime.year==0)
    {
        time tempTime;
        printf("\n  סԺ�Ǽ�\n\n");
        printf("  ��ʼסԺʱ�䣺%d/%d/%d %d:%d",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
        printf("  ������Ԥ�Ƴ�Ժʱ��\n");
        tempTime.year=2020;
        printf("  �£�");
        scanf("%d",&tempTime.month);
        printf("  �գ�");
        scanf("%d",&tempTime.day);
        printf("  ʱ��");
        scanf("%d",&tempTime.hour);
        printf("  �֣�");
        scanf("%d",&tempTime.minute);
        clear();

        if(!timeCheck(tempTime) || dayCount(tempTime)<dayCount(nowTime)+1)
        {
            printf("\n  ʱ���������");
            system("pause");
            return;
        }

        printf("\n  ��ʼסԺʱ�䣺%d/%d/%d %d:%d\n",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
        printf("  Ԥ�Ƴ�Ժʱ�䣺%d/%d/%d %d:%d\n",tempTime.year,tempTime.month,tempTime.day,tempTime.hour,tempTime.minute);
        int days=dayCount(tempTime)-dayCount(nowTime);
        int deposit=100000+days*20000;
        printf("  ��Ҫ����Ѻ��1000 + Ԥ��סԺ���� X 200����%.2f Ԫ",deposit/100.0);

        printf("\n  ������yȷ�Ͽ�ʼסԺ��Ĭ��Ϊn����");
        if(getchar()=='y')
        {
            temp->data_hospitalized.startTime=nowTime;
            temp->data_hospitalized.deposit=deposit;
            p->deposit+=deposit;

            clear();
            printf("\n  סԺ�Ǽǳɹ���");
            system("pause");
        }
        else
        {
            clear();
            printf("\n  ������ȡ����");
            system("pause");
        }
    }
    else if(temp->data_hospitalized.endTime.year==0)
    {
        int select=0,money;
        while(select!=3)
        {
            clear();
            time startTime = temp->data_hospitalized.startTime;
            printf("\n  ��ʼסԺʱ�䣺%d/%d/%d %d:%d\n",startTime.year,startTime.month,startTime.day,startTime.hour,startTime.minute);
            printf("  ��ǰʱ�䣺%d/%d/%d %d:%d\n",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
            printf("  ��ʼѺ��%.2f Ԫ\n",temp->data_hospitalized.deposit/100.0);
            printf("  ʣ��Ѻ��%.2f Ԫ\n\n",getOverDeposit(i)/100.0);
            printf("  1.����Ѻ�� 2.�Ǽǳ�Ժ 3.����\n\n");
            printf("  ��ѡ��");
            scanf("%d",&select);
            if(select==1)
            {
                clear();
                printf("\n  ������Ҫ�����Ѻ�������λ ��Ԫ����");
                scanf("%d",&money);
                clear();
                printf("\n  ����yȷ������Ѻ�� %d Ԫ��Ĭ��Ϊn����",money*100);
                scanf("%c",(char*)&select);
                if(select=='y')
                {
                    temp->data_hospitalized.deposit+=money*10000;
                    p->deposit+=money*10000;
                }
                select =0 ;
            }
            else if(select==2)
            {
                clear();
                if(getOverDeposit(i)<0)
                {
                    printf("\n  ʣ��Ѻ��С��0����Ҫ����Ѻ����ܵǼǳ�Ժ��");
                    system("pause");
                    select=0;
                    continue;
                }
                int od = getOverDeposit(i);
                int used = temp->data_hospitalized.deposit-od;
                printf("\n  סԺ������ %d Ԫ���Ǽǳ�Ժ���˻� %d ԪѺ��\n����yȷ�ϵǼǣ�Ĭ��Ϊn����",used/100,od/100);
                scanf("%c",(char*)&select);
                if(select=='y')
                {
                    recordChangeHospitalized(i,used);
                    p->deposit-=temp->data_hospitalized.deposit;
                    temp->data_hospitalized.deposit=0;
                    temp->data_hospitalized.endTime=nowTime;
                    select = 3;
                }
            }
        }

    }
    else
    {
        printf("\n  �ùҺŻ����Ѿ��Ǽǹ�סԺ�����Ѿ���Ժ��");
        system("pause");
    }
    recordSave();
}

void recordListAll()
{

    clear();
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","�Һ�","����","����","ҽ��","��黨��","��ҩ����","סԺ����","סԺѺ��");
    for(int i=0; i<listSize(records); i++)
    {
        record *temp=listGet(records,i);
        patient *temp2=listGet(patients,patientGetById(temp->patientId));
        docter *temp3=listGet(docters,docterGetById(temp->docterId));
        printf("  %-10d %-12s %-12s %-12s %-12.2f %-12.2f %-12.2f %-12.2f",
               temp->id,temp2->name,getDepartment(temp3->department),temp3->name,
               temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->data_hospitalized.deposit/100.0);
        printf("\n");
    }
    printf("\n  ");
    system("pause");
}

//���տ��Ҳ�ѯ��¼
void recordListByDepartment()
{
    int d=departmentSelector();
    if(d==-1)
    {
        clear();
        printf("\n  δ�ҵ��ÿ��ң�");
        system("pause");
        return;
    }
    clear();
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","�Һ�","����","����","ҽ��","��黨��","��ҩ����","סԺ����","סԺѺ��");
    for(int i=0; i<listSize(records); i++)
    {
        record *temp=listGet(records,i);
        patient *temp2=listGet(patients,patientGetById(temp->patientId));
        docter *temp3=listGet(docters,docterGetById(temp->docterId));
        if(temp3->department!=d)
            continue;
        printf("  %-10d %-12s %-12s %-12s %-12.2f %-12.2f %-12.2f %-12.2f",
               temp->id,temp2->name,getDepartment(temp3->department),temp3->name,
               temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->data_hospitalized.deposit/100.0);
        printf("\n");
    }
    printf("\n  ");
    system("pause");
}

//����ҽ����ѯ��¼
void recordListByDocter()
{
    int di = docterSelector();
    if(di==-1)
        return;
    docter *d = listGet(docters,di);
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","�Һ�","����","����","ҽ��","��黨��","��ҩ����","סԺ����","סԺѺ��");
    for(int i=0; i<listSize(records); i++)
    {
        record *temp=listGet(records,i);
        if(d->id!=temp->docterId)
            continue;
        patient *temp2=listGet(patients,patientGetById(temp->patientId));
        docter *temp3=listGet(docters,docterGetById(temp->docterId));
        printf("  %-10d %-12s %-12s %-12s %-12.2f %-12.2f %-12.2f %-12.2f",
               temp->id,temp2->name,getDepartment(temp3->department),temp3->name,
               temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->data_hospitalized.deposit/100.0);
        printf("\n");
    }
    printf("\n  ");
    system("pause");
}

//���ջ��߲�ѯ��¼
void recordListByPatient()
{
    int pi = patientSelector(false);
    if(pi==-1)
        return;
    patient *p = listGet(patients,pi);
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","�Һ�","����","����","ҽ��","��黨��","��ҩ����","סԺ����","סԺѺ��");
    for(int i=0; i<listSize(records); i++)
    {
        record *temp=listGet(records,i);
        if(strcmp(p->id,temp->patientId))
            continue;
        patient *temp2=listGet(patients,patientGetById(temp->patientId));
        docter *temp3=listGet(docters,docterGetById(temp->docterId));
        printf("  %-10d %-12s %-12s %-12s %-12.2f %-12.2f %-12.2f %-12.2f",
               temp->id,temp2->name,getDepartment(temp3->department),temp3->name,
               temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->data_hospitalized.deposit/100.0);
        printf("\n");
    }
    printf("\n  ");
    system("pause");
}

//����ʱ���ѯ��¼
void recordListByTime()
{
    clear();
    int select = selector(4,"����","����","����ʱ��","����",NULL,NULL,NULL,NULL);
    clear();
    timeFlush();
    time start=nowTime;
    time end=nowTime;
    if(select==4)
    {
        return;
    }
    else if(select==1)
    {
        start.hour=0;
        start.minute=0;
        end.hour=23;
        end.minute=59;
    }
    else if(select==2)
    {
        start.day=0;
        start.hour=0;
        start.minute=0;
        end.hour=23;
        end.minute=59;
        end.day=31;
    }
    else if(select==3)
    {
        time tempTime;
        printf("\n  �����뿪ʼʱ��\n");
        tempTime.year=2020;
        printf("  �£�");
        scanf("%d",&tempTime.month);
        printf("  �գ�");
        scanf("%d",&tempTime.day);
        printf("  ʱ��");
        scanf("%d",&tempTime.hour);
        printf("  �֣�");
        scanf("%d",&tempTime.minute);
        if(!timeCheck(tempTime))
        {
            clear();
            printf("\n  ʱ���������");
            system("pause");
            return;
        }
        start=tempTime;
        printf("\n  ���������ʱ��\n");
        tempTime.year=2020;
        printf("  �£�");
        scanf("%d",&tempTime.month);
        printf("  �գ�");
        scanf("%d",&tempTime.day);
        printf("  ʱ��");
        scanf("%d",&tempTime.hour);
        printf("  �֣�");
        scanf("%d",&tempTime.minute);
        end=tempTime;

        if(!timeCheck(tempTime))
        {
            clear();
            printf("\n  ʱ���������");
            system("pause");
            return;
        }
    }
    clear();
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","�Һ�","����","����","ҽ��","��黨��","��ҩ����","סԺ����","סԺѺ��");
    for(int i=0; i<listSize(records); i++)
    {
        record *temp=listGet(records,i);
        time r=temp->dateTime;

        if(dayCount(r)<dayCount(start) || dayCount(r)>dayCount(end))
            continue;
        if(dayCount(r)==dayCount(start) && (r.hour*60+r.minute < start.hour*60+start.minute || r.hour*60+r.minute > end.hour*60+end.minute))
            continue;

        patient *temp2=listGet(patients,patientGetById(temp->patientId));
        docter *temp3=listGet(docters,docterGetById(temp->docterId));
        printf("  %-10d %-12s %-12s %-12s %-12.2f %-12.2f %-12.2f %-12.2f",
               temp->id,temp2->name,getDepartment(temp3->department),temp3->name,
               temp->bill_check/100.0,temp->bill_medicine/100.0,temp->bill_hospitalized/100.0,temp->data_hospitalized.deposit/100.0);
        printf("\n");
    }
    printf("\n  ");
    system("pause");

}

void hospitalizationStatistics()
{
    clear();
    timeFlush();
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s\n","�Һ�","����","����","ҽ��","��ʼѺ��","ʣ��Ѻ��","סԺ��ʼʱ��");
    for(int i=0; i<listSize(records); i++)
    {
        record *temp=listGet(records,i);
        patient *temp2=listGet(patients,patientGetById(temp->patientId));
        docter *temp3=listGet(docters,docterGetById(temp->docterId));
        record_hospitalized h=temp->data_hospitalized;
        if(h.startTime.year==0 || h.endTime.year!=0)
            continue;
        printf("  %-10d %-12s %-12s %-12s %-12.2f %-12.2f %d/%d/%d %d:%d",
               temp->id,temp2->name,getDepartment(temp3->department),temp3->name,
               h.deposit/100.0,getOverDeposit(i)/100.0,
               h.startTime.year,h.startTime.month,h.startTime.month,h.startTime.hour,h.startTime.minute);
        printf("\n");
    }
    printf("\n  ");
    system("pause");
}

void docterStatistics()
{
    timeFlush();
    SetConsoleTitle("�г�����ҽ��");
    printf("\n  %-10s %-12s %-12s %-12s %-12s\n","����","����","���ճ���","���³���","������");
    for(int i=0; i<listSize(docters); i++)
    {
        docter *temp=listGet(docters,i);
        printf("  %-10d %-12s ",temp->id,temp->name);
        int day=0,mon=0,total=0;
        for(int i=0; i<listSize(records); i++)
        {
            record *t=listGet(records,i);
            docter *d=listGet(docters,docterGetById(t->docterId));
            if(d->id==temp->id)
            {
                if(t->dateTime.day==nowTime.day)
                    day++;
                if(t->dateTime.month==nowTime.month)
                    mon++;
                total++;
            }
        }
        printf("%-12d %-12d %-12d\n",day,mon,total);
    }
    printf("\n  ");
    system("pause");
}

void recordList()
{
    do
    {
        system("cls");
        SetConsoleTitle("��¼��ѯ");
    }
    while(selector(6,"���տ��Ҳ�ѯ","����ҽ����ѯ","���ջ��߲�ѯ","����ʱ���ѯ","�г����м�¼","����",recordListByDepartment,recordListByDocter,recordListByPatient,recordListByTime,recordListAll,NULL)!=6);
}


void recordManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("������Ϣ����");
    }
    while(selector(8,"�½��Һ�","���","��ҩ","סԺ","��¼��ѯ","סԺͳ��","ҽ��ͳ��","����",recordRegister,check,medicine,hospitalized,recordList,hospitalizationStatistics,docterStatistics,NULL)!=8);
}
