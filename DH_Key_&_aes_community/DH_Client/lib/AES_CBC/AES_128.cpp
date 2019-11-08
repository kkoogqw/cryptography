//
// Created by kkoog on 2018/10/23.
//

#include "AES_128.h"

string fill_key_128(string key) {
	string filled_key = key;
	char fill_byte = 0;
	int org_len = key.length();
	while (filled_key.length() < 128) {
		filled_key += fill_byte;
	}
	return filled_key;
}

string fill_plaintext_128(string text) {
	string filled_text = text;
	int length = text.length();
	if (length % 16 != 0) {
		int fill_count = 16 - (length % 16);
		unsigned char fill_byte = (unsigned char)fill_count;
		for (int i = 0; i < fill_count; ++i) {
			filled_text += (char)fill_byte;
		}
	}
	return filled_text;
}

AES_128_block string_to_128_AES_block(string str) {
	AES_128_block dest;
	if (str.length() == 16) {
		string group[4] = { str.substr(0, 4), str.substr(4, 4), str.substr(8, 4), str.substr(12, 4) };
		for (int i = 0; i < 4; ++i) {
			dest.line0[i] = (unsigned char)group[i][0];
			dest.line1[i] = (unsigned char)group[i][1];
			dest.line2[i] = (unsigned char)group[i][2];
			dest.line3[i] = (unsigned char)group[i][3];
		}
	}
	else if (str.length() < 16) {
		while (str.length() < 16) {
			str += (char)0;
		}
		string group[4] = { str.substr(0, 4), str.substr(4, 4), str.substr(8, 4), str.substr(12, 4) };
		for (int i = 0; i < 4; ++i) {
			dest.line0[i] = (unsigned char)group[i][0];
			dest.line1[i] = (unsigned char)group[i][1];
			dest.line2[i] = (unsigned char)group[i][2];
			dest.line3[i] = (unsigned char)group[i][3];
		}
	}
	return dest;
}

string AES_block_128_to_string(AES_128_block t) {
	string result;
	for (int i = 0; i < 4; ++i) {
		result += (char)t.line0[i];
		result += (char)t.line1[i];
		result += (char)t.line2[i];
		result += (char)t.line3[i];
	}
	return result;
}

int get_hex_high(unsigned char hex) {
	return ((int)hex) / 16;
}

int get_hex_low(unsigned char hex) {
	return ((int)hex) % 16;
}

unsigned char multiply(unsigned char a, unsigned char b) {
	unsigned char result = 0;
	if ((b & 1) == 1) result = a;
	b = b >> 1;
	for (int i = 0; i < 8; i++) {
		if ((a > 127))
			a = (a << 1) ^ 0x1b;
		else
			a = a << 1;
		if ((b & 1) == 1) {
			result ^= a;
		}
		b >>= 1;
	}
	return result;
}

