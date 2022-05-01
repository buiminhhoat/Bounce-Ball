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
#include "Utils.h"

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
    gbarLife->setXPos(15);
    gbarLife->setYPos(5);
    gbarLife->render(screen);
    std::string strLife = " x " + std::to_string(life.getLife());
    lifeText.setText(strLife);
    lifeText.loadFromRenderText(fontGame, screen);
    lifeText.showText(screen, 15 + gbarLife->getWidth(), 5);
    gbarLife->cleanUp();
}

void showRemainRings(LTexture remainRingText, ManagementObject &object, SDL_Renderer* screen) {
    RingsObject* gbarRing = new RingsObject;
    gbarRing->loadImage("img//rings//gbar_Ring.png", screen);
    gbarRing->setXPos(325);
    gbarRing->setYPos(5);
    gbarRing->render(screen);
    std::string strRing = " x " + std::to_string(object.getRemRings());
    remainRingText.setText(strRing);
    remainRingText.loadFromRenderText(fontGame, screen);
    remainRingText.showText(screen, 325 + gbarRing->getWidth(), 5);
    //object.setRemRings(0);
    if (object.getRemRings() == 0) {
        object.openAllEndpointObject(screen);
    }
    gbarRing->cleanUp();
}

void showGameOver(SDL_Renderer* screen) {
    BaseObject gameOver;
    gameOver.loadImage("img//gameover//gameover.png", screen);
    gameOver.setRectPos((SCREEN_WIDTH - gameOver.getRect().w) / 2, 
                        (SCREEN_HEIGHT - gameOver.getRect().h) / 2);
    gameOver.render(screen);
    SDL_RenderPresent(screen);
}

