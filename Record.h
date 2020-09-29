#pragma once
#include "DataHandler.h"
#include "stdbool.h"
#include "Utils.h"
//检查、开药相当于购买类型，住院相当于租用类型

typedef struct {
    char name[100];//检查名称
    int price;//价格，单位为分
}record_check;

typedef struct {
    char name[100];//药品名称
    int num;//药品数量
    int price;//单价，单位为分
}record_medicine;

typedef struct {
    time startTime;//开始住院时间
    time endTime;//结束住院时间
    int deposit;//押金，单位为分
}record_hospitalized;

typedef struct{
    int id;//挂号id
    char patientId[100];//患者身份证
    int docterId;//医生工号
    time dateTime;//时间，储存结构为月、日、时、分
    bool registeredOnly;//是否仅仅挂号
    int Bill_check;//检查价格
    int Bill_medicine;//药物花费
    int Bill_hospitalized;//住院花费
    node* data_check;//检查
    node* data_medicine;//开药
    record_hospitalized data_hospitalized;//住院
}record;

node* records;
int patientSelect();
int patientGetById(char *id);
void recordSave();
void recordRead();
void recordListByPatient();
void recordListByDocter();