AES_128_block AES_128_block_multip(AES_128_block a, AES_128_block b) {
	// must a*b != b*a
	AES_128_block result;
	result.line0[0] = (multiply(a.line0[0], b.line0[0])) ^ (multiply(a.line0[1], b.line1[0])) ^ (multiply(a.line0[2], b.line2[0])) ^ (multiply(a.line0[3], b.line3[0]));
	result.line0[1] = (multiply(a.line0[0], b.line0[1])) ^ (multiply(a.line0[1], b.line1[1])) ^ (multiply(a.line0[2], b.line2[1])) ^ (multiply(a.line0[3], b.line3[1]));
	result.line0[2] = (multiply(a.line0[0], b.line0[2])) ^ (multiply(a.line0[1], b.line1[2])) ^ (multiply(a.line0[2], b.line2[2])) ^ (multiply(a.line0[3], b.line3[2]));
	result.line0[3] = (multiply(a.line0[0], b.line0[3])) ^ (multiply(a.line0[1], b.line1[3])) ^ (multiply(a.line0[2], b.line2[3])) ^ (multiply(a.line0[3], b.line3[3]));

	result.line1[0] = (multiply(a.line1[0], b.line0[0])) ^ (multiply(a.line1[1], b.line1[0])) ^ (multiply(a.line1[2], b.line2[0])) ^ (multiply(a.line1[3], b.line3[0]));
	result.line1[1] = (multiply(a.line1[0], b.line0[1])) ^ (multiply(a.line1[1], b.line1[1])) ^ (multiply(a.line1[2], b.line2[1])) ^ (multiply(a.line1[3], b.line3[1]));
	result.line1[2] = (multiply(a.line1[0], b.line0[2])) ^ (multiply(a.line1[1], b.line1[2])) ^ (multiply(a.line1[2], b.line2[2])) ^ (multiply(a.line1[3], b.line3[2]));
	result.line1[3] = (multiply(a.line1[0], b.line0[3])) ^ (multiply(a.line1[1], b.line1[3])) ^ (multiply(a.line1[2], b.line2[3])) ^ (multiply(a.line1[3], b.line3[3]));

	result.line2[0] = (multiply(a.line2[0], b.line0[0])) ^ (multiply(a.line2[1], b.line1[0])) ^ (multiply(a.line2[2], b.line2[0])) ^ (multiply(a.line2[3], b.line3[0]));
	result.line2[1] = (multiply(a.line2[0], b.line0[1])) ^ (multiply(a.line2[1], b.line1[1])) ^ (multiply(a.line2[2], b.line2[1])) ^ (multiply(a.line2[3], b.line3[1]));
	result.line2[2] = (multiply(a.line2[0], b.line0[2])) ^ (multiply(a.line2[1], b.line1[2])) ^ (multiply(a.line2[2], b.line2[2])) ^ (multiply(a.line2[3], b.line3[2]));
	result.line2[3] = (multiply(a.line2[0], b.line0[3])) ^ (multiply(a.line2[1], b.line1[3])) ^ (multiply(a.line2[2], b.line2[3])) ^ (multiply(a.line2[3], b.line3[3]));

	result.line3[0] = (multiply(a.line3[0], b.line0[0])) ^ (multiply(a.line3[1], b.line1[0])) ^ (multiply(a.line3[2], b.line2[0])) ^ (multiply(a.line3[3], b.line3[0]));
	result.line3[1] = (multiply(a.line3[0], b.line0[1])) ^ (multiply(a.line3[1], b.line1[1])) ^ (multiply(a.line3[2], b.line2[1])) ^ (multiply(a.line3[3], b.line3[1]));
	result.line3[2] = (multiply(a.line3[0], b.line0[2])) ^ (multiply(a.line3[1], b.line1[2])) ^ (multiply(a.line3[2], b.line2[2])) ^ (multiply(a.line3[3], b.line3[2]));
	result.line3[3] = (multiply(a.line3[0], b.line0[3])) ^ (multiply(a.line3[1], b.line1[3])) ^ (multiply(a.line3[2], b.line2[3])) ^ (multiply(a.line3[3], b.line3[3]));

	return result;
}

AES_128_block AES_128_block_xor(AES_128_block a, AES_128_block b) {
	AES_128_block result;
	for (int j = 0; j < 4; ++j) {
		result.line0[j] = a.line0[j] ^ b.line0[j];
		result.line1[j] = a.line1[j] ^ b.line1[j];
		result.line2[j] = a.line2[j] ^ b.line2[j];
		result.line3[j] = a.line3[j] ^ b.line3[j];
	}
	return result;
}

void print_block(AES_128_block b) {
	printf("%x %x %x %x\n", b.line0[0], b.line0[1], b.line0[2], b.line0[3]);
	printf("%x %x %x %x\n", b.line1[0], b.line1[1], b.line1[2], b.line1[3]);
	printf("%x %x %x %x\n", b.line2[0], b.line2[1], b.line2[2], b.line2[3]);
	printf("%x %x %x %x\n", b.line3[0], b.line3[1], b.line3[2], b.line3[3]);
}

void print_ciphertext(string cip) {
	for (int i = 0; i < cip.length(); ++i) {
		printf("%02x ", (unsigned char)cip[i]);
	}
	printf("\n");
}

void print_decrypt_result(string plaintext) {
	int pla_length = plaintext.length();
	for (int i = 0; i <= pla_length; i++) {
		if ((unsigned char)(plaintext[i]) >= 0x20 && (unsigned char)(plaintext[i]) <= 0x7e) {
			cout << plaintext[i];
		}
		else {
			break;
		}
	}
}