//Christian Wylie, cwylie
//2023 Winter CSE 101 PA2
//List.c
//Main source code for List ADT
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

//Node Struct/Constructor/Destructor---------
// private Node type
typedef struct NodeObj Node; //could declare as a pointer here, but that would make dereferencing it later on kinda weird

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node *prev;
   Node *next;
} NodeObj;

Node *node_create() {
    Node *n = (Node *) malloc(sizeof(Node));
    assert(n != NULL); //make sure that it's not NULL after we allocate
    n->data = 0;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

void node_delete(Node **n) {
    if (*n != NULL) {
        free(*n);
        (n = NULL);
    }
}
//-------------------------------------------

// private ListObj type
typedef struct ListObj{ //front is always represented on the left, back on the right
   int length;
   int cur_ind;
   Node *front;
   Node *back;
   Node *cursor;
} ListObj;
//-------------------------------------------

//Constructor and Destructor
//-------------------------------------------
List newList(void) {
    List l = malloc(sizeof(ListObj));
    assert(l != NULL);
    l->length = 0; //default values for List
    l->cur_ind = -1;
    l->front = l->back = l->cursor = NULL;
    return l;
}

void freeList(List *pL) {
    if (*pL != NULL) {
        if ((*pL)->length != 0) {
            Node *temp = (*pL)->front;
            while (temp != NULL) {
                Node *temp2 = temp->next;
                node_delete(&temp);
                temp = temp2;
            }
        }
        free(*pL);
        *pL = NULL;
    }
}

//Access Functions
//-------------------------------------------
int length(List L) { //gives the lenght of the List
    return L->length;
}

int index(List L) { //gets the cursor index, and name is different from index in string.h
    if (L->cursor != NULL) { //check to see that it is not NULL before returning the index
        return L->cur_ind;
    }
    return -1;
}

int front(List L) { //gets the element at the front of the list
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling front on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

int back(List L) { //gets the element at the back of the list
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling front on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

int get(List L) { //gets the element at the cursor
    if (L == NULL) {
        fprintf(stderr, "List Error: calling front on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0 || L->cur_ind < 0) {
        fprintf(stderr, "List Error: calling front on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

bool equals(List A, List B) { //checks if two Lists have the same state
    if (A == NULL || B == NULL) {
        fprintf(stderr, "List Error: calling equals on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->length == 0 && B->length == 0) { //they are both empty lists
        return true;
    }
    if ((A->length == B->length) && (A->front->data == B->front->data) && (A->back->data == B->back->data)) { //all same state
        return true;
    }
    return false;
}

//Manipulation Procedures
//-------------------------------------------
void clear(List L) { //sets the state of the List back to the default
    if (L == NULL) {
        fprintf(stderr, "List Error: calling clear on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = L->front;
    while (temp != NULL) {
        Node *temp2 = temp->next;
        node_delete(&temp);
        temp = temp2;
    }
    L->length = 0;
    L->cur_ind = -1;
    L->front = L->back = L->cursor = NULL;
}

void set(List L, int x) { //Overwrites the cursor element’s data with x.
    if (L->length <= 0 || L->cur_ind < 0) {
        fprintf(stderr, "List Error: calling set on an empty List\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

void moveFront(List L) { //sets the cursor to the front
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveFront on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length != 0) { //the List is non-empty
        L->cursor = L->front;
        L->cur_ind = 0;
    }
}

void moveBack(List L) { //move cursor to the back
     if (L == NULL) {
        fprintf(stderr, "List Error: calling moveBack on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length != 0) { //the List is non-empty
        L->cursor = L->back;
        L->cur_ind = (L->length-1);
    }
}

void movePrev(List L) { //move the cursor toward the front
    if (L == NULL) {
        fprintf(stderr, "List Error: calling movePrev on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->cursor != L->front) { //if it is not the front, move it closer to the front
        L->cursor = L->cursor->prev;
        L->cur_ind -= 1;
    }
    else if (L->cursor != NULL && L->cursor == L->front) { //if it is the front, make it undefined
        L->cursor = NULL;
        L->cur_ind = -1;
    }
}

void moveNext(List L) { //move cursor toward the back
    if (L == NULL) {
        fprintf(stderr, "List Error: calling moveNext on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->cursor != L->back) { //if it is not the front, move it closer to the front
        L->cursor = L->cursor->next;
        L->cur_ind += 1;
    }
    else if (L->cursor != NULL && L->cursor == L->back) { //if it is the front, make it undefined
        L->cursor = NULL;
        L->cur_ind = -1;
    }
}

void prepend(List L, int x) { //prepend on from the front
    if (L == NULL) {
        fprintf(stderr, "List Error: calling prepend on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node *n = node_create();
    n->data = x;
    if (L->length == 0) {
        L->front = L->back = n;
    }
    else if (L->length > 0)  { //L is not empty
        Node *temp = L->front;
        n->next = temp; //make n the new front, moves from left to right
        n->prev = NULL;
        temp->prev = n;
        L->front = n;
    }
    L->length += 1;
    L->cur_ind += 1; //increase the index to offset the newly added node
}

void append(List L, int x) { //append on from the back
    if (L == NULL) {
        fprintf(stderr, "List Error: calling append on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node *n = node_create();
    n->data = x;
    if (L->length == 0) {
        L->back = L->front = n;
        L->cur_ind = 0; //0 because there is only 1 node in the list, so cursor must be at 0
    }
    else if (L->length > 0) { //L is not empty
        Node *temp = L->back;
        n->next = NULL;
        n->prev = temp;
        temp->next = n;
        L->back = n;
    }
    L->length += 1;
}

void insertBefore(List L, int x) { //insert before the cursor
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertBefore on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0 || L->cur_ind < 0) {
        fprintf(stderr, "List Error: calling insertBefore on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cur_ind == 0 && L->cursor != NULL) { //it's at the front
        prepend(L, x);
    }
    else if (L->cursor != NULL) {
        Node *n = node_create();
        n->data = x;
        Node *temp = L->cursor->prev;
        L->cursor->prev = n;
        n->next = L->cursor;
        n->prev = temp;
        temp->next = n;
        L->length += 1;
        L->cur_ind += 1; //once again, offset the index to account for the newly added Node
    }
}

void insertAfter(List L, int x) { //insert after the cursor
    if (L == NULL) {
        fprintf(stderr, "List Error: calling insertAfter on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0 || L->cur_ind < 0) {
        fprintf(stderr, "List Error: calling insertAfter on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cur_ind == (L->length -1) && L->cursor != NULL) { //it's at the back
        append(L, x);
    }
    else if (L->cursor != NULL) {
        Node *n = node_create();
        n->data = x;
        Node *temp = L->cursor->next;
        L->cursor->next = n;
        n->next = temp;
        n->prev = L->cursor;
        temp->prev = n;
        L->length += 1;
    }
}

void deleteFront(List L) { //delete front of the List
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling deleteFront on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) {
        clear(L);
        return;
    }
    Node *temp = L->front;
    L->front = temp->next;
    L->front->prev = NULL;
    node_delete(&temp); //see if this works correctly
    L->length -= 1;
    L->cur_ind -= 1; //move everything over 1 pretty much
}

void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteBack on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling deleteBack on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) {
        clear(L);
        return;
    }
    Node *temp = L->back;
    L->back = temp->prev;
    L->back->next = NULL;
    node_delete(&temp);
    if (L->cur_ind == (L->length-1)) { //makes the cursor undefined if it gets deleted
        L->cur_ind = -1;
    }
    L->length -= 1;
}

void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling delete on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0 || L->cur_ind < 0) {
        fprintf(stderr, "List Error: calling delete on empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cur_ind == 0) {
        deleteFront(L);
        return;
    }
    else if (L->cur_ind == (L->length-1)) {
        deleteBack(L);
        return;
    }
    Node *temp = L->cursor;
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    node_delete(&temp);
    L->cursor = NULL;
    L->cur_ind = -1;
    L->length -= 1;
}

//Other Operations
//-------------------------------------------
void printList(FILE* out, List L) { //prints out L to out, out should already be opened and thus should not need to be closed in this function
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) { //don't print anything if empty
        return;
    }
    Node *temp = L->front;
    while (temp != NULL) {
        if (temp->next == NULL) {
            fprintf(out, "%d", temp->data);
        }
        else {
            fprintf(out, "%d ", temp->data);
        }
        temp = temp->next;
    }
}

List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling copyList on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    List nL = newList();
    if (L->length == 0) {
        return nL;
    }
    Node *temp = L->front;
    while (temp != NULL) { //should work, maybe not though
        append(nL, temp->data);
        temp = temp->next;
    }
    return nL;
}
