
#include <iostream>
#include <ctime>
#include "Rsa.h"

using namespace std;

string text_to_string_in_hex(string input) {
	string result = "";
	unsigned char hex_table[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	int len = input.length();
	for (int i = 0; i < len; i++) {
		char high = hex_table[(int)input[i] / 16];
		result += high;
		char low = hex_table[(int)input[i] % 16];
		result += low;

	}
	return result;

}

string BigInt_in_hex_to_string(BigInt input) {
	string in = input.to_string(input);
	string result = "";
	for (int i = 0; i < in.length(); i += 2) {
		char high = in[i];
		char low = in[i + 1];

		if (high == '0' && low == '0') {
			continue;
		}
		int count = 0;
		if (high >= 'A' && high <= 'F') {
			count += ((high - 'A') * 16);
		}
		else {
			count += ((high - '0') * 16);
		}
		if (low >= 'A' && low <= 'F') {
			count += (low - 'A') + 10;
		}
		else {
			count += (low - '0');
		}
		result += (unsigned char)count;
		//cout << i << " " << high << low << " //" << count << " " << result << endl;
	}
	return result;
}

void print_menu(){
	cout << "----------------------------------------\n";
	cout << "\t 1. Encrypt (input string type)\n";
	cout << "\t 2. Decrypt (input hex type)\n";
	cout << "\t 3. Print the RSA unit information\n";
	cout << "\t 4. Refresh RSA unit\n";
	cout << "\t 0. Exit\n";

}

bool islegal(const string& str) {
	for (string::const_iterator it = str.begin(); it != str.end(); ++it)
		if (!isalnum(*it))
			return false;
	return true;
}

bool decode(RSA& RSA) {
	string str;
	while (cin && str.length() < 1) {
		cout << "> Please Input the ciphertext in hex: \n";
		cin >> str;
	} 
	if (!cin || islegal(str) == false)
		return false;
	BigInt c(str);

	long t1 = clock();
	BigInt m = RSA.decrypt(c);
	long t2 = clock();
	cout << "Time cost:\t" << (t2 - t1) << "ms." << endl;

	cout << "Ciphertext:\n" << c << endl;
	cout << "Plaintext(in hex):\n" << m << endl;
	cout << "Plaintext(in string):\n" << BigInt_in_hex_to_string(m) << endl;
	return true;
}

bool encode(RSA& RSA, BigInt& c){
	string str;
	while (cin && str.length() < 1){
		cout << "> Please input the string you want to encrypt:\n";
		//cin >> str;
		getline(cin, str);
	}
	
	string str_hex = text_to_string_in_hex(str);
	BigInt m(str_hex);

	c = RSA.encrypt(m);

	cout << "Plaintext:\n" << m << endl
		<< "Ciphertext:\n" << c << endl;
	return true;
}

void build_RSA_unit(RSA& RSA, int n) {

	cout << "Initializing...." << endl;
	long t1 = clock();
	RSA.create_RSA_unit(n);
	long t2 = clock();
	cout << "Initilization successfully!" << endl;
	cout << "Time cost:\t" << (t2 - t1) << "ms." << endl;
}

int run_RSA() {
	char ch;
	string choose;
	RSA RSA;
	BigInt c, m;
	cout << "Please input the RSA key length (128/256/512/1024...)\nAttention: Big number for key length will spend more time on initialization: ";
	int n;
	cin >> n;
	build_RSA_unit(RSA, n / 2);

	while (true){
		print_menu();
		cout << ">: ";
		cin >> choose;
		if (!cin) return 0;
		if (choose.length() < 1) cout << "Please try input again:\n";
		else {
			ch = choose[0];
			switch (ch){
			case '1':
				encode(RSA, c);
				cout << "-----------------------------------\n";
				break;
			case '2':
				decode(RSA);
				cout << "-----------------------------------\n";
				break;
			case '3':
				cout << RSA;
				//cout << "-----------------------------------\n";
				break;
			case '4':
				cout << "-----------------------------------\n";
				run_RSA();
				break;
			case '0':
				return 0;
			}
		}
	}
}


void static_test() {
	cout << "============================ RSA Static Test ============================\n";
	string static_test_text = "SUN YAT-SEN UNIVERSITY";
	long en_time_s = clock();
	BigInt static_test(text_to_string_in_hex(static_test_text));
	cout << "The test string is:\n" << static_test_text << endl;
	cout << "The text after operation(char to hex):\n" << static_test.to_string(static_test) << endl;
	RSA STATIC_TEST_UNIT;
	int test_key_length = 256;
	build_RSA_unit(STATIC_TEST_UNIT, test_key_length);
	cout << "RSA unit information:\n" << STATIC_TEST_UNIT;
	BigInt after_encrypt;
	after_encrypt = STATIC_TEST_UNIT.encrypt(static_test);
	long en_time_e = clock();
	cout << "The string after RSA encrypt ciphertext(in hex):\n" << after_encrypt.to_string(after_encrypt) << endl;
	cout << "Encrypt time cost:" << en_time_e - en_time_s << "ms." << endl;
	
	string decrypt_result;
	long de_time_s = clock();
	BigInt after_decrypt = STATIC_TEST_UNIT.decrypt(after_encrypt);
	cout << "After decrypt the ciphertext (in hex): \n" << after_decrypt.to_string(after_decrypt) << endl;
	decrypt_result = BigInt_in_hex_to_string(after_decrypt);
	long de_time_e = clock();
	cout << "The decrypt result (in string):\n" << decrypt_result << endl;
	cout << "Decrypt time cost:" << de_time_e - de_time_s << "ms." << endl;
}

void random_test() {
	cout << "============================ RSA Random Test ============================\n";
	run_RSA();
}

int main(){
	cout << "Modern Cryptography - Exp 5 : RSA\n";
	cout << "Name:\tGao Qian-wen\n";
	cout << "ID: \t16338002\n";
	cout << "Major:\tInformation Security\n";
	cout << endl;
	while (true) {
		cout << "-----------------------------------------------------------------------\n";
		cout << "1. Static test\n2. Random test\n";
		cout << "Press key '1' to run static test, press '2' key to run random test: ";
		string choose;
		cin >> choose;
		char ch = choose[0];
		if (ch == '1') {
			static_test();
		}
		else if (ch == '2') {
			random_test();
		}
		else {
			cout << "Error Input! \n";
		}
	}
	
	system("pause");
	return 0;
}