//
// Created by kkoog on 2018/10/23.
//
#include "AES_128_CBC.h"

AES_128_block set_IV(string iv_str) {
	return string_to_128_AES_block(iv_str);
}

string AES_128_CBC_encrypt(string k, string plaintext, string iv) {
	// plaintext to x AES block
	string filled_plaintext = fill_plaintext_128(plaintext);
	int plaintext_block = filled_plaintext.length() / 16;
	vector<AES_128_block> plaintext_group(plaintext_block);
	// AES_128_block plaintext_group[plaintext_block];
	for (int j = 0; j < plaintext_block; ++j) {
		plaintext_group[j] = string_to_128_AES_block(filled_plaintext.substr(16 * j, 16));
	}
	// record result
	vector<AES_128_block> result(plaintext_block);
	// AES_128_block result[plaintext_block];

	// set first key (iv xor key)
	AES_128_block IV = set_IV(iv);
	AES_128_key key(k);

	AES_128_block offset = IV;
	for (int i = 0; i < plaintext_block; ++i) {
		AES_128_block in = AES_128_block_xor(offset, plaintext_group[i]);
		result[i] = AES_encrypt_loop(in, key);
		offset = result[i];
	}
	string re;
	vector<unsigned char> result_list(16 * plaintext_block);
	// unsigned char result_list[16 * plaintext_block];
	// hex to string
	for (int l = 0; l < plaintext_block; ++l) {
		for (int i = 0; i < 4; ++i) {
			result_list[(l * 16) + (i * 4)] = result[l].line0[i];
			result_list[(l * 16) + (i * 4) + 1] = result[l].line1[i];
			result_list[(l * 16) + (i * 4) + 2] = result[l].line2[i];
			result_list[(l * 16) + (i * 4) + 3] = result[l].line3[i];
		}
	}

	for (int m = 0; m < 16 * plaintext_block; ++m) {
		re += (char)result_list[m];
	}

	return re;
}

string AES_128_CBC_decrypt(string k, string cip, string iv) {
	string re = "";
	int cip_length = cip.length();
	if (cip_length % 16 != 0) {
		return "Ciphertext length Error!";
	}
	else {
		int cip_block_count = cip_length / 16;
		vector<AES_128_block> cip_group(cip_block_count);
		// AES_128_block cip_group[cip_block_count];
		for (int j = 0; j < cip_block_count; ++j) {
			string cip_temp = cip.substr(16 * j, 16);
			cip_group[j] = string_to_128_AES_block(cip_temp);
		}
		// record result
		vector<AES_128_block> result(cip_block_count);
		// AES_128_block result[cip_block_count];

		// set first key (iv xor key)
		AES_128_block IV = set_IV(iv);
		AES_128_key key(k);
		AES_128_block offset = IV;
		for (int i = 0; i < cip_block_count; ++i) {
			AES_128_block in = AES_decrypt_loop(cip_group[i], key);
			result[i] = AES_128_block_xor(offset, in);
			offset = cip_group[i];
		}
		vector<unsigned char> result_list(16 * cip_block_count);
		// unsigned char result_list[16 * cip_block_count];
		// hex to string
		for (int l = 0; l < cip_block_count; ++l) {
			for (int i = 0; i < 4; ++i) {
				result_list[(l * 16) + (i * 4)] = result[l].line0[i];
				result_list[(l * 16) + (i * 4) + 1] = result[l].line1[i];
				result_list[(l * 16) + (i * 4) + 2] = result[l].line2[i];
				result_list[(l * 16) + (i * 4) + 3] = result[l].line3[i];
			}
		}

		for (int m = 0; m < 16 * cip_block_count; ++m) {
			re += (char)result_list[m];
		}
	}

	return re;
}