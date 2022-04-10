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
	string ConvertNumberToString(int Number);
	void setNumber(int Number) {
		this->Number = Number;
	}

	int getNumber() {
		return Number;
	}
private:
	int Number;
};
#endif // __CRYPTOSYSTEM__
