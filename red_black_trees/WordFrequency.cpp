//-----------------------------------------------------------------------------
// WordFrequency.cpp
// Main source code for Order executable
//-----------------------------------------------------------------------------
//Christian Wylie, cwylie
//2023 Winter CSE 101 PA8
//WordFrequency.cpp
//Main source code for Order executable

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
    int length;
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string token;
    //string delim = " ";
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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
    while (getline(in, line)) {
        len = line.length();
        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        string token_lower = "";
        if (token != "") { //stop it from adding nothing to the dictionary
            length = token.length();
            for (int i = 0; i < length; i += 1) { //convert to lower case
                token_lower += tolower(token[i]);
            }
            if (D.contains(token_lower)) {
                D.setValue(token_lower, D.getValue(token_lower) + 1);
            }
            else {
                D.setValue(token_lower, 1);
            }
        }
        while(token!=""){  // we have a token
            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
            if (token == "") { //stop it from adding nothing to the dictionary
                break;
            }
            token_lower = "";
            length = token.length();
            for (int i = 0; i < length; i += 1) {
                token_lower += tolower(token[i]);
            }
            if (D.contains(token_lower)) {
                D.setValue(token_lower, D.getValue(token_lower) + 1);
            }
            else {
                D.setValue(token_lower, 1);
            }
        }
    }
    out << D << endl; //print it first as an in-order string

    in.close();
    out.close();
    return 0;
}