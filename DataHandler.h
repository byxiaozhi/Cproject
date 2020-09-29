#pragma once
#include "stdbool.h"
typedef struct node
{
    void* data;
    struct node* next;
} node;

typedef struct listInfo
{
    int size;//���������С
    node* tail;//����β�ڵ�ָ��
} listInfo;

node* listCreate();
void listDelete();
void* listGet(node* head, int index);
void listAddFirst(node* head, void* data);
void listAddLast(node* head, void* data);
bool listRemove(node* head, int index);
int listSize(node* head);
