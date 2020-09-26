#include "Patient.h"
#include "windows.h"

const char *types[3]={"检查","开药","住院"};

void patientManage()
{
    int select;
    while(1)
    {
        system("cls");
        SetConsoleTitle("患者管理");

        printf("主菜单：\n");
        printf("1.功能一\n");
        printf("2.功能二\n");
        printf("3.功能三\n");
        printf("4.返回\n");
        printf("请选择:");

        scanf("%d",&select);
        switch(select)
        {

        }

        if(select==4)
            break;
    }
}
