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

//记录检查金额变化
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

//记录药物金额变化
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

//记录住院金额变化
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


//获取挂号检查总价，参数为挂号储存索引
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

//获取挂号药物总价，参数为挂号储存索引
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

//获取挂号药物数量，参数为挂号储存索引
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
    printf("\n  请输入挂号：");
    scanf("%d",&id);
    i = recordGetById(id);
    if(i==-1)
    {
        clear();
        printf("\n  未找到该挂号，");
        system("pause");
        return -1;
    }
    return i;
}

void recordRegister()
{
    int t1=0,t2=0;
    timeFlush();
    //检查今天医院是否挂号超过500
    for(int i=0; i<listSize(records); i++)
    {
        record *t=listGet(records,i);
        if(t->dateTime.day==nowTime.day)
            t1++;
    }
    if(t1>=500)
    {
        printf("\n  今天医院受理挂号已满，无法挂号，");
        system("pause");
        return;
    }

    //开始选择患者
    int pi = patientSelector(true);
    if(pi==-1)
        return;
    patient *p = listGet(patients,pi);

    //检查患者是否挂号超过5个
    t1=0;
    for(int i=0; i<listSize(records); i++)
    {
        record *t=listGet(records,i);
        if(t->dateTime.day==nowTime.day && strcmp(t->patientId,p->id)==0)
            t1++;
    }
    if(t1>=5)
    {
        printf("\n  患者今天已经挂号5个，无法再挂号，");
        system("pause");
        return;
    }

    //开始选择医生
    int di = docterSelector();
    if(di==-1)
        return;
    docter *d = listGet(docters,di);


    //检查患者是否在同一科室挂过号，医生挂号是否达到20
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
        printf("\n  这个医生今天受理挂号达到20个，无法再挂号");
        system("pause");
        return;
    }
    if(t2>=1)
    {
        clear();
        printf("\n  患者今天已经在这个科室挂过号，无法再挂号，");
        system("pause");
        return;
    }
    if(!(1<<weekCount(nowTime) & d->visitTime))
    {
        clear();
        printf("\n  这个医生今天不出诊，无法挂号");
        system("pause");
        return;
    }


    SetConsoleTitle("新建挂号");
    printf("\n  患者：%s\n  科室：%s\n  医生：%s\n",p->name,getDepartment(d->department),d->name);
    printf("\n  请输入y确认挂号（默认为n）：");
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
        printf("\n  挂号成功，号码是：%d\n\n  ",temp->id);
        system("pause");
    }
    else
    {
        clear();
        printf("\n  操作被取消，");
        system("pause");
    }
}

void check()
{
    int i = recordGetByUser();
    if(i==-1)
        return;
    SetConsoleTitle("检查");
    record *temp = listGet(records,i);
    node *checks = temp->data_check;
    temp->registeredOnly = false;
    int select=0;
    int total0 = recordGetPriceOfCheck(i);
    while(select!=3)
    {
        clear();
        if(listSize(checks))
            printf("\n  %-12s %-12s %-12s\n","序号","名称","价格（元）");
        for(int i=0; i<listSize(checks); i++)
        {
            record_check *check=listGet(checks,i);
            printf("  %-12d %-12s %-12.2f\n",i,check->name,check->price/100.0);
        }
        printf("\n  合计：%.2f元",recordGetPriceOfCheck(i)/100.0);
        switch(select)
        {
        case 1:
        {
            select = 0;
            record_check *check = (record_check*)malloc(sizeof(record_check));
            printf("\n\n  请输入检查名称：");
            scanf("%s",check->name);
            printf("  请输入检查价格（元）：");
            float price;
            scanf("%f",&price);
            check->price = price*100;
            if(recordGetPriceOfCheck(i)+check->price>10*10000*100)
            {
                printf("\n  检查总价不能超过10万，");
                system("pause");
                continue;
            }

            listAddLast(checks,check);

        }
        break;
        case 2:
            select = 0;
            printf("\n\n  请输入要删除的序号：");
            scanf("%d",&select);
            listRemove(checks,select);
            break;
        default:
            printf("\n\n  操作：1.增加记录 2.删除记录 3.确认保存\n\n  请选择：");
            scanf("%d",&select);
        }
    }

    //处理金额变化
    int d_total = recordGetPriceOfCheck(i)-total0;
    recordChangeCheck(i,d_total);
    recordSave();
}

