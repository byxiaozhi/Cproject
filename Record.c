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
    printf("请输入挂号：");
    scanf("%d",&id);
    i = recordGetById(id);
    if(i==-1)
    {
        clear();
        printf("未找到该挂号，");
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
    SetConsoleTitle("新建挂号");
    printf("\n  患者：%s\n  科室：%s\n  医生：%s\n",p->name,getDepartment(d->department),d->name);
    printf("\n请输入y确认挂号（默认为n）：");
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
        printf("挂号成功，号码是：%d\n",temp->id);
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
            printf("\n%-12s %-12s %-12s\n","序号","名称","价格");
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
            printf("\n请输入检查名称：");
            scanf("%s",check->name);
            printf("请输入检查价格：");
            scanf("%d",&check->price);
            listAddLast(checks,check);
            select = 0;
        }
        break;
        case 2:
            printf("\n请输入要删除的序号：");
            scanf("%d",&select);
            listRemove(checks,select);
            select = 0;
            break;
        default:
            printf("\n操作：1.增加记录 2.删除记录 3.确认保存\n\n请选择：");
            scanf("%d",&select);
        }
    }

    //处理金额变化
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
            printf("\n%-12s %-12s %-12s %-12s %-12s\n","序号","名称","数量","单价","总价");
        for(i=0; i<listSize(medicines); i++)
        {
            record_medicine *medicine=listGet(medicines,i);
            printf("%-12d %-12s %-12d %-12d %-12d\n",i,medicine->name,medicine->num,medicine->price,medicine->num*medicine->price);
        }
        printf("合计：%d",recordGetPriceOfMedicine(i));

        switch(select)
        {
        case 1:
        {
            record_medicine *medicine = (record_medicine*)malloc(sizeof(record_medicine));
            printf("\n请输入药品名称：");
            scanf("%s",medicine->name);
            printf("请输入药品单价：");
            scanf("%d",&medicine->price);
            printf("请输入药品数量：");
            scanf("%d",&medicine->num);
            listAddLast(medicines,medicine);
            select = 0;
        }
        break;
        case 2:
            printf("\n请输入要删除的序号：");
            scanf("%d",&select);
            listRemove(medicines,select);
            select = 0;
            break;
        default:
            printf("\n操作：1.增加记录 2.删除记录 3.确认保存\n\n请选择：");
            scanf("%d",&select);
        }
    }

    //处理金额变化
    int d_total = recordGetPriceOfMedicine(i)-total0;
    temp->Bill_medicine+=d_total;
    turnover_medicine+=d_total;
    turnover_all+=d_total;
    recordSave();
}

//获取剩余押金
int getOverDeposit(int index){
    record *temp = listGet(records,i);

    //距离开始住院已经过去的天数
    int pastDays = dayCount(nowTime) - dayCount(temp->data_hospitalized.startTime)

    //如果过8点，则多加这一天的费用
    if(temp->data_hospitalized.startTime.hour>=8)
        pastDays++;

    //剩余押金为缴纳的押金减去每天的住院花费
    return temp->data_hospitalized.deposit-pastDays*200;

}

void hospitalized()
{
    timeFlush();
    int i = recordGetByUser();
    if(i==-1)
        return;
    SetConsoleTitle("住院");
    record *temp = listGet(records,i);
    if(temp->data_hospitalized.startTime.year==0)
    {
        time tempTime;
        printf("住院登记\n");
        printf("开始住院时间：%d/%d/%d %d:%d",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
        printf("请输入预计出院时间\n");
        tempTime.year=2020;
        printf("月：");
        scanf("%d",&tempTime.month);
        printf("日：");
        scanf("%d",&tempTime.day);
        printf("时：");
        scanf("%d",&tempTime.hour);
        printf("分：");
        scanf("%d",&tempTime.minute);
        clear();

        printf("开始住院时间：%d/%d/%d %d:%d\n",nowTime.year,nowTime.month,nowTime.day,nowTime.hour,nowTime.minute);
        printf("预计出院时间：%d/%d/%d %d:%d",tempTime.year,tempTime.month,tempTime.day,tempTime.hour,tempTime.minute);
        int days=dayCount(tempTime)-dayCount(nowTime);
        int deposit=1000+days*200;
        printf("需要缴纳押金（1000 + 预计住院天数 X 200）：%d",deposit);

        printf("\n请输入y确认开始住院（默认为n）：");
        if(getchar()=='y')
        {
            temp->data_hospitalized.startTime=nowTime;
            temp->data_hospitalized.deposit=deposit;
            clear();
            printf("确认成功，");
            system("pause");
        }
        else
        {
            clear();
            printf("操作被取消，");
            system("pause");
        }
    }
    else
    {
        switch(selector(2,"增加押金","出院登记",NULL,NULL)){
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
    printf("%-10s %-12s %-12s %-12s\n","挂号","姓名","科室","医生");
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
        SetConsoleTitle("诊疗信息管理");
    }
    while(selector(6,"新建挂号","检查","开药","住院","记录查询","返回",recordRegister,check,medicine,hospitalized,recordList,NULL)!=6);
}
