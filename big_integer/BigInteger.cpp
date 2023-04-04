//-----------------------------------------------------------------------------
// BigInteger.cpp
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------
//Christian Wylie, cwylie
//2023 Winter CSE 101 PA6
//BigInteger.cpp
//Main source code for BigInteger ADT

#include<iostream>
#include <sstream>
#include<climits>
#include<cmath>
#include<string>
#include<stdexcept> //catches exceptions, allowing the client to keep working
#include "BigInteger.h"

/*
If, in a list representation of a number, there is a number that has two trailing 0s in front of it, like 007, it will be represented as just 7, 
so it will need to be altered to be in the same base as the current selected base.
*/

//Global Variables-------------------------------------------------------
int power = 9; //1 <= power <= 9, 9 for grading
long base = std::pow(10, power);

//Helper Functions-------------------------------------------------------
void negateList(List &L) { // Changes the sign of each integer in List L.
    if (L.length() != 0) { //only change it if there is stuff to change
        L.moveFront();
        while (L.position() < L.length()) {
            int data = L.moveNext();
            L.setBefore(-1*data);
        }
    }
}

//Overwrites the state of S with A + sgn*B, assuming A and B are of the same size
void sumList(List& S, List A, List B, int sgn) { 
    if (A.length() < B.length()) { //we need the extra zeros for the arithmetic, otherwise, it won't perform the operations correctly
        A.moveFront();
        while (A.length() < B.length()) {
            A.insertBefore(0);
        }
    }
    else { //we will take off the zeros anyway later on with the eraseZeros
        B.moveFront();
        while (B.length() < A.length()) {
            B.insertBefore(0);
        }
    }
    if (A.length() == B.length()) {
        A.moveFront();
        B.moveFront();
        while (A.position() < A.length()) { //assuming there is no 0 sign
            if (sgn < 0) {
                S.insertBefore(A.moveNext() - B.moveNext()); //add and moveNext at the same time
            }
            else if (sgn > 0) {
                S.insertBefore(A.moveNext() + B.moveNext()); //add and moveNext at the same time
            }
        }
    }
}

bool eraseZeros(List &L) { //gets rid of all zeros created at the front of the list after add/sub, and it will tell you if the entire list was all 0s
    L.moveFront();
    while (L.position() < L.length()) {
        long val = L.moveNext();
        if (val == 0) { //erase all the zeros at the front
            L.eraseBefore();
        }
        else {
            return false;
        }
    }
    return true;
}

// Performs carries from right to left (least to most significant digits), then returns the sign of the resulting integer
int normalizeList(List& L) { //we want number to be in between 0 <= num < base(10)
    int sign = 1;
    ListElement rem;
    ListElement carr;
    ListElement num;
    if (L.front() < 0) { //if it starts with a negative, flip it
        negateList(L);
        sign = -1;
    }
    L.moveBack(); //we start at the back, in front of the very last number
    while (L.position() > 0) {
        num = L.peekPrev();
        rem = num % base;
        carr = num / base;
        if (num >= base || num < 0) {
            if (num < 0 && (rem < base && rem != 0)) { //if the remainder is still not in the right region and the number was less than 0, just add to it to get it in the base range
                rem += base; //this makes it so that negative numbers actually end up in the range
                carr -= 1; //subtract because the carr is already negative, so we need to make it one less
            }
            L.setBefore(rem); //the remainder is essentially just subtracting the right number of times, and the carr over number is exactly how much we add or subtract from the next number, same as it was with a normal subtraction loop
            L.movePrev();
            if (L.position() == 0) { //if you're at the end, then you need to make sure there is space for the new remainder, this only happens if it is not already in the correct interval
                L.insertBefore(0);
            }
            L.setBefore(L.peekPrev() + carr);
            L.moveNext();
        }
        L.movePrev();
    }
    return sign;
}

// Prepends p zero digits to L, multiplying L by base^p.
void shiftList(List& L, int p) { //back of list is least significant digit, front of list is most significant digit
    L.moveBack();
    for (int i = 0; i < p; i += 1) {
        L.insertAfter(0);
    }
}

