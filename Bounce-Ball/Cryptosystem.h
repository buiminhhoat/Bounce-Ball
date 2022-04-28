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

    std::string insert_linebreaks(std::string str, size_t distance);
    template <typename String, unsigned int line_length>
    std::string encode_with_line_breaks(String s);
    template <typename String>
    std::string encode_pem(String s);
    template <typename String>
    std::string encode_mime(String s);
    template <typename String>
    std::string encode(String s, bool url);
    template <typename String>
    std::string decode(String encoded_string, bool remove_linebreaks);
    std::string base64_encode(std::string const& s, bool url = false);
    std::string base64_encode_pem(std::string const& s);
    std::string base64_encode_mime(std::string const& s);

    std::string base64_decode(std::string const& s, bool remove_linebreaks = false);
    std::string base64_encode(unsigned char const*, size_t len, bool url = false);
private:
	int number;
};
#endif // __CRYPTOSYSTEM__
