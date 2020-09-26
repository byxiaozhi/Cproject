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
        SetConsoleTitle("医院管理系统");

        printf("主菜单：\n");
        printf("1.挂号管理\n");
        printf("2.患者管理\n");
        printf("3.医生管理\n");
        printf("4.财务管理\n");
        printf("请选择:");

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