// Multiplies L (considered as a vector) by m.
void scalarMultList(List& L, ListElement m) {
    L.moveBack(); //move to the least significant bit
    while (L.position() > 0) { //stop before 0 so you don't get an error setting the -1 position
        L.movePrev();
        L.setAfter(L.peekNext() * m);
    }
}

//Public Constructors--------------------------------------------------
BigInteger::BigInteger() { //default constructor
    signum = 0;
    List digits; //initialize it as empty
}

BigInteger::BigInteger(std::string s) { //works as intended
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    bool sign = false;
    if (s[0] == '0' && s.length() == 1) {
        signum = 0;
        return;
    }
    if (s[0] == '+') {
        signum = 1;
        sign = true;
    }
    else if (s[0] == '-') {
        signum = -1;
        sign = true;
    }
    else {
        signum = 1;
    }
    int end = 0; //if there is a sign, we don't want to parse it as a long
    int marker = 0;
    if (sign == true) {
        end = 1;
    }
    int s_length = s.length();
    std::string store = "";
    if (s_length <= power) { //if the number we're using is less than the power, only represent as much as we can, including 
        for (int i = end; i < s_length; i += 1) {
            if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8'  && s[i] != '9') {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
            store += s[i];
        }
        digits.insertAfter(std::stol(store));
        return;
    }
    for (int i = s.length()-power; i >= end; i -= power) { //power is 2
        for (int j = i; j < i + power; j += 1) { //parse them in order of how many digits we want
            if (s[j] != '0' && s[j] != '1' && s[j] != '2' && s[j] != '3' && s[j] != '4' && s[j] != '5' && s[j] != '6' && s[j] != '7' && s[j] != '8'  && s[j] != '9') {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
            store += s[j];
        }
        digits.insertAfter(std::stol(store)); //convert from string to long
        store = "";
        marker = i; //store the last value that i was before the loop ended
    }
    int length = s.length(); //if the length is odd with the sign, we don't want it to accidentally activate the loop, so make sure it knows its just the numbers, no sign
    if (sign == true) {
        length--; //disregard the sign from the length
    }
    if ((length % power != 0)) { //if it is not a direct divider of the power, then grab all the leftover numbers, or if it was offset by the sign in the front
        for (int i = end; i < marker; i += 1) { //go from the end point of the last loop, might change if there is a +/-, to the last value i was
            if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8'  && s[i] != '9') {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
            store += s[i];
        }
        digits.insertAfter(std::stol(store)); //convert from string to long
    }
    if (eraseZeros(digits)) { //erase any zeros that might have been added to the front because of the difference in digits
        signum = 0;
    }
}

BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits; //copy constructor;
}


int BigInteger::sign() const {
    return signum;
}

