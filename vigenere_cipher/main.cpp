#include "VigenereDecode.h"
#include "CrackVigenere.h"
#include <fstream>
#include <sstream>
#include <time.h>

string getTime()
{
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    return tmp;
}

int main(){
    ifstream infile1;
    infile1.open("ciphertext1.txt");
    string c1;
    while (!infile1.eof()) { infile1 >> c1;}
    infile1.close();
    string cip1 = c1;

    ifstream infile2;
    infile1.open("ciphertext2.txt");
    string c2;
    while (!infile1.eof()) { infile1 >> c2;}
    infile1.close();
    string cip2 = c2;

    FILE *stream;
    stream = freopen( "Record.log", "a+", stdout);
    cout << "------------------------------------------------------------" << endl;
    cout << "Record time:\t" << getTime() << endl;
    cout << "cip1: " << cip1 << endl;
    cout << "cip2: " << cip2 << endl;
    int keyLen = getKeyLength(cip1);
    string key = getKey(cip1, keyLen);
    cout << "cip2 -> key length = " << keyLen << "\tkey = "<< key << endl;
    string clearText = decodingVigenere(key, cip1);
    cout << clearText << endl;
    return 0;
}
