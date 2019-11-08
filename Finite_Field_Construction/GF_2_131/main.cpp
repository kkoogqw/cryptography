
#include "GF_2_131.h"


int main() {

//    test part 1:
//    GF_2_131 test1(2);
//    GF_2_131 test2(2);
//    GF_2_131 test3(2);
//    // test2/3 = test1, in order to keep test1 = 2 (x)
//    GF_2_131 _add(4); //4 -> 100 -> x^2
//    test1.mod();
//    cout << test1.Poly_toString() << endl;
//    test3.add(_add);
//    cout << test3.Poly_toString() << endl;
//    test2.inverse();
//    cout << test2.Poly_toString() << endl;
//    test1.square();
//    cout << test1.Poly_toString() << endl;

//    test part2:
//    int t[1] = {131};
//    GF_2_131 test4(t, 1);
//    test4.mod();
//    cout << test4.Poly_toString() << endl;

//    test part 3:
//    int t[5] = {131,13,2,1,0};
//    GF_2_131 test5(t, 5);
//    test5.inverse();
//    cout << test5.Poly_toString() << endl;

    string str = "Name:\tGao Qian wen\nID:\t16338002\nMajor:\tInformation Security (SDCS)\nWork:\tEXP2 - GF(2^131)";
    cout << str;
    cout << "\n------------ Use Student ID to test GF(2^131) ------------\n";

    int my_id = 16338002;
    string str1 = "Test my Student-ID:\n";
    cout << str1;
    GF_2_131 s_ID(my_id);
    cout << "ID in Decimal:\t" << my_id << endl;
    cout << "ID in Binary:\t" << endl;
    s_ID.printPoly_BIN();
    cout << endl;
    cout << "ID in string:\t" << endl << s_ID.Poly_toString() << endl;

    cout << endl;

    GF_2_131 temp_S_ID(s_ID.getPolynomials());
    temp_S_ID.mod();
    cout << "After do mod() operation: " << endl;
    cout << "Polynomials type:\n" << temp_S_ID.Poly_toString() << endl;
    cout << "Binary type:\n";
    temp_S_ID.printPoly_BIN(); cout << endl;

    cout << endl;

    temp_S_ID.setPolynomials(s_ID.getPolynomials());
    temp_S_ID.inverse();
    cout << "After do inverse() operation: " << endl;
    cout << "Polynomials type:\n" << temp_S_ID.Poly_toString() << endl;
    cout << "Binary type:\n";
    temp_S_ID.printPoly_BIN(); cout << endl;

    cout << "\n----------------------- Random test -----------------------\n";

    while (true) {
        cout << "Input 1 to continue or 0 to exit:";
        bool choose;
        cin >> choose;
        if (!choose) {
            break;
        } else {
            system("cls");
            GF_2_131 gf;
            cout << "----------------------- Random test -----------------------\n";
            cout << "You can use an array or a Decimal number to create a Polynomials:" << endl;
            cout << "1.\tArray\n2.\tDecimal number\n0.\texit\n";
            int ch1;
            cin >> ch1;
            switch (ch1) {
                case 1 : {
                    cout << "The input should be: {length, array[0], arry[1], array[2], ......}" << endl;
                    int count = 0;
                    int array[count];
                    cin >> count;
                    for (int i = 0; i < count; ++i) {
                        cin >> array[i];
                    }
                    GF_2_131 t1(array, count);
                    gf = t1;
                    break;
                }
                case 2 :
                    cout << "Input the decimal number:\t" ;
                    int dec;
                    cin >> dec;
                    gf.setPolynomials(dec);
                    break;
                case 0 :
                    break;
                default:
                    cout << "Invalid input! " << endl;
                    continue;
            }

            cout << "The input Polynomials:" << endl;
            cout << gf.Poly_toString() << endl;
            cout << "Polynomials display in Binary:" << endl;
            gf.printPoly_BIN(); cout << endl;

            cout << "You can do these operations for the Polynomials:" << endl;
            cout << "1.\taddition()\n2.\tsubtraction()\n3.\tmod()\n4.\tinverse()\n5.\tmultiplication()\n6.\tsquare()\n0.\texit\n";
            int ch2;
            cin >> ch2;
            GF_2_131 t2;
            switch (ch2) {
                case 1 : {
                    cout << "You can use an array or a Decimal number to create another Polynomials:" << endl;
                    cout << "1.\tArray\n2.\tDecimal number\n0.\texit\n";
                    int ch3;
                    cin >> ch3;
                    switch (ch3) {
                        case 1 : {
                            cout << "The input should be: {length, array[0], arry[1], array[2], ......}" << endl;
                            int count = 0;
                            int array[count];
                            cin >> count;
                            for (int i = 0; i < count; ++i) {
                                cin >> array[i];
                            }
                            GF_2_131 t3(array, count);
                            t2 = t3;
                            break;
                        }
                        case 2 :
                            cout << "Input the decimal number:\t" ;
                            int dec;
                            cin >> dec;
                            t2.setPolynomials(dec);
                            break;
                        case 0 :
                            break;
                        default:
                            cout << "Invalid input! " << endl;
                            continue;
                    }
                    // input t2
                    t2.add(gf);
                    cout << "After do add() Polynomials:" << endl;
                    cout << t2.Poly_toString() << endl;
                    cout << "Polynomials display in Binary:" << endl;
                    t2.printPoly_BIN(); cout << endl;
                    continue;
                }
                case 2 : {
                    cout << "You can use an array or a Decimal number to create another Polynomials:" << endl;
                    cout << "1.\tArray\n2.\tDecimal number\n0.\texit\n";
                    int ch3;
                    cin >> ch3;
                    switch (ch3) {
                        case 1 : {
                            cout << "The input should be: {length, array[0], arry[1], array[2], ......}" << endl;
                            int count = 0;
                            int array[count];
                            cin >> count;
                            for (int i = 0; i < count; ++i) {
                                cin >> array[i];
                            }
                            GF_2_131 t3(array, count);
                            t2 = t3;
                            break;
                        }
                        case 2 :
                            cout << "Input the decimal number:\t" ;
                            int dec;
                            cin >> dec;
                            t2.setPolynomials(dec);
                            break;
                        case 0 :
                            break;
                        default:
                            cout << "Invalid input! " << endl;
                            continue;
                    }
                    // input t2
                    t2.sub(gf);
                    cout << "After do sub() Polynomials:" << endl;
                    cout << t2.Poly_toString() << endl;
                    cout << "Polynomials display in Binary:" << endl;
                    t2.printPoly_BIN(); cout << endl;
                    continue;
                }
                case 3 :
                    t2.setPolynomials(gf.getPolynomials());
                    t2.mod();
                    cout << "After do mod() Polynomials:" << endl;
                    cout << t2.Poly_toString() << endl;
                    cout << "Polynomials display in Binary:" << endl;
                    t2.printPoly_BIN(); cout << endl;
                    continue;
                case 4 :
                    t2.setPolynomials(gf.getPolynomials());
                    t2.inverse();
                    cout << "After do inverse() Polynomials:" << endl;
                    cout << t2.Poly_toString() << endl;
                    cout << "Polynomials display in Binary:" << endl;
                    t2.printPoly_BIN(); cout << endl;
                    continue;
                case 5 : {
                    cout << "You can use an array or a Decimal number to create another Polynomials:" << endl;
                    cout << "1.\tArray\n2.\tDecimal number\n0.\texit\n";
                    int ch3;
                    cin >> ch3;
                    switch (ch3) {
                        case 1 : {
                            cout << "The input should be: {length, array[0], arry[1], array[2], ......}" << endl;
                            int count = 0;
                            int array[count];
                            cin >> count;
                            for (int i = 0; i < count; ++i) {
                                cin >> array[i];
                            }
                            GF_2_131 t3(array, count);
                            t2 = t3;
                        }
                        case 2 :
                            cout << "Input the decimal number:\t" ;
                            int dec;
                            cin >> dec;
                            t2.setPolynomials(dec);
                        case 0 :
                            break;
                        default:
                            cout << "Invalid input! " << endl;
                            continue;
                    }
                    // input t2
                    t2.multip(gf);
                    cout << "After do multip() Polynomials:" << endl;
                    cout << t2.Poly_toString() << endl;
                    cout << "Polynomials display in Binary:" << endl;
                    t2.printPoly_BIN(); cout << endl;
                    continue;
                }
                case 6 :
                    t2.setPolynomials(gf.getPolynomials());
                    t2.square();
                    cout << "After do square() Polynomials:" << endl;
                    cout << t2.Poly_toString() << endl;
                    cout << "Polynomials display in Binary:" << endl;
                    t2.printPoly_BIN(); cout << endl;
                    continue;
                case 0 :
                    break;
                default:
                    cout << "Invalid input! " << endl;
                    continue;
            }
        }
    }

    system("pause");
    return 0;
}