#pragma once

#include <sstream>
#include <ctime>
#include "lib/BigInt/BigInt.h"
#include "lib/AES_CBC/AES_128_CBC.h"

string BinInt_string_to_hex(BigInt share_key_info);

BigInt create_Odd_Num(unsigned int n);

BigInt create_Random_Small_Than(const BigInt& a);

bool is_Prime(const BigInt& n, const unsigned int k);

BigInt create_Prime(unsigned int n, int it_count);

BigInt build_128_number();

BigInt build_private_key();

string build_encrypt_key(BigInt private_key, BigInt recived_info, BigInt mod_p);

string pack_send_key_info(BigInt private_key, BigInt mod_p, BigInt g);

BigInt unpack_rec_key_info(string rec_key_info);

string pack_send_msg(string input_msg, string AES_key, string AES_iv);

string unpack_rec_msg(string rec_msg);

BigInt unpack_rec_p(string rec_msg);
