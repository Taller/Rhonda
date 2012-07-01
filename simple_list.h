#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

//#include "linear_sequence.h"

struct _iterator
{
    LSQ_IntegerIndexT index;
    struct _node * prev;
    struct _node * next;
    struct _node * self;
};

struct _node
{
    LSQ_BaseTypeT value;
    struct _iterator *iter_ptr;
};


void append(struct _node **nlist, int node);
void in_begin(struct _node **nlist, int node);
void del(struct _node **nlist, int node);
void in_middle(struct _node **nlist, int, int);
int count(struct _node *nlist);
void display(struct _node *nlist);

#endif // SIMPLE_LIST_H
