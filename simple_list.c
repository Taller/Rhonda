#include "simple_list.h"
#include <stdlib.h>

void append(node **q,int num)
{
    node *temp,*r;
    temp = *q;
    if(NULL == *q)
    {
        temp = (struct node *)malloc(sizeof(node));
        temp->value=num;
        temp->next=NULL;
        *q=temp;
     }
     else
     {
        temp = *q;
        while(temp->next !=NULL)
        {
            temp=temp->next;
        }
        r = (struct node *)malloc(sizeof(node));
        r->value=num;
        r->next=NULL;
        temp->next=r;
     }
}

void display(node *q)
{
    if(q==NULL)
    {
        printf("\n\nEmpty Link List. Can't Display The Value");
        return;
    }
    while(q!=NULL)
    {
        printf("\n%d",q->value);
        q=q->next;
    }
}

int count(node *q)
{
    if(q==NULL)
    {
        printf("Empty Link List.\n");
        return 0;
    }

    int c=0;
    while(q!=NULL)
    {
        c++;
        q=q->next;
    }
    return c;
}

void in_begin(node **q,int num)
{
    if(*q==NULL)
    {
        printf("Link List Is Empty.Can't Insert.");
    }
    else
    {
        node *temp;
        temp=(node *)malloc(sizeof(node));
        temp->value=num;
        temp->next=*q;
        *q=temp;  /* first node */
     }
}

void in_middle(node **q,int loc,int num)
{
    node *temp,*n;
    int c=1,flag=0;
    temp=*q;
    if(*q==NULL)
    {
        printf("\n\nLink List Is Empty. Can't Insert.");
    }
    else
    while(temp!=NULL)
    {
        if(c==loc)
        {
            n = (node *)malloc(sizeof(node));
            n->value=num;
            n->next=temp->next;
            temp->next=n;
            flag=1;
        }
        c++;
        temp=temp->next;
     }
     if(flag==0)
     {
         printf("\n\nNode Specified Doesn't Exist. Cant Enter The Value");
     }
     else
     {
         printf("Data Inserted");
     }
}

void del(node**q,int num)
{
    if(*q==NULL)
    {
        printf("\n\nEmpty Linked List. Cant Delete The Value.");
        return;
    }
    else
    {
        node *old,*temp;
        int flag=0;
        temp=*q;
        while(temp!=NULL)
        {
            if(temp->value==num)
            {
                if(temp==*q)         /* First Node case */
                *q=temp->next;       /* shifted the header node */
                else
                old->next=temp->next;

                free(temp);
                flag=1;
            }
            else
            {  old=temp;
                temp=temp->next;
            }
        }
        if(flag==0)
            printf("Value Not Found...");
        else
            printf("Value Deleted...Tap a key to continue");
    }
}
