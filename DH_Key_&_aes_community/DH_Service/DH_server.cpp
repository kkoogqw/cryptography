#include "DH_server.h"

BigInt create_Odd_Num(unsigned int n) {
	n = n / 4;
	static unsigned char hex_table[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if (n) {
		ostringstream oss;
		for (std::size_t i = 0; i < n - 1; ++i)
			oss << hex_table[rand() % 16];
		oss << hex_table[1];
		string str(oss.str());
		return BigInt(str);
	}
	else
		return BigInt::Zero;
}

BigInt create_Random_Small_Than(const BigInt& a) {
	unsigned long t = 0;

	srand(int(time(0)));
	while (t == 0) {
		t = rand();
	}
	BigInt mod(t);
	BigInt r = mod % a;
	if (r == BigInt::Zero)
		r = a - BigInt::One;
	return r;
}

bool is_Prime(const BigInt& n, const unsigned int k) {
	assert(n != BigInt::Zero);
	if (n == BigInt::Two)
		return true;
	BigInt n_1 = n - 1;
	BigInt::bit b(n_1);
	if (b.at(0) == 1)
		return false;

	for (std::size_t t = 0; t < k; ++t) {
		BigInt a = create_Random_Small_Than(n_1);
		BigInt d(BigInt::One);
		for (int i = b.size() - 1; i >= 0; --i) {
			BigInt x = d;
			d = (d * d) % n;
			if (d == BigInt::One && x != BigInt::One && x != n_1)
				return false;
			if (b.at(i)) {
				assert(d != BigInt::Zero);
				d = (a * d) % n;
			}
		}
		if (d != BigInt::One)
			return false;
	}
	return true;
}

BigInt create_Prime(unsigned int n, int it_count) {
	assert(it_count > 0);
	BigInt res = create_Odd_Num(n);
	while (!is_Prime(res, it_count)) {
		res = res + BigInt("2");
	}
	return res;
}

string build_mod_p() {
	BigInt temp_init = create_Prime(128, 20);
	BigInt mod_p = create_Prime(128, 20);
	string p_string = mod_p.to_string(mod_p);
	return p_string;
}

string pack_send_mod(string string_type_mod) {
	string send_mod = "&MOD-P&";
	send_mod += string_type_mod;
	return send_mod;
}

