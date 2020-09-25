#include "DataHandler.h"
#include "stdlib.h"

//创建一个链表并返回头节点指针
node* listCreate()
{
    //头节点储存链表属性
    listInfo *newListInfo=(listInfo*)malloc(sizeof(listInfo));
    newListInfo->size=0;
    newListInfo->tail=NULL;

    //新建一个节点作为链表头节点
    node* newNode=(node*)malloc(sizeof(node));
    newNode->next=NULL;
    newNode->data=newListInfo;

    return newNode;
}

//查询并返回节点指针地址，若没找到则返回NULL
void* listGetNode(node* head, int index)
{
    listInfo* info=((listInfo*)head->data);

    //不存在这个节点，返回NULL
    if(index<0 || index>=info->size)
        return NULL;

    //寻找该节点并返回
    head=head->next;
    while(index--)
        head=head->next;

    return head;
}

//查询并返回节点中数据指针地址，若没找到则返回NULL
void* listGet(node* head, int index)
{
    node* temp=listGetNode(head,index);

    //若没找到节点，则返回NULL，否则返回节点数据指针
    return temp==NULL?NULL:temp->data;
}

//插入节点到链表头部
void listAddFirst(node* head, void* data)
{
    //新建一个链表节点
    node* newNode=(node*)malloc(sizeof(node));
    newNode->next=head->next;
    newNode->data=data;

    listInfo* info=((listInfo*)head->data);

    //如果链表为空，就将新节点作为尾节点
    if(head->next==NULL)
        info->tail=newNode;
    //将新节点作为第一个元素节点
    head->next=newNode;

    info->size++;
}

//插入节点到链表尾部
void listAddLast(node* head, void* data)
{
    //新建一个链表节点
    node* newNode=(node*)malloc(sizeof(node));
    newNode->next=NULL;
    newNode->data=data;

    listInfo* info=((listInfo*)head->data);

    //如果链表为空，就将新节点作为第一个元素节点，否则将尾节点指向新节点
    if(head->next==NULL)
        head->next=newNode;
    else
        info->tail->next=newNode;
    //将新节点作为尾节点
    info->tail=newNode;

    info->size++;
}

//查询并删除指定节点，若删除成功返回1，失败返回0
int listRemove(node* head, int index)
{
    listInfo* info=((listInfo*)head->data);

    //不存在这个节点，返回0
    if(index<0 || index>=info->size)
        return 0;

    node* temp;
    //找到该节点的上一个节点，并将其指向要删除节点的下一个节点
    if(index==0)
        temp=head;
    else
        temp=listGetNode(head,index-1);

    node* remove=temp->next;
    temp->next=remove->next;

    //将该节点和节点储存的数据一并删除
    free(remove->data);
    free(remove);

    info->size--;
}

//返回链表节点数量，失败返回-1
int listSize(node* head)
{
    if(head==NULL || head->data==NULL)
        return -1;
    else
        return ((listInfo*)head->data)->size;
}
