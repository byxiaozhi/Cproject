#include "DataHandler.h"
#include "stdlib.h"

//����һ����������ͷ�ڵ�ָ��
node* listCreate()
{
    //ͷ�ڵ㴢����������
    listInfo *newListInfo=(listInfo*)malloc(sizeof(listInfo));
    newListInfo->size=0;
    newListInfo->tail=NULL;

    //�½�һ���ڵ���Ϊ����ͷ�ڵ�
    node* newNode=(node*)malloc(sizeof(node));
    newNode->next=NULL;
    newNode->data=newListInfo;

    return newNode;
}

//��ѯ�����ؽڵ�ָ���ַ����û�ҵ��򷵻�NULL
void* listGetNode(node* head, int index)
{
    listInfo* info=((listInfo*)head->data);

    //����������ڵ㣬����NULL
    if(index<0 || index>=info->size)
        return NULL;

    //Ѱ�Ҹýڵ㲢����
    head=head->next;
    while(index--)
        head=head->next;

    return head;
}

//��ѯ�����ؽڵ�������ָ���ַ����û�ҵ��򷵻�NULL
void* listGet(node* head, int index)
{
    node* temp=listGetNode(head,index);

    //��û�ҵ��ڵ㣬�򷵻�NULL�����򷵻ؽڵ�����ָ��
    return temp==NULL?NULL:temp->data;
}

//����ڵ㵽����ͷ��
void listAddFirst(node* head, void* data)
{
    //�½�һ������ڵ�
    node* newNode=(node*)malloc(sizeof(node));
    newNode->next=head->next;
    newNode->data=data;

    listInfo* info=((listInfo*)head->data);

    //�������Ϊ�գ��ͽ��½ڵ���Ϊβ�ڵ�
    if(head->next==NULL)
        info->tail=newNode;
    //���½ڵ���Ϊ��һ��Ԫ�ؽڵ�
    head->next=newNode;

    info->size++;
}

//����ڵ㵽����β��
void listAddLast(node* head, void* data)
{
    //�½�һ������ڵ�
    node* newNode=(node*)malloc(sizeof(node));
    newNode->next=NULL;
    newNode->data=data;

    listInfo* info=((listInfo*)head->data);

    //�������Ϊ�գ��ͽ��½ڵ���Ϊ��һ��Ԫ�ؽڵ㣬����β�ڵ�ָ���½ڵ�
    if(head->next==NULL)
        head->next=newNode;
    else
        info->tail->next=newNode;
    //���½ڵ���Ϊβ�ڵ�
    info->tail=newNode;

    info->size++;
}

//��ѯ��ɾ��ָ���ڵ㣬��ɾ���ɹ�����1��ʧ�ܷ���0
int listRemove(node* head, int index)
{
    listInfo* info=((listInfo*)head->data);

    //����������ڵ㣬����0
    if(index<0 || index>=info->size)
        return 0;

    node* temp;
    //�ҵ��ýڵ����һ���ڵ㣬������ָ��Ҫɾ���ڵ����һ���ڵ�
    if(index==0)
        temp=head;
    else
        temp=listGetNode(head,index-1);

    node* remove=temp->next;
    temp->next=remove->next;

    //���ýڵ�ͽڵ㴢�������һ��ɾ��
    free(remove->data);
    free(remove);

    info->size--;
}

//��������ڵ�������ʧ�ܷ���-1
int listSize(node* head)
{
    if(head==NULL || head->data==NULL)
        return -1;
    else
        return ((listInfo*)head->data)->size;
}
