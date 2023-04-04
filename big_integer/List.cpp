//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
//Christian Wylie, cwylie
//2023 Winter CSE 101 PA6
//List.cpp
//Main source code for List ADT

#include<iostream>
#include<climits>
#include<string>
#include<stdexcept> //catches exceptions, allowing the client to keep working
#include "List.h"

//Private Constructor

List::Node::Node(ListElement x) { //inside the List class, there is a struct Node, in that struct, there is a function constructor Node
    data = x;
    next = nullptr;
    prev = nullptr;
}

//Public Class Constructor & Destructor

List::List() {
    frontDummy = new Node(INT_MAX); //make nodes first so you know what to manipulate
    backDummy = new Node(INT_MIN); //make it INT_MAX so you know something is wrong if printed
    frontDummy->next = backDummy;
    frontDummy->prev = nullptr;
    backDummy->prev = frontDummy;
    backDummy->next = nullptr;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) { //creates a copy of the list
    frontDummy = new Node(INT_MAX); //create an empty list first
    backDummy = new Node(INT_MIN);
    frontDummy->next = backDummy;
    frontDummy->prev = nullptr;
    backDummy->prev = frontDummy;
    backDummy->next = nullptr;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    if (L.num_elements > 0) { //if we're copying an empty list, just leave it at that
        Node *N = L.frontDummy->next;
        while (N != L.backDummy) {
            insertBefore(N->data); //insert it continually throughout the List
            N = N->next;
        }
        num_elements = L.num_elements;
        moveFront(); //shift the cursors back to their original location
        int i = 0;
        while (i < L.pos_cursor) {
            moveNext();
            i++;
        }
    }
}

List::~List() {
    Node *temp = frontDummy;
    while (temp != nullptr) {
        Node *temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
}

// Access functions --------------------------------------------------------
int List::length() const{
    return num_elements;
}

ListElement List::front() const {
    if (!(length() > 0)) {
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
}

ListElement List::back() const {
    if (!(length() > 0)) {
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

int List::position() const{
    return pos_cursor;
}

ListElement List::peekNext() const{
    if (!(position() < length())) {
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (!(position() > 0)) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------
void List::clear() {
    if (length() > 0) {
        Node *temp = frontDummy->next; //delete everything inbetween the frontDummy and backDummy
        while (temp != backDummy) {
            Node *temp2 = temp->next;
            delete temp;
            temp = temp2;
        }
    }

    frontDummy->next = backDummy; //then reset everything back to it's current state
    frontDummy->prev = nullptr;
    frontDummy->data = INT_MIN;
    backDummy->prev = frontDummy;
    backDummy->next = nullptr;
    backDummy->data = INT_MIN;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

void List::moveBack() {
    pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext() {
    if (!(position() < length())) {
        throw std::range_error("List: moveNext(): cursor at back");
    }
    pos_cursor++;
    ListElement next = afterCursor->data;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return next;
}

ListElement List::movePrev() {
    if (!(position() > 0)) {
        throw std::range_error("List: movePrev(): cursor at front");
    }
    pos_cursor--;
    ListElement prev = beforeCursor->data;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return prev;
}

void List::insertAfter(ListElement x) {
    Node *temp = afterCursor;
    Node *insert = new Node(x);
    afterCursor = insert;
    beforeCursor->next = insert;
    insert->prev = beforeCursor;
    insert->next = temp;
    temp->prev = insert;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node *temp = beforeCursor;
    Node *insert = new Node(x);
    beforeCursor = insert;
    afterCursor->prev = insert;
    insert->next = afterCursor;
    insert->prev = temp;
    temp->next = insert;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x) {
    if (!(position() < length())) {
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (!(position() > 0)) {
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
} 

void List::eraseAfter() {
    if (!(position() < length())) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    Node *temp = afterCursor->next;
    beforeCursor->next = temp;
    temp->prev = beforeCursor;
    delete afterCursor; //delete it then set the new aftercursor to what was originally after afterCursor
    afterCursor = temp;
    num_elements--;
}

void List::eraseBefore() {
    if (!(position() > 0)) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    Node *temp = beforeCursor->prev;
    afterCursor->prev = temp;
    temp->next = afterCursor;
    delete beforeCursor;
    beforeCursor = temp;
    num_elements--;
    pos_cursor--;
}

// Other Functions ---------------------------------------------------------
int List::findNext(ListElement x) {
    int dat = 0;
    while (position() < length()) {
        dat = moveNext();
        if (dat == x) {
            return position();
        }
    }
    moveBack();
    return -1;//it wasn't found
}

int List::findPrev(ListElement x) {
    int dat = 0;
    while (position() > 0) {
        dat = movePrev();
        if (dat == x) {
            return position();
        }
    }
    moveFront(); 
    return -1;
} 

void List::cleanup() { //remove all duplicates from the List
    bool front = false;
    bool back = false;
    bool before = false;
    if (position() == 0) { //special cases for it cursor is at back or front
        front = true;
    }
    else if (position() == length()) {
        back = true;
    }
    Node *N = frontDummy->next; //main portion to delete duplicates
    while (N != backDummy) {
        before = false;
        Node *after = N->next;
        while (after != backDummy) { //go through and check if there are any duplicates of the one you're on
            if (after == beforeCursor) {
                before = true;
            }
            if (after->data == N->data) {
                if (after == beforeCursor) { //if it's both a dup and the before cursor
                    beforeCursor = beforeCursor->prev; //everytime we find out the beforeCursor is a dup, just move it again to make sure its on a non dup
                    pos_cursor--;
                }
                Node *temp = after;
                after = after->next;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                num_elements--;
                if (before == false) { //if we're only deleting stuff before the cursor, move the cursor, otherwise don't
                    pos_cursor--;
                }
            }
            else {
                after = after->next;
            }
        }
        N = N->next;
    }
    if (front == true) { //if it was already at the beginning, stay there
        moveFront();
        return;
    }
    else if (back == true) { //if it was already at the end, stay there
        moveBack();
        return;
    }
    afterCursor = beforeCursor->next;
}

List List::concat(const List& L) const { //Join together two lists
    List Con;
    Node *start1 = frontDummy->next;
    Node *start2 = L.frontDummy->next;
    while (start1 != backDummy) {
        Con.insertBefore(start1->data);
        start1 = start1->next;
    }
    while (start2 != L.backDummy) {
        Con.insertBefore(start2->data);
        start2 = start2->next;
    }
    Con.moveFront();
    return Con;
}

std::string List::to_string() const {
    Node *start = frontDummy->next;
    std::string s = "(";
    while (start != backDummy) { //stop so it doesn't accidentally print the backDummy value
        if (start == backDummy->prev) {
            s += std::to_string(start->data) + ")";
        }
        else {
            s += std::to_string(start->data) + ", ";
        }
        start = start->next;
    }
    if (length() == 0) {
        s += ")";
    }
    return s;
}

bool List::equals(const List& R) const {
    if (length() != R.length()) {
        return false;
    }
    Node *start1 = frontDummy->next;
    Node *start2 = R.frontDummy->next;
    while (start1 != nullptr) {
        if (start1->data != start2->data) {
            return false;//they aren't equal
        }
        start1 = start1->next;
        start2 = start2->next;
    }
    return true;
}

// Overriden Operators -----------------------------------------------------

std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

List& List::operator=( const List& L ) { //takes a List, L, on the right side of an = and assigns everything in it to everything in the list as 'this'
    if (this != &L) { //not a self assignment
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }

    return *this; //return the newly created assignment as a pointer
    //temp is deleted upon the return because the compiler has nothing left to do with it
}
