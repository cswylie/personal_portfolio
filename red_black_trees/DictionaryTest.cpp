//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test client for Dictionary ADT
//-----------------------------------------------------------------------------
//Christian Wylie, cwylie
//2023 Winter CSE 101 PA8
//DictionaryTest.cpp
//Test code for Dictionary ADT

#include "Dictionary.h"
#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

int main() {
    /*
    Dictionary B;
    B.setValue("b", 78);
    B.setValue("a", 93);
    B.setValue("forty-three", 2);
    cout << B << endl;
    cout << B.pre_string() << endl;

    B.remove("b");
    cout << B << endl;
    cout << B.pre_string() << endl;

    Dictionary D; //test default Dictionary
    D.setValue("c", 5);
    D.setValue("b", 9);
    D.setValue("a", 10);
    D.setValue("e", 4);
    D.setValue("d", 8);
    D.setValue("f", 33);
    cout << D;
    cout << D.pre_string() << endl;

    Dictionary L = D;
    D.remove("c");
    //cout << D.pre_string() << endl;
    cout << "L: " << L;
    cout << L.size() << endl;
    cout << "D: " << D;
    cout << D.size() << endl;
    D.setValue("f", 93);
    cout << "D: " << D;
    if (D.contains("a")) {
        cout << "has a" << endl;
    }
    else {
        cout << "doesn't have a" << endl;
    }
    L.setValue("maybe", 43);
    cout << L.getValue("maybe") << endl;
    cout << "L: " << L << endl;
    cout << "D: " << D << endl;
    if (D.hasCurrent()) {
        cout << "has current" << endl;
    }
    else {
        cout << "doesn't have current" << endl;
    }
    D.begin();
    if (D.hasCurrent()) {
        cout << "has current" << endl;
    }
    else {
        cout << "doesn't have current" << endl;
    }
    cout << D.currentKey() << endl;
    cout << D.currentVal() << endl;
    D.next();
    cout << D.currentKey() << endl;
    cout << D.currentVal() << endl;
    D.end();
    cout << D.currentKey() << endl;
    cout << D.currentVal() << endl;
    
    //D.next();
    //cout << D.currentKey() << endl;
    //cout << D.currentVal() << endl;
    
    D.prev();
    cout << D.currentKey() << endl;
    cout << D.currentVal() << endl;
    D.next();
    D.remove("f");
    if (D.hasCurrent()) {
        cout << "has current" << endl;
    }
    else {
        cout << "doesn't have current" << endl;
    }
    cout << "D: " << D << endl;

    cout << "Iterate through dicitonary D:" << endl;
    for (D.begin(); D.hasCurrent() != false; D.next()) { //test to see if we can iterate through the dictionary and it prints the same order
        cout << D.currentKey() << endl;
    }
    cout << endl;
    for (D.end(); D.hasCurrent() != false; D.prev()) {
        cout << D.currentKey() << endl;
    }
    cout << "D: " << D << endl;

    D.clear();
    L.clear();
    cout << "D: " << D << endl;
    cout << "L: " << D << endl;
    if (D == L) {
        cout << "they are equal" << endl;
    }
    else {
        cout << "they aren't equal" << endl;
    }
    D.setValue("a", 86);
    L.setValue("a", 86);
    cout << "D: " << D << endl;
    cout << "L: " << D << endl;
    if (D == L) {
        cout << "they are equal" << endl;
    }
    else {
        cout << "they aren't equal" << endl;
    }
    //D.setValue("yes", 4756);
    //cout << D.getValue("e") << endl;
    //D.end();
    //cout << D.currentKey() << endl;
    */
    string S[] =   { // words to insert
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };
   string T[] =   { // words to delete
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",      
                  };

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }
   
   // call operator=()
   B = A;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;

   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);

   // call copy constructor
   Dictionary C = B;

   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << A.getValue("hemiolia") << endl;
   A.getValue("hemiolia") *= 10; // change the value associated with "hemiolia"
   cout << A.getValue("hemiolia") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // remove some pairs from A
   for(int i=0; i<13; i++){ 
      A.remove(T[i]);
   }

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // do forward iteration on B
   cout << "forward iteration on B, changing values:" << endl;
   for(B.begin(); B.hasCurrent(); B.next()){
      cout << "("+B.currentKey()+", " << B.currentVal() << ") ";
      B.currentVal()++;  // change value
      cout << "("+B.currentKey()+", " << B.currentVal() << ")\n";
   }
   cout << endl;

   // do reverse iteration on C
   cout << "reverse iteration on C, changing values" << endl;
   for(C.end(); C.hasCurrent(); C.prev()){
      cout << "("+C.currentKey()+", " << C.currentVal() << ") ";
      C.currentVal()++;  // change value
      cout << "("+C.currentKey()+", " << C.currentVal() << ")\n";
   }
   cout << endl;
   
   // check exceptions
   cout << "test pre-condition errors:" << endl;
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << endl;
   
    /*
    Dictionary C;
    C.setValue("plaices", 34);
    C.setValue("ambusher", 7);
    C.setValue("crosby", 54);
    C.setValue("wattles", 2);
    C.setValue("pardoner", 4);
    C.setValue("pythons", 98);
    C.setValue("second", 7);
    C.setValue("forms", 9);
    C.setValue("impales", 8);
    cout << C.pre_string() << endl;
    */
}