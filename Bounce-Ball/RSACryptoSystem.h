#ifndef __RSACRYPTOSYSTEM__
#define __RSACRYPTOSYSTEM__

#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <Windows.h>

using namespace std;

class RSACryptoSystem {
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
#endif // !__RSACRYPTOSYSTEM__
