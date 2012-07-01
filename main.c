#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include "simple_list.h"
#include "linear_sequence.h"



int main(void)
{
    LSQ_node_ptr node_list = (LSQ_node_ptr)LSQ_CreateSequence();
    node_list->iterator = (LSQ_iterator_ptr)malloc(sizeof(LSQ_Iterator));

    LSQ_InsertRearElement(node_list, 10);
    LSQ_InsertRearElement(node_list, 15);
    LSQ_InsertRearElement(node_list, 16);
    LSQ_IntegerIndexT s = LSQ_GetSize(node_list);
    printf("size = %d\n", s);
//    srand ( time(NULL) );
//    num = rand() % 10 +1;

    return 0;
}

