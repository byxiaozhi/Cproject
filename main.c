#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "DataHandler.h"
#include "Doctor.h"
#include "Record.h"
#include "Patient.h"
#include "Hospital.h"

void recordManage();
void patientManage();
void docterManage();
void hospitalManage();

int main()
{
    init();
    while(1)
    {
        system("cls");
        SetConsoleTitle("医院管理系统");
        selector(4,"挂号管理","患者管理","医生管理","财务管理",recordManage,patientManage,docterManage,hospitalManage);
    }
    return 0;
}

int init()
{
    //执行初始化操作
    docters = listCreate();
    patients = listCreate();
    records = listCreate();
}
