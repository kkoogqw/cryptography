//
// Created by kkoog on 2018/10/28.
//

#ifndef SHA_1_SHA_1_H
#define SHA_1_SHA_1_H

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned long word;
typedef unsigned long long dword;

vector<word> SHA_1_PAD(string input);

word f_x(word b, word c, word d, int t);

word ROLT(word in, int pos);

word getK(int t);

vector<word> SHA_1(vector<word> in);

void print_hash_result(vector<word> hash);

#endif //SHA_1_SHA_1_H
