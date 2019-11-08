#pragma once
#include"BigInt.h"
class RSA
{
public:
	BigInt e;
	BigInt N; // N = p*q

	void create_RSA_unit(unsigned int n);

	BigInt encrypt(const BigInt plaintext);
	BigInt decrypt(const BigInt ciphertext);
	void get_RSA_info();
	long long int rsa_ID;

private:
	BigInt _d;
	BigInt _p;
	BigInt _q;
	BigInt _Eulor; // _Eulor = (p-1)*(q-1)

	BigInt create_Odd_Num(unsigned int n);
	bool is_Prime(const BigInt& a,const unsigned int k);
	BigInt create_Prime(unsigned int n,int it_cout);
	BigInt create_Random_Small_Than(const BigInt& a);
	friend ostream& operator <<(ostream& out, const RSA& RSA);

};