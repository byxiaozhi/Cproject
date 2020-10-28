#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "DataHandler.h"
#include "Doctor.h"
#include "Record.h"
#include "Patient.h"
#include "Hospital.h"
#include "Utils.h"

void recordManage();
void patientManage();
void docterManage();
void hospitalManage();

int init()
{
    //执行初始化操作
    docters = listCreate();
    patients = listCreate();
    records = listCreate();
    docterRead();
    patientRead();
    recordRead();
    hospitalRead();

}

int main()
{
    init();
    while(1)
    {
        clear();
        SetConsoleTitle("医院管理系统");
        selector(4,"诊疗信息管理","患者信息管理","医生信息管理","财务信息管理",recordManage,patientManage,docterManage,hospitalManage);
    }

    return 0;
}