void displaySettings(InfoPlayer *infoPlayer, SDL_Renderer* screen) {
    BaseObject boardSettings;
    boardSettings.loadImage("img//settingsBoard//settingsBoard.png", screen);
    boardSettings.setRectPos((SCREEN_WIDTH - boardSettings.getRect().w) / 2,
        (SCREEN_HEIGHT - boardSettings.getRect().h) / 2);
    boardSettings.render(screen);

    int setSound = infoPlayer->getSound();
    ButtonObject* soundOnButton = new ButtonObject;
    soundOnButton->loadImage("img//settingsBoard//settingsBoard_OnButton.png", screen);
    soundOnButton->setXPos(boardSettings.getRect().x + 235);
    soundOnButton->setYPos(boardSettings.getRect().y + 148);
    soundOnButton->setRectPos(soundOnButton->getXPos(), soundOnButton->getYPos());

    ButtonObject* soundOffButton = new ButtonObject;
    soundOffButton->loadImage("img//settingsBoard//settingsBoard_OffButton.png", screen);
    soundOffButton->setXPos(boardSettings.getRect().x + 235);
    soundOffButton->setYPos(boardSettings.getRect().y + 148);
    soundOffButton->setRectPos(soundOffButton->getXPos(), soundOffButton->getYPos());

    ButtonObject* saveButton = new ButtonObject;
    saveButton->loadImage("img//settingsBoard//settingsBoard_SaveButton.png", screen);
    saveButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    saveButton->setYPos(boardSettings.getRect().y + 210);
    saveButton->setRectPos(saveButton->getXPos(), saveButton->getYPos());

    ButtonObject* restoreButton = new ButtonObject;
    restoreButton->loadImage("img//settingsBoard//settingsBoard_RestoreButton.png", screen);
    restoreButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    restoreButton->setYPos(saveButton->getRect().y + saveButton->getRect().h + 20);
    restoreButton->setRectPos(restoreButton->getXPos(), restoreButton->getYPos());

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//settingsBoard//settingsBoard_BackButton.png", screen);

    backButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    backButton->setYPos(restoreButton->getRect().y + restoreButton->getRect().h + 20);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());

    ButtonObject* exitButton = new ButtonObject;
    exitButton->loadImage("img//settingsBoard//settingsBoard_exitButton.png", screen);
    exitButton->setXPos(boardSettings.getRect().x + boardSettings.getRect().w - exitButton->getRect().w);
    exitButton->setYPos(boardSettings.getRect().y);
    exitButton->setRectPos(exitButton->getXPos(), exitButton->getYPos());

    SDL_RenderPresent(screen);
    bool quit = false;
    int sound = infoPlayer->getSound();
    while (!quit) {
        MouseEvents mouse;
        mouse.mouseHandleEvent();
        bool selectSoundOnButton = bool(mouse.checkMouseInButton(soundOnButton));
        bool selectSoundOffButton = bool(mouse.checkMouseInButton(soundOffButton));
        bool selectBackButton = bool(mouse.checkMouseInButton(backButton));
        bool selectSaveButton = bool(mouse.checkMouseInButton(saveButton));
        bool selectRestoreButton = bool(mouse.checkMouseInButton(restoreButton));
        bool selectExitButton = bool(mouse.checkMouseInButton(exitButton));
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && (selectBackButton || selectExitButton))) {
                quit = true;
                return;
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectSoundOnButton || selectSoundOffButton) {
                    if (setSound == BounceBall::typeSound::ON) setSound = BounceBall::typeSound::OFF;
                    else setSound = BounceBall::typeSound::ON;
                }
                if (selectRestoreButton)
                    setSound = BounceBall::typeSound::ON;
                if (selectSaveButton) {
                    sound = setSound;
                    infoPlayer->setSound(sound);
                    return;
                }
            }
        }

        boardSettings.render(screen);
        if (setSound == true)
            soundOnButton->render(screen);
        else
            soundOffButton->render(screen);
        saveButton->render(screen);
        restoreButton->render(screen);
        backButton->render(screen);
        exitButton->render(screen);
        SDL_RenderPresent(screen);
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
    MouseEvents mouse;

    score.setScore(infoPlayer->getScore());
    score.setYourHighScore(infoPlayer->getYourHighScore());
    life.SetLife(infoPlayer->getLife());
    background.loadImage("img//background//background.jpg", screen);

    if (TTF_Init() == -1) return BounceBall::typeLevel::ERROR_GAME;

    fontGame = TTF_OpenFont("font//no_continue.ttf", FONT_SIZE);
    if (fontGame == NULL) {
        return BounceBall::typeLevel::ERROR_GAME;
    }

    gamemap.loadMap(nameFileMap);
    gamemap.loadIMGBlock(screen);

    player.loadImage("img//ball//ball.png", screen);
    player.setRectPos(gamemap.getStartXPlayer(), gamemap.getStartYPlayer());

    scoreText.setColor(LTexture::WHITE_COLOR);
    lifeText.setColor(LTexture::WHITE_COLOR);
    yourHighScoreText.setColor(LTexture::WHITE_COLOR);
    remainRingText.setColor(LTexture::WHITE_COLOR);

    object.setAllObject(&gamemap, &player, &score, &life, infoPlayer);

    object.loadAllObject(infoPlayer, screen);

    gamemap.fixMap();
    mapData = gamemap.getMap();

    bool isQuit = false;
    
    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", screen);

    backButton->setXPos(0);
    backButton->setYPos(SCREEN_HEIGHT - backButton->getRect().h);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());
    backButton->render(screen);

    ButtonObject* settingsButton = new ButtonObject;
    settingsButton->loadImage("img//button//settings_button.png", screen);
    settingsButton->setXPos(SCREEN_WIDTH - settingsButton->getRect().w);
    settingsButton->setYPos(SCREEN_HEIGHT - settingsButton->getRect().h);
    settingsButton->setRectPos(settingsButton->getXPos(), settingsButton->getYPos());
    settingsButton->render(screen);

    while (!isQuit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool selectBackButton = bool(mouse.checkMouseInButton(backButton));
        bool selectSettingsButton = bool(mouse.checkMouseInButton(settingsButton));
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && selectBackButton) {
                isQuit = true;
                infoPlayer->setScore(0);
                infoPlayer->setYourHighScore(score.getYourHighScore());
                return BounceBall::typeLevel::QUIT_GAME;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && selectSettingsButton) {
                displaySettings(infoPlayer, screen);
            }
            player.inputAction(event, screen);
        }
        SDL_SetRenderDrawColor(screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(screen);

        background.render(screen);

        player.setMapXY(mapData->startX, mapData->startY);
        player.doPlayer(mapData);
        player.render(screen);

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
            /* Next level */
            infoPlayer->setLevel(infoPlayer->getLevel() + 1);
            infoPlayer->setYourHighScore(score.getYourHighScore());
            Cryptosystem addressLevel;
            string address = "map//level";
            /* Conver x to 0x*/
            if (infoPlayer->getLevel() <= MAX_ONE_DIGIT) address += "0";
            address += addressLevel.convertNumberToString(infoPlayer->getLevel());
            address += ".map";
            return BounceBall::typeLevel::NEXT_LEVEL;
        }

        if (object.getIsIntersectBallVsThreats()) {
            player.loadImage("img//ball//ball_pop.png", screen);
            player.render(screen);

            life.increaseLife(INCREASE_LIFE);

            if (life.getLife() == 0) {
                showLife(lifeText, life, screen);
                SDL_RenderPresent(screen);
                showGameOver(screen);
                SDL_Delay(TIME_DELAY_GAMEOVER);
                infoPlayer->setlife(life.getLife());
                infoPlayer->setScore(0);
                infoPlayer->setYourHighScore(score.getYourHighScore());
                return BounceBall::typeLevel::GAME_OVER;
            }
            
            showLife(lifeText, life, screen);
            
            SDL_RenderPresent(screen);
            SDL_Delay(TIME_DELAY_POPBALL);
            object.setIsIntersectBallVsThreats(false);
            player.loadImage("img//ball//ball.png", screen);
            player.render(screen);
            player.setRectPos(player.getXPosCheckpoint(), player.getYPosCheckpoint());
            SDL_RenderPresent(screen);
        }
        
        showLife(lifeText, life, screen);

        backButton->render(screen);
        settingsButton->render(screen);
        SDL_RenderPresent(screen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = MS_ONE_SECOND / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
}