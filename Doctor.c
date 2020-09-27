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

void docterAdd()
{
    char comfirm;
    docter *temp=(docter*)malloc(sizeof(docter));
    SetConsoleTitle("增加医生");

    system("cls");
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

    fflush(stdin);
    system("cls");
    printf("请验证信息\n");
    printf("工号：%d\n姓名：%s\n级别：%s\n科室：%s\n",temp->id,temp->name,levels[temp->level],departments[temp->department]);
    printf("请输入y确认（默认为n）：");
    if(getchar()=='y')
    {
        listAddLast(docters,temp);
        system("cls");
        printf("添加成功");
    }
    else
    {
        system("cls");
        printf("操作被取消");
        free(temp);
    }
    Sleep(3000);
}

void docterDelete()
{


}

void docterList()
{
    system("cls");
    for(int i=0; i<listSize(docters); i++)
    {
        docter *temp=listGet(docters,i);
        printf("%-10s %-10s %-10s %-10s\n","工号","姓名","级别","科室");
        printf("%-10d %-10s %-10s %-10s\n",temp->id,temp->name,levels[temp->level],departments[temp->department]);
    }
    printf("\n按任意键返回...");
    fflush(stdin);
    getchar();
}

void docterInfo()
{

}

void docterManage()
{
    do
    {
        system("cls");
        SetConsoleTitle("医生管理");
    }
    while(selector(5,"增加医生","删除医生","列出所有医生","查询医生信息","返回",docterAdd,docterDelete,docterList,docterInfo,NULL)!=5);
}
