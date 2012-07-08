#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dlfcn.h>

#include "linear_sequence.h"
#include "lsq_struct.h"


int main(void)
{
    void *fhandle;
    char *ferror;

    LSQ_HandleT ( *LSQ_CreateSequence)(void);
    void (* LSQ_DestroySequence)(LSQ_HandleT handle);
    LSQ_IntegerIndexT (* LSQ_GetSize)(LSQ_HandleT handle);
    int (* LSQ_IsIteratorDereferencable)(LSQ_IteratorT iterator);
    int (* LSQ_IsIteratorPastRear)(LSQ_IteratorT iterator);
    int (* LSQ_IsIteratorBeforeFirst)(LSQ_IteratorT iterator);
    LSQ_BaseTypeT* (* LSQ_DereferenceIterator)(LSQ_IteratorT iterator);
    LSQ_IteratorT (* LSQ_GetElementByIndex)(LSQ_HandleT handle, LSQ_IntegerIndexT index);
    LSQ_IteratorT (* LSQ_GetFrontElement)(LSQ_HandleT handle);
    LSQ_IteratorT (* LSQ_GetPastRearElement)(LSQ_HandleT handle);
    void (* LSQ_DestroyIterator)(LSQ_IteratorT iterator);
    void (* LSQ_AdvanceOneElement)(LSQ_IteratorT iterator);
    void (* LSQ_RewindOneElement)(LSQ_IteratorT iterator);
    void (* LSQ_ShiftPosition)(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift);
    void (* LSQ_SetPosition)(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos);
    void (* LSQ_InsertFrontElement)(LSQ_HandleT handle, LSQ_BaseTypeT element);
    void (* LSQ_InsertRearElement)(LSQ_HandleT handle, LSQ_BaseTypeT element);
    void (* LSQ_InsertElementBeforeGiven)(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement);
    void (* LSQ_DeleteFrontElement)(LSQ_HandleT handle);
    void (* LSQ_DeleteRearElement)(LSQ_HandleT handle);
    void (* LSQ_DeleteGivenElement)(LSQ_IteratorT iterator);
    void (* insertFirstElement)(LSQ_HandleT handle, LSQ_BaseTypeT element);
    
    
    fhandle = dlopen ("lib_lsq.so", RTLD_LAZY);
    if (!fhandle) {
        fputs (dlerror(), stderr);
        exit(1);
    }
    LSQ_CreateSequence = dlsym(fhandle, "LSQ_CreateSequence");
    ferror = dlerror();
    if ( ferror != NULL)  
    {
        fputs(ferror, stderr);
        exit(1);
    }

    LSQ_DestroySequence = dlsym(fhandle, "LSQ_DestroySequence");
    
    ferror = dlerror();
    if ( ferror != NULL)  
    {
        fputs(ferror, stderr);
        exit(1);
    }

    
    
    HandleT * handler = (HandleT *)LSQ_CreateSequence();
/*    LSQ_IntegerIndexT s;
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
*/
    LSQ_DestroySequence(handler);


//    srand ( time(NULL) );
//    num = rand() % 10 +1;

    dlclose(fhandle);
    return 0;
}

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
