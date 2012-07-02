#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linear_sequence.h"



int main(void)
{
    LSQ_node_ptr node_list = (LSQ_node_ptr)LSQ_CreateSequence();
    LSQ_iterator_ptr iterator = (LSQ_iterator_ptr)malloc(sizeof(LSQ_Iterator));
    printf("node_list = %p\n", node_list);

    LSQ_InsertRearElement(node_list, 10);
    LSQ_InsertRearElement(node_list, 15);
    LSQ_InsertRearElement(node_list, 16);
    LSQ_IntegerIndexT s = LSQ_GetSize(node_list);
    printf("size = %d\n", s);

    LSQ_InsertFrontElement(node_list, 9);
    s = LSQ_GetSize(node_list);
    printf("size = %d\n", s);
    printf("node_list = %p\n", node_list);
    LSQ_DestroySequence(node_list);

//    srand ( time(NULL) );
//    num = rand() % 10 +1;

    return 0;
}

