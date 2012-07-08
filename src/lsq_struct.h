#ifndef LSQ_STRUCT_H
#define LSQ_STRUCT_H

#include "linear_sequence.h"

extern void insertFirstElement(LSQ_HandleT handle, LSQ_BaseTypeT element);

typedef struct _node
{
    LSQ_BaseTypeT value;
    struct _node * prev;
    struct _node * next;
} NodeT;


typedef struct
{
    NodeT * head;
    NodeT * tail;
    int length;
} HandleT;

typedef struct
{
    NodeT * self;
    LSQ_HandleT handle;
    int index;
} IteratorT;

#endif // LSQ_STRUCT_H
