#ifndef __CRYPTOSYSTEM__
#define __CRYPTOSYSTEM__

#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <Windows.h>

using namespace std;

class Cryptosystem {
public:
	Cryptosystem();
	~Cryptosystem();
	string convertNumberToString(int number);
	void setNumber(int number) {
		this->number = number;
	}

	int getNumber() {
		return number;
	}
private:
	int number;
};
#endif // __CRYPTOSYSTEM__
