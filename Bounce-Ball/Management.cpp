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

#include "Management.h"

#include "BounceBall.h"

using namespace std;

Management::Management() {
    Mix_Chunk* ballPop = NULL;
    Mix_Chunk* musicType1 = NULL;
    Mix_Chunk* musicType2 = NULL;
}

Management::~Management() {
    Mix_FreeChunk(ballPop);
    Mix_FreeChunk(musicType1);
    Mix_FreeChunk(musicType2);
    ballPop = NULL;
    musicType1 = NULL;
    musicType2 = NULL;
    
    for (int i = 0; i < threatsList.size(); ++i)
        threatsList[i]->cleanUp();
    threatsList.clear();

    for (int i = 0; i < ringsList.size(); ++i)
        ringsList[i]->cleanUp();
    ringsList.clear();

    for (int i = 0; i < checkpointsList.size(); ++i)
        checkpointsList[i]->cleanUp();
    checkpointsList.clear();

    for (int i = 0; i < lifesList.size(); ++i)
        lifesList[i]->cleanUp();
    lifesList.clear();

    for (int i = 0; i < endpointsList.size(); ++i)
        endpointsList[i]->cleanUp();
    endpointsList.clear();
}

typedef struct CircleObject {
    double cx;
    double cy;
    double radius;
};

typedef struct RectObject {
    double x1;
    double y1;
    double x2;
    double y2;
};

bool checkIntersectBallVsObject(const CircleObject &circlePlayer, const RectObject &rectObject) {
    double px = circlePlayer.cx;
    double py = circlePlayer.cy;

    if (px < rectObject.x1)
        px = rectObject.x1;
    else if (px > rectObject.x2)
        px = rectObject.x2;

    if (py < rectObject.y1)
        py = rectObject.y1;
    else if (py > rectObject.y2)
        py = rectObject.y2;

    double dx = circlePlayer.cx - px;
    double dy = circlePlayer.cy - py;

    return (dx * dx + dy * dy) < circlePlayer.radius * circlePlayer.radius;
}

void Management::loadThreatsObject(SDL_Renderer* screen) {
    Map *cMap = gameMap->getMap();
    for (int i = 0; i < cMap->maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap->maxX / TILE_SIZE; ++j) {
            if (cMap->block[i][j] == DYN_THORN) {
                ThreatsObject *dynThreats = new ThreatsObject;
                int x = j * TILE_SIZE;
                int y = i * TILE_SIZE;
                dynThreats->loadImage("img//threats//dyn_thorn.png", screen);
                dynThreats->setXPos(x);
                dynThreats->setYPos(y);

                int pos1 = dynThreats->getYPos() - SCREEN_HEIGHT;
                int pos2 = dynThreats->getYPos() + SCREEN_HEIGHT;

                dynThreats->setAnimationPos(pos1, pos2);
                dynThreats->setInputUp(true);
                dynThreats->setTypeMove(ThreatsObject::MOVE_IN_SPACE_THREAT);
                threatsList.push_back(dynThreats);
            }
        }
    }

    for (int i = 0; i < cMap->maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap->maxX / TILE_SIZE; ++j) {
            if (cMap->block[i][j] == THORN) {
                ThreatsObject *thornObject = new ThreatsObject;
                int x = j * TILE_SIZE;
                int y = i * TILE_SIZE;
                thornObject->loadImage("img//threats//thorn.png", screen);
                thornObject->setXPos(x);
                thornObject->setYPos(y);
                thornObject->setTypeMove(ThreatsObject::STATIC_THREAT);
                thornObject->setInputUp(0);
                threatsList.push_back(thornObject);
            }
        }
    }
}

