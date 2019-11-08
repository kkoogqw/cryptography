//
// Created by kkoog on 2018/10/28.
//

#include "SHA_1.h"

vector<word> SHA_1_PAD(string input){
    if (input.length() > pow(2, 64)){
        throw "The input size is out of range!";
    }
    vector<word> padded_input;
    vector<unsigned char> temp;
    for (int i = 0; i < input.length(); ++i) {
        temp.push_back((unsigned char)input[i]);
    }
    temp.push_back(0x80);
    while ((8 * temp.size()) % 512 != 448) {
        temp.push_back(0x00);
    }
    dword pad_len = input.length() * 8;
    word h_len = (word)(pad_len >> 32);
    word l_len = (word)pad_len;
    for (int j = 0; j < temp.size(); j += 4) {
        word t = temp[j];
        t = (t << 8) + temp[j + 1];
        t = (t << 8) + temp[j + 2];
        t = (t << 8) + temp[j + 3];
        padded_input.push_back(t);
    }
    padded_input.push_back(h_len);
    padded_input.push_back(l_len);

    return padded_input;
}

word f_x(word b, word c, word d, int t){
    word re;
    if (t < 0 || t > 79) {
        throw "Error index!";
    }
    else if (t >= 0 && t <= 19) {
        re = (b & c) | ((~ b) & d);
    }
    else if (t >= 20 && t <= 39) {
        re = b ^ c ^ d;
    }
    else if (t >= 40 && t <= 59) {
        re = (b & c) | (b & d) | (c & d);
     }
    else if (t >= 60 && t <= 79) {
        re = b ^ c ^ d;
    }
    return re;
}

// (a >> (N - n)) | (a << n)
word ROLT(word in, int pos){
    word result;
    result = (in >> (32 - pos)) | (in << pos);
    return result;
}

word getK(int t){
    if (t < 0 || t > 79) {
        throw "Error index!";
    }
    else if (t >= 0 && t <= 19) {
        return 0x5A827999;
    }
    else if (t >= 20 && t <= 39) {
        return 0x6ED9EBA1;
    }
    else if (t >= 40 && t <= 59) {
        return 0x8F1BBCDC;
    }
    else if (t >= 60 && t <= 79) {
        return 0xCA62C1D6;
    }
}

vector<word> SHA_1(vector<word> in){
    word H[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    vector<word> result;


    for (int i = 0; i < in.size(); i += 16) {
        word ext_W[80];
        for (int k = 0; k < 16; ++k) {
            ext_W[k] = in[k];
        }
        for (int l = 16; l < 80; ++l) {
            ext_W[l] = ROLT(ext_W[l - 3] ^ ext_W[l - 8] ^ ext_W[l - 14] ^ ext_W[l - 16], 1);
        }
        word A = H[0];
        word B = H[1];
        word C = H[2];
        word D = H[3];
        word E = H[4];
        for (int j = 0; j < 80; ++j) {
            word t = ROLT(A, 5) + f_x(B, C, D, j) + E + ext_W[j] + getK(j);
            E = D;
            D = C;
            C = ROLT(B, 30);
            B = A;
            A = t;
        }
        H[0] = H[0] + A;
        H[1] = H[1] + B;
        H[2] = H[2] + C;
        H[3] = H[3] + D;
        H[4] = H[4] + E;
    }

    for (int k = 0; k < 5; ++k) {
        result.push_back(H[k]);
    }
    return result;

}

void print_hash_result(vector<word> hash){
    for (int i = 0; i < hash.size(); ++i) {
        printf("%08lx", hash[i]);
    }
    printf("\n");
}