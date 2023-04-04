//-----------------------------------------------------------------------------
// BigIntegerTest.cpp
// A test client for BigInteger ADT
//-----------------------------------------------------------------------------
//Christian Wylie, cwylie
//2023 Winter CSE 101 PA6
//BigIntegerTest.cpp
//Test code for BigIntger ADT

#include "BigInteger.h"
#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

int main() {
    /*
    BigInteger big; //default string and print work
    //Testing the actual functions themselves
    cout << "Big: " << big << endl;
    BigInteger big2 = BigInteger("14562"); //the algorithmn  breaks if you use it like this
    cout << "Big2: " << big2 << endl;
    //big2.makeZero();
    //cout << "Big2: " << big2 << endl;
    BigInteger big3 = BigInteger("12345");
    cout << "Big3: " << big3 << endl;

    BigInteger big4 = big3.add(big2);
    cout << "Big4: " << big4 << endl;

    BigInteger big5 = big2.sub(big3);
    cout << "Big5: " << big5 << endl;

    cout << "Compare Big2 & Big3: " << big3.compare(big2) << endl;

    BigInteger big6 = big3.mult(big2);
    cout << "Mult: " << big6 << endl;
    */
    //Testing the operations--------------------------------
    BigInteger A = BigInteger("3729150928554702442414149175620649235932141254958609994754881086870354096432680978993974017043517393400280356415203677444742476780562224472222470125604137189551277980367362171212444067225678772359177116881449546540702038965861964164395654700469546344046303360514086169267280531990390968431018269967602725536356259464264923063986493485397252686907417460537701591125888290685214292533968150707980477146032778794315480469863328540030290972792502783859859312394797018261343321636183470041086019167175518395121825556034255391119033649639704413255260359955129701152148110535199153752017052945142999636863598376486516579220721168164096768678790800097521542472312143230487291626846272595887082025564868641148258377596132372685002001938955882516194044765800040395427510589581300192931326584649602225549954316147167407238954252097008977547037150046068855444291240639911613631879542764207788151538410067602495753941387332622510027115559538659227916526367307536124261995940902191801615884809192434029710130888164");
    BigInteger B = BigInteger("123756284682");
    BigInteger C = BigInteger("3");
    BigInteger D = BigInteger("3");

    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "B: " << B * C << endl;
    C = A;
    A *= A;
    cout << "A^2: " << A << endl;
    A *= C;
    cout << "A^3: " << A << endl;
    A *= C;
    cout << "A^4: " << A << endl;
    A *= C;
    cout << "A^5: " << A << endl;

    cout << "A + B: " << A + B << endl;
    cout << "A - B: " << A - B << endl;
    B *= C;
    cout << "B: " << B << endl;
    cout << "A * B: " << A * B << endl;

    A *= D;
    cout << "A: " << A << endl;
    cout << "A * B: " << A * B << endl;

    A -= C;
    cout << "A: " << A << endl;
    B += D;
    cout << "B: " << B << endl;
    cout << "A + B: " << A + B << endl;

    if (A >= B) {
        cout << "A >= B" << endl;
    }
    if (A <= B) {
        cout << "A <= B" << endl;
    }
    if (C == D) {
        cout << "C = D" << endl;
    }
    if (C >= D) {
        cout << "C >= D" << endl;
    }
    if (C <= D) {
        cout << "C <= D" << endl;
    }
    if (C < D) {
        cout << "C < D" << endl;
    }
    A.negate();
    cout << "A: " << A << endl;
    if (A >= B) {
        cout << "A >= B" << endl;
    }
    A.makeZero();
    cout << "A: " << A << endl;
    return 0;
}
