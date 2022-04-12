#include <vector>
#include <string>
#include <fstream>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "FPS.h"

#include "GameComponents.h"

#include "LevelGame.h"

#include "ManagementObject.h"

using namespace std;

ManagementObject::ManagementObject() {
    Mix_Chunk* ballPop = NULL;
    Mix_Chunk* intersectObject1 = NULL;
    Mix_Chunk* intersectObject2 = NULL;
}

ManagementObject::~ManagementObject() {
    Mix_FreeChunk(ballPop);
    Mix_FreeChunk(intersectObject1);
    Mix_FreeChunk(intersectObject2);
    ballPop = NULL;
    intersectObject1 = NULL;
    intersectObject2 = NULL;
}

typedef struct CircleObject {
    float cx;
    float cy;
    float radius;
};

typedef struct RectObject {
    float x1;
    float y1;
    float x2;
    float y2;
};

void ManagementObject::loadThreatsObject(SDL_Renderer* screen) {
    Map cMap = gameMap->getMap();
    for (int i = 0; i < cMap.maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap.maxX / TILE_SIZE; ++j) {
            if (cMap.block[i][j] == DYN_THORN) {
                ThreatsObject* dynThreats = new ThreatsObject;
                if (dynThreats != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    dynThreats->loadImage("img//threats//dyn_thorn.png", screen);
                    dynThreats->setClips();
                    dynThreats->setXPos(x);
                    dynThreats->setYPos(y);

                    int pos1 = dynThreats->getYPos() - SCREEN_HEIGHT;
                    int pos2 = dynThreats->getYPos() + SCREEN_HEIGHT;

                    dynThreats->setAnimationPos(pos1, pos2);
                    dynThreats->setInputUp(1);
                    dynThreats->setTypeMove(ThreatsObject::MOVE_IN_SPACE_THREAT);
                    threatsList.push_back(dynThreats);
                }
            }
        }
    }

    for (int i = 0; i < cMap.maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap.maxX / TILE_SIZE; ++j) {
            if (cMap.block[i][j] == THORN) {
                ThreatsObject* thornObject = new ThreatsObject;
                if (thornObject != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    thornObject->loadImage("img//threats//thorn.png", screen);
                    thornObject->setClips();
                    thornObject->setXPos(x);
                    thornObject->setYPos(y);
                    thornObject->setTypeMove(ThreatsObject::STATIC_THREAT);
                    thornObject->setInputUp(0);
                    threatsList.push_back(thornObject);
                }
            }
        }
    }
}

int checkIntersectBallVsObject(const CircleObject &circlePlayer, const RectObject &rectObject) {
    float px = circlePlayer.cx;
    float py = circlePlayer.cy;

    if (px < rectObject.x1)
        px = rectObject.x1;
    else if (px > rectObject.x2)
        px = rectObject.x2;

    if (py < rectObject.y1)
        py = rectObject.y1;
    else if (py > rectObject.y2)
        py = rectObject.y2;

    float dx = circlePlayer.cx - px;
    float dy = circlePlayer.cy - py;

    return (dx * dx + dy * dy) <= circlePlayer.radius * circlePlayer.radius;
}

void ManagementObject::checkIntersectThreatsObject(SDL_Renderer* screen) {
    for (int i = 0; i < threatsList.size(); ++i) {
        ThreatsObject* threats = threatsList.at(i);
        if (threats != NULL) {
            threats->setMapXY(mapData.startX, mapData.startY);
            threats->impMoveType(screen);
            threats->doPlayer(mapData);
            threats->showImage(screen);

            float x1Threats = threats->getXPos();
            float y1Threats = threats->getYPos();
            float x2Threats = x1Threats + threats->getWidthFrame();
            float y2Threats = y1Threats + threats->getHeightFrame();

            float cxPlayer = player->getXPos() + player->getWidthFrame() / 2;
            float cyPlayer = player->getYPos() + player->getHeightFrame() / 2;
            float rPlayer = min(player->getWidthFrame(), player->getHeightFrame()) / 2 - 1;
            RectObject rect_threat = { x1Threats, y1Threats, x2Threats, y2Threats };
            CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };
            if (checkIntersectBallVsObject(circlePlayer, rect_threat)) {
                isIntersectBallVsThreats = 1;
                Mix_PlayChannel(-1, ballPop, 0);
            }
        }
    }
}

void ManagementObject::loadRingsObject(SDL_Renderer* screen) {
    Map cMap = gameMap->getMap();
    for (int i = 0; i < cMap.maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap.maxX / TILE_SIZE; ++j) {
            if (cMap.block[i][j] == RING_HORIZONTAL) {
                RingsObject* ringObject = new RingsObject;
                if (ringObject != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    ringObject->loadImage("img//rings//RING_HORIZONTAL.png", screen);
                    ringObject->setClips();
                    ringObject->setXPos(x);
                    ringObject->setYPos(y);
                    ringObject->setScoreRing(SCORE_RING_HORIZONTAL);
                    ringObject->setIsVertical(0);
                    ringsList.push_back(ringObject);
                    ++remRings;
                }
            }
            else if (cMap.block[i][j] == RING_VERTICAL)  {
                RingsObject* ringObject = new RingsObject;
                if (ringObject != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    ringObject->loadImage("img//rings//RING_VERTICAL.png", screen);
                    ringObject->setClips();
                    ringObject->setXPos(x);
                    ringObject->setYPos(y);
                    ringObject->setScoreRing(SCORE_RING_VERTICAL);
                    ringObject->setIsVertical(1);
                    ringsList.push_back(ringObject);
                    ++remRings;
                }
            }
        }
    }
}

void ManagementObject::checkIntersectRingsObject(SDL_Renderer* screen) {
    for (int i = 0; i < ringsList.size(); ++i) {
        RingsObject* ringObject = ringsList.at(i);
        if (ringObject != NULL) {
            ringObject->setMapXY(mapData.startX, mapData.startY);
            ringObject->showImage(screen);

            float x1Ring = ringObject->getXPos();
            float y1Ring = ringObject->getYPos();
            float x2Ring = x1Ring + ringObject->getWidthFrame();
            float y2Ring = y1Ring + ringObject->getHeightFrame();

            float cxPlayer = player->getXPos() + player->getWidthFrame() / 2;
            float cyPlayer = player->getYPos() + player->getHeightFrame() / 2;
            float rPlayer = min(player->getWidthFrame(), player->getHeightFrame()) / 2 - 1;

            RectObject rect_ring = { x1Ring, y1Ring, x2Ring, y2Ring };
            CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };
            if (checkIntersectBallVsObject(circlePlayer, rect_ring)
                && ringObject->getIsCatched() == 0) {
                if (rand() % 2) Mix_PlayChannel(-1, intersectObject1, 0);
                else Mix_PlayChannel(-1, intersectObject2, 0);

                isIntersectBallVsRing = 1;
                score->increaseScore(ringObject->getScoreRing());
                ringObject->setScoreRing(0);
                ringObject->setIsCatched(1);
                if (ringObject->getIsVertical()) {
                    ringObject->loadImage("img//rings//RING_VERTICAL_catched.png", screen);
                    ringObject->setClips();
                }
                else {
                    ringObject->loadImage("img//rings//RING_HORIZONTAL_catched.png", screen);
                    ringObject->setClips();
                }
                --remRings;
            }
        }
    }
}

void ManagementObject::loadCheckpointObject(SDL_Renderer* screen) {
    Map cMap = gameMap->getMap();
    for (int i = 0; i < cMap.maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap.maxX / TILE_SIZE; ++j) {
            if (cMap.block[i][j] == START_POINT) {
                player->setPosCheckpoint(j * TILE_SIZE, i * TILE_SIZE);
            }
            else if (cMap.block[i][j] == CHECKPOINT) {
                CheckpointObject* checkpointObject = new CheckpointObject;
                if (checkpointObject != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    checkpointObject->loadImage("img//checkpoint//checkpoint.png", screen);
                    checkpointObject->setClips();
                    checkpointObject->setXPos(x);
                    checkpointObject->setYPos(y);
                    checkpointObject->setScoreRing(SCORE_CHECKPOINT);
                    checkpointsList.push_back(checkpointObject);
                }
            }
        }
    }
}

