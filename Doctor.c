#include "Doctor.h"
#include "stdlib.h"
#include "stdio.h"
#include "windows.h"

//级别
const char *levels[4]= {"主任医师","副主任医师","主治医师","住院医师"};

//科室
const char *departments[27]= {"内科","外科","儿科","妇科","眼科","耳鼻喉科","口腔科","皮肤科","中医科","针灸推拿科",
                              "呼吸内科","消化内科","泌尿内科","心内科","血液科","内分泌科","神经内科","小儿科","感染科",
                              "普外科","骨科","神经外科","肝胆外科","泌尿外科","烧伤科","妇科","产科"
                             };

void docterSave()
{
    FILE *fp=fopen("docters.dat", "w+");
    for(int i=0; i<listSize(docters); i++)
    {
        docter *temp=listGet(docters,i);
        fprintf(fp, "%d %s %d %d %d\n",temp->id,temp->name,temp->level,temp->department,temp->visitTime);
    }
    fclose(fp);
}

void docterRead()
{
    FILE *fp=fopen("docters.dat", "r");
    if(!fp)
    {
        return;
    }
    docter *temp=(docter*)malloc(sizeof(docter));
    while(fscanf(fp,"%d %s %d %d %d\n",&temp->id,temp->name,&temp->level,&temp->department,&temp->visitTime)==5)
    {
        listAddLast(docters,temp);
        temp=(docter*)malloc(sizeof(docter));
    }
    free(temp);
    fclose(fp);
}

void printVisitTime(int t)
{
    if(t & Mon)
        printf("周一 ");
    if(t & Tue)
        printf("周二 ");
    if(t & Wed)
        printf("周三 ");
    if(t & Thur)
        printf("周四 ");
    if(t & Fri)
        printf("周五 ");
    if(t & Sat)
        printf("周六 ");
    if(t & Sun)
        printf("周日 ");
}

char* getLevel(int i)
{
    if(i>=0 && i<sizeof(levels)/sizeof(char*))
        return levels[i];
    return "未知";
}

char* getDepartment(int i)
{
    if(i>=0 && i<sizeof(departments)/sizeof(char*))
        return departments[i];
    return "未知";
}

void docterAdd()
{
    char comfirm;
    docter *temp=(docter*)malloc(sizeof(docter));
    SetConsoleTitle("增加医生");

    clear();
    printf("请输入信息\n");

    printf("请输入工号：");
    scanf("%d",&temp->id);

    printf("请输入姓名：");
    scanf("%s",&temp->name);

    for(int i=0; i<sizeof(levels)/sizeof(char*); i++)
        printf("%d.%s ",i,levels[i]);
    printf("\n请选择级别：");
    scanf("%d",&temp->level);

    for(int i=0; i<sizeof(departments)/sizeof(char*); i++)
        printf("%d.%s ",i,departments[i]);
    printf("\n请选择科室：");
    scanf("%d",&temp->department);

    printf("请输入出诊时间（格式如1234567）：");
    int time;
    temp->visitTime=0;
    scanf("%d",&time);
    while(time)
    {
        if(time%10 >=1 && time%10<=7)
            temp->visitTime|=1<<(time%10);
        time/=10;
    }

    clear();
    printf("请验证信息\n");
    printf("工号：%d\n姓名：%s\n级别：%s\n科室：%s\n出诊时间：",temp->id,temp->name,getLevel(temp->level),getDepartment(temp->department));
    printVisitTime(temp->visitTime);

    printf("\n请输入y确认添加（默认为n）：");
    if(getchar()=='y')
    {
        listAddLast(docters,temp);
        docterSave();
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

void docterDelete()
{
    int id,i;
    docter *temp;
    printf("请输入工号进行查询：");
    scanf("%d",&id);
    for(i=0; i<listSize(docters); i++)
    {
        temp=listGet(docters,i);
        if(temp->id==id)
            break;
    }
    if(i==listSize(docters))
    {
        clear();
        printf("未找到该医生，");
        system("pause");
    }
    else
    {
        printf("请验证信息\n");
        printf("工号：%d\n姓名：%s\n级别：%s\n科室：%s\n出诊时间：",temp->id,temp->name,getLevel(temp->level),getDepartment(temp->department));
        printVisitTime(temp->visitTime);

        printf("\n请输入y确认删除（默认为n）：");
        if(getchar()=='y')
        {
            listRemove(docters,i);
            docterSave();
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

void docterList()
{
    clear();
    printf("%-10s %-12s %-12s %-12s%s\n","工号","姓名","级别","科室","出诊时间");
    for(int i=0; i<listSize(docters); i++)
    {
        docter *temp=listGet(docters,i);
        printf("%-10d %-12s %-12s %-12s",temp->id,temp->name,getLevel(temp->level),getDepartment(temp->department));
        printVisitTime(temp->visitTime);
        printf("\n");
    }
    system("pause");
}

void docterInfo()
{

}

void docterManage()
{
    do
    {
        clear();
        SetConsoleTitle("医生管理");
    }
    while(selector(5,"增加医生","删除医生","列出所有医生","查询医生信息","返回",docterAdd,docterDelete,docterList,docterInfo,NULL)!=5);
}