//returns -1 if this < N, or 1 if this > N, or 0 is the same
int BigInteger::compare(const BigInteger& N) const {
    List D = N.digits;
    List D2 = digits;
    if (signum > N.signum) { //first check the signs, its the easiest way to see if they are greater or less than each other
        return 1;
    }
    else if (signum < N.signum){
        return -1;
    }
    if (digits.length() < D.length()) {
        return -1;
    }
    else if (digits.length() > D.length()) {
        return 1;
    }
    else { //if the lengths are the same
        if (digits == D) {
            return 0;
        }
        D2.moveFront(); //if they aren't straight up equal, then go through and look for where they are different, then compare
        D.moveFront();
        while (D.position() < D.length()) {
            if (D.moveNext() != D2.moveNext()) {
                if (D.peekPrev() > D2.peekPrev()) {
                    return -1;
                }
                else if (D.peekPrev() < D2.peekPrev()) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------
 // Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() { //reverse the sign only
    signum *= -1;
}

// BigInteger Arithmetic operations ----------------------------------------
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger Sum = BigInteger();
    List tot;
    List A = digits;
    if (signum == 0) {
        Sum.digits = N.digits;
        Sum.signum = N.signum;
        return Sum;
    }
    else if (N.signum == 0) {
        Sum.digits = digits;
        Sum.signum = signum;
        return Sum;
    }
    if (signum == -1) { //if this->digits is also negative, we need to let sumList know that we're adding two negatives, otherwise it's just positive
        negateList(A);
    }
    sumList(tot, A, N.digits, N.signum);
    Sum.signum = normalizeList(tot);
    if (eraseZeros(tot)) { //get rid of all zeros at the front
        Sum.signum = 0;
    }
    Sum.digits = tot;
    return Sum;
}

// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger Sub = BigInteger();
    List tot;
    List A = digits;
    if (signum == 0) {
        Sub.digits = N.digits;
        Sub.signum = N.signum*-1;
        return Sub;
    }
    else if (N.signum == 0) {
        Sub.digits = digits;
        Sub.signum = signum;
        return Sub;
    }
    if (signum == -1) { //if this->digits is also negative, we need to let sumList know that we're adding two negatives, otherwise it's just positive
        negateList(A);
    }
    sumList(tot, A, N.digits, N.signum * -1);
    Sub.signum = normalizeList(tot);
    if (eraseZeros(tot)) { //get rid of every zero at the front or all zeros if the result is 0
        Sub.signum = 0;
    }
    Sub.digits = tot;
    return Sub;
}

BigInteger BigInteger::mult(const BigInteger& N) const { //this one takes a long time and is wrong sometimes
    int shift = 0;
    BigInteger Mult = BigInteger();
    List result;
    List result2;
    if (N.signum == 0 || signum == 0) {
        return Mult;
    }
    List A; //top function
    List B; //bottom function
    bool b_greater = false;
    if (digits.length() > (N.digits).length()) { //we're going to loop through the shortest one on the bottom
        A = digits;
        B = N.digits;
        b_greater = true;
    }
    else {
        A = N.digits;
        B = digits;
    }
    B.moveBack();
    while (B.position() > 0) {
        if (b_greater == true) {
            A = digits;
        }
        else {
            A = N.digits;
        }
        ListElement val = B.movePrev();
        if (B.position() == B.length()-1) { //first time
            scalarMultList(A, val);
            normalizeList(A);
            result = A;
        }
        else { //every other time besides the first time
            scalarMultList(A, val);
            shiftList(A, shift);
            sumList(result2, A, result, 1);
            normalizeList(result2);
            result = result2;
            result2.clear(); //clear it to fill it later
        }
        shift += 1;
    }
    eraseZeros(result);
    //normalizeList(result); //if you normalize at the end, it is really fast, but for some reason it doesn't work for really really large multiplications
    Mult.signum = signum * N.signum;
    Mult.digits = result;
    return Mult;
}

std::string BigInteger::to_string() {
    std::string number = "";
    if (signum == 0) {
        return "0";
    }
    else if (signum == -1) {
        number += "-";
    }
    digits.moveFront(); //move to the most significant digit
    while (digits.position() < digits.length()) {
        ListElement print = digits.moveNext();
        long digit = std::log10(print) + 1;
        if (print == 0) { //if it's a zero, just add the rest of the zeros
            for (int i = 0; i < power-1; i += 1) {
                number += "0"; //we need to add in the zeros that have been taken out
            }
        }
        else if (((digits.position() > 1) && digit < power)) { //if it has less digits than the power and it is in the middle of the number, add zeros to fill the space
            for (int i = 0; i < power-digit; i += 1) {
                number += "0"; //we need to add in the zeros that have been taken out
            }
        }
        number += std::to_string(print);
        //number += " ";
    }
    return number;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0) {
        return true;
    }
    return false;
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) {
        return true;
    }
    return false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int op = A.compare(B); 
    if (op == -1 || op == 0) {
        return true;
    }
    return false;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {
        return true;
    }
    return false;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int op = A.compare(B); 
    if (op == 1 || op == 0) {
        return true;
    }
    return false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}
