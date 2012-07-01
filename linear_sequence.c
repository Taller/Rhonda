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
    return malloc(sizeof(struct _node));
}


/* Функция, уничтожающая контейнер с заданным дескриптором. Освобождает принадлежащую ему память */
void LSQ_DestroySequence(LSQ_HandleT handle)
{
    LSQ_node_ptr t = (LSQ_node_ptr)handle;
    free(t->iterator);
    free(handle);
}

/* Функция, возвращающая текущее количество элементов в контейнере */
LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)
{
    LSQ_IntegerIndexT size = 1;
    if(handle != LSQ_HandleInvalid)
    {
        LSQ_node_ptr  t = (LSQ_node_ptr)handle;
        LSQ_iterator_ptr t_iptr;
        t_iptr = t->iterator;

        do
        {
            t_iptr = t->iterator;
            t = t_iptr->next;
            size++;
        }
        while(t_iptr->next != NULL);
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
}

/* Функция, определяющая, указывает ли данный итератор на элемент, предшествующий первому в контейнере */
int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
}

/* Функция, разыменовывающая итератор. Возвращает указатель на элемент, на который ссылается данный итератор */
LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{

}

/* Следующие три функции создают итератор в памяти и возвращают его дескриптор */
/* Функция, возвращающая итератор, ссылающийся на элемент с указанным индексом */
LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
}

/* Функция, возвращающая итератор, ссылающийся на первый элемент контейнера */
LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)
{

}

/* Функция, возвращающая итератор, ссылающийся на элемент контейнера следующий за последним */
LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)
{
}

/* Функция, уничтожающая итератор с заданным дескриптором и освобождающая принадлежащую ему память */
void LSQ_DestroyIterator(LSQ_IteratorT iterator)
{

}

/* Функция, перемещающая итератор на один элемент вперед */
void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)
{
    iterator++;
}

/* Функция, перемещающая итератор на один элемент назад */
void LSQ_RewindOneElement(LSQ_IteratorT iterator)
{
    iterator--;
}

/* Функция, перемещающая итератор на заданное смещение со знаком */
void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
    iterator += shift;
}

/* Функция, устанавливающая итератор на элемент с указанным номером */
void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
    iterator = pos;
}

/* Функция, добавляющая элемент в начало контейнера */
void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
}

/* Функция, добавляющая элемент в конец контейнера */
void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    /* передается ли инициализированный список */
    if(handle == LSQ_HandleInvalid)
    {
        printf("Handle Invalid");
        return;
    }
    else
    {
        LSQ_node_ptr t_node = (LSQ_node_ptr)handle;
        LSQ_iterator_ptr t_iterator = t_node->iterator;

        LSQ_Node *new_node = (LSQ_node_ptr)malloc(sizeof(LSQ_node_ptr));
        LSQ_Iterator *new_iterator = (LSQ_iterator_ptr)malloc(sizeof(LSQ_Iterator));
        new_node->value = element;
        t_iterator->next = new_node;
//        int s = LSQ_GetSize(t_node);
//        printf("%d", LSQ_GetSize(handle));
//        new_iterator->index = LSQ_GetSize(handle);
        new_iterator->next = NULL;
        new_iterator->prev = t_node;
        new_iterator->self = new_node;
        new_node->iterator = new_iterator;
    }
}

/* Функция, добавляющая элемент в контейнер на позицию, указываемую в данный момент итератором.         */
/* Элемент, на который указывает итератор, а также все последующие, сдвигается на одну позицию в конец. */
/* Заданный итератор продолжает указывать на элемент последовательности с тем же индексом.              */
void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement)
{
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
}

/* #endif */
