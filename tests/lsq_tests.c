#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linear_sequence.h"
#include "lsq_struct.h"

void print_LSQ(LSQ_HandleT handle)
{
    if(handle != LSQ_HandleInvalid)
    {
        HandleT * t_handler = (HandleT *)handle;
        NodeT * t_node = t_handler->head;
        int i = 1;
        printf("=========BEGIN OUTPUT================\n");
        do
        {
            printf("t_node = %p\t\tvalue = %d\t\tindex = %d\n", t_node, t_node->value, i);
            t_node = t_node->next;
            i++;
        }
        while(t_node->next != t_node);
        printf("t_node = %p\t\tvalue = %d\t\tindex = %d\n", t_node, t_node->value, i);
        printf("=========END OUTPUT==================\n");
    }
}

int main(void)
{
    HandleT * handler = (HandleT *)LSQ_CreateSequence();
    LSQ_IntegerIndexT s;
    IteratorT * iterator;

    printf("handler = %p\n", handler);
    printf("node_list = %p\n", handler->head);

    LSQ_InsertFrontElement(handler, 6);
    LSQ_InsertRearElement(handler, 10);
    LSQ_InsertRearElement(handler, 15);
    LSQ_InsertRearElement(handler, 16);
    LSQ_InsertFrontElement(handler, 9);

    s = LSQ_GetSize(handler);
    printf("size = %d\n", s);
    print_LSQ(handler);

    iterator = LSQ_GetFrontElement(handler);
    printf("iterator->self = %p\n", iterator->self);
    printf("t_node->value = %d\n", iterator->self->value);
    printf("=====================================\n");
    LSQ_DestroyIterator(iterator);

    iterator = LSQ_GetElementByIndex(handler, 2);
    printf("iterator->self->value = %d\n", (iterator->self)->value);
    printf("iterator->self = %p\n", iterator->self);

    LSQ_AdvanceOneElement(iterator);
    printf("iterator->self->value = %d\n", (iterator->self)->value);
    printf("iterator->self = %p\n", iterator->self);

    LSQ_RewindOneElement(iterator);
    LSQ_RewindOneElement(iterator);
    printf("iterator->self->value = %d\n", (iterator->self)->value);
    printf("iterator->self = %p\n", iterator->self);

//    LSQ_BaseTypeT a = LSQ_DereferenceIterator(iterator);
//    printf("a = %p\n", a);
//    printf("*a = %p\n", &a);

    LSQ_DeleteFrontElement(handler);
    print_LSQ(handler);

    LSQ_DeleteRearElement(handler);
    print_LSQ(handler);

    LSQ_DestroySequence(handler);


//    srand ( time(NULL) );
//    num = rand() % 10 +1;

    return 0;
}


