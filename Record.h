#pragma once
#include "DataHandler.h"
typedef struct{
    char patientId[100];//�������֤
    int docterId;//ҽ������
    int dateTime[4];//ʱ�䣬����ṹΪ�¡��ա�ʱ����
    int type;//��¼����
    void* data;//��¼����
}record;

//��顢��ҩ�൱�ڹ������ͣ�סԺ�൱����������
//��������
typedef struct {
    char name[100];//��Ʒ����
    int price;//����λΪ��
}record_buy;

//��������
typedef struct {
    int startDateTime[4];//��ʼ����ʱ��
    int endDateTime[4];//��������ʱ��
    int deposit;//Ѻ�𣬵�λΪ��
}record_hospitalized;


node* records;
