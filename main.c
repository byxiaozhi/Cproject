#include "stdio.h"
#include "stdlib.h"
#include "DataHandler.h"


int main()
{
    node* head=listCreate();

    for(int i=0; i<10; i++)
    {
        int *data;
        data=(int *)malloc(sizeof(int));
        *data=i;
        //listAddFirst(head,data);
        listAddLast(head,data);
    }

    for(int i=0; i<listSize(head); i++)
    {
        printf("%d",*(int*)listGet(head,i));
    }

    printf("\n");
    //listDelete(head);

    for(int i=0; i<listSize(head); i++)
    {
        printf("%d",*(int*)listGet(head,i));
    }

    //printf("%d",head->next);

    return 0;
}
