#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "linear_sequence.h"
#include "lsq_struct.h"

void test1(void);
void test2(void);
void print_LSQ(LSQ_HandleT handle);


int main(void)
{
    /* Create and destroy sequence immediately */
    test1();

    /* Create sequence, fill fron, fill rear and destroy */
    test2();
    return 0;
}

/* Create and destroy sequence immediately */
void test1(void)
{
    printf("\nCreate and destroy sequence immediately");
    HandleT * handle = (HandleT *)LSQ_CreateSequence();
    IteratorT * iter = LSQ_GetFrontElement(handle);
    LSQ_DestroyIterator(iter); 
    LSQ_DestroySequence(handle);
    printf("\t ---\t OK \n");
}

/* Test adding elements */
void test2(void)
{
    LSQ_BaseTypeT front[50], rear[50];
    int i;

    printf("Generating test data");
    srand ( time(NULL) );
    for(i = 0; i < 50; i++)
    {
        front[i] = rand() % 1000 +1;
        rear[i] = rand() % 1000 +1;
    }
    printf("\t ---\t OK \n");

    HandleT * handle = (HandleT *)LSQ_CreateSequence();
    printf("Insert front elements");
    for(i = 0; i < 50; i++)
    {
        LSQ_InsertFrontElement(handle, front[i]);
    }
    printf("\t ---\t OK \n");

    printf("Insert rear elements");
    for(i = 0; i < 50; i++)
    {
        LSQ_InsertRearElement(handle, rear[i]);
    }
    printf("\t ---\t OK \n");

//    print_LSQ(handle);    

    IteratorT * iter = LSQ_GetFrontElement(handle);
    HandleT * h2 = handle;
    IteratorT * iter2 = LSQ_GetFrontElement(h2);
    for(i = 49; i >= 0; i--)
    {
        printf("front = %d \t index i = %d \t value = %d \n",front[i], i, *LSQ_DereferenceIterator(iter));
        assert( *LSQ_DereferenceIterator(iter) == front[i] );
//        assert( *LSQ_DereferenceIterator(iter2) == front[i] );
        LSQ_AdvanceOneElement(iter);
//        LSQ_ShiftPosition(iter, -1);
    }

    LSQ_SetPosition(iter, LSQ_GetSize(handle));
//    print_LSQ(handle);    
//    printf("iter = %p \t node = %p \t value = %d \n", iter, iter->self, iter->self->value);
    for(i = 49; i >= 0; i--)
    {
        printf("rear = %d \t index i = %d \t value = %d \n",rear[i], i, *LSQ_DereferenceIterator(iter));
        assert( *LSQ_DereferenceIterator(iter) == rear[i] );
        LSQ_RewindOneElement(iter);
    }

//    print_LSQ(handle);
    printf("Destroing sequence");
    LSQ_DestroySequence(handle);
    printf("\t ---\t OK \n");
}
	

void print_LSQ(LSQ_HandleT handle)
{
    if(handle != LSQ_HandleInvalid)
    {
        HandleT * t_handler = (HandleT *)handle;
        NodeT * t_node = t_handler->head;
//        NodeT * t_node = t_handler->head->next;
        int i = 1;
        printf("\n=========BEGIN OUTPUT================\n");
        while(t_node)
        {
            printf("t_node = %p\t\tvalue = %d\t\tindex = %d\n", t_node, t_node->value, i);
            t_node = t_node->next;
            i++;
        }
        printf("=========END OUTPUT==================\n");
    }
}
