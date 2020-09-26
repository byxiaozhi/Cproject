#include "Doctor.h"
#include "stdlib.h"
#include "windows.h"


//级别
const char *levels[4]= {"主任医师","副主任医师","主治医师","住院医师"};

//科室
const char *departments[27]= {"内科","外科","儿科","妇科","眼科","耳鼻喉科","口腔科","皮肤科","中医科","针灸推拿科",
                              "呼吸内科","消化内科","泌尿内科","心内科","血液科","内分泌科","神经内科","小儿科","感染科",
                              "普外科","骨科","神经外科","肝胆外科","泌尿外科","烧伤科","妇科","产科"
                             };

void docterManage()
{
    int select;
    while(1)
    {
        system("cls");
        SetConsoleTitle("医生管理");

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
