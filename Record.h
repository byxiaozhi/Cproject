#pragma once

const char *types[3]={"检查","开药","住院"};

typedef struct{
    char patientId[100];//患者身份证
    int docterId;//医生工号
    int dateTime[4];//时间，储存结构为月、日、时、分
    int type;//记录类型
    void* data;//记录内容
}record;

//检查、开药相当于购买类型，住院相当于租用类型
//购买类型
typedef struct {
    char name[100];//商品名称
    int amount;//金额，单位为分
}record_buy;

//租用类型
typedef struct {
    int startDateTime[4];//开始租用时间
    int endDateTime[4];//结束租用时间
    int deposit;//押金，单位为分
}record_hospitalized;
