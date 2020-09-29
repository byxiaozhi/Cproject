#pragma once
#include "DataHandler.h"
#include "stdbool.h"
#include "Utils.h"
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
    time startTime;//��ʼסԺʱ��
    time endTime;//����סԺʱ��
    int deposit;//Ѻ�𣬵�λΪ��
}record_hospitalized;

typedef struct{
    int id;//�Һ�id
    char patientId[100];//�������֤
    int docterId;//ҽ������
    time dateTime;//ʱ�䣬����ṹΪ�¡��ա�ʱ����
    bool registeredOnly;//�Ƿ�����Һ�
    int Bill_check;//���۸�
    int Bill_medicine;//ҩ�ﻨ��
    int Bill_hospitalized;//סԺ����
    node* data_check;//���
    node* data_medicine;//��ҩ
    record_hospitalized data_hospitalized;//סԺ
}record;

node* records;
int patientSelect();
int patientGetById(char *id);
void recordSave();
void recordRead();
void recordListByPatient();
void recordListByDocter();
