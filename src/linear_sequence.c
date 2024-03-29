#include "linear_sequence.h"
#include "lsq_struct.h"
#include <malloc.h>

/* Функция, создающая пустой контейнер. Возвращает назначенный ему дескриптор */
LSQ_HandleT LSQ_CreateSequence(void)
{
    HandleT * handle = malloc(sizeof(HandleT));

    NodeT * gagHead = malloc(sizeof(NodeT));
    NodeT * gagTail = malloc(sizeof(NodeT));

    *gagHead = (NodeT ) { .prev = NULL, .next = gagTail, .value = 0 };
    *gagTail = (NodeT ) { .prev = gagHead, .next = NULL, .value = 0 };

    *handle = (HandleT ) { .head = gagHead, .tail = gagTail, .length = 0};

    return handle;
}
/* READY                                 */
/* LSQ_HandleT LSQ_CreateSequence(void)  */


/* Функция, уничтожающая контейнер с заданным дескриптором. Освобождает принадлежащую ему память */
void LSQ_DestroySequence(LSQ_HandleT handle)
{
    if(handle == LSQ_HandleInvalid)
    {
        return;
    }

    while( ((HandleT *)handle)->length )
    {
        LSQ_DeleteRearElement(handle);
    }


    free(((HandleT *)handle)->head);
    free(((HandleT *)handle)->tail);
    free(handle);
}
/* READY                                         */
/* void LSQ_DestroySequence(LSQ_HandleT handle)  */


/* Функция, возвращающая текущее количество элементов в контейнере */
LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)
{
    if(handle == LSQ_HandleInvalid)
    {
        return 0;
    }

    return ((HandleT *)handle)->length;
}
/* READY                                              */
/* LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)  */


/* Функция, определяющая, может ли данный итератор быть разыменован */
int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator)
{
    if(iterator == NULL)
    {
        return 0;
    }
    
    if(((IteratorT *)iterator)->self == NULL)
    {
        return 0;
    }

    if(((IteratorT *)iterator)->handle == NULL) 
    {
        return 0;
    }

    if(LSQ_IsIteratorPastRear(iterator))
    {
        return 0;
    }

    if(LSQ_IsIteratorBeforeFirst(iterator))
    {
        return 0;
    }
    return 1;
}

/* Функция, определяющая, указывает ли данный итератор на элемент, следующий за последним в контейнере */
int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)
{
    if(iterator == NULL)
    {
        return 0;
    }

    HandleT * handle = ((IteratorT *)iterator)->handle;

    if(((IteratorT *)iterator)->self == handle->tail)
    {
        return 1;
    }
    return 0;
}


/* Функция, определяющая, указывает ли данный итератор на элемент, предшествующий первому в контейнере */
int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
    if(iterator == NULL)
    {
        return 0;
    }

    HandleT * handle = ((IteratorT *)iterator)->handle;
//    NodeT * node_iterator = ((IteratorT *)iterator)->self;
//    NodeT * node_handle = handle->head->next;

    if(((IteratorT *)iterator)->self == handle->head)
    {
        return 1;
    }
    return 0;
}


/* Функция, разыменовывающая итератор. Возвращает указатель на элемент, на который ссылается данный итератор */
LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{
    if(!LSQ_IsIteratorDereferencable(iterator))
    {
        return NULL;
    }
    return &(((NodeT *)((IteratorT *)iterator)->self)->value);
}


/* Следующие три функции создают итератор в памяти и возвращают его дескриптор */
/* Функция, возвращающая итератор, ссылающийся на элемент с указанным индексом */
LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
    if( handle == LSQ_HandleInvalid)
    {
        return NULL;
    }
    
    if(((HandleT *)handle)->length == 0)
    {
    	return NULL;
    }

    if( index < 0)
    {
        return NULL;
    }

    if( index >= ((HandleT *)handle)->length)
    {
        return NULL;
    }

    NodeT * t_node = ((HandleT *)handle)->head->next;
    int i = 0;
    while(i < index)
    {
        t_node = t_node->next;
        i++;
    }

    IteratorT * t_iterator = malloc(sizeof(IteratorT));
    t_iterator->self = t_node;
    t_iterator->handle = handle;

    return t_iterator;
}

