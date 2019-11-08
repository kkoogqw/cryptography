#include "Rsa.h"
#include<iostream>
#include<sstream>
#include<ctime>
#include<cstdlib>

using namespace std;


void RSA::create_RSA_unit(unsigned int n){
	rsa_ID = clock();
	srand(time(NULL));
	_p = create_Prime(n, 10);
	_q = create_Prime(n, 10);
	N = _p * _q;
	_Eulor = (_p - 1) * (_q - 1);
	e = 20083361;
	_d = e.extendEuclid(_Eulor);

}

void RSA::get_RSA_info() {
	cout << this;
}

BigInt RSA::create_Odd_Num(unsigned int n){
	n=n/4;
	static unsigned char hex_table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	if(n) {
		ostringstream oss;
		for(std::size_t i = 0;i < n - 1; ++i)
			oss << hex_table[rand() % 16];
		oss << hex_table[1];
		string str(oss.str());
		return BigInt(str);
	}
	else
		return BigInt::Zero;
}

bool RSA::is_Prime(const BigInt& n, const unsigned int k){
	assert(n != BigInt::Zero);
	if(n == BigInt::Two)
		return true;
	BigInt n_1 = n - 1;
	BigInt::bit b(n_1);
	if(b.at(0) == 1)
		return false;

	for(std::size_t t = 0; t < k; ++t){
		BigInt a = create_Random_Small_Than(n_1);
		BigInt d(BigInt::One);
		for(int i = b.size() - 1; i >= 0; --i){
			BigInt x = d;
			d = (d * d) % n;
			if(d == BigInt::One && x != BigInt::One && x != n_1)
				return false;
			if(b.at(i)){
				assert(d != BigInt::Zero);
				d = (a * d) % n;
			}
		}
		if(d != BigInt::One)
			return false;
	}
	return true;
}

BigInt RSA::create_Random_Small_Than(const BigInt& a){
	unsigned long t = 0;
	while (t == 0){
		t = rand();
	}
	BigInt mod(t);
	BigInt r = mod % a;
	if(r == BigInt::Zero)
		r = a - BigInt::One;	
	return r;
}

BigInt RSA::create_Prime(unsigned int n, int it_count){
	assert(it_count > 0);
	BigInt res = create_Odd_Num(n);
	while(!is_Prime(res, it_count)){
		res = res + BigInt("2");
	}
	return res;
}


BigInt RSA::encrypt(const BigInt plaintext) {
	return plaintext.moden(e, N);
}

BigInt RSA::decrypt(const BigInt ciphertext) {
	return ciphertext.moden(_d, N);
}

ostream& operator <<(ostream& out, const RSA& RSA) {
	out << "--------------------------------------------------\n";
	out << "N: " << RSA.N << endl;
	out << "p: " << RSA._p << endl;
	out << "q: " << RSA._q << endl;
	out << "e: " << RSA.e << endl;
	out << "d: " << RSA._d << endl;
	out << "\t\t\tRSA_ID: " << RSA.rsa_ID << endl;
	out << "--------------------------------------------------\n";

	return out;
}