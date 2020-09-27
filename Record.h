#pragma once
#include "DataHandler.h"
#include "stdbool.h"
//��顢��ҩ�൱�ڹ������ͣ�סԺ�൱����������

typedef struct {
    char name[100];//�������
    int price;//�۸񣬵�λΪ��
}record_check;

typedef struct {
    char name[100];//ҩƷ����
    int num;//ҩƷ����
    int price;//���ۣ���λΪ��
}record_medicine;

typedef struct {
    int startDateTime[4];//��ʼסԺʱ��
    int endDateTime[4];//����סԺʱ��
    int deposit;//Ѻ�𣬵�λΪ��
}record_hospitalized;

typedef struct{
    int id;//�Һ�id
    char patientId[100];//�������֤
    bool docterId;//ҽ������
    int dateTime[4];//ʱ�䣬����ṹΪ�¡��ա�ʱ����
    int registeredOnly;//�Ƿ�����Һ�
    int Bill_check;//���۸�
    int Bill_medicine;//ҩ�ﻨ��
    node* data_check;//���
    node* data_medicine;//��ҩ
    record_hospitalized record_hospitalized;//סԺ
}record;

node* records;
int patientSelect();
