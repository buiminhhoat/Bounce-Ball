#include <vector>
#include <string>
#include <fstream>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "FPS.h"

#include "ThreatsObject.h"
#include "RingsObject.h"
#include "ScoreObject.h"
#include "CheckpointObject.h"
#include "TextObject.h"

#include "LevelGame.h"

#include "ManagementObject.h"

using namespace std;

ScoreObject::ScoreObject() {
	Score = 0;
}

ScoreObject::~ScoreObject() {

}