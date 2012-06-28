#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

#include "linear_sequence.h"


typedef struct _node
{
    LSQ_BaseTypeT value;
//    struct _node *prev;
    LSQ_HandleT prev;
//    struct _node *next;
    LSQ_HandleT next;
} node;


void append(node **,int);
void in_begin(node **,int);
void del(node **,int);
void in_middle(node **,int,int);
int count(node *);
void display(node *);

#endif // SIMPLE_LIST_H