void medicine()
{
    int i = recordGetByUser();
    if(i==-1)
        return;
    SetConsoleTitle("开药");
    record *temp = listGet(records,i);
    node *medicines = temp->data_medicine;
    temp->registeredOnly = false;
    int select=0;
    int total0 = recordGetPriceOfMedicine(i);
    while(select!=3)
    {
        clear();
        if(listSize(medicines))
            printf("\n  %-12s %-12s %-12s %-12s %-12s\n","序号","名称","数量","单价","总价");
        for(int i=0; i<listSize(medicines); i++)
        {
            record_medicine *medicine=listGet(medicines,i);
            printf("  %-12d %-12s %-12d %-12.2f %-12.2f\n",i,medicine->name,medicine->num,medicine->price/100.0,medicine->num*medicine->price/100.0);
        }
        printf("\n  合计：%.2f 元",recordGetPriceOfMedicine(i)/100.0);

        switch(select)
        {
        case 1:
        {
            select = 0;
            record_medicine *medicine = (record_medicine*)malloc(sizeof(record_medicine));
            printf("\n\n  请输入药品名称：");
            scanf("%s",medicine->name);
            printf("  请输入药品单价：");
            float price;
            scanf("%f",&price);
            medicine->price = price*100;
            printf("  请输入药品数量：");
            scanf("%d",&medicine->num);
            if(recordGetPriceOfMedicine(i)+medicine->price*medicine->num>10*10000*100)
            {
                printf("\n  药品总价不能超过10万，");
                system("pause");
                continue;
            }
            if(recordGetCountOfMedicine(i)+medicine->num>100)
            {
                printf("\n  药品总数量一次不能超过 100 ，");
                system("pause");
                continue;
            }
            listAddLast(medicines,medicine);

        }
        break;
        case 2:
            select = 0;
            printf("\n\n  请输入要删除的序号：");
            scanf("%d",&select);
            listRemove(medicines,select);
            break;
        default:
            printf("\n\n  操作：1.增加记录 2.删除记录 3.确认保存\n\n  请选择：");
            scanf("%d",&select);
        }
    }

    //处理金额变化
    int d_total = recordGetPriceOfMedicine(i)-total0;
    recordChangeMedicine(i,d_total);
    recordSave();
}

//获取住院过去的天数
int getPastDays(int index)
{
    record *temp = listGet(records,index);

    //距离开始住院已经过去的天数
    int pastDays = dayCount(nowTime) - dayCount(temp->data_hospitalized.startTime);

    //如果过8点，则多加这一天的费用
    if(nowTime.hour>=8)
        pastDays++;

    //剩余押金为缴纳的押金减去每天的住院花费
    return pastDays;
}

//获取剩余押金
int getOverDeposit(int index)
{
    record *temp = listGet(records,index);
    //剩余押金为缴纳的押金减去每天的住院花费
    return temp->data_hospitalized.deposit-getPastDays(index)*20000;
}

