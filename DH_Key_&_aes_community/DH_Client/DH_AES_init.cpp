#include "DH_AES_init.h"

string BinInt_string_to_hex(BigInt share_key_info) {
	string key_info = share_key_info.to_string(share_key_info);
	int key_byte_length = 0;
	string AES_key = "";
	for (int i = 0; i < key_info.length(); i = i + 2) {
		unsigned char high = key_info[i];
		unsigned char low = key_info[i + 1];
		if (high == '0' && low == '0') {
			continue;
		}
		else {
			unsigned char pos_byte = 0x00;
			if (high >= '0' && high <= '9') {
				pos_byte += (high - '0');
				pos_byte *= 16;
			}
			else if (high >= 'A' && high <= 'F') {
				pos_byte += (high - 'A' + 10);
				pos_byte *= 16;
			}

			if (low >= '0' && low <= '9') {
				pos_byte += (low - '0');
			}
			else if (low >= 'A' && low <= 'F') {
				pos_byte += (low - 'A' + 10);
			}
			AES_key += pos_byte;
		}
	}
	return AES_key;
}

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

BigInt build_128_number() {
	int K = 15;
	unsigned int mod_length = 128;
	BigInt result = create_Prime(mod_length, K);
	return result;
}

BigInt build_private_key() {
	return build_128_number();
}

string build_encrypt_key(BigInt private_key, BigInt recived_info, BigInt mod_p) {
	BigInt AES_encrypt_key = recived_info.moden(private_key, mod_p);
	string encrypt_key = AES_encrypt_key.to_string(AES_encrypt_key);
	// test print
	// cout << encrypt_key << endl;
	string hex_key = BinInt_string_to_hex(AES_encrypt_key);
	// test print
	//print_ciphertext(hex_key);
	return hex_key;
}

string pack_send_key_info(BigInt private_key, BigInt mod_p, BigInt g) {
	string send_string = "$K-INFO$";
	BigInt send_data = g.moden(private_key, mod_p);
	send_string += send_data.to_string(send_data);
	return send_string;
}

BigInt unpack_rec_key_info(string rec_key_info) {
	string key_info;
	for (int i = 1; i <= rec_key_info.length(); i++)
	{
		if (rec_key_info[i] == '$' && rec_key_info.substr(0, i) == "$K-INFO") {
			key_info = rec_key_info.substr(i + 1, rec_key_info.length() - 8);
			break;
		}
	}
	BigInt key_rec(key_info);
	return key_rec;
}

string pack_send_msg(string input_msg, string AES_key, string AES_iv) {
	string send_msg = "#EN-MSG#";
	string AES_ciphertext = AES_128_CBC_encrypt(AES_key, input_msg, AES_iv);
	send_msg += AES_ciphertext;
	return send_msg;
}

string unpack_rec_msg(string rec_msg) {
	string cip;
	for (int i = 1; i <= rec_msg.length(); i++)
	{
		if (rec_msg[i] == '#' && rec_msg.substr(0, i) == "#EN-MSG") {
			cip = rec_msg.substr(i + 1, rec_msg.length() - 8);
			break;
		}
	}
	return cip;
}

BigInt unpack_rec_p(string rec_msg) {
	BigInt p;
	for (int i = 1; i <= rec_msg.length(); i++)
	{
		if (rec_msg[i] == '&' && rec_msg.substr(0, i) == "&MOD-P") {
			string mod = rec_msg.substr(i + 1, rec_msg.length() - 7);
			BigInt temp(mod);
			p = temp;
			break;
		}
	}
	return p;
}