/*
Created by: Benjamin Olsen
Student Number: 19481681
Purpose: To act as the file which contains all the functions to manipulate a
         linked list, and create linked lists. The list implemented is a doubly
         ended, doubly linked list, and therefore the functions implement the
         use of the tail pointer and previous pointers.
*/
/* Obtained from Benjamin Olsen (me), Previously submitted with the UCP structs
   practical and the UCP 2018 Assignment*/
#include "linkedlist.h"
LinkedList* makeEmpty(int inMax)
{
    /* Creates the pointer, allocates the space, and ensures their head and
       tail are null */
    LinkedList* list;

    list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    list->max = inMax;

    return list;
}

void insertFirst(LinkedList* list,int inPid,int inBurst)
{
    if(list->count!=list->max){
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

        newNode->pid=inPid;
        newNode->burstTime=inBurst;
        if(list->head==NULL)
        {/* If there isnt any nodes, the first is also the last */
            list->head = newNode;
            list->tail = newNode;
            newNode->next = NULL;
            newNode->prev = NULL;
            list->count++;
        }
        else
        {/* Otherwise, shuffle pointers */
            newNode->next=list->head;
            list->head->prev = newNode;
            newNode->prev=NULL;
            list->head=newNode;
            list->count++;
        }
    }
}

void insertLast(LinkedList* list,int inPid,int inBurst)
{
    if(list->count!=list->max){
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));

        newNode->pid=inPid;
        newNode->burstTime=inBurst;
        if(list->head==NULL)
        {/* If the list is empty, the end is also the start */
            list->head = newNode;
            list->tail = newNode;
            newNode->next = NULL;
            list->count++;
        }
        else
        {/* Otherwise, insert and point to it accordingly */
            newNode->prev=list->tail;
            list->tail->next=newNode;
            list->tail=newNode;
            newNode->next=NULL;
            list->count++;
        }
    }
}

void deleteFirst(LinkedList* list)
{
    ListNode* temp;

    if(list->head==NULL)
    {/* If the list is empty, nothing can be deleted */
        perror("The head was empty");
    }
    else if(list->head->next==NULL)
    {/* If the list has one element, remove the head and tail */
        free(list->head);
        list->head=NULL;
        list->tail=NULL;
        list->count--;
    }
    else
    {/* Otherwise, just remove the head and shuffle it all down */
        temp = list->head->next;
        free(list->head);
        list->head=NULL;
        list->head = temp;
        list->head->prev=NULL;
        list->count--;
    }
}

void deleteLast(LinkedList* list)
{
    ListNode* temp;
    if(list->head==NULL)
    {/* If the list is empty, nothing can be deleted */
        perror("The head was empty");
    }
    else if(list->head->next==NULL)
    {/* If the list has one item in it, remove both head and tail */
        free(list->head);
        list->head=NULL;
        list->tail=NULL;
        list->count--;
    }
    else
    {/* Otherwise, remove the tail, and point the tail to the previous */
        temp = list->tail->prev;
        free(list->tail);
        list->tail=NULL;
        list->tail = temp;
        list->tail->next=NULL;
        list->count--;
    }
}

void freeList(LinkedList* list)
{
    freeRecurse(list->head);
    free(list);
    list = NULL;
}
void freeRecurse(ListNode* cur)
{
    if(cur!= NULL)
    {/* Feels like you were here a second ago */
        /* Keeps calling until the end of the list, then frees all the
           pids + bursts and pointers going back up! */
        freeRecurse(cur->next);
        free(cur);
        cur = NULL;
    }
}
