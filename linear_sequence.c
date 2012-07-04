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
    LSQ_handler_ptr quit = (LSQ_handler_ptr)malloc(sizeof(LSQ_handler));
    LSQ_node_ptr new_node = (LSQ_node_ptr)malloc(sizeof(LSQ_Node));

    new_node->next = NULL;
    new_node->prev = NULL;

    quit->node_list = new_node;

    return quit;
}
/* READY                                 */
/* LSQ_HandleT LSQ_CreateSequence(void)  */


/* Функция, уничтожающая контейнер с заданным дескриптором. Освобождает принадлежащую ему память */
void LSQ_DestroySequence(LSQ_HandleT handle)
{
    LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
    LSQ_node_ptr t_node = t_handler->node_list;
    LSQ_node_ptr node_alone;

    while(t_node->next != t_node)
    {
        t_node = t_node->next;
    }

    do
    {
        t_node = t_node->prev;
        node_alone = t_node->next;
        t_node->next = t_node;

        node_alone->next = NULL;
        node_alone->prev = NULL;

        free(node_alone);
    }
    while(t_node->prev != t_node);
    node_alone = t_handler->node_list;
    free(node_alone);

    free(t_handler);
}
/* READY                                         */
/* void LSQ_DestroySequence(LSQ_HandleT handle)  */


/* Функция, возвращающая текущее количество элементов в контейнере */
LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)
{
    LSQ_IntegerIndexT size = 0;

    if(handle != LSQ_HandleInvalid)
    {
        LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
        LSQ_node_ptr t_node = t_handler->node_list;
        if(t_node->next != NULL && t_node->prev != NULL)
        {
            while(t_node->prev != t_node)
            {
                t_node = t_node->prev;
            }

            while(t_node->next != t_node)
            {
                t_node = t_node->next;
                size++;
            }
            size++;
        }
    }

    return size;
}
/* READY                                              */
/* LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)  */


/* Функция, определяющая, может ли данный итератор быть разыменован */
int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;

        if(t_iterator->self != NULL)
        {
            return 1;
        }
    }

    return 0;
}

/* Функция, определяющая, указывает ли данный итератор на элемент, следующий за последним в контейнере */
/* Функция, определяющая, указывает ли данный итератор на предпоследний элемент                        */
int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;
        LSQ_node_ptr t_node = t_iterator->self;
        LSQ_node_ptr t_node_last = t_node->next;

        if(t_node_last->next == t_node_last)
        {
            return 1;
        }
    }

    return 0;
}
/* READY                                               */
/* int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)  */


/* Функция, определяющая, указывает ли данный итератор на элемент, предшествующий первому в контейнере */
/* Функция, определяющая, указывает ли данный итератор на второй элемент */
int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;
        LSQ_node_ptr t_node = t_iterator->self;
        LSQ_node_ptr t_node_first = t_node->prev;
        if(t_node_first->prev == t_node_first)
        {
            return 1;
        }
    }
    return 0;
}
/* READY                                                  */
/* int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)  */


/* Функция, разыменовывающая итератор. Возвращает указатель на элемент, на который ссылается данный итератор */
LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        LSQ_node_ptr t_node = (LSQ_node_ptr)iterator;
        return &(t_node->value);
    }
    else
    {
        return NULL;
    }
}
/* ???? */

/* Следующие три функции создают итератор в памяти и возвращают его дескриптор */
/* Функция, возвращающая итератор, ссылающийся на элемент с указанным индексом */
/* TODO что должна возвращать функция, если индекс указан больше, количества элементов? NULL? */
LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
    int i = 0;
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
        LSQ_node_ptr t_node = (LSQ_node_ptr)t_handler->node_list;
        while(i < index && t_node != t_node->next)
        {
            t_node = t_node->next;
            i++;
        }
        LSQ_iterator_ptr t_iter = (LSQ_iterator_ptr)malloc(sizeof(LSQ_Iterator));
        t_iter->self = t_node;
        return t_iter;
    }
    else
    {
        return NULL;
    }
}

/* Функция, возвращающая итератор, ссылающийся на первый элемент контейнера */
LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)
{
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)malloc(sizeof(LSQ_Iterator));
        LSQ_node_ptr t_node = (LSQ_node_ptr)t_handler->node_list;
        while(t_node->prev != t_node)
        {
            t_node = t_node->prev;
        }

        t_iterator->self = t_node;
        return t_iterator;
    }
    else
    {
        return NULL;
    }
}
/* READY                                                  */
/* LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)  */



/* Функция, возвращающая итератор, ссылающийся на элемент контейнера следующий за последним */
/* Функция, возвращающая итератор, ссылающийся на предпоследний элемент контейнера */
LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)
{
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
        LSQ_node_ptr t_node_last = t_handler->node_list;

        while(t_node_last != t_node_last->next)
        {
            t_node_last = t_node_last->next;
        }

        LSQ_node_ptr t_node = t_node_last->prev;
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)malloc(sizeof(LSQ_Iterator));
        t_iterator->self = t_node;
        return t_iterator;
    }
    else
    {
        return NULL;
    }
}
/* READY                                                     */
/* LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)  */


