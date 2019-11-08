//
// Created by kkoog on 2018/10/23.
//

#ifndef AES_128_CBC_AES_128_H
#define AES_128_CBC_AES_128_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

struct AES_128_block {
	unsigned char line0[4];
	unsigned char line1[4];
	unsigned char line2[4];
	unsigned char line3[4];
};

string fill_key_128(string key);

string fill_plaintext_128(string text);

AES_128_block string_to_128_AES_block(string str);
string AES_block_128_to_string(AES_128_block t);

int get_hex_high(unsigned char hex);

int get_hex_low(unsigned char hex);

unsigned char multiply(unsigned char a, unsigned char b);

AES_128_block AES_128_block_multip(AES_128_block a, AES_128_block b);

AES_128_block AES_128_block_xor(AES_128_block a, AES_128_block b);

void print_block(AES_128_block b);

void print_ciphertext(string cip);

void print_decrypt_result(string plaintext);
#endif //AES_128_CBC_AES_128_H
