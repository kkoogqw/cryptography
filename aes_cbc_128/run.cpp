//
// Created by kkoog on 2018/10/23.
//

#include "AES_128_CBC.h"

int test(){
    cout << "16338002/Gao Qian Wen/SDCS-information security\n";
    cout << "AES-CBC (128 bits) encrypt/decrypt project:\n";

    // test
    string text = "School of data science and computer, Sun Yat-sen University.";
    string key = "sysu";
    string IV = "123";
    string cip = AES_128_CBC_encrypt(key, text, IV);

    cout << "----------------------  AES Test  ----------------------\n";
    cout << "text:\t" << text << endl;
    cout << "key:\t" << key << endl;
    cout << "IV:\t" << IV << endl;
    cout << "\nAfter AES-CBC encode:\n";
    //cout << "string type:\n" << cip << endl;
    cout << "hex type:\n";
    print_ciphertext(cip);

    cout << endl;

    cout << "---------------------- Random Test ----------------------\n";
    while (1){
        string your_text;
        string your_key;
        string your_iv;
        cout << "please input the text you want to encode:\n"; cin >> your_text;
        cout << "please input the key:\n"; cin >> your_key;
        cout << "please input the iv:\n"; cin >> your_iv;

        cout << "\nAfter AES-CBC encode:\n";
        string your_cip = AES_128_CBC_encrypt(your_key, your_text, your_iv);
        cout << "hex typr:\n";
        print_ciphertext(your_cip);
        cout << "--------------------------------------------------------\n";

    }

}
