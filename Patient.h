#pragma once
#include "DataHandler.h"
typedef struct {
    char id[100];//���֤��Ψһ
    char name[100];//����
    int age;//����
    int bill_all;//���˵�
    int bill_check;//����˵�
    int bill_medicine;//��ҩ�˵�
    int bill_hospitalized;//סԺ�˵�
    int deposit;//Ѻ��
}patient;

node* patients;
int patientSelector(bool allowAdd);
void patientSave();
void patientRead();
