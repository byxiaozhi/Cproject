#pragma once
#include "stdbool.h"
typedef struct node
{
    void* data;
    struct node* next;
} node;

typedef struct listInfo
{
    int size;//储存链表大小
    node* tail;//储存尾节点指针
} listInfo;

node* listCreate();
void listDelete();
void* listGet(node* head, int index);
void listAddFirst(node* head, void* data);
void listAddLast(node* head, void* data);
bool listRemove(node* head, int index);
int listSize(node* head);