void Management::checkIntersectThreatsObject(SDL_Renderer* screen) {
    for (int i = 0; i < threatsList.size(); ++i) {
        ThreatsObject *threats = threatsList.at(i);
        threats->setMapXY(mapData->startX, mapData->startY);
        threats->impMoveType(screen);
        threats->doPlayer(mapData);
        threats->render(screen);

        double x1Threats = threats->getXPos();
        double y1Threats = threats->getYPos();
        double x2Threats = x1Threats + threats->getWidth();
        double y2Threats = y1Threats + threats->getHeight();

        double cxPlayer = player->getXPos() + player->getWidth() / 2;
        double cyPlayer = player->getYPos() + player->getHeight() / 2;
        double rPlayer = min(player->getWidth(), player->getHeight()) / 2;
        RectObject rect_threat = { x1Threats, y1Threats, x2Threats, y2Threats };
        CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };
        if (checkIntersectBallVsObject(circlePlayer, rect_threat)) {
            isIntersectBallVsThreats = true;
            if (infoPlayer->getSound() == BounceBall::typeSound::ON) {
                Mix_PlayChannel(-1, ballPop, 0);
            }
        }
    }
}

void Management::loadRingsObject(SDL_Renderer* screen) {
    Map *cMap = gameMap->getMap();
    for (int i = 0; i < cMap->maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap->maxX / TILE_SIZE; ++j) {
            if (cMap->block[i][j] == RING_HORIZONTAL) {
                RingsObject *ringObject = new RingsObject;
                int x = j * TILE_SIZE;
                int y = i * TILE_SIZE;
                ringObject->loadImage("img//rings//RING_HORIZONTAL.png", screen);
                ringObject->setXPos(x);
                ringObject->setYPos(y);
                ringObject->setScoreRing(SCORE_RING_HORIZONTAL);
                ringObject->setIsVertical(false);
                ringsList.emplace_back(ringObject);
                ++remRings;
            }
            else if (cMap->block[i][j] == RING_VERTICAL)  {
                RingsObject* ringObject = new RingsObject;
                int x = j * TILE_SIZE;
                int y = i * TILE_SIZE;
                ringObject->loadImage("img//rings//RING_VERTICAL.png", screen);
                ringObject->setXPos(x);
                ringObject->setYPos(y);
                ringObject->setScoreRing(SCORE_RING_VERTICAL);
                ringObject->setIsVertical(true);
                ringsList.emplace_back(ringObject);
                ++remRings;
            }
        }
    }
}

void Management::checkIntersectRingsObject(SDL_Renderer* screen) {
    for (int i = 0; i < ringsList.size(); ++i) {
        RingsObject *ringObject = ringsList.at(i);
        ringObject->setMapXY(mapData->startX, mapData->startY);
        ringObject->render(screen);

        double x1Ring = ringObject->getXPos();
        double y1Ring = ringObject->getYPos();
        double x2Ring = x1Ring + ringObject->getWidth();
        double y2Ring = y1Ring + ringObject->getHeight();

        double cxPlayer = player->getXPos() + player->getWidth() / 2;
        double cyPlayer = player->getYPos() + player->getHeight() / 2;
        double rPlayer = min(player->getWidth(), player->getHeight()) / 2;

        RectObject rect_ring = { x1Ring, y1Ring, x2Ring, y2Ring };
        CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };
        if (checkIntersectBallVsObject(circlePlayer, rect_ring)
            && ringObject->getIsCatched() == false) {
            if (infoPlayer->getSound() == BounceBall::typeSound::ON) {
                if (rand() % 2) Mix_PlayChannel(-1, musicType1, 0);
                else Mix_PlayChannel(-1, musicType2, 0);
            }

            isIntersectBallVsRing = true;
            score->increaseScore(ringObject->getScoreRing());
            ringObject->setScoreRing(0);
            ringObject->setIsCatched(true);
            if (ringObject->getIsVertical()) {
                ringObject->loadImage("img//rings//RING_VERTICAL_catched.png", screen);
            }
            else {
                ringObject->loadImage("img//rings//RING_HORIZONTAL_catched.png", screen);
            }
            --remRings;
        }
    }
}

