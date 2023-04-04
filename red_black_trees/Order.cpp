//-----------------------------------------------------------------------------
// Order.cpp
// Main source code for Order executable
//-----------------------------------------------------------------------------
//Christian Wylie, cwylie
//2023 Winter CSE 101 PA8
//Order.cpp
//Main source code for Order executable

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
    ifstream in;
    ofstream out;
    string line;

    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }
    //open for reading and writing
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
    Dictionary D;
    int line_number = 1;
    while (getline(in, line)) {
        D.setValue(line, line_number);
        line_number += 1;
    }
    out << D << endl; //print it first as an in-order string
    out << D.pre_string() << endl; //print it second as a pre-order string

    in.close();
    out.close();
    return 0;
}