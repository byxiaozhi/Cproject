#include "Patient.h"
#include "windows.h"

const char *types[3]={"���","��ҩ","סԺ"};

void patientManage()
{
    int select;
    while(1)
    {
        system("cls");
        SetConsoleTitle("���߹���");

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
