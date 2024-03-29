#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "linear_sequence.h"

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
void test8(void);
void test9(void);                           
void test10(void);                           
void print_LSQ(LSQ_HandleT handle);

LSQ_BaseTypeT front[50], rear[50], all[MAX_handleALL_LEN];
LSQ_HandleT handle;
LSQ_HandleT handleAll;

int main(void)
{
    handle = LSQ_CreateSequence();
    handleAll = LSQ_CreateSequence();
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

    /* Test delete with DeleteFrontElement */
    test8();

    /* Test delete with DeleteRearElement */
    test9(); 

    /* Test IsIteratorDereferencable, DeleteGivenElement pastReaer, beforeFirst */
    test10();
    return 0;
}

/* Create and destroy sequence immediately */
void test1(void)
{
    printf("Testing create and destroy sequence immediately");
    LSQ_HandleT handle1 = LSQ_CreateSequence();
    assert( handle1 != NULL);
    LSQ_IteratorT iter = LSQ_GetFrontElement(handle1);
    assert( iter == NULL);
    /* попытка удаления из пустой очереди */
    LSQ_DeleteFrontElement(handle1);
    LSQ_DeleteRearElement(handle1); 

    int i;
    for(i = 0; i < MAX_handleALL_LEN; i++)
    {
        LSQ_InsertRearElement(handle1, all[i]);
    } 

    LSQ_DestroyIterator(iter); 
    LSQ_DestroySequence(handle1);
    printf("\t ---\t OK \n");
}

/* Checking front and rear filling */
void test2(void)
{
    int i;
//    print_LSQ(handle);    

    LSQ_IteratorT iter = LSQ_GetFrontElement(handle);
    assert( iter != NULL);
    for(i = 49; i >= 0; i--)
    {
//        printf("front = %d \t index i = %d \t value = %d \n",front[i], i, *LSQ_DereferenceIterator(iter));
        assert( *LSQ_DereferenceIterator(iter) == front[i] );
        assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1 );
        LSQ_AdvanceOneElement(iter);
    }

    LSQ_SetPosition(iter, LSQ_GetSize(handle)-1);
    assert( iter != NULL);

//    print_LSQ(handle);    
//    printf("iter = %p \t node = %p \t value = %d \n", iter, iter->self, iter->self->value);

    for(i = 49; i >= 0; i--)
    {
//        printf("rear = %d \t index i = %d \t value = %d \n",rear[i], i, *LSQ_DereferenceIterator(iter));
        assert( *LSQ_DereferenceIterator(iter) == rear[i] );
        assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1 );
        LSQ_RewindOneElement(iter);
    }

//    print_LSQ(handle);
    LSQ_DestroyIterator(iter);

}


/* Test before first and past rear */
void test3(void)
{
    LSQ_IteratorT iter = LSQ_GetFrontElement(handle);
    assert( iter != NULL);
    assert(LSQ_IsIteratorBeforeFirst(iter) != 1);
    LSQ_RewindOneElement(iter);
    assert(LSQ_IsIteratorBeforeFirst(iter) == 1);
    printf("LSQ_IsIteratorBeforeFirst\t --- \t OK \n");


    LSQ_IteratorT iter2 = LSQ_GetPastRearElement(handle);
    assert( iter2 != NULL);
    assert(LSQ_IsIteratorPastRear(iter2) == 1);
    LSQ_RewindOneElement(iter2);
    assert(LSQ_IsIteratorPastRear(iter2) != 1);
    printf("LSQ_IsIteratorPastRear\t\t --- \t OK \n");

    LSQ_DestroyIterator(iter);
    LSQ_DestroyIterator(iter2);
}	


/* Test moving on list with setPosition */
void test4(void)
{
    int i, j;
    srand ( time(NULL) );
    LSQ_IteratorT iter = LSQ_GetFrontElement(handleAll);
    assert( iter != NULL);

//    print_LSQ(handleAll);
    printf("Testing SetPosition");
    for(i = 0; i < MAX_TEST_ATTEMPTS; i++)
    {
        j = rand() % 1000;
//        printf("\n Step = %d \t setPosition = %d ", i, j);
        LSQ_SetPosition(iter, j);
        if( j < LSQ_GetSize(handleAll))
        {
//            printf("\n Expecting value = %d \t ", all[j]);
//            printf("\n Found value = %d \t ", iter->self->value);
            assert( *LSQ_DereferenceIterator(iter) == all[j]);
            assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1);
        } 
    }
    printf("\t\t ---\t OK \n");
    LSQ_DestroyIterator(iter);
}	


/* Test moving on list with Advance/Rewind */
void test5(void)
{
    int i;
    LSQ_IteratorT iter = LSQ_GetFrontElement(handleAll);
    assert( iter != NULL);

//    print_LSQ(handleAll);
    printf("Testing Advance");
    for(i = 0; i < LSQ_GetSize(handleAll); i++)
    {
        assert( *LSQ_DereferenceIterator(iter) == all[i]);
        assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1);
        LSQ_AdvanceOneElement(iter);
    }
    printf("\t\t ---\t OK \n");


    printf("Testing Rewind");
    iter = LSQ_GetPastRearElement(handleAll);
    for(i = LSQ_GetSize(handleAll)-1; i >= 0; i--)
    {
        LSQ_RewindOneElement(iter);
        assert( *LSQ_DereferenceIterator(iter) == all[i]);
        assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1);
    }
    printf("\t\t ---\t OK \n");

    LSQ_DestroyIterator(iter);
}

