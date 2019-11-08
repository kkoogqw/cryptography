//
// Created by kkoog on 2018/10/4.
//
//Software Implementation of ECC2-131
//ECC2-131 Finite Field Construction
//ECC2-131 Addition
//ECC2-131 Reduction
//ECC2-131 Square
//ECC2-131 Multiplication
//ECC2-131 Inversion
//ECC2-131 Square Root
//ECC2-131 Solving the Quadratic Equation
//

#ifndef FINITEFIELDCONSTRUCTION_ECC2_131_H
#define FINITEFIELDCONSTRUCTION_ECC2_131_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
/*
 *
 *
 */

class ECC2_131
{
private:
    static const int MAX_INDEX = 131;
    static const int P_x_size = 132;
    static const int Extend_Index = 261;
    int P_x[P_x_size] = {0};
    int Polynomial[MAX_INDEX] = {0};
    int Extend_array[Extend_Index] = {0};

public:
    ECC2_131();
    ECC2_131(bool x);
    ECC2_131(int index[MAX_INDEX]);
    ECC2_131(int )

    void addition(const ECC2_131 p);
    void reduction();
    void square();
    void multiplication();
    void inversion();
    void squareRoot();

    bool check();

    int* toArray();
    int* Px_toArray();
    string Px_toString();
    string toString();
    void displayArray(int array[], int size);


};

#endif //FINITEFIELDCONSTRUCTION_ECC2_131_H
