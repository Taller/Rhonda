#include "linear_sequence.h"
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
    LSQ_HandleT quit = malloc(sizeof(LSQ_Node));
    ((LSQ_node_ptr)quit)->next = NULL;
    ((LSQ_node_ptr)quit)->prev = NULL;
    return quit;
}


/* Функция, уничтожающая контейнер с заданным дескриптором. Освобождает принадлежащую ему память */
void LSQ_DestroySequence(LSQ_HandleT handle)
{
//    LSQ_node_ptr t = (LSQ_node_ptr)handle;
//    while(t->next != t)
//    {
//        t = t->next;
//    }
//    do
//    {
//        t = t->prev;
//        if(t->next != t)
//        {
//            printf("free %p, with value",t, t->value);
//            free(t->next);
//        }
//    }
//    while(t->prev != t);
    free(handle);
}

/* Функция, возвращающая текущее количество элементов в контейнере */
LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)
{
    int size = 1;

    if(handle != NULL)
    {
        LSQ_node_ptr t_node = (LSQ_node_ptr)handle;
        printf("value = %d \t size = %d\n", t_node->value, size);
        do
        {
            t_node = t_node->next;
            size++;
            printf("value = %d \t size = %d\n", t_node->value, size);
        }
        while(t_node->next != t_node);
    }

    return size;
}

/* Функция, определяющая, может ли данный итератор быть разыменован */
int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/* Функция, определяющая, указывает ли данный итератор на элемент, следующий за последним в контейнере */
int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/* Функция, определяющая, указывает ли данный итератор на элемент, предшествующий первому в контейнере */
int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
    if(iterator != NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/* Функция, разыменовывающая итератор. Возвращает указатель на элемент, на который ссылается данный итератор */
LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{
    LSQ_node_ptr t_node = (LSQ_node_ptr)iterator;
    return &t_node->value;
}

/* Следующие три функции создают итератор в памяти и возвращают его дескриптор */
/* Функция, возвращающая итератор, ссылающийся на элемент с указанным индексом */
LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
    int i = 1;
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_node_ptr t_node = (LSQ_node_ptr)handle;
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
        LSQ_iterator_ptr t_iter = (LSQ_iterator_ptr)malloc(sizeof(LSQ_Iterator));
        LSQ_node_ptr t_node = (LSQ_node_ptr)handle;
        t_iter->self = t_node;
        return t_iter;
    }
    else
    {
        return NULL;
    }
}

/* Функция, возвращающая итератор, ссылающийся на элемент контейнера следующий за последним */
LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)
{
    (LSQ_node_ptr)handle;
    return NULL;
}

/* Функция, уничтожающая итератор с заданным дескриптором и освобождающая принадлежащую ему память */
void LSQ_DestroyIterator(LSQ_IteratorT iterator)
{

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

/* Функция, перемещающая итератор на заданное смещение со знаком */
void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
    if(iterator != NULL)
    {
        LSQ_node_ptr t_node = (LSQ_node_ptr)iterator;
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
        iterator = t_node;
    }
}

/* Функция, устанавливающая итератор на элемент с указанным номером */
void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
    if(iterator != NULL)
    {
        LSQ_node_ptr t_node = (LSQ_node_ptr)iterator;
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

        iterator = t_node;
    }
}

/* Функция, добавляющая элемент в начало контейнера */
void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if(handle == LSQ_HandleInvalid)
    {
        printf("Handle Invalid");
        return;
    }
    else
    {
        LSQ_node_ptr t_node = (LSQ_node_ptr)handle;
        LSQ_node_ptr new_node = (LSQ_node_ptr)malloc(sizeof(LSQ_Node));
        new_node->prev = t_node;
        new_node->next = t_node->next;
        new_node->value = t_node->value;
        t_node->value = element;
        t_node->next = new_node;

        printf("handle %p\n", handle);
        printf("element = %d\n", element);
        printf("new_node %p\n", new_node);
        printf("new_node->next %p\n", new_node->next);
        printf("new_node->prev %p\n", new_node->prev);
        printf("new_node->value %d\n", new_node->value);
        printf("t_node %p\n", t_node);
        printf("t_node->next %p\n", t_node->next);
        printf("t_node->prev %p\n", t_node->prev);
        printf("t_node->value %d\n", t_node->value);
        printf("=====================================\n");
    }

}

/* Функция, добавляющая элемент в конец контейнера */
void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    if(handle == LSQ_HandleInvalid)
    {
        printf("Handle Invalid");
        return;
    }
    else
    {
        LSQ_node_ptr t_node = (LSQ_node_ptr)handle;
        if(t_node->next == NULL && t_node->prev == NULL)
        {
            t_node->value = element;
            t_node->prev = t_node;
            t_node->next = t_node;
            printf("element = %d\n", element);
            printf("t_node %p\n", t_node);
            printf("t_node->next %p\n", t_node->next);
            printf("t_node->prev %p\n", t_node->prev);
            printf("t_node->value %d\n", t_node->value);
            printf("=====================================\n");
        }
        else
        {
            LSQ_node_ptr new_node = (LSQ_node_ptr)malloc(sizeof(LSQ_Node));
            t_node->prev = new_node;
            while(t_node->next != t_node)
            {
                t_node = t_node->next;
            }
            t_node->next = new_node;

            new_node->next = new_node;
            new_node->value = element;
            new_node->prev = t_node;

            printf("element = %d\n", element);
            printf("new_node %p\n", new_node);
            printf("new_node->next %p\n", new_node->next);
            printf("new_node->prev %p\n", new_node->prev);
            printf("new_node->value %d\n", new_node->value);
            printf("t_node %p\n", t_node);
            printf("t_node->next %p\n", t_node->next);
            printf("t_node->prev %p\n", t_node->prev);
            printf("t_node->value %d\n", t_node->value);
            printf("=====================================\n");
        }

    }
}

/* Функция, добавляющая элемент в контейнер на позицию, указываемую в данный момент итератором.         */
/* Элемент, на который указывает итератор, а также все последующие, сдвигается на одну позицию в конец. */
/* Заданный итератор продолжает указывать на элемент последовательности с тем же индексом.              */
void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement)
{
    if(iterator == NULL)
    {
        printf("Handle Invalid");
        return;
    }
    else
    {
        LSQ_node_ptr node_before = (LSQ_node_ptr)iterator;
        LSQ_node_ptr node_after =  node_before->prev;
        LSQ_node_ptr new_node = (LSQ_node_ptr)malloc(sizeof(LSQ_Node));
        node_after->next = new_node;
        node_before->prev = new_node;

        new_node->prev = node_after;
        new_node->next = node_before;
        new_node->value = newElement;
    }
}

/* Функция, удаляющая первый элемент контейнера */
void LSQ_DeleteFrontElement(LSQ_HandleT handle)
{
}

/* Функция, удаляющая последний элемент контейнера */
void LSQ_DeleteRearElement(LSQ_HandleT handle)
{
}

/* Функция, удаляющая элемент контейнера, указываемый заданным итератором.                 */
/* Все последующие элементы смещаются на одну позицию в сторону начала.                    */
/* Заданный итератор продолжает указывать на элемент последовательности с тем же индексом. */
void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)
{
    LSQ_node_ptr t_node = (LSQ_node_ptr)iterator;
}

/* #endif */