/* Функция, уничтожающая итератор с заданным дескриптором и освобождающая принадлежащую ему память */
/* TODO нужно ли делать iterator-self = NULL перед free(iterator)? */
void LSQ_DestroyIterator(LSQ_IteratorT iterator)
{
    free(iterator);
}

/* Функция, перемещающая итератор на один элемент вперед */
void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;
        LSQ_node_ptr t_node = t_iterator->self;
        t_iterator->self = t_node->next;
        iterator = t_iterator;
    }
}
/* READY                                               */
/* void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)  */


/* Функция, перемещающая итератор на один элемент назад */
void LSQ_RewindOneElement(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;
        LSQ_node_ptr t_node = t_iterator->self;
        t_iterator->self = t_node->prev;
        iterator = t_iterator;
    }
}
/* READY                                              */
/* void LSQ_RewindOneElement(LSQ_IteratorT iterator)  */


/* Функция, перемещающая итератор на заданное смещение со знаком */
void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
    if(iterator != NULL)
    {
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;
        LSQ_node_ptr t_node = t_iterator->self;
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
        t_iterator->self = t_node;
        iterator = t_iterator;
    }
}
/* READY                                                                    */
/* void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)  */


/* Функция, устанавливающая итератор на элемент с указанным номером */
void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
    if(iterator != NULL)
    {
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;
        LSQ_node_ptr t_node = t_iterator->self;

        while(t_node != t_node->prev)
        {
            t_node = t_node->prev;
        }
        int i = 0;
        while(t_node != t_node->next || i < pos )
        {
            t_node = t_node->next;
            i++;
        }
        t_iterator->self = t_node;
        iterator = t_iterator;
    }
}
/* READY                                                                */
/* void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)  */



/* Функция, добавляющая элемент в начало контейнера */
void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
        LSQ_node_ptr old_first = t_handler->node_list;

        if(old_first->next == NULL && old_first->prev == NULL)
        {
            old_first->next = old_first;
            old_first->prev = old_first;
            old_first->value = element;
        }
        else
        {
            LSQ_node_ptr new_first = (LSQ_node_ptr)malloc(sizeof(LSQ_Node));

            new_first->next = old_first;
            new_first->prev = new_first;
            new_first->value = element;

            old_first->prev = new_first;

            t_handler->node_list = new_first;
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
        LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
        LSQ_node_ptr t_node = t_handler->node_list;
        if(t_node->next == NULL && t_node->prev == NULL)
        {
            t_node->value = element;
            t_node->prev = t_node;
            t_node->next = t_node;
        }
        else
        {
            LSQ_node_ptr new_node = (LSQ_node_ptr)malloc(sizeof(LSQ_Node));

            while(t_node->next != t_node)
            {
                t_node = t_node->next;
            }
            t_node->next = new_node;

            new_node->next = new_node;
            new_node->value = element;
            new_node->prev = t_node;
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
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;
        LSQ_node_ptr prev_node = t_iterator->self->prev;
        LSQ_node_ptr next_node = t_iterator->self;
        LSQ_node_ptr new_node = (LSQ_node_ptr)malloc(sizeof(LSQ_Node));

        new_node->value = newElement;
        new_node->next = next_node;
        new_node->prev = prev_node;

        prev_node->next = new_node;
        next_node->prev = new_node;

        t_iterator->self = new_node;
    }
}
/* READY                                                                               */
/* void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement) */


/* Функция, удаляющая первый элемент контейнера */
void LSQ_DeleteFrontElement(LSQ_HandleT handle)
{
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
        LSQ_node_ptr old_first = t_handler->node_list;
        LSQ_node_ptr new_first = old_first->next;

        new_first->prev = new_first;
        t_handler->node_list = new_first;

        old_first->next = NULL;
        old_first->prev = NULL;
        free(old_first);
    }
}
/* READY                                           */
/* void LSQ_DeleteFrontElement(LSQ_HandleT handle) */


/* Функция, удаляющая последний элемент контейнера */
void LSQ_DeleteRearElement(LSQ_HandleT handle)
{
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_handler_ptr t_handler = (LSQ_handler_ptr)handle;
        LSQ_node_ptr old_last = t_handler->node_list;
        while(old_last->next != old_last)
        {
            old_last = old_last->next;
        }

        LSQ_node_ptr new_last = old_last->prev;

        new_last->next = new_last;

        old_last->next = NULL;
        old_last->prev = NULL;
        free(old_last);
    }

}
/* READY                                           */
/* void LSQ_DeleteRearElement(LSQ_HandleT handle)  */



/* Функция, удаляющая элемент контейнера, указываемый заданным итератором.                 */
/* Все последующие элементы смещаются на одну позицию в сторону начала.                    */
/* Заданный итератор продолжает указывать на элемент последовательности с тем же индексом. */
void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        LSQ_iterator_ptr t_iterator = (LSQ_iterator_ptr)iterator;
        LSQ_node_ptr t_node = t_iterator->self;
        LSQ_node_ptr prev_node = t_node->prev;
        LSQ_node_ptr next_node = t_node->next;


        prev_node->next = next_node;
        next_node->prev = prev_node;

        t_iterator->self = next_node;

        t_node->next = NULL;
        t_node->prev = NULL;

        free(t_node);
    }
}
/* READY                                                */
/* void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)  */

/* #endif */
