#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "linear_sequence.h"
#include "lsq_struct.h"

#define MAX_handleALL_LEN 100
#define MAX_TEST_ATTEMPTS 1000
#define MAX_ELEMENT_VALUE 1000

void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);
void test7(void);
void print_LSQ(LSQ_HandleT handle);

LSQ_BaseTypeT front[50], rear[50], all[MAX_handleALL_LEN];
HandleT * handle;
HandleT * handleAll;

int main(void)
{
    handle = (HandleT *)LSQ_CreateSequence();
    handleAll = (HandleT *)LSQ_CreateSequence();
    int i;
    printf("Generating test data");
    srand ( time(NULL) );
    for(i = 0; i < 50; i++)
    {
        front[i] = rand() % MAX_ELEMENT_VALUE +1;
        rear[i] = rand() % MAX_ELEMENT_VALUE +1;
        all[i] =  rand() % MAX_ELEMENT_VALUE +1;
        all[i + 50] =  rand() % MAX_ELEMENT_VALUE +1;
    }
    printf("\t ---\t OK \n");

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

    printf("Insert ALL elements");
    for(i = 0; i < MAX_handleALL_LEN; i++)
    {
        LSQ_InsertRearElement(handleAll, all[i]);
    }
    printf("\t ---\t OK \n");

    /* Create and destroy sequence immediately */
    test1();

    /* Create sequence, fill front, fill rear and destroy */
    test2();

    /* Test before first and past rear */
    test3();

    /* Test moving on list with setPosition */
    test4();

    /* Test moving on list with Advance/Rewind */
    test5();

    /* Test moving on list with ShiftPosition */
    test6();

    /* Test moving on list with GetElementByIndex */
    test7();
    return 0;
}

/* Create and destroy sequence immediately */
void test1(void)
{
    printf("\nCreate and destroy sequence immediately");
    HandleT * handle1 = (HandleT *)LSQ_CreateSequence();
    IteratorT * iter = LSQ_GetFrontElement(handle1);
    LSQ_DestroyIterator(iter); 
    LSQ_DestroySequence(handle1);
    printf("\t ---\t OK \n");
}

/* Create sequence, fill front, fill rear and destroy */
void test2(void)
{
    int i;
//    print_LSQ(handle);    

    IteratorT * iter = LSQ_GetFrontElement(handle);
    for(i = 49; i >= 0; i--)
    {
//        printf("front = %d \t index i = %d \t value = %d \n",front[i], i, *LSQ_DereferenceIterator(iter));
        assert( *LSQ_DereferenceIterator(iter) == front[i] );
        LSQ_AdvanceOneElement(iter);
    }

    LSQ_SetPosition(iter, LSQ_GetSize(handle)-1);

//    print_LSQ(handle);    
//    printf("iter = %p \t node = %p \t value = %d \n", iter, iter->self, iter->self->value);

    for(i = 49; i >= 0; i--)
    {
//        printf("rear = %d \t index i = %d \t value = %d \n",rear[i], i, *LSQ_DereferenceIterator(iter));
        assert( *LSQ_DereferenceIterator(iter) == rear[i] );
        LSQ_RewindOneElement(iter);
    }

//    print_LSQ(handle);
    LSQ_DestroyIterator(iter);

}


/* Test before first and past rear */
void test3(void)
{
    IteratorT * iter = LSQ_GetFrontElement(handle);
    assert(LSQ_IsIteratorBeforeFirst(iter) == 1);
    printf("LSQ_IsIteratorBeforeFirst\t --- \t OK \n");

    IteratorT * iter2 = LSQ_GetPastRearElement(handle);
    assert(LSQ_IsIteratorPastRear(iter2) == 1);
    printf("LSQ_IsIteratorPastRear\t\t --- \t OK \n");

    LSQ_DestroyIterator(iter);
    LSQ_DestroyIterator(iter2);
}	


/* Test moving on list with setPosition */
void test4(void)
{
    int i, j;
    srand ( time(NULL) );
    IteratorT * iter = LSQ_GetFrontElement(handleAll);

//    print_LSQ(handleAll);
    printf("Testing SetPosition");
    for(i = 0; i < MAX_TEST_ATTEMPTS; i++)
    {
        j = rand() % 1000;
//        printf("\n Step = %d \t setPosition = %d ", i, j);
        LSQ_SetPosition(iter, j);
        if( j < handleAll->length )
        {
//            printf("\n Expecting value = %d \t ", all[j]);
//            printf("\n Found value = %d \t ", iter->self->value);
            assert(iter->self->value == all[j]);
        } 
    }
    printf("\t\t ---\t OK \n");
    LSQ_DestroyIterator(iter);
}	


/* Test moving on list with Advance/Rewind */
void test5(void)
{
    int i;
    IteratorT * iter = LSQ_GetFrontElement(handleAll);

//    print_LSQ(handleAll);
    printf("Testing Advance");
    for(i = 0; i < LSQ_GetSize(handleAll); i++)
    {
        assert(iter->self->value == all[i]);
        LSQ_AdvanceOneElement(iter);
    }
    printf("\t\t ---\t OK \n");


    printf("Testing Rewind");
    iter = LSQ_GetPastRearElement(handleAll);
    for(i = LSQ_GetSize(handleAll)-1; i >= 0; i--)
    {
        assert(iter->self->value == all[i]);
        LSQ_RewindOneElement(iter);
    }
    printf("\t\t ---\t OK \n");

    LSQ_DestroyIterator(iter);
}

/* Test moving on list with ShiftPosition */
void test6(void)
{
    int i, j;
    IteratorT * iter;
    srand ( time(NULL) );

//    print_LSQ(handleAll);
    printf("Testing ShiftPosition forward");
    for(i = 0; i < MAX_TEST_ATTEMPTS; i++)
    {
	iter = LSQ_GetFrontElement(handleAll);

        j = rand() % handleAll->length;
        LSQ_ShiftPosition(iter, j);
        assert(iter->self->value == all[j]);

        LSQ_DestroyIterator(iter);
    }
    printf("\t\t ---\t OK \n");

    printf("Testing ShiftPosition backward");
    for(i = 0; i < MAX_TEST_ATTEMPTS; i++)
    {
	iter = LSQ_GetPastRearElement(handleAll);

        j = rand() % handleAll->length;
        LSQ_ShiftPosition(iter, -j);
        assert(iter->self->value == all[LSQ_GetSize(handleAll) - 1 - j]);

        LSQ_DestroyIterator(iter);
    }
    printf("\t\t ---\t OK \n");
}


/* Test moving on list with GetElementByIndex */
void test7(void)
{
    int i, j;
    srand ( time(NULL) );

//    print_LSQ(handleAll);
    printf("Testing GetElementByIndex");
    for(i = 0; i < MAX_TEST_ATTEMPTS; i++)
    {
        j = rand() % handleAll->length;
        IteratorT * iter = LSQ_GetElementByIndex(handleAll, j);
//        printf("\nFound = %d \t Expecting = %d \t at index = %d", iter->self->value, all[j-1], j);
        assert(iter->self->value == all[j-1]);
        LSQ_DestroyIterator(iter);
    }
    printf("\t\t ---\t OK \n");

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
