#include "Doctor.h"
#include "stdlib.h"
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
    int select;
    printf("���ҽ��");
    scanf("%d",&select);
}

void docterDelete()
{


}

void docterList()
{


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