/* Функция, возвращающая итератор, ссылающийся на первый элемент контейнера */
LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)
{
    if(handle == NULL)
    {
        return NULL;
    }
    
    if( ((HandleT *)handle)->length == 0)
    {
    	return NULL;
    }

    IteratorT * t_iterator = malloc(sizeof(IteratorT));

    t_iterator->self = ((HandleT *)handle)->head->next;
    t_iterator->handle = handle;

    return t_iterator;
}
/* READY                                                  */
/* LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)  */



/* Функция, возвращающая итератор, ссылающийся на элемент контейнера следующий за последним */
LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)
{
    if(handle == NULL)
    {
        return NULL;
    }

    if( ((HandleT *)handle)->length == 0)
    {
    	return NULL;
    }
    
    IteratorT * t_iterator = malloc(sizeof(IteratorT));

    t_iterator->self = ((HandleT *)handle)->tail;
    t_iterator->handle = handle;

    return t_iterator;
}

/* Функция, уничтожающая итератор с заданным дескриптором и освобождающая принадлежащую ему память */
void LSQ_DestroyIterator(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        free(iterator);
    }
}

/* Функция, перемещающая итератор на один элемент вперед */
void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)
{
    if(iterator == NULL)
    {
        return;
    }

    if(LSQ_IsIteratorPastRear(iterator))
    {
        return;
    }


    NodeT * next_node = ((IteratorT *)iterator)->self->next;
    if(next_node != NULL)
    {
        ((IteratorT *)iterator)->self = next_node;
    }
}
/* READY                                               */
/* void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)  */


/* Функция, перемещающая итератор на один элемент назад */
void LSQ_RewindOneElement(LSQ_IteratorT iterator)
{
    if(iterator == NULL)
    {
        return;
    }

    if(LSQ_IsIteratorBeforeFirst(iterator))
    {
        return;
    }

    NodeT * prev_node = ((IteratorT *)iterator)->self->prev;
    if(prev_node != NULL)
    {
        ((IteratorT *)iterator)->self = prev_node;
    }

}
/* READY                                              */
/* void LSQ_RewindOneElement(LSQ_IteratorT iterator)  */


/* Функция, перемещающая итератор на заданное смещение со знаком */
void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
    if(iterator == NULL)
    {
        return;
    }

	
    while(shift)
    {
        if(shift > 0)
        {
            shift--;
            LSQ_AdvanceOneElement(iterator);
        }
        if(shift < 0)
        {
            shift++;
            LSQ_RewindOneElement(iterator);
        }
    }
}
/* READY                                                                    */
/* void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)  */


/* Функция, устанавливающая итератор на элемент с указанным номером */
void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
    if(iterator == NULL)
    {
        return;
    }

    if( (pos < 0) 
        || (pos >= LSQ_GetSize(((IteratorT *)iterator)->handle)) )
    {
        return;
    }


    if(pos <= (LSQ_GetSize(((IteratorT *)iterator)->handle) - pos) )
    {
        ((IteratorT *)iterator)->self = ((HandleT *)((IteratorT *)iterator)->handle)->head->next;
        int i;
        for(i = 0; i < pos; i++)
        {
            LSQ_AdvanceOneElement(iterator);
        }
    }
    else
    {
        ((IteratorT *)iterator)->self = ((HandleT *)((IteratorT *)iterator)->handle)->tail->prev;
        int i;
        for(i = 0; i < LSQ_GetSize(((IteratorT *)iterator)->handle) - pos - 1; i++)
        {
            LSQ_RewindOneElement(iterator);
        }
    }

}
/* READY                                                                */
/* void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)  */



/* Функция, добавляющая элемент в начало контейнера */
void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if(handle == LSQ_HandleInvalid)
    {
        return;
    }

    NodeT * new_first = malloc(sizeof(NodeT));
    NodeT * old_first = ((HandleT *)handle)->head->next;
    
    new_first->prev = ((HandleT *)handle)->head;
    new_first->next = old_first;
    new_first->value = element;

    old_first->prev = new_first;
    ((HandleT *)handle)->head->next = new_first;

    ((HandleT *)handle)->length++;

}
/* READY                                                                   */
/* void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)  */




