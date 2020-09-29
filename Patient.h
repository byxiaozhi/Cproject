#pragma once
#include "DataHandler.h"
typedef struct {
    char id[100];//身份证，唯一
    char name[100];//姓名
    int age;//年龄
    int bill_all;//总账单
    int bill_check;//检查账单
    int bill_medicine;//开药账单
    int bill_hospitalized;//住院账单
    int deposit;//押金
}patient;

node* patients;
int patientSelector(bool allowAdd);
void patientSave();
void patientRead();
