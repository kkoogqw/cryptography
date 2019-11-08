
#include "SHA_1.h"

int main() {

    printf("Name :\tGao Qian Wen\n");
    printf("ID   :\t16338002\n");
    printf("Major:\tInformation Security\n");

    printf("---------------------------- Static Test ----------------------------\n");
    printf("The test string is (My student ID):\t16338002\n");
    printf("The SHA-1 of test string is (in hex):\n");
    print_hash_result(SHA_1(SHA_1_PAD("16338002")));


    printf("---------------------------- Random Test ----------------------------\n");
    while (true) {

        printf("Please input the test message:");
        string test_str;
        getline(cin, test_str);
        printf("The SHA-1 of test string is (in hex):\n");
        print_hash_result(SHA_1(SHA_1_PAD(test_str)));
        printf("\n");
    }

    return 0;
}
