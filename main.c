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
        SetConsoleTitle("ҽԺ����ϵͳ");
        selector(4,"�ҺŹ���","���߹���","ҽ������","�������",recordManage,patientManage,docterManage,hospitalManage);
    }
    return 0;
}

int init()
{
    //ִ�г�ʼ������
    docters = listCreate();
    patients = listCreate();
    records = listCreate();
}
