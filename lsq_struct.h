#ifndef LSQ_STRUCT_H
#define LSQ_STRUCT_H

struct _node;
struct _iterator;
struct _handler;

typedef struct _node* LSQ_node_ptr;
typedef struct _iterator* LSQ_iterator_ptr;
typedef struct _handler* LSQ_handler_ptr;

typedef struct _node
{
    LSQ_BaseTypeT value;
    LSQ_node_ptr prev;
    LSQ_node_ptr next;
} LSQ_Node;

typedef struct _iterator
{
    LSQ_node_ptr self;
} LSQ_Iterator;

typedef struct _handler
{
    LSQ_node_ptr node_list;
} LSQ_handler;

#endif // LSQ_STRUCT_H