void Management::loadCheckpointObject(SDL_Renderer* screen) {
    Map *cMap = gameMap->getMap();
    for (int i = 0; i < cMap->maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap->maxX / TILE_SIZE; ++j) {
            if (cMap->block[i][j] == START_POINT) {
                player->setPosCheckpoint(j * TILE_SIZE, i * TILE_SIZE);
            }
            else if (cMap->block[i][j] == CHECKPOINT) {
                CheckpointObject *checkpointObject = new CheckpointObject;
                int x = j * TILE_SIZE;
                int y = i * TILE_SIZE;
                checkpointObject->loadImage("img//checkpoint//checkpoint.png", screen);
                checkpointObject->setXPos(x);
                checkpointObject->setYPos(y);
                checkpointObject->setScoreRing(SCORE_CHECKPOINT);
                checkpointsList.push_back(checkpointObject);
            }
        }
    }
}

void Management::checkIntersectCheckpointObject(SDL_Renderer* screen) {
    for (int i = 0; i < checkpointsList.size(); ++i) {
        CheckpointObject *checkpointObject = checkpointsList.at(i);
        checkpointObject->setMapXY(mapData->startX, mapData->startY);
        checkpointObject->render(screen);

        double x1Checkpoint = checkpointObject->getXPos();
        double y1Checkpoint = checkpointObject->getYPos();
        double x2Checkpoint = x1Checkpoint + checkpointObject->getWidth();
        double y2Checkpoint = y1Checkpoint + checkpointObject->getHeight();

        double cxPlayer = player->getXPos() + player->getWidth() / 2;
        double cyPlayer = player->getYPos() + player->getHeight() / 2;
        double rPlayer = min(player->getWidth(), player->getHeight()) / 2;

        RectObject rect_checkpoint = { x1Checkpoint, y1Checkpoint, x2Checkpoint, y2Checkpoint };
        CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };
        if (checkIntersectBallVsObject(circlePlayer, rect_checkpoint)
            && checkpointObject->getIsCatched() == false) {
            isIntersectBallVsRing = true;
            if (infoPlayer->getSound() == BounceBall::typeSound::ON) {
                if (rand() % 2) Mix_PlayChannel(-1, musicType1, 0);
                else Mix_PlayChannel(-1, musicType2, 0);
            }
            score->increaseScore(checkpointObject->getScoreRing());
            checkpointObject->setScoreRing(0);
                
            int id_checkpoint = player->getIdCheckpoint();
            if (id_checkpoint != NO_CHECKPOINT) {
                CheckpointObject *last_checkpoint = checkpointsList.at(id_checkpoint);
                last_checkpoint->loadImage("img//checkpoint//checkpoint_clear.png", screen);
            }
            checkpointObject->setIsCatched(true);
            player->setPosCheckpoint(x1Checkpoint, y1Checkpoint);
            player->setIdCheckpoint(i);
            checkpointObject->loadImage("img//checkpoint//checkpoint_catched.png", screen);
        }
    }
}

void Management::loadLifeObject(SDL_Renderer* screen) {
    Map *cMap = gameMap->getMap();
    for (int i = 0; i < cMap->maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap->maxX / TILE_SIZE; ++j) {
            if (cMap->block[i][j] == LIFE) {
                LifeObject *lifeObject = new LifeObject;
                int x = j * TILE_SIZE;
                int y = i * TILE_SIZE;
                lifeObject->loadImage("img//life//life.png", screen);
                lifeObject->setXPos(x);
                lifeObject->setYPos(y);
                lifeObject->setScoreLife(SCORE_LIFE);
                lifesList.push_back(lifeObject);
            }
        }
    }
}