void ManagementObject::checkIntersectCheckpointObject(SDL_Renderer* screen) {
    for (int i = 0; i < checkpointsList.size(); ++i) {
        CheckpointObject* checkpointObject = checkpointsList.at(i);
        if (checkpointObject != NULL) {
            checkpointObject->setMapXY(mapData.startX, mapData.startY);
            checkpointObject->showImage(screen);

            float x1Checkpoint = checkpointObject->getXPos();
            float y1Checkpoint = checkpointObject->getYPos();
            float x2Checkpoint = x1Checkpoint + checkpointObject->getWidthFrame();
            float y2Checkpoint = y1Checkpoint + checkpointObject->getHeightFrame();

            float cxPlayer = player->getXPos() + player->getWidthFrame() / 2;
            float cyPlayer = player->getYPos() + player->getHeightFrame() / 2;
            float rPlayer = min(player->getWidthFrame(), player->getHeightFrame()) / 2 - 1;

            RectObject rect_checkpoint = { x1Checkpoint, y1Checkpoint, x2Checkpoint, y2Checkpoint };
            CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };
            if (checkIntersectBallVsObject(circlePlayer, rect_checkpoint)
                && checkpointObject->getIsCatched() == 0) {
                isIntersectBallVsRing = 1;
                if (rand() % 2) Mix_PlayChannel(-1, intersectObject1, 0);
                else Mix_PlayChannel(-1, intersectObject2, 0);
                score->increaseScore(checkpointObject->getScoreRing());
                checkpointObject->setScoreRing(0);
                
                int id_checkpoint = player->getIdCheckpoint();
                if (id_checkpoint != -1) {
                    CheckpointObject* last_checkpoint = checkpointsList.at(id_checkpoint);
                    last_checkpoint->loadImage("img//checkpoint//checkpoint_clear.png", screen);
                    last_checkpoint->setClips();
                }
                checkpointObject->setIsCatched(1);
                player->setPosCheckpoint(x1Checkpoint, y1Checkpoint);
                player->setIdCheckpoint(i);
                checkpointObject->loadImage("img//checkpoint//checkpoint_catched.png", screen);
                checkpointObject->setClips();
            }
        }
    }
}

void ManagementObject::loadLifeObject(SDL_Renderer* screen) {
    Map cMap = gameMap->getMap();
    for (int i = 0; i < cMap.maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap.maxX / TILE_SIZE; ++j) {
            if (cMap.block[i][j] == LIFE) {
                LifeObject* lifeObject = new LifeObject;
                if (lifeObject != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    lifeObject->loadImage("img//life//life.png", screen);
                    lifeObject->setClips();
                    lifeObject->setXPos(x);
                    lifeObject->setYPos(y);
                    lifeObject->setScoreLife(SCORE_LIFE);
                    lifesList.push_back(lifeObject);
                }
            }
        }
    }
}

void ManagementObject::checkIntersectLifeObject(SDL_Renderer* screen) {
    for (int i = 0; i < lifesList.size(); ++i) {
        LifeObject* lifeObject = lifesList.at(i);
        if (lifeObject != NULL) {
            lifeObject->setMapXY(mapData.startX, mapData.startY);
            lifeObject->showImage(screen);

            float x1Checkpoint = lifeObject->getXPos();
            float y1Checkpoint = lifeObject->getYPos();
            float x2Checkpoint = x1Checkpoint + lifeObject->getWidthFrame();
            float y2Checkpoint = y1Checkpoint + lifeObject->getHeightFrame();

            float cxPlayer = player->getXPos() + player->getWidthFrame() / 2;
            float cyPlayer = player->getYPos() + player->getHeightFrame() / 2;
            float rPlayer = min(player->getWidthFrame(), player->getHeightFrame()) / 2 - 1;

            RectObject rect_checkpoint = { x1Checkpoint, y1Checkpoint, x2Checkpoint, y2Checkpoint };
            CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };

            if (checkIntersectBallVsObject(circlePlayer, rect_checkpoint)
                && lifeObject->getIsCatched() == 0) {
                if (rand() % 2) Mix_PlayChannel(-1, intersectObject1, 0);
                else Mix_PlayChannel(-1, intersectObject2, 0);
                isIntersectBallVsRing = 1;
                score->increaseScore(lifeObject->getScoreLife());
                life->increaseLife(1);
                lifeObject->setScoreLife(0);
                lifeObject->setIsCatched(1);
                lifeObject->loadImage("img//life//life_clear.png", screen);
                lifeObject->setClips();
            }
        }
    }
}

void ManagementObject::loadEndpointObject(SDL_Renderer* screen) {
    Map cMap = gameMap->getMap();
    for (int i = 0; i < cMap.maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap.maxX / TILE_SIZE; ++j) {
            if (cMap.block[i][j] == ENDPOINT) {
                EndpointObject* endpointObject = new EndpointObject;
                if (endpointObject != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    endpointObject->loadImage("img//ENDPOINT//ENDPOINT.png", screen);
                    endpointObject->setClips();
                    endpointObject->setXPos(x);
                    endpointObject->setYPos(y);
                    endpointObject->setScoreEndpoint(SCORE_ENDPOINT);
                    endpointsList.push_back(endpointObject);
                }
            }
        }
    }
}

void ManagementObject::openAllEndpointObject(SDL_Renderer* screen) {
    for (int i = 0; i < endpointsList.size(); ++i) {
        EndpointObject* endpointObject = endpointsList.at(i);
        if (endpointObject != NULL) {
            endpointObject->setIsOpened(1);
            endpointObject->loadImage("img//ENDPOINT//ENDPOINT_opened.png", screen);
            endpointObject->showImage(screen);
        }
    }
}

void ManagementObject::checkIntersectEndpointObject(SDL_Renderer* screen) {
    for (int i = 0; i < endpointsList.size(); ++i) {
        EndpointObject* endpointObject = endpointsList.at(i);
        if (endpointObject != NULL) {
            endpointObject->setMapXY(mapData.startX, mapData.startY);
            endpointObject->showImage(screen);

            float x1Checkpoint = endpointObject->getXPos();
            float y1Checkpoint = endpointObject->getYPos();
            float x2Checkpoint = x1Checkpoint + endpointObject->getWidthFrame();
            float y2Checkpoint = y1Checkpoint + endpointObject->getHeightFrame();

            float cxPlayer = player->getXPos() + player->getWidthFrame() / 2;
            float cyPlayer = player->getYPos() + player->getHeightFrame() / 2;
            float rPlayer = min(player->getWidthFrame(), player->getHeightFrame()) / 2 - 1;

            RectObject rect_checkpoint = { x1Checkpoint, y1Checkpoint, x2Checkpoint, y2Checkpoint };
            CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };

            if (checkIntersectBallVsObject(circlePlayer, rect_checkpoint)) {
                if (endpointObject->getIsOpened() == 0)
                    player->setPos(player->getXPos() - 64, player->getYPos());
                else
                    isIntersectBallVsEndpoint = 1;
            }
        }
    }
}

void ManagementObject::loadAllObject(InfoPlayer *infoPlayer, SDL_Renderer* screen) {
    ballPop = Mix_LoadWAV("sound//Ballpop.wav");
    if (ballPop == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    intersectObject1 = Mix_LoadWAV("sound//IntersectObject1.wav");
    if (intersectObject1 == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    intersectObject2 = Mix_LoadWAV("sound//IntersectObject2.wav");
    if (intersectObject2 == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    threatsList.clear();
    ringsList.clear();
    checkpointsList.clear();
    lifesList.clear();
    endpointsList.clear();
    remRings = 0;
    loadThreatsObject(screen);
    loadRingsObject(screen);
    loadCheckpointObject(screen);
    loadLifeObject(screen);
    loadEndpointObject(screen); 
}

void ManagementObject::checkIntersectAllObject(SDL_Renderer* screen) {
    checkIntersectThreatsObject(screen);
    checkIntersectRingsObject(screen);
    checkIntersectCheckpointObject(screen);
    checkIntersectLifeObject(screen);
    checkIntersectEndpointObject(screen);
}