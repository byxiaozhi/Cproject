#pragma once
#include "DataHandler.h"
int turnover_all; //总营业额，单位为分
int turnover_check; //检查营业额，单位为分
int turnover_medicine; //开药营业额，单位为分
int turnover_hospitalized; //住院营业额，单位为分

void hospitalSave();
void hospitalRead();