void hospitalized()
{
    timeFlush();
    int i = recordGetByUser();
    if(i==-1)
        return;
    SetConsoleTitle("住院");
    record *temp = listGet(records,i);
    patient *p = listGet(patients,patientGetById(temp->patientId));
    if(temp->data_hospitalized.startTime.year==0)
    {
        time tempTime;
        printf("\n  住院登记\n\n");
        printf("  开始住院时间：%d/%d/%d %d:%d",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
        printf("  请输入预计出院时间\n");
        tempTime.year=2020;
        printf("  月：");
        scanf("%d",&tempTime.month);
        printf("  日：");
        scanf("%d",&tempTime.day);
        printf("  时：");
        scanf("%d",&tempTime.hour);
        printf("  分：");
        scanf("%d",&tempTime.minute);
        clear();

        if(!timeCheck(tempTime) || dayCount(tempTime)<dayCount(nowTime)+1)
        {
            printf("\n  时间输入错误，");
            system("pause");
            return;
        }

        printf("\n  开始住院时间：%d/%d/%d %d:%d\n",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
        printf("  预计出院时间：%d/%d/%d %d:%d\n",tempTime.year,tempTime.month,tempTime.day,tempTime.hour,tempTime.minute);
        int days=dayCount(tempTime)-dayCount(nowTime);
        int deposit=100000+days*20000;
        printf("  需要缴纳押金（1000 + 预计住院天数 X 200）：%.2f 元",deposit/100.0);

        printf("\n  请输入y确认开始住院（默认为n）：");
        if(getchar()=='y')
        {
            temp->data_hospitalized.startTime=nowTime;
            temp->data_hospitalized.deposit=deposit;
            p->deposit+=deposit;

            clear();
            printf("\n  住院登记成功，");
            system("pause");
        }
        else
        {
            clear();
            printf("\n  操作被取消，");
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
            printf("\n  开始住院时间：%d/%d/%d %d:%d\n",startTime.year,startTime.month,startTime.day,startTime.hour,startTime.minute);
            printf("  当前时间：%d/%d/%d %d:%d\n",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
            printf("  初始押金：%.2f 元\n",temp->data_hospitalized.deposit/100.0);
            printf("  剩余押金：%.2f 元\n\n",getOverDeposit(i)/100.0);
            printf("  1.补充押金 2.登记出院 3.返回\n\n");
            printf("  请选择：");
            scanf("%d",&select);
            if(select==1)
            {
                clear();
                printf("\n  请输入要补充的押金数额（单位 百元）：");
                scanf("%d",&money);
                clear();
                printf("\n  输入y确认增加押金 %d 元（默认为n）：",money*100);
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
                    printf("\n  剩余押金小于0，需要补充押金才能登记出院，");
                    system("pause");
                    select=0;
                    continue;
                }
                int od = getOverDeposit(i);
                int used = temp->data_hospitalized.deposit-od;
                printf("\n  住院共花费 %d 元，登记出院将退还 %d 元押金\n输入y确认登记（默认为n）：",used/100,od/100);
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
        printf("\n  该挂号患者已经登记过住院并且已经出院，");
        system("pause");
    }
    recordSave();
}

void recordListAll()
{

    clear();
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","挂号","姓名","科室","医生","检查花费","开药花费","住院花费","住院押金");
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

//按照科室查询记录
void recordListByDepartment()
{
    int d=departmentSelector();
    if(d==-1)
    {
        clear();
        printf("\n  未找到该科室，");
        system("pause");
        return;
    }
    clear();
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","挂号","姓名","科室","医生","检查花费","开药花费","住院花费","住院押金");
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

//按照医生查询记录
void recordListByDocter()
{
    int di = docterSelector();
    if(di==-1)
        return;
    docter *d = listGet(docters,di);
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","挂号","姓名","科室","医生","检查花费","开药花费","住院花费","住院押金");
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

//按照患者查询记录
void recordListByPatient()
{
    int pi = patientSelector(false);
    if(pi==-1)
        return;
    patient *p = listGet(patients,pi);
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","挂号","姓名","科室","医生","检查花费","开药花费","住院花费","住院押金");
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

//按照时间查询记录
void recordListByTime()
{
    clear();
    int select = selector(4,"今天","本月","输入时间","返回",NULL,NULL,NULL,NULL);
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
        printf("\n  请输入开始时间\n");
        tempTime.year=2020;
        printf("  月：");
        scanf("%d",&tempTime.month);
        printf("  日：");
        scanf("%d",&tempTime.day);
        printf("  时：");
        scanf("%d",&tempTime.hour);
        printf("  分：");
        scanf("%d",&tempTime.minute);
        if(!timeCheck(tempTime))
        {
            clear();
            printf("\n  时间输入错误，");
            system("pause");
            return;
        }
        start=tempTime;
        printf("\n  请输入结束时间\n");
        tempTime.year=2020;
        printf("  月：");
        scanf("%d",&tempTime.month);
        printf("  日：");
        scanf("%d",&tempTime.day);
        printf("  时：");
        scanf("%d",&tempTime.hour);
        printf("  分：");
        scanf("%d",&tempTime.minute);
        end=tempTime;

        if(!timeCheck(tempTime))
        {
            clear();
            printf("\n  时间输入错误，");
            system("pause");
            return;
        }
    }
    clear();
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","挂号","姓名","科室","医生","检查花费","开药花费","住院花费","住院押金");
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
    printf("\n  %-10s %-12s %-12s %-12s %-12s %-12s %-12s\n","挂号","姓名","科室","医生","初始押金","剩余押金","住院开始时间");
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
    SetConsoleTitle("列出所有医生");
    printf("\n  %-10s %-12s %-12s %-12s %-12s\n","工号","姓名","今日出诊","本月出诊","共出诊");
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
        SetConsoleTitle("记录查询");
    }
    while(selector(6,"按照科室查询","按照医生查询","按照患者查询","按照时间查询","列出所有记录","返回",recordListByDepartment,recordListByDocter,recordListByPatient,recordListByTime,recordListAll,NULL)!=6);
}


void recordManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("诊疗信息管理");
    }
    while(selector(8,"新建挂号","检查","开药","住院","记录查询","住院统计","医生统计","返回",recordRegister,check,medicine,hospitalized,recordList,hospitalizationStatistics,docterStatistics,NULL)!=8);
}
