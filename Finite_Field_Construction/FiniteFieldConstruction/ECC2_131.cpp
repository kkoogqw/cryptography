//
// Created by kkoog on 2018/10/4.
//

#include "ECC2_131.h"


ECC2_131::ECC2_131() {
    // build p(x) = x^131 + x^13 + x^2 + x + 1
    for (int i = 0; i < P_x_size; ++i) {
        if (i == 0 || i == 1 || i == 2 || i == 13 || i == 131){
            P_x[i] = 1;
        } else {
            P_x[i] = 0;
        }
    }
    //
}
ECC2_131::ECC2_131(bool x) {
    // build p(x) = x^131 + x^13 + x^2 + x + 1
    for (int i = 0; i < P_x_size; ++i) {
        if (i == 0 || i == 1 || i == 2 || i == 13 || i == 131){
            P_x[i] = 1;
        } else {
            P_x[i] = 0;
        }
    }
    //init poly:
    if (x == true){
        for (int i = 0; i < MAX_INDEX; ++i) {
            this->Polynomial[i] = 1;
        }
    } else {
        for (int i = 0; i < MAX_INDEX; ++i) {
            this->Polynomial[i] = 0;
        }
    }

}

ECC2_131::ECC2_131(int index[]) {
    // build p(x) = x^131 + x^13 + x^2 + x + 1
    for (int i = 0; i < P_x_size; ++i) {
        if (i == 0 || i == 1 || i == 2 || i == 13 || i == 131){
            P_x[i] = 1;
        } else {
            P_x[i] = 0;
        }
    }
    //init poly:
    for (int i = 0; i < MAX_INDEX; ++i) {
        this->Polynomial[i] = index[i];
    }
}

void ECC2_131::addition(const ECC2_131 that) {
    // build p(x) = x^131 + x^13 + x^2 + x + 1
    for (int i = 0; i < 132; ++i) {
        if (i == 0 || i == 1 || i == 2 || i == 13 || i == 131){
            P_x[i] = 1;
        } else {
            P_x[i] = 0;
        }
    }
    //init poly:
    for (int i = 0; i < MAX_INDEX; ++i) {
        this->Polynomial[i] = this->Polynomial[i] ^ that.Polynomial[i];
    }
}

void ECC2_131::reduction() {

}

void ECC2_131::square() {

}

void ECC2_131::multiplication() {

}

void ECC2_131::inversion() {

}

void ECC2_131::squareRoot() {

}

bool ECC2_131::check() {
    for (int i = 0; i < MAX_INDEX; ++i) {
        if(Polynomial[i] != 1 || Polynomial[i] != 0){
            return false;
        }
    }
    return true;
}

string ECC2_131::toString() {
    string ploy;
    if (this->Polynomial[0] == 1){
        ploy += "1 + ";
    }
    for (int i = 1; i < MAX_INDEX; ++i) {
        if (this->Polynomial[i] != 0){
            ploy += "x^";
            stringstream ss;
            ss << i;
            string temp;
            ss >> temp;
            ploy += temp;
            ploy += " + ";
        }
    }
    if (ploy.substr(ploy.length() - 2, ploy.length()) == "+ "){
        ploy = ploy.substr(0, ploy.length() - 2);

    }
    return ploy;
}

int* ECC2_131::toArray() {
    return this->Polynomial;
}

string ECC2_131::Px_toString() {
    string p;
    if (this->P_x[0] == 1){
        p += "1 + ";
    }
    for (int i = 1; i < P_x_size; ++i) {
        if (this->P_x[i] != 0){
            p += "x^";
            stringstream ss;
            ss << i;
            string temp;
            ss >> temp;
            p += temp;
            p += " + ";
        }
    }
    if (p.substr(p.length() - 2, p.length()) == "+ "){
        p = p.substr(0, p.length() - 2);

    }
    return p;
}

int* ECC2_131::Px_toArray() {
    return this->P_x;
}

void ECC2_131::displayArray(int *array, int size) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
}