/* Функция, добавляющая элемент в конец контейнера */
void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if(handle == LSQ_HandleInvalid)
    {
        return;
    }

    NodeT * new_last = malloc(sizeof(NodeT));
    NodeT * old_last = ((HandleT *)handle)->tail->prev;

    new_last->prev = old_last;
    new_last->next = ((HandleT *)handle)->tail;
    new_last->value = element;

    old_last->next = new_last;
    ((HandleT *)handle)->tail->prev = new_last;

    ((HandleT *)handle)->length++;
}
/* READY                                                                  */
/* void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)  */


/* Функция, добавляющая элемент в контейнер на позицию, указываемую в данный момент итератором.         */
/* Элемент, на который указывает итератор, а также все последующие, сдвигается на одну позицию в конец. */
/* Заданный итератор продолжает указывать на элемент последовательности с тем же индексом.              */
void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement)
{
    if(iterator != NULL)
    {
        IteratorT * t_iterator = (IteratorT *)iterator;
        NodeT * prev_node = t_iterator->self->prev;
        NodeT * next_node = t_iterator->self;
        NodeT * new_node = malloc(sizeof(NodeT));

        new_node->value = newElement;
        new_node->next = next_node;
        new_node->prev = prev_node;

        prev_node->next = new_node;
        next_node->prev = new_node;

        t_iterator->self = new_node;
        ((HandleT *)t_iterator->handle)->length++;
    }
}
/* READY                                                                               */
/* void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement) */


/* Функция, удаляющая первый элемент контейнера */
void LSQ_DeleteFrontElement(LSQ_HandleT handle)
{
    if(handle == LSQ_HandleInvalid)
    {
        return;
    }

    if(((HandleT *)handle)->length <= 0)
    {
        return;
    }

    NodeT * gagHead = ((HandleT *)handle)->head;
    NodeT * old_first = ((HandleT *)handle)->head->next;
    NodeT * new_first = old_first->next;

    gagHead->next = new_first;
    new_first->prev = gagHead;

    free(old_first);

    ((HandleT *)handle)->length--;
}
/* READY                                           */
/* void LSQ_DeleteFrontElement(LSQ_HandleT handle) */


/* Функция, удаляющая последний элемент контейнера */
void LSQ_DeleteRearElement(LSQ_HandleT handle)
{
    if(handle == LSQ_HandleInvalid)
    {
        return;
    }

    if(((HandleT *)handle)->length <= 0)
    {
        return;
    }

    NodeT * gagTail = ((HandleT *)handle)->tail;
    NodeT * old_last = gagTail->prev;
    NodeT * new_last = old_last->prev;

    gagTail->prev = new_last;
    new_last->next = gagTail;

    free(old_last);

    ((HandleT *)handle)->length--;
}
/* READY                                           */
/* void LSQ_DeleteRearElement(LSQ_HandleT handle)  */



/* Функция, удаляющая элемент контейнера, указываемый заданным итератором.                 */
/* Все последующие элементы смещаются на одну позицию в сторону начала.                    */
/* Заданный итератор продолжает указывать на элемент последовательности с тем же индексом. */
void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)
{
    if(iterator == NULL)
    {
        return;
    }

    if( !LSQ_IsIteratorDereferencable(iterator) )
    {
        return;
    }

    NodeT * t_node = ((IteratorT *)iterator)->self;
    NodeT * prev_node = t_node->prev;
    NodeT * next_node = t_node->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    ((IteratorT *)iterator)->self = next_node;

    free(t_node);

    ((HandleT *)((IteratorT *)iterator)->handle)->length--;
}
/* READY                                                */
/* void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)  */


void print_LSQ(LSQ_HandleT handle)
{
    if(handle != LSQ_HandleInvalid)
    {
        HandleT * t_handler = (HandleT *)handle;
        NodeT  * t_node = t_handler->head;
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

/* #endif */
