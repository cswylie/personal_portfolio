//-----------------------------------------------------------------------------
// Arithmetic.cpp
// Main source code for Arithmetic executable
//-----------------------------------------------------------------------------
//Christian Wylie, cwylie
//2023 Winter CSE 101 PA6
//Arithmetic.cpp
//Main source code for Arithmetic executable

#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h"

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
    string number;
    string number2;
    in >> number;
    in >> number2;
    
    BigInteger A = BigInteger(number);
    BigInteger B = BigInteger(number2);

    BigInteger mult = BigInteger("3");
    BigInteger mult2 = BigInteger("2");
    BigInteger mult3 = BigInteger("16");
    BigInteger mult4 = BigInteger("9");

    out << A << endl;
    out << endl;
    out << B << endl;
    out << endl;
    out << A + B << endl;
    out << endl;
    out << A - B << endl;
    out << endl;
    out << A - A << endl;
    out << endl;
    out << (mult * A) - (mult2 * B) << endl;
    out << endl;
    out << A*B << endl;
    out << endl;
    out << A*A << endl;
    out << endl;
    out << B*B << endl;
    out << endl;
    BigInteger A2 = A;
    BigInteger B2 = B;
    A = A * A * A * A;
    B = B * B * B * B * B;
    out << (mult4 * A) + (mult3 * B) << endl; 

    in.close();
    out.close();
    return 0;
}