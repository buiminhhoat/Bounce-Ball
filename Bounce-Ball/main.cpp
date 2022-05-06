#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <Windows.h>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "FPS.h"
#include "GameComponents.h"
#include "LevelGame.h"
#include "BounceBall.h"

#include "Management.h"

using namespace std;

#define debug1(a) cout << #a << " = " << a << ";"
#define debug1l(a) cout << #a << " = " << a << ";" << '\n'
#define debug2(a, b) cout << #a << " = " << a << "; " << #b << " = " << b << "; "
#define debug2l(a, b) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << '\n'
#define debug3(a, b, c) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; "
#define debug3l(a, b, c) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << '\n'
#define debug4(a, b, c, d) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << #d << " = " << d << "; "
#define debug4l(a, b, c, d) cout << #a << " = " << a << "; " << #b << " = " << b << "; " << #c << " = " << c << "; " << #d << " = " << d << "; " << '\n'

int main(int argc, char* argv[]) {
    srand(time(NULL));
    BounceBall* bounceBall = new BounceBall;
    bounceBall->startGame();  
    return 0;
}


