//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for Dictionary ADT
//-----------------------------------------------------------------------------
//Christian Wylie, cwylie
//2023 Winter CSE 101 PA8
//Dictionary.cpp
//Main source code for Dictionary ADT

#include<iostream>
#include<climits>
#include<string>
#include<stdexcept> //catches exceptions, allowing the client to keep working
#include "Dictionary.h"

//private constructor
Dictionary::Node::Node(keyType k, valType v) { //initialize the basic node
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 0; //0 is black, 1 is red
}

//private functions HELPER FUNCTIONS----------------------
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val); //this is basically tree insert, so insert the subtree in a preOrderCopy order
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) { //deletes everything in the tree, sets R to nil
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        //R = nil;
    }
    //R = nil; //set R to nil
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || R->key == k) {
        return R;
    }
    else if (k < R->key) {
        return search(R->left, k);
    }
    else { // k > R->key
        return search(R->right, k);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nil) {
        throw std::logic_error("R is equal to nil");
    }
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == nil) {
        throw std::logic_error("R is equal to nil");
    }
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node *temp = N->parent;
    while (temp != nil && N == temp->right) {
        N = temp;
        temp = temp->parent;
    }
    return temp;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node *temp = N->parent;
    while (temp != nil && N == temp->left) {
        N = temp;
        temp = temp->parent;
    }
    return temp;
}

//RED-BLACK TREE HELPER FUNCTIONS-------------------------------
void Dictionary::LeftRotate(Node* N) {
    Node *y = N->right;
    //turn y->left tree into N's right subtree
    N->right = y->left;
    if (y->left != nil) {
        y->left->parent = N;
    }
    //link y's parent to N
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    }
    else if (N == N->parent->left) {
        N->parent->left = y;
    }
    else {
        N->parent->right = y;
    }

    //put N on y's left child
    y->left = N;
    N->parent = y;
}