void Management::checkIntersectLifeObject(SDL_Renderer* screen) {
    for (int i = 0; i < lifesList.size(); ++i) {
        LifeObject *lifeObject = lifesList.at(i);
        lifeObject->setMapXY(mapData->startX, mapData->startY);
        lifeObject->render(screen);

        double x1Checkpoint = lifeObject->getXPos();
        double y1Checkpoint = lifeObject->getYPos();
        double x2Checkpoint = x1Checkpoint + lifeObject->getWidth();
        double y2Checkpoint = y1Checkpoint + lifeObject->getHeight();

        double cxPlayer = player->getXPos() + player->getWidth() / 2;
        double cyPlayer = player->getYPos() + player->getHeight() / 2;
        double rPlayer = min(player->getWidth(), player->getHeight()) / 2;

        RectObject rect_checkpoint = { x1Checkpoint, y1Checkpoint, x2Checkpoint, y2Checkpoint };
        CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };

        if (checkIntersectBallVsObject(circlePlayer, rect_checkpoint)
            && lifeObject->getIsCatched() == false) {
            if (infoPlayer->getSound() == BounceBall::typeSound::ON) {
                if (rand() % 2) Mix_PlayChannel(-1, musicType1, 0);
                else Mix_PlayChannel(-1, musicType2, 0);
            }
            isIntersectBallVsRing = true;
            score->increaseScore(lifeObject->getScoreLife());
            life->increaseLife(1);
            lifeObject->setScoreLife(0);
            lifeObject->setIsCatched(true);
            lifeObject->loadImage("img//life//life_clear.png", screen);
        }
    }
}

void Management::loadEndpointObject(SDL_Renderer* screen) {
    Map *cMap = gameMap->getMap();
    for (int i = 0; i < cMap->maxY / TILE_SIZE; ++i) {
        for (int j = 0; j < cMap->maxX / TILE_SIZE; ++j) {
            if (cMap->block[i][j] == ENDPOINT) {
                EndpointObject *endpointObject = new EndpointObject;
                int x = j * TILE_SIZE;
                int y = i * TILE_SIZE;
                endpointObject->loadImage("img//ENDPOINT//ENDPOINT.png", screen);
                endpointObject->setXPos(x);
                endpointObject->setYPos(y);
                endpointObject->setScoreEndpoint(SCORE_ENDPOINT);
                endpointsList.push_back(endpointObject);
            }
        }
    }
}

void Management::openAllEndpointObject(SDL_Renderer* screen) {
    for (int i = 0; i < endpointsList.size(); ++i) {
        EndpointObject *endpointObject = endpointsList.at(i);
        endpointObject->setIsOpened(true);
        endpointObject->loadImage("img//ENDPOINT//ENDPOINT_opened.png", screen);
        endpointObject->render(screen);
    }
}

void Management::checkIntersectEndpointObject(SDL_Renderer* screen) {
    for (int i = 0; i < endpointsList.size(); ++i) {
        EndpointObject *endpointObject = endpointsList.at(i);
        endpointObject->setMapXY(mapData->startX, mapData->startY);
        endpointObject->render(screen);

        double x1Checkpoint = endpointObject->getXPos();
        double y1Checkpoint = endpointObject->getYPos();
        double x2Checkpoint = x1Checkpoint + endpointObject->getWidth();
        double y2Checkpoint = y1Checkpoint + endpointObject->getHeight();

        double cxPlayer = player->getXPos() + player->getWidth() / 2;
        double cyPlayer = player->getYPos() + player->getHeight() / 2;
        double rPlayer = min(player->getWidth(), player->getHeight()) / 2;

        RectObject rect_checkpoint = { x1Checkpoint, y1Checkpoint, x2Checkpoint, y2Checkpoint };
        CircleObject circlePlayer = { cxPlayer, cyPlayer, rPlayer };

        if (checkIntersectBallVsObject(circlePlayer, rect_checkpoint)) {
            if (endpointObject->getIsOpened() == false)
                player->setRectPos(player->getXPos() - 64, player->getYPos());
            else
                isIntersectBallVsEndpoint = true;
        }
    }
}

void Management::loadAllObject(InfoPlayer *infoPlayer, SDL_Renderer* screen) {
    ballPop = Mix_LoadWAV("sound//Ballpop.wav");
    if (ballPop == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    musicType1 = Mix_LoadWAV("sound//musicType1.wav");
    if (musicType1 == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    musicType2 = Mix_LoadWAV("sound//musicType2.wav");
    if (musicType2 == NULL) {
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

void Management::checkIntersectAllObject(SDL_Renderer* screen) {
    checkIntersectThreatsObject(screen);
    checkIntersectRingsObject(screen);
    checkIntersectCheckpointObject(screen);
    checkIntersectLifeObject(screen);
    checkIntersectEndpointObject(screen);
}