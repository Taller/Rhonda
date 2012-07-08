#include "linear_sequence.h"
#include "lsq_struct.h"
#include <malloc.h>


/* Тип хранимых в контейнере значений */
/* typedef int LSQ_BaseTypeT; */


/* Дескриптор контейнера */
/* typedef void* LSQ_HandleT; */

/* Неинициализированное значение дескриптора контейнера */
/* #define LSQ_HandleInvalid NULL */

/* Дескриптор итератора */
/* typedef void* LSQ_IteratorT; */

/* Тип целочисленного индекса контейнера */
/* typedef int LSQ_IntegerIndexT; */


/* Функция, создающая пустой контейнер. Возвращает назначенный ему дескриптор */
LSQ_HandleT LSQ_CreateSequence(void)
{
    HandleT * handle = malloc(sizeof(HandleT));
    NodeT * node = malloc(sizeof(NodeT));

    *node = (NodeT) { .next = NULL, .prev = NULL};
    *handle = (HandleT ) { .head = node, .tail= node, .length = 0};

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

    if(((HandleT *)handle)->head->next == NULL
            || ((HandleT *)handle)->head->prev == NULL)
    {
        free(handle);
        return;
    }

    NodeT * t_node = ((HandleT *)handle)->tail;

    do
    {
        t_node = t_node->prev;
        free(t_node->next);
    }
    while(t_node->prev != t_node);

    free(t_node);
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
    if(iterator != NULL
            && ((IteratorT *)iterator)->self != NULL
            && ((IteratorT *)iterator)->handle != NULL)
    {
        NodeT * t_node = ((HandleT *)((IteratorT *)iterator)->handle)->head;
        while(t_node->next != t_node)
        {
            if(t_node == ((IteratorT *)iterator)->self)
            {
                return 1;
            }
            t_node = t_node->next;
        }
    }

    return 0;
}

/* Функция, определяющая, указывает ли данный итератор на элемент, следующий за последним в контейнере */
int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)
{
    return 0;
}


/* Функция, определяющая, указывает ли данный итератор на элемент, предшествующий первому в контейнере */
int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
    return 0;
}


/* Функция, разыменовывающая итератор. Возвращает указатель на элемент, на который ссылается данный итератор */
LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{
    if(!LSQ_IsIteratorDereferencable(iterator))
    {
        return NULL;
    }
    return &((NodeT *)iterator)->value;
}
/* ???? */

/* Следующие три функции создают итератор в памяти и возвращают его дескриптор */
/* Функция, возвращающая итератор, ссылающийся на элемент с указанным индексом */
/* TODO что должна возвращать функция, если индекс указан больше, количества элементов? NULL? */
LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
    int i = 0;
    if(handle == LSQ_HandleInvalid)
    {
        return NULL;
    }

    if(index > ((HandleT *)handle)->length)
    {
        return 0;
    }

    NodeT * t_node = ((HandleT *)handle)->head;
    while(i < index && t_node != t_node->next)
    {
        t_node = t_node->next;
        i++;
    }

    IteratorT * t_iterator = malloc(sizeof(IteratorT));
    t_iterator->self = t_node;
    t_iterator->handle = handle;
    t_iterator->index = index;

    return t_iterator;
}

/* Функция, возвращающая итератор, ссылающийся на первый элемент контейнера */
LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)
{
    if(handle == NULL)
    {
        return NULL;
    }

    IteratorT * t_iterator = malloc(sizeof(IteratorT));
    NodeT * t_node = ((HandleT *)handle)->head;

    ((IteratorT *)t_iterator)->self = t_node;
    ((IteratorT *)t_iterator)->handle = handle;
    ((IteratorT *)t_iterator)->index = 0;

    return t_iterator;
}
/* READY                                                  */
/* LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)  */



/* Функция, возвращающая итератор, ссылающийся на элемент контейнера следующий за последним */
LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)
{
    return NULL;
}

/* Функция, уничтожающая итератор с заданным дескриптором и освобождающая принадлежащую ему память */
void LSQ_DestroyIterator(LSQ_IteratorT iterator)
{
    free(iterator);
}

