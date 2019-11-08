#pragma once

#include <sstream>
#include <ctime>
#include "lib/BigInt/BigInt.h"

BigInt create_Odd_Num(unsigned int n);

BigInt create_Random_Small_Than(const BigInt& a);

bool is_Prime(const BigInt& n, const unsigned int k);

BigInt create_Prime(unsigned int n, int it_count);

string build_mod_p();

string pack_send_mod(string string_type_mod);