#include <vector>
#include <string>
#include <fstream>

#include "BounceBall.h"
#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "FPS.h"
#include "GameComponents.h"
#include "LevelGame.h"
#include "ManagementObject.h"
#include "Cryptosystem.h"

using namespace std;

TTF_Font* fontGame;

LevelGame::LevelGame() {

}

LevelGame::~LevelGame() {
    
}

void showScore(LTexture scoreText, ScoreObject score, SDL_Renderer* screen) {
    std::string strScore = "score: " + std::to_string(score.getScore());
    scoreText.setText(strScore);
    scoreText.loadFromRenderText(fontGame, screen);
    scoreText.showText(screen, SCREEN_WIDTH - 200, 5);
}

void showYourHighScore(LTexture yourHighScoreText, ScoreObject score, SDL_Renderer* screen) {
    std::string strYourScore = "Your Highscore: " + std::to_string(score.getYourHighScore());
    yourHighScoreText.setText(strYourScore);
    yourHighScoreText.loadFromRenderText(fontGame, screen);
    yourHighScoreText.showText(screen, SCREEN_WIDTH - 320, 35);
}

void showLife(LTexture lifeText, LifeObject life, SDL_Renderer* screen) {
    LifeObject* gbarLife = new LifeObject;
    gbarLife->loadImage("img//life//gbar_Life.png", screen);
    gbarLife->setClips();
    gbarLife->setXPos(15);
    gbarLife->setYPos(5);
    gbarLife->showImage(screen);
    gbarLife->cleanUp();
    std::string strLife = " x " + std::to_string(life.getLife());
    lifeText.setText(strLife);
    lifeText.loadFromRenderText(fontGame, screen);
    lifeText.showText(screen, 15 + gbarLife->getWidthFrame(), 5);
}

void showRemainRings(LTexture remainRingText, ManagementObject &object, SDL_Renderer* screen) {
    RingsObject* gbarRing = new RingsObject;
    gbarRing->loadImage("img//rings//gbar_Ring.png", screen);
    gbarRing->setClips();
    gbarRing->setXPos(325);
    gbarRing->setYPos(5);
    gbarRing->showImage(screen);
    gbarRing->cleanUp();
    std::string strRing = " x " + std::to_string(object.getRemRings());
    remainRingText.setText(strRing);
    remainRingText.loadFromRenderText(fontGame, screen);
    remainRingText.showText(screen, 325 + gbarRing->getWidthFrame(), 5);
    //object.setRemRings(0);
    if (object.getRemRings() == 0) {
        object.openAllEndpointObject(screen);
    }
}

int LevelGame::loadLevelGame(const char* nameFileMap, SDL_Renderer* screen, 
                                SDL_Event event, InfoPlayer* infoPlayer) {
    BaseObject background;
    FPS fpsTimer;
    MainObject player;
    GameMap gamemap;
    Map *mapData;
    ManagementObject object;
    ScoreObject score;
    LifeObject life;
    LTexture scoreText;
    LTexture yourHighScoreText;
    LTexture lifeText;
    LTexture remainRingText;

    score.setScore(infoPlayer->getScore());
    score.setYourHighScore(infoPlayer->getYourHighScore());
    life.SetLife(infoPlayer->getLife());
    background.loadImage("img//background//background.jpg", screen);

    if (TTF_Init() == -1) return BounceBall::typeLevel::ERROR_GAME;

    fontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (fontGame == NULL) {
        return BounceBall::typeLevel::ERROR_GAME;
    }

    gamemap.loadMap(nameFileMap);
    gamemap.loadIMGBlock(screen);

    player.loadImage("img//ball//ball.png", screen);
    player.setClips();
    player.setPos(gamemap.getStartXPlayer(), gamemap.getStartYPlayer());

    scoreText.setColor(LTexture::WHITE_COLOR);
    lifeText.setColor(LTexture::WHITE_COLOR);
    yourHighScoreText.setColor(LTexture::WHITE_COLOR);
    remainRingText.setColor(LTexture::WHITE_COLOR);

    object.setAllObject(&gamemap, &player, &score, &life, infoPlayer);

    object.loadAllObject(infoPlayer, screen);

    gamemap.fixMap();
    mapData = gamemap.getMap();

    bool isQuit = false;
    while (!isQuit) {
        fpsTimer.start();
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
                return BounceBall::typeLevel::QUIT_GAME;
            }
            player.inputAction(event, screen);
        }
        SDL_SetRenderDrawColor(screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(screen);

        background.render(screen, NULL);

        player.setMapXY(mapData->startX, mapData->startY);
        player.doPlayer(mapData);
        player.showImage(screen);

        gamemap.setMap(mapData);
        gamemap.drawMap(screen);

        object.setAllObject(&gamemap, &player, &score, &life, infoPlayer);
        object.checkIntersectAllObject(screen);
        object.setAllObject(&gamemap, &player, &score, &life, infoPlayer);

        if (score.getYourHighScore() < score.getScore()) {
            score.setYourHighScore(score.getScore());
        }
        showScore(scoreText, score, screen); 
        showYourHighScore(yourHighScoreText, score, screen);
        showRemainRings(remainRingText, object, screen); 

        if (object.getIsIntersectBallVsEndpoint()) {
            object.setIsIntersectBallVsEndpoint(0);
            infoPlayer->setlife(life.getLife()); 
            infoPlayer->setScore(score.getScore());
            infoPlayer->setLevel(infoPlayer->getLevel() + 1);
            infoPlayer->setYourHighScore(score.getYourHighScore());
            Cryptosystem addressLevel;
            string address = "map//level";
            if (infoPlayer->getLevel() < 10) address += "0";
            address += addressLevel.convertNumberToString(infoPlayer->getLevel());
            address += ".map";
            return BounceBall::typeLevel::NEXT_LEVEL;
        }

        if (object.getIsIntersectBallVsThreats()) {
            //return BounceBall::typeLevel::NEXT_LEVEL;
            player.loadImage("img//ball//ball_pop.png", screen);
            player.setClips();
            player.showImage(screen);

            life.increaseLife(-1);

            if (life.getLife() == 0) {
                showLife(lifeText, life, screen);
                SDL_RenderPresent(screen);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "GameOver!!!", "GameOver!!!", NULL);
                return BounceBall::typeLevel::GAME_OVER;
            }
            
            showLife(lifeText, life, screen);
            
            SDL_RenderPresent(screen);
            SDL_Delay(1000);
            object.setIsIntersectBallVsThreats(0);
            player.loadImage("img//ball//ball.png", screen);
            player.setClips();
            player.showImage(screen);
            player.setPos(player.getXPosCheckpoint(), player.getYPosCheckpoint());
            SDL_RenderPresent(screen);
        }
        
        showLife(lifeText, life, screen);

        SDL_RenderPresent(screen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = 1000 / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
}