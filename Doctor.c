#include "Doctor.h"
#include "stdlib.h"
#include "stdio.h"
#include "windows.h"

//����
const char *levels[4]= {"����ҽʦ","������ҽʦ","����ҽʦ","סԺҽʦ"};

//����
const char *departments[27]= {"�ڿ�","���","����","����","�ۿ�","���Ǻ��","��ǻ��","Ƥ����","��ҽ��","������ÿ�",
                              "�����ڿ�","�����ڿ�","�����ڿ�","���ڿ�","ѪҺ��","�ڷ��ڿ�","���ڿ�","С����","��Ⱦ��",
                              "�����","�ǿ�","�����","�ε����","�������","���˿�","����","����"
                             };

void docterAdd()
{
    char comfirm;
    docter *temp=(docter*)malloc(sizeof(docter));
    SetConsoleTitle("����ҽ��");

    system("cls");
    printf("��������Ϣ\n");
    printf("�����빤�ţ�");
    scanf("%d",&temp->id);
    printf("������������");
    scanf("%s",&temp->name);
    for(int i=0; i<sizeof(levels)/sizeof(char*); i++)
        printf("%d.%s ",i,levels[i]);
    printf("\n��ѡ�񼶱�");
    scanf("%d",&temp->level);
    for(int i=0; i<sizeof(departments)/sizeof(char*); i++)
        printf("%d.%s ",i,departments[i]);
    printf("\n��ѡ����ң�");
    scanf("%d",&temp->department);

    fflush(stdin);
    system("cls");
    printf("����֤��Ϣ\n");
    printf("���ţ�%d\n������%s\n����%s\n���ң�%s\n",temp->id,temp->name,levels[temp->level],departments[temp->department]);
    printf("������yȷ�ϣ�Ĭ��Ϊn����");
    if(getchar()=='y')
    {
        listAddLast(docters,temp);
        system("cls");
        printf("��ӳɹ�");
    }
    else
    {
        system("cls");
        printf("������ȡ��");
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
        printf("%-10s %-10s %-10s %-10s\n","����","����","����","����");
        printf("%-10d %-10s %-10s %-10s\n",temp->id,temp->name,levels[temp->level],departments[temp->department]);
    }
    printf("\n�����������...");
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
        SetConsoleTitle("ҽ������");
    }
    while(selector(5,"����ҽ��","ɾ��ҽ��","�г�����ҽ��","��ѯҽ����Ϣ","����",docterAdd,docterDelete,docterList,docterInfo,NULL)!=5);
}