void Dictionary::RightRotate(Node* N) {
    Node *y = N->left;
    //turn N's left subtree into y's right subtree
    N->left = y->right;
    if (y->right != nil) {
        y->right->parent = N;
    }
    //link the parents
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    }
    else if (N == N->parent->right) {
        N->parent->right = y;
    }
    else {
        N->parent->left = y;
    }
    //put N on y's right child
    y->right = N;
    N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N) {
    Node *y;
    while (N->parent->color == 1) { //1 is RED
        if (N->parent == N->parent->parent->left) {
            y = N->parent->parent->right;
            if (y->color == 1) { //case 1
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            }
            else {
                if (N == N->parent->right) { //case 2
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = 0; //case 3
                N->parent->parent->color = 1;
                RightRotate(N->parent->parent);
            }
        }
        else {
            y = N->parent->parent->left;
            if (y->color == 1) { //case 4
                N->parent->color = 0;
                y->color = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            }
            else {
                if (N == N->parent->left) { //case 5
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = 0; //case 6
                N->parent->parent->color = 1;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 0;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
    Node *w;
    while (N != root and N->color == 0) {
        if (N == N->parent->left) { //case 1
            w = N->parent->right;
            if (w->color == 1) { //w is RED
                w->color = 0;
                N->parent->color = 1;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0) { //w->left and w->right are BLACK; case 2
                w->color = 1;
                N = N->parent;
            }
            else {
                if (w->right->color == 0) { //w->right is BLACK; case 3
                    w->left->color = 0;
                    w->color = 1;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color; //case 4
                N->parent->color = 0;
                w->right->color = 0;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else {
            w = N->parent->left;
            if (w->color == 1) { //w is RED; case 5
                w->color = 0;
                N->parent->color = 1;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->left->color == 0 && w->right->color == 0) { //w->left and w->right are BLACK; case 6
                w->color = 1;
                N = N->parent;
            }
            else {
                if (w->left->color == 0) { //w->left is BLACK; case 7
                    w->right->color = 0;
                    w->color = 1;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color; //case 8
                N->parent->color = 0;
                w->left->color = 0;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 0;
}

void Dictionary::RB_Delete(Node* N) {
    Node *y = N;
    Node *x;
    int y_original_color = y->color;
    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == 0) {
            RB_DeleteFixUp(x);
    }
}

//public constructors-------------------------------------------
Dictionary::Dictionary() {
    nil = new Node("nil", INT_MAX);
    nil->right = nil;
    nil->left = nil;
    nil->parent = nil;
    nil->color = 0; //color nil BLACK
    root = nil;
    current = root;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("nil", INT_MAX);
    nil->right = nil;
    nil->left = nil;
    nil->parent = nil;
    nil->color = 0; //color nil BLACK
    root = nil;
    current = root;

    preOrderCopy(D.root, D.nil);
    num_pairs = D.num_pairs; //assign it after, otherwise it will add to the total num_pairs
}

Dictionary::~Dictionary() { //Destructor
    postOrderDelete(root);
    delete nil; //we allocated nil, so we need to now delete it
}

// Access functions --------------------------------------------------------
int Dictionary::size() const{
    return num_pairs;
}

bool Dictionary::contains(keyType k) const{
    if (search(root, k) != nil) {
        return true;
    }
    return false;
}

valType& Dictionary::getValue(keyType k) const{
    if (contains(k) == false) {
        std::string exception = "Dictionary: getValue(): key \"";
        exception += k;
        exception += "\" does not exist";
        throw std::logic_error(exception);
    }
    Node *ref = search(root, k);
    return ref->val;
}

bool Dictionary::hasCurrent() const {
    if (current != nil) {
        return true;
    }
    return false;
}

keyType Dictionary::currentKey() const {
    if (hasCurrent() != true) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (hasCurrent() != true) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


// Manipulation procedures -------------------------------------------------
void Dictionary::clear() { //clears is back to its default state
    postOrderDelete(root);
    root = nil;
    root->color = 0;
    current = root;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node *z = new Node(k, v);
    z->parent = nil; //initalize them all to nil first
    z->left = nil;
    z->right = nil;
    Node *y = nil;
    Node *x = root;
    while (x != nil) {
        y = x;
        if (k == x->key) {
            x->val = v;
            delete z;
            return;
        }
        else if (k < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil) {
        root = z;
    }
    else if (k < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = 1; //color is RED
    RB_InsertFixUp(z);
    num_pairs += 1;
}

void Dictionary::remove(keyType k) {
    if (contains(k) == false) {
        std::string exception = "Dictionary: remove(): key \"";
        exception += k;
        exception += "\" does not exist";
        throw std::logic_error(exception);
    }
    Node *z = search(root, k); //get the node that we're deleting
    if (z == current) {
        current = nil;
    }
    RB_Delete(z);
    delete z;
    num_pairs -= 1;
}

void Dictionary::begin() {
    if (size() != 0) {
        current = findMin(root);
    }
}

void Dictionary::end() {
    if (size() != 0) {
        current = findMax(root);
    }
}

void Dictionary::next() {
    if (hasCurrent() != true) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    if (current == findMax(root)) {
        current = nil;
    }
    else {
        current = findNext(current);
    }
}

void Dictionary::prev() {
    if (hasCurrent() != true) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    if (current == findMin(root)) {
        current = nil;
    }
    else {
        current = findPrev(current);
    }
}

std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string k = "";
    preOrderString(k, root);
    return k;
}

bool Dictionary::equals(const Dictionary& D) const {
    std::string s1 = "";
    std::string s2 = "";
    inOrderString(s1, root);
    D.inOrderString(s2, D.root); //we need to call it on D, otherwise it will use the nil value of this Dictionary
    if (s1 == s2) {
        return true;
    }
    return false;
}

//Overloaded Operators
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this != &D) {
        Dictionary temp = D;

        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs); 
    }
    return *this;
}
