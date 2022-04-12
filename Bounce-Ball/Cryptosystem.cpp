#include "Cryptosystem.h"

Cryptosystem::Cryptosystem() {
    number = 0;
}

Cryptosystem::~Cryptosystem() {

}
string Cryptosystem::convertNumberToString(int number) {
    string ANS = "";
    if (number == 0) return "0";
    while (number > 0) {
        int k = number % 10;
        ANS = (char)(k + '0') + ANS;
        number /= 10;
    }
    return ANS;
}
