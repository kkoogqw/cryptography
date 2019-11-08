//
// Created by kkoog on 2018/10/23.
//

#include "AES_128_encrypt.h"

AES_128_block byte_substitution(AES_128_block in) {
	AES_128_block temp;
	for (int i = 0; i < 4; ++i) {
		int high0 = get_hex_high(in.line0[i]);
		int low0 = get_hex_low(in.line0[i]);
		temp.line0[i] = s_box[(16 * high0) + low0];

		int high1 = get_hex_high(in.line1[i]);
		int low1 = get_hex_low(in.line1[i]);
		temp.line1[i] = s_box[(16 * high1) + low1];

		int high2 = get_hex_high(in.line2[i]);
		int low2 = get_hex_low(in.line2[i]);
		temp.line2[i] = s_box[(16 * high2) + low2];

		int high3 = get_hex_high(in.line3[i]);
		int low3 = get_hex_low(in.line3[i]);
		temp.line3[i] = s_box[(16 * high3) + low3];
	}
	return temp;
}

AES_128_block shift_row(AES_128_block in) {
	AES_128_block temp;
	for (int i = 0; i < 4; ++i) {
		temp.line0[i] = in.line0[i];
		temp.line1[i] = in.line1[(i + 1) % 4];
		temp.line2[i] = in.line2[(i + 2) % 4];
		temp.line3[i] = in.line3[(i + 3) % 4];
	}
	return temp;
}

AES_128_block mix_colume(AES_128_block in) {
	AES_128_block temp;
	AES_128_block matrix;
	matrix.line0[0] = 0x02; matrix.line0[1] = 0x03; matrix.line0[2] = 0x01; matrix.line0[3] = 0x01;
	matrix.line1[0] = 0x01; matrix.line1[1] = 0x02; matrix.line1[2] = 0x03; matrix.line1[3] = 0x01;
	matrix.line2[0] = 0x01; matrix.line2[1] = 0x01; matrix.line2[2] = 0x02; matrix.line2[3] = 0x03;
	matrix.line3[0] = 0x03; matrix.line3[1] = 0x01; matrix.line3[2] = 0x01; matrix.line3[3] = 0x02;

	temp = AES_128_block_multip(matrix, in);
	return temp;
}

AES_128_block xor_round_key(AES_128_block in, AES_128_block round_key) {
	AES_128_block result;
	result = AES_128_block_xor(in, round_key);
	return result;
}

AES_128_block AES_encrypt_loop(AES_128_block text, AES_128_key key) {
	AES_128_block out;
	int round = 0;
	while (round <= 10) {
		AES_128_block k = key.get_encrypt_key(round);
		if (round == 0) {
			out = xor_round_key(text, k);
			round++;
			continue;
		}
		else if (round == 10) {
			out = byte_substitution(out);
			out = shift_row(out);
			out = xor_round_key(out, k);
			round++;
			break;
		}
		else {
			out = byte_substitution(out);
			out = shift_row(out);
			out = mix_colume(out);
			out = xor_round_key(out, k);
			round++;
			continue;
		}
	}

	return out;
}