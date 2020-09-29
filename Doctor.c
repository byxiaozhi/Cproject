#include "Doctor.h"
#include "stdlib.h"
#include "stdio.h"
#include "windows.h"

void recordListByDocter();
//����
const char *levels[4]= {"����ҽʦ","������ҽʦ","����ҽʦ","סԺҽʦ"};

//����
const char *departments[27]= {"�ڿ�","���","����","����","�ۿ�","���Ǻ��","��ǻ��","Ƥ����","��ҽ��","������ÿ�",
                              "�����ڿ�","�����ڿ�","�����ڿ�","���ڿ�","ѪҺ��","�ڷ��ڿ�","���ڿ�","С����","��Ⱦ��",
                              "�����","�ǿ�","�����","�ε����","�������","���˿�","����","����"
                             };

void docterSave()
{
    FILE *fp=fopen("docters.txt", "w+");
    for(int i=0; i<listSize(docters); i++)
    {
        docter *temp=listGet(docters,i);
        fprintf(fp, "%d %s %d %d %d\n",temp->id,temp->name,temp->level,temp->department,temp->visitTime);
    }
    fclose(fp);
}

void docterRead()
{
    FILE *fp=fopen("docters.txt", "r");
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

int docterGetById(int id)
{
    for(int i=0; i<listSize(docters); i++)
    {
        docter *temp=listGet(docters,i);
        if(temp->id==id)
            return i;
    }
    return -1;
}

void printVisitTime(int t)
{
    if(t & Mon)
        printf("��һ ");
    if(t & Tue)
        printf("�ܶ� ");
    if(t & Wed)
        printf("���� ");
    if(t & Thur)
        printf("���� ");
    if(t & Fri)
        printf("���� ");
    if(t & Sat)
        printf("���� ");
    if(t & Sun)
        printf("���� ");
}

char* getLevel(int i)
{
    if(i>=0 && i<sizeof(levels)/sizeof(char*))
        return levels[i];
    return "δ֪";
}

char* getDepartment(int i)
{
    if(i>=0 && i<sizeof(departments)/sizeof(char*))
        return departments[i];
    return "δ֪";
}

void docterAdd()
{
    char comfirm;
    docter *temp=(docter*)malloc(sizeof(docter));
    SetConsoleTitle("����ҽ��");

    clear();
    printf("��������Ϣ\n");

    printf("�����빤�ţ�");
    scanf("%d",&temp->id);

    printf("������������");
    scanf("%s",temp->name);

    for(int i=0; i<sizeof(levels)/sizeof(char*); i++)
        printf("%d.%s ",i,levels[i]);
    printf("\n��ѡ�񼶱�");
    scanf("%d",&temp->level);

    for(int i=0; i<sizeof(departments)/sizeof(char*); i++)
        printf("%d.%s ",i,departments[i]);
    printf("\n��ѡ����ң�");
    scanf("%d",&temp->department);

    printf("���������ʱ�䣨��ʽ��1234567����");
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
    if(docterGetById(temp->id)!=-1)
    {
        free(temp);
        printf("��ҽ���Ѵ��ڣ�");
        system("pause");
        return;
    }


    printf("����֤��Ϣ\n");
    printf("���ţ�%d\n������%s\n����%s\n���ң�%s\n����ʱ�䣺",temp->id,temp->name,getLevel(temp->level),getDepartment(temp->department));
    printVisitTime(temp->visitTime);

    printf("\n������yȷ����ӣ�Ĭ��Ϊn����");
    if(getchar()=='y')
    {
        listAddLast(docters,temp);
        docterSave();
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

int departmentSelector()
{
    int d;
    clear();
    for(int i=0; i<sizeof(departments)/sizeof(char*); i++)
        printf("  %d.%s\n",i,departments[i]);
    printf("\n��ѡ����ң�");
    scanf("%d",&d);
    if(d<0 || d>=sizeof(departments)/sizeof(char*))
        return -1;
    return d;
}

int docterSelector()
{
    char comfirm;
    int i,d;
    SetConsoleTitle("ѡ��ҽ��");
    d = departmentSelector();
    if(d==-1)
    {
        clear();
        printf("δ�ҵ��ÿ��ң�");
        system("pause");
        return -1;
    }
    printf("\n%-10s %-12s %-12s %-12s%s\n","����","����","����","����","����ʱ��");
    for(int i=0; i<listSize(docters); i++)
    {
        docter *temp=listGet(docters,i);
        if(d==temp->department)
        {
            printf("%-10d %-12s %-12s %-12s",temp->id,temp->name,getLevel(temp->level),getDepartment(temp->department));
            printVisitTime(temp->visitTime);
            printf("\n");
        }
    }
    printf("\n�����빤����ȷ��ҽ����");
    int id;
    scanf("%d",&id);
    int r = docterGetById(id);
    if(r!=-1)
        return r;
    clear();
    printf("δ�ҵ���ҽ����");
    system("pause");
    return -1;
}

void docterDelete()
{
    int id,i;
    docter *temp;
    clear();
    printf("�����빤�Ž��в�ѯ��");
    scanf("%d",&id);
    i = docterGetById(id);
    if(i==-1)
    {
        clear();
        printf("δ�ҵ���ҽ����");
        system("pause");
    }
    else
    {
        clear();
        temp=listGet(docters,i);
        printf("����֤��Ϣ\n");
        printf("���ţ�%d\n������%s\n����%s\n���ң�%s\n����ʱ�䣺",temp->id,temp->name,getLevel(temp->level),getDepartment(temp->department));
        printVisitTime(temp->visitTime);

        printf("\n������yȷ��ɾ����Ĭ��Ϊn����");
        if(getchar()=='y')
        {
            listRemove(docters,i);
            docterSave();
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

void docterList()
{
    clear();
    printf("%-10s %-12s %-12s %-12s%s\n","����","����","����","����","����ʱ��");
    for(int i=0; i<listSize(docters); i++)
    {
        docter *temp=listGet(docters,i);
        printf("%-10d %-12s %-12s %-12s",temp->id,temp->name,getLevel(temp->level),getDepartment(temp->department));
        printVisitTime(temp->visitTime);
        printf("\n");
    }
    system("pause");
}

void docterManage()
{
    do
    {
        clear();
        SetConsoleTitle("ҽ������");
    }
    while(selector(5,"����ҽ��","ɾ��ҽ��","�г�����ҽ��","��ѯҽ����Ϣ","����",docterAdd,docterDelete,docterList,recordListByDocter,NULL)!=5);
}
