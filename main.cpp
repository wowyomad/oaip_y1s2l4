#include <iostream>
#include <cstdio>
#include <Windows.h>

struct List
{
    int data;
    List *prev;
    List *next;
};

//функции Push, Pop, Print, Clear - универсальные и подходят
//как для указателя на начало списка, так и на конец. Сделано
//это путём проверки указателя на предыдущий(prev) элемент.
// prev == NULL - значит предыдущего элемента нет и
//*list - указатель на начало, иначе *list - указаатель на конец.

void CreateList(List **beg, List **end, const int data = 0);
void Push(List **list, const int data = 0);
void Pop(List **list, int *data = NULL);
void Print(List *list);
void Clear(List **list);

void Zadanie(List **list);

int main(int argc, char **arv)
{
    List *beg;
    List *end;
    CreateList(&beg, &end, 4);
    Push(&beg, 3);
    Push(&beg, 1);
    Print(beg);
    Print(end);
    Zadanie(&beg);
    Print(beg);
    Print(end);
    Clear(&beg);
    std::cout << "End\n";
    getchar();
}

void Print(List *list)
{
    List *temp = list;
    if (list->prev == NULL)
    {
        while (temp != NULL)
        {
            printf("%d%c", temp->data, ' ');
            temp = temp->next;
        }
    }
    else
    {
        while (temp != NULL)
        {
            printf("%d%c", temp->data, ' ');
            temp = temp->prev;
        }
    }
    printf("%c", '\n');
}

void CreateList(List **beg, List **end, const int data)
{
    List *temp = new List;
    temp->data = data;
    temp->next = temp->prev = NULL;
    *beg = *end = temp;
}

void Push(List **list, const int data)
{
    if (*list == NULL)
        return;

    List *temp = new List;
    temp->data = data;

    if ((*list)->prev == NULL)
    {
        temp->prev = NULL;
        temp->next = *list;
        (*list)->prev = temp;
        *list = temp;
    }
    else
    {
        temp->next = NULL;
        temp->prev = *list;
        (*list)->next = temp;
        *list = temp;
    }
}

void Pop(List **list, int *data)
{
    if (*list == NULL)
        return;

    if (data != NULL)
        *data = (*list)->data;

    List *temp;

    if ((*list)->prev == NULL)
    {
        temp = (*list)->next;
        temp->prev = NULL;
        delete *list;
        (*list) = temp;
    }
    else
    {
        temp = (*list)->prev;
        temp->next = NULL;
        delete *list;
        (*list) = temp;
    }
}

void Clear(List **list)
{
    List *temp;

    if ((*list)->prev == NULL)
        while (*list != NULL)
        {
            temp = *list;
            (*list) = (*list)->next;
            delete temp;
        }
    else
        while (*list != NULL)
        {
            temp = *list;
            (*list) = (*list)->prev;
            delete temp;
        }
}

void Zadanie(List **list)
{
    List *temp = *list;
    float avg = 0;
    int count = 0;

    while (temp != NULL)
    {
        avg += temp->data;
        count++;
        temp = temp->next;
    }

    avg /= count;
    List *temp1 = NULL;
    Push(list);
    temp = *list;

    //если *list - это начало
    if ((*list)->prev == NULL)
        while (temp->next != NULL)
        {
            if (temp->next->data < avg)
            {
                temp1 = temp->next;
                temp->next->next->prev = temp;
                temp->next = temp->next->next;
                delete temp1;
            }
            else
            {
                temp = temp->next;
            }
        }
    else
    {
        while (temp->prev != NULL)
        {
            if (temp->prev->data < avg)
            {
                temp1 - temp->prev;
                temp->prev->prev->next = temp;
                temp->prev = temp->prev->prev;
                delete temp1;
            }
            else
            {
                temp = temp->prev;
            }
        }
    }
    Pop(list);
}