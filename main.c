#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "DataHandler.h"
#include "Doctor.h"
#include "Record.h"
#include "Patient.h"
#include "Hospital.h"

int main()
{
    int select;
    while(1)
    {
        system("cls");
        SetConsoleTitle("ҽԺ����ϵͳ");

        printf("���˵���\n");
        printf("1.�ҺŹ���\n");
        printf("2.���߹���\n");
        printf("3.ҽ������\n");
        printf("4.�������\n");
        printf("��ѡ��:");

        scanf("%d",&select);
        switch(select)
        {
        case 1:
            recordManage();
            break;
        case 2:
            patientManage();
            break;
        case 3:
            docterManage();
            break;
        case 4:
            hospitalManage();
            break;
        }
    }
    return 0;
}
