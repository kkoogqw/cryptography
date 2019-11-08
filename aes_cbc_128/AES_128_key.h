//
// Created by kkoog on 2018/10/23.
//

#ifndef AES_128_CBC_AES_128_KEY_H
#define AES_128_CBC_AES_128_KEY_H

#include "AES_128.h"


class AES_128_key {

private:
    string key;
    static const int ROUND = 10;
    static const int NK = 4;
    AES_128_block org_key;
    AES_128_block ext_key[ROUND + 1];

    AES_128_block g_x(AES_128_block ext_key_block, int pos);

public:
    AES_128_key();
    AES_128_key(string p);

    AES_128_block get_encrypt_key(int round);

    AES_128_block get_decrypt_key(int round);

};


#endif //AES_128_CBC_AES_128_KEY_H
