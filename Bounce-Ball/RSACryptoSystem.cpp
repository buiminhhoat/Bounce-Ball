#include "RSACryptoSystem.h"

string RSACryptoSystem::ConvertNumberToString(int Number) {
    string ANS = "";
    if (Number == 0) return "0";
    while (Number > 0) {
        int k = Number % 10;
        ANS = (char)(k + '0') + ANS;
        Number /= 10;
    }
    return ANS;
}