/* Функция, перемещающая итератор на один элемент вперед */
void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        ((IteratorT *)iterator)->self = ((IteratorT *)iterator)->self->next;
        ((IteratorT *)iterator)->index++;
    }
}
/* READY                                               */
/* void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)  */


/* Функция, перемещающая итератор на один элемент назад */
void LSQ_RewindOneElement(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        ((IteratorT *)iterator)->self = ((IteratorT *)iterator)->self->prev;
        ((IteratorT *)iterator)->index--;
    }
}
/* READY                                              */
/* void LSQ_RewindOneElement(LSQ_IteratorT iterator)  */


/* Функция, перемещающая итератор на заданное смещение со знаком */
void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
    if(iterator != NULL)
    {
        NodeT * t_node = ((IteratorT *)iterator)->self;
        while(shift)
        {
            if(shift > 0)
            {
                shift--;
                t_node = t_node->prev;
            }
            if(shift < 0)
            {
                shift++;
                t_node = t_node->next;
            }
        }
        ((IteratorT *)iterator)->self = t_node;
        ((IteratorT *)iterator)->index += shift;
    }
}
/* READY                                                                    */
/* void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)  */


/* Функция, устанавливающая итератор на элемент с указанным номером */
void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
    if(iterator != NULL)
    {
        NodeT * t_node = ((HandleT *)((IteratorT *)iterator))->head;

        int i = 0;
        while(t_node != t_node->next || i < pos )
        {
            t_node = t_node->next;
            i++;
        }
        ((IteratorT *)iterator)->self = t_node;
    }
}
/* READY                                                                */
/* void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)  */



/* Функция, добавляющая элемент в начало контейнера */
void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if(handle != LSQ_HandleInvalid)
    {
        if(((HandleT *)handle)->head->next == NULL && ((HandleT *)handle)->head->prev == NULL)
        {
            insertFirstElement(handle, element);
        }
        else
        {
            NodeT * new_first = malloc(sizeof(NodeT));

            new_first->next = ((HandleT *)handle)->head;
            new_first->prev = new_first;
            new_first->value = element;

            ((HandleT *)handle)->head->prev = new_first;

            ((HandleT *)handle)->head = new_first;
            ((HandleT *)handle)->length++;
        }
    }

}
/* READY                                                                   */
/* void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)  */




/* Функция, добавляющая элемент в конец контейнера */
void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if(handle != LSQ_HandleInvalid)
    {
        if(((HandleT *)handle)->tail->next == NULL && ((HandleT *)handle)->tail->prev == NULL)
        {
            insertFirstElement(handle, element);
        }
        else
        {
            NodeT * new_last = malloc(sizeof(NodeT));

            new_last->next = new_last;
            new_last->prev = ((HandleT *)handle)->tail;
            new_last->value = element;

            ((HandleT *)handle)->tail->next = new_last;

            ((HandleT *)handle)->tail = new_last;
            ((HandleT *)handle)->length++;
        }
    }
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

    NodeT * old_first = ((HandleT *)handle)->head;
    NodeT * new_first = old_first->next;

    new_first->prev = new_first;
    free(old_first);

    ((HandleT *)handle)->length--;
    ((HandleT *)handle)->head = new_first;
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

    NodeT * old_last = ((HandleT *)handle)->tail;
    NodeT * new_last = old_last->prev;
    new_last->next = new_last;
    free(old_last);
    ((HandleT *)handle)->length--;
    ((HandleT *)handle)->tail = new_last;
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

void insertFirstElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if(handle == LSQ_HandleInvalid)
    {
        return;
    }

    NodeT * t_node =  malloc(sizeof(NodeT));
    t_node->next = t_node;
    t_node->prev = t_node;
    t_node->value = element;

    ((HandleT *)handle)->head = t_node;
    ((HandleT *)handle)->tail = t_node;
    ((HandleT *)handle)->length = 1;
}

/* #endif */
