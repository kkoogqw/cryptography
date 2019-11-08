//
// Created by kkoog on 2018/10/23.
//

#ifndef AES_128_CBC_AES_128_CBC_H
#define AES_128_CBC_AES_128_CBC_H

#include "AES_128_encrypt.h"
#include "AES_128_decrypt.h"

AES_128_block set_IV(string iv_str);

string AES_128_CBC_encrypt(string k, string plaintext, string iv);

string AES_128_CBC_decrypt(string k, string cip, string iv);

#endif //AES_128_CBC_AES_128_CBC_H
