
#include "ECC2_131.h"


int main(){
    ECC2_131 test1;
    ECC2_131 test2(1);

    int a[131] = {0};
    a[12] = 1;
    a[56] = 1;
    a[100] = 1;
    ECC2_131 test3(a);
    test1.addition(test3);
    cout << test1.Px_toString() << endl;
    test1.displayArray(test2.toArray(), 131);

}