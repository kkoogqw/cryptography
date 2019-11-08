//
// Created by kkoog on 2018/9/19.
//

#ifndef INC_1_1_CRACKVIGENERE_H
#define INC_1_1_CRACKVIGENERE_H

#include <iostream>
#include <string>
using namespace std;

int getArrayMin(double array[]){
    int minPosition = 0;
    for(int i = 1;  i < 26; ++i){
        if (array[i] < array[minPosition]){
            minPosition = i;
        }
    }
    return minPosition;
}

//独立函数，用于计算重合指数值
double getIndexOfChar(string ciphertext){
    int charCout[26] = {0};
    int stringLength = ciphertext.length();
    for(int i = 0; i < stringLength; i++){
        if (ciphertext[i] <= 'Z' && ciphertext[i] >= 'A') {
            charCout[(int)(ciphertext[i] - 'A')] += 1;
        }
    }
    int temp = 0;
    for(int i = 0; i < 26; i++){
        temp += (charCout[i] * (charCout[i] - 1));
    }
    int temp2 = ((stringLength * (stringLength - 1)));
    double IC = (temp * 1.00) / temp2;
    return IC;
}

//测定密钥长度
int getKeyLength(string ciphertext){
    int keyLength = 1;
    int ciphertextLength = ciphertext.length();
    double AvgIC[27] = {0.00};
    //将KeyLength从1至26长度求每种v长度下的重合指数
    while(true){
        double SumIC = 0.0;
        string cipGroup[keyLength];
        //密文分组
        for (int i = 0; i < keyLength; ++i) {
            for (int j = 0; i + (j * keyLength) < ciphertextLength; ++j) {
                cipGroup[i] += (ciphertext[i + (j * keyLength)]);
            }
        }
        /*
         * Record the IC of every Keylength values:
         */
        for (int k = 0; k < keyLength; ++k) {
            double temp = getIndexOfChar(cipGroup[k]);
            //test
            cout << keyLength  << "\t" << temp << endl;
            //over
            SumIC += temp;
        }
        /*
         * Record the Average IC of every Keylength values:
         */
        double avgIC = (SumIC * 1.00)/keyLength;
        AvgIC[keyLength] = ((avgIC - 0.065) > 0 ? (avgIC - 0.065) : (0.065 - avgIC));
        //test
        cout << "Key length is:\t" << keyLength  << "\tAvgIC\t" << AvgIC[keyLength] << endl;
        //over
        keyLength += 1;
        if(keyLength > 26) break;
    }
    /*
     * Record the distance between 0.065 and Average IC:
     */
    //test
    for (int l = 1; l <= 26; ++l) {
        cout << "Key length = " << l << ",\t Distance to \"STANDARD(0.065)\" is:\t" << AvgIC[l] << endl;
    }
    //over
    int keyLenResult = 1;
    //遍历找到平均重合指数与0.065差值最小的长度
    for(int i = 2; i < 27; i++){
        if (AvgIC[i] < AvgIC[keyLenResult]) {
            keyLenResult = i;
        }
    }
    return keyLenResult;
}

double charP[27] = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020,
                    0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067,
                    0.075, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028,
                    0.010, 0.023, 0.001, 0.020, 0.001};


string getKey(string ciphertext, int Keylength){
    string Key;
    string cipGroup[Keylength];
    double charCountTable[Keylength][26];
    //密文按照计算完成的KeyLength分组
    int ciphertextLength = ciphertext.length();
    for (int i = 0; i < Keylength; ++i) {
        for (int j = 0; i + (j * Keylength) < ciphertextLength; ++j) {
            cipGroup[i] += (ciphertext[i + (j * Keylength)]);
        }
    }
    /*
     * Record the sub-ciphertext:
     */
    //test
    for (int k = 0; k < Keylength; ++k) {
        cout << k + 1 << ":\t" << cipGroup[k] << endl;
    }
    //over
    //即使算每一组的测量指标
    for (int l = 0; l < Keylength; ++l) {

        for(int i = 0; i < 26; i++)
        {
            int charCount[26] = {0};
            for (int k = 0; k < cipGroup[l].length(); ++k) {
                charCount[(int)(cipGroup[l][k] - 'A')]++;
            }
            double temp = 0;
            for (int j = 0; j < 26; ++j) {
                temp += (double)(charCount[(j + i) % 26] * charP[j]);
            }
            charCountTable[l][i] = temp / cipGroup[l].length();
        }

        /*
         * Record the every offset values (IC) in each sub-cip:
         */
        //test
        cout << "line " << l + 1 << endl;
        for (int j = 0; j < 26; ++j) {
            cout << (char)('A' + j) << "\tProbability: " << charCountTable[l][j] << endl;
        }
        //test over

    }

    for(int i = 0; i < Keylength; i++)
    {
        int point = 0;
        double dis[26] = {0.00};
        for(int j = 0; j < 26; j++)
        {
            dis[j] = (double)((charCountTable[i][j] > 0.065) ? (charCountTable[i][j] - 0.065) : (0.065 - charCountTable[i][j]));

            /*
             * Record the result list:
             */
            //test
            cout << "line:\t" << i + 1 << "\t char \t" << (char)(j + 'A') << "\t" << dis[j] << endl;
            //over
        }
        point = getArrayMin(dis);
        /*
         * Record the min IC's position and the char:
         */
        //test
        cout << "Min pos is :\t" << point << "\t" << (char)(point + 'A') << endl;
        //over
        Key += (char)('A' + point);
    }
    return Key;
}


#endif //INC_1_1_CRACKVIGENERE_H