/* Test moving on list with ShiftPosition */
void test6(void)
{
    int i, j;
    LSQ_IteratorT iter;
    srand ( time(NULL) );

//    print_LSQ(handleAll);
    printf("Testing ShiftPosition forward");
    for(i = 0; i < MAX_TEST_ATTEMPTS; i++)
    {
	iter = LSQ_GetFrontElement(handleAll);
        assert( iter != NULL);

        j = rand() % LSQ_GetSize(handleAll);
        LSQ_ShiftPosition(iter, j);
        assert(*LSQ_DereferenceIterator(iter) == all[j]);
        assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1);

        LSQ_DestroyIterator(iter);
    }
    printf("\t\t ---\t OK \n");

    printf("Testing ShiftPosition backward");
    for(i = 0; i < MAX_TEST_ATTEMPTS; i++)
    {
        iter = LSQ_GetPastRearElement(handleAll);
        LSQ_RewindOneElement(iter);
        assert( iter != NULL);

        j = rand() % LSQ_GetSize(handleAll);
        LSQ_ShiftPosition(iter, -j);
        assert( *LSQ_DereferenceIterator(iter) == all[LSQ_GetSize(handleAll) - 1 - j]);
        assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1);

        LSQ_DestroyIterator(iter);
//        printf("i = %d \t j = %d\n", i, j);

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
        j = rand() % LSQ_GetSize(handleAll);
//        printf("\ni = %d \t j = %d \t size = %d", i , j, LSQ_GetSize(handleAll));
        LSQ_IteratorT iter = LSQ_GetElementByIndex(handleAll, j);
        assert( iter != NULL);
//        printf("\nFound = %d \t Expecting = %d \t", *LSQ_DereferenceIterator(iter), all[j]);
        assert( *LSQ_DereferenceIterator(iter) == all[j]);
        assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1);

        LSQ_DestroyIterator(iter);
    }
    printf("\t\t ---\t OK \n");

}


/* Test delete with DeleteFrontElement */
void test8(void)
{
    int i, j;

//    print_LSQ(handleAll);

    printf("Testing DeleteFrontElement");
    i = 0;
    while(LSQ_GetSize(handleAll))
    {
        LSQ_IteratorT iter = LSQ_GetFrontElement(handleAll);
        assert( iter != NULL);
//        print_LSQ(handleAll);
        for(j = i; j < LSQ_GetSize(handleAll); j++)
        {
//            printf("\nFound = %d \t Expecting = %d \t at index = %d", *LSQ_DereferenceIterator(iter), all[j], j);
            assert( *LSQ_DereferenceIterator(iter) == all[j]);
            assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1);
            LSQ_AdvanceOneElement(iter);
        }
        LSQ_DestroyIterator(iter);
        LSQ_DeleteFrontElement(handleAll);
        i++;
    }
    printf("\t\t ---\t OK \n");
    for(i = 0; i < MAX_handleALL_LEN; i++)
    {
        LSQ_InsertRearElement(handleAll, all[i]);
    }
}

/* Test delete with DeleteRearElement */
void test9(void)
{
    int i, j;

    printf("Testing DeleteRearElement");
    while(LSQ_GetSize(handleAll))
    {
        LSQ_IteratorT iter = LSQ_GetFrontElement(handleAll);
        assert( iter != NULL);
//        print_LSQ(handleAll);
        for(j = 0; j < LSQ_GetSize(handleAll); j++)
        {
//            printf("\nFound = %d \t Expecting = %d \t at index = %d", *LSQ_DereferenceIterator(iter), all[j], j);
            assert( *LSQ_DereferenceIterator(iter) == all[j]);
            assert( *LSQ_DereferenceIterator(iter) != MAX_ELEMENT_VALUE + 1);
            LSQ_AdvanceOneElement(iter);
        }
        LSQ_DestroyIterator(iter);
        LSQ_DeleteRearElement(handleAll);
    }
    printf("\t\t ---\t OK \n");
    for(i = 0; i < MAX_handleALL_LEN; i++)
    {
        LSQ_InsertRearElement(handleAll, all[i]);
    }
}

/* Test IsIteratorDereferencable, DeleteGivenElement pastReaer, beforeFirst */
void test10(void)
{
    int i, j;

    printf("Testing IsIteratorDereferencable");
    LSQ_IteratorT iterator = LSQ_GetPastRearElement(handleAll);
    assert(LSQ_IsIteratorDereferencable(iterator) == 0);
    assert(LSQ_IsIteratorPastRear(iterator) == 1);
    LSQ_DeleteGivenElement(iterator);
    LSQ_DestroyIterator(iterator);
    printf("\t\t ---\t OK \n");
    
    iterator = LSQ_GetFrontElement(handleAll);
    LSQ_RewindOneElement(iterator);
    printf("Testing IsIteratorBeforeFirst");
    assert(LSQ_IsIteratorDereferencable(iterator) == 0);
    assert(LSQ_IsIteratorBeforeFirst(iterator) == 1);
    LSQ_DeleteGivenElement(iterator);
    LSQ_DestroyIterator(iterator);
    printf("\t\t ---\t OK \n");
}


/*
void print_LSQ(LSQ_HandleT handle)
{
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_HandleT * t_handler = (HandleT *)handle;
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
        printf("=========TOTAL \t %d\t==================\n",t_handler->length);
        printf("=========END OUTPUT\t==================\n");
    }
}
*/
