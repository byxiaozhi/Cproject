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

void docterManage()
{
    int select;
    while(1)
    {
        system("cls");
        SetConsoleTitle("ҽ������");

        printf("���˵���\n");
        printf("1.����һ\n");
        printf("2.���ܶ�\n");
        printf("3.������\n");
        printf("4.����\n");
        printf("��ѡ��:");

        scanf("%d",&select);
        switch(select)
        {

        }

        if(select==4)
            break;
    }
}
