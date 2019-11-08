//
// Created by kkoog on 2018/9/19.
//

#ifndef INC_1_1_VIGENEREDECODE_H
#define INC_1_1_VIGENEREDECODE_H

#include <iostream>
#include <string>
using namespace std;

string decodingVigenere(string key, string ciphertext){
    string cleartext;
    int keyLength = key.length();
    int cipLength = ciphertext.length();
    for (int i = 0; i < cipLength; ++i) {
        int keyoffset = (((i + 1) % keyLength) - 1) >= 0 ? (((i + 1) % keyLength) - 1) : (keyLength - 1);
        //((i + 1) % keyLength) - 1;
        int pos = ((ciphertext[i] - 'A')-(key[keyoffset] - 'A'));
        if (pos < 0){
            pos += 26;
        }
        char temp = (char)('A' + pos);
        //test
        cout << "cip char: " << ciphertext[i] << "\tkey offset: " << key[keyoffset] << "\tclear text: " << temp << endl;
        //over

        cleartext += temp;
    }
    return cleartext;
}


#endif //INC_1_1_VIGENEREDECODE_H
