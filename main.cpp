#include <iostream>
#include <cstdio>
#include <Windows.h>

struct List
{
    int data;
    List *prev;
    List *next;
};

void CreateList(List **beg, List **end, const int data = 0);

void PushBack(List **end, const int data = 0);
void PushFront(List **beg, const int data = 0);
void Push(List **list, const int data = 0);
void Pop(List **list, const int data = 0);
void PopBack(List **end, int data);
void PopFront(List **beg, int data);

void PrintBack(List *end);
void PrintFront(List *beg);

void Clear(List **list);

void Zadanie(List **list);

int main(int argc, char **arv)
{

    List *beg;
    List *end;
    CreateList(&beg, &end, 5);
    PushBack(&end, 10);
    PushFront(&beg, 15);
    PrintBack(end);
    PrintFront(beg);
    Clear(&beg);
    std::cout << "End\n";
    getchar();
}

void PrintBack(List *end)
{
    List *temp = end;
    while (temp != NULL)
    {
        printf("%d%c", temp->data, ' ');
        temp = temp->next;
    }
    printf("%c", '\n');
}

void PrintFront(List *beg)
{
    List *temp = beg;
    while (temp != NULL)
    {
        printf("%d%c", temp->data, ' ');
        temp = temp->prev;
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

void PushBack(List **end, const int data)
{
    if (*end == NULL)
    {
        return;
    }
    List *temp = new List{data, NULL, *end};
    (*end)->prev = temp;
    *end = temp;
}

void PushFront(List **beg, const int data)
{

    List *temp = new List{data, *beg, NULL};
    (*beg)->next = temp;
    *beg = temp;
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
    PushBack(list);
    temp = *list;
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
}