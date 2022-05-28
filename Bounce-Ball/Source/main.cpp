#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <Windows.h>

#include "../Header/CommonFunc.h"
#include "../Header/BaseObject.h"
#include "../Header/GameMap.h"
#include "../Header/MainObject.h"
#include "../Header/FPS.h"
#include "../Header/GameComponents.h"
#include "../Header/LevelGame.h"
#include "../Header/BounceBall.h"
#include "../Header/Management.h"

using namespace std;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    string generalAddressBackground = ADDRESS_BACKGROUND
           + to_string(rand() % MAX_BACKGROUND) + ".jpg";
    BounceBall* bounceBall = new BounceBall;
    bounceBall->setGeneralAddressBackground(generalAddressBackground);
    bounceBall->startGame();  
    return 0;
}


