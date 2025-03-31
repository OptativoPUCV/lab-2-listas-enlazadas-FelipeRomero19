#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*) malloc (sizeof(List)) ;
    list->head = NULL ;
    list->tail= NULL ;
    list->current = NULL ;

    return list;
}

void * firstList(List * list) {
    if(list == NULL || list->head == NULL)
    {
        return NULL ;
    }
    list->current = list->head ;

    return list->head->data ; 
}

void * nextList(List * list) {
    if(list == NULL || list->current == NULL || list->current->next == NULL)
    {
        return NULL ;
    }
    list->current = list->current->next ;
    
    return list->current->data;
}

void * lastList(List * list) {
    if(list==NULL || list->head == NULL)
    {
        return NULL ;
    }
    while(list->current->next != NULL)
    {
        list->current = list->current->next ;
    }
    return list->current->data ;
}

void * prevList(List * list) {
    
    if(list == NULL || list->current == NULL)
    {
        return NULL ;
    }
    list->current = list->current->prev ;
    if(list->current == NULL)
    {
        return NULL;
    }

    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data) ;
    newNode->data = data ;
    newNode->prev = NULL ;
    newNode->next =  list->head ;
    if(list->head)list->head->prev = newNode ;
    list->head =  newNode ;

    if(list->tail == NULL){
        list->tail = newNode ;
    }
}

void pushBack(List * list, void * data) { //esto no sale en el readme
    Node* aux = list->head;
    while(aux->next != NULL){
        aux = aux->next ;
    }
    Node* newNode = createNode(data) ;
    aux->next = newNode;
    newNode->prev = aux ;
    
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* newNode = createNode(data) ;
    if(newNode == NULL){
        return;
    }
    if(list->current == NULL){
        list->head = newNode;
        list->tail = newNode;
    }
    else{
        newNode->prev = list->current ;
        newNode->next = list->current->next ;
        if(list->current->next != NULL){
            list->current->next->prev = newNode;
        }
        else{
            list->tail = newNode;
        }
        list->current->next = newNode;
    }
    list->current = newNode;

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list->current == NULL){
        return NULL ;
    }
    Node *izq = list->current->prev;
    Node *der = list->current->next;
    izq->next = der ;
    der->prev = izq ;
    free(list->current) ;
    list->current = NULL ;

    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}