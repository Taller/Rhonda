//#include "simple_list.h"
#include <stdlib.h>
#include <stdio.h>

void append(struct _node **q, int num)
{
    struct _node *temp, *r;
    struct _iterator *iter_tmp;
    temp = *q;
//    iter_tmp = (*q)->iter_ptr;
    if(NULL == *q)
    {
        temp = (struct _node *)malloc(sizeof(struct _node));
        iter_tmp = (struct _iterator *)malloc(sizeof(struct _iterator));


        temp->value = num;
        temp->iter_ptr->next = LSQ_HandleInvalid;
        temp->iter_ptr->prev = temp;

        *q = temp;
     }
     else
     {
        temp = *q;
        while(temp->iter_ptr->next != LSQ_HandleInvalid)
        {
            temp = temp->iter_ptr->next;
        }
        r = (struct _node *)malloc(sizeof(struct _node));
        r->value = num;
        r->iter_ptr->next = NULL;
        r->iter_ptr->prev = temp;
        temp->iter_ptr->next = r;
     }
}

void display(struct _node *q)
{
    if(q == LSQ_HandleInvalid)
    {
        printf("\n\nEmpty Link List. Can't Display The Value");
        return;
    }
    while(q != NULL)
    {
        printf("\n%d", q->value);
        q = q->iter_ptr->next;
    }
}

int count(struct _node *q)
{
    if(q == LSQ_HandleInvalid)
    {
        printf("Empty Link List.\n");
        return 0;
    }

    int c=0;
    while(q != LSQ_HandleInvalid)
    {
        c++;
        q = q->iter_ptr->next;
    }
    return c;
}

void in_begin(struct _node **q, int nodeValue)
{
    if(*q == LSQ_HandleInvalid)
    {
        printf("Link List Is Empty.Can't Insert.");
    }
    else
    {
        struct _node *temp;
        temp = (struct _node *)malloc(sizeof(struct _node));
        temp->value = nodeValue;
        temp->iter_ptr->next = *q;
        *q = temp;  /* first node */
     }
}

void in_middle(struct _node **q, int loc, int num)
{
    struct _node *temp,*n;
    int c = 1,flag=0;
    temp = *q;
    if(*q == LSQ_HandleInvalid)
    {
        printf("\n\nLink List Is Empty. Can't Insert.");
    }
    else
    while(temp != LSQ_HandleInvalid)
    {
        if(c == loc)
        {
            n = (struct _node *)malloc(sizeof(struct _node));
            n->value = num;
            n->iter_ptr->next = temp->iter_ptr->next;
            temp->iter_ptr->next = n;
            flag = 1;
        }
        c++;
        temp = temp->iter_ptr->next;
     }
     if(flag == 0)
     {
         printf("\n\nNode Specified Doesn't Exist. Cant Enter The Value");
     }
     else
     {
         printf("Data Inserted");
     }
}

void del(struct _node **q, int num)
{
    if(*q == LSQ_HandleInvalid)
    {
        printf("\n\nEmpty Linked List. Cant Delete The Value.");
        return;
    }
    else
    {
        struct _node *old, *temp;
        int flag = 0;
        temp = *q;
        while(temp != LSQ_HandleInvalid)
        {
            if(temp->value == num)
            {
                if(temp == *q)         /* First Node case */
                *q = temp->iter_ptr->next;       /* shifted the header node */
                else
                old->iter_ptr->next = temp->iter_ptr->next;

                free(temp);
                flag = 1;
            }
            else
            {  old = temp;
                temp = temp->iter_ptr->next;
            }
        }
        if(flag == 0)
            printf("Value Not Found...");
        else
            printf("Value Deleted...Tap a key to continue");
    }
}
