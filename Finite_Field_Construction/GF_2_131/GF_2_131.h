//
// Created by kkoog on 2018/10/5.
//

#ifndef GF_2_131_GF_2_131_H
#define GF_2_131_GF_2_131_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

/*
 * ECC2-131 Addition            --> OK
 * ECC2-131 Subtraction         --> OK (Same as Add)
 * ECC2-131 Reduction(MOD)      --> OK
 * ECC2-131 Square              --> OK (Just as this * this)
 * ECC2-131 Multiplication      --> OK
 * ECC2-131 Inversion           --> OK
 *
 */

class GF_2_131 {


private:
    static const int POLY_MAX_DEGREE = 130;
    static const int P_x_DEGREE = 131;
    vector<bool> P_x;
    vector<bool> Polynomials;
    int degree;
    bool flag;

    vector<bool> xor_BIT(vector<bool> a, vector<bool> b);
    vector<bool> and_BIT(vector<bool> a, vector<bool> b);
    vector<bool> right_shift_BIT(vector<bool> a, int position);
    vector<bool> left_shift_BIT(vector<bool> a, int position);
    int vector_degree(vector<bool> v);
    void refresh();

public:
    GF_2_131();
    GF_2_131(int DEC_num);
    GF_2_131(int *index, int length);
    GF_2_131(vector<bool> p);

    void add(GF_2_131 that);        // Addition
    void sub(GF_2_131 that);        // Subtraction
    void mod();                     // Modulo
    void multip(GF_2_131 that);     // Multiplication
    void square();                  // Square
    void inverse();                 // Inverse

    int getDegree();
    vector<bool> getPolynomials();
    bool getFlag();
    void setPolynomials(vector<bool> p);
    void setPolynomials(int num);
    string Poly_toString();
    string P_x_toString();
    void printPoly_BIN();


};


#endif //GF_2_131_GF_2_131_H
