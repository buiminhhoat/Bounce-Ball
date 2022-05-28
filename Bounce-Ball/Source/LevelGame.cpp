#include <vector>
#include <string>
#include <fstream>

#include "../Header/BounceBall.h"
#include "../Header/CommonFunc.h"
#include "../Header/BaseObject.h"
#include "../Header/GameMap.h"
#include "../Header/MainObject.h"
#include "../Header/FPS.h"
#include "../Header/GameComponents.h"
#include "../Header/LevelGame.h"
#include "../Header/Management.h"
#include "../Header/Cryptosystem.h"
#include "../Header/Mouse.h"

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
    const int RIGHT_MARGIN = 200;
    const int TOP_MARGIN = 5;
    scoreText.showText(screen, SCREEN_WIDTH - RIGHT_MARGIN, TOP_MARGIN);
}

void showYourHighScore(LTexture yourHighScoreText, ScoreObject score, SDL_Renderer* screen) {
    std::string strYourScore = "Your Highscore: " + std::to_string(score.getYourHighScore());
    yourHighScoreText.setText(strYourScore);
    yourHighScoreText.loadFromRenderText(fontGame, screen);
    const int RIGHT_MARGIN = 320;
    const int TOP_MARGIN = 35;
    yourHighScoreText.showText(screen, SCREEN_WIDTH - RIGHT_MARGIN, TOP_MARGIN);
}

void showLife(LTexture lifeText, LifeObject life, SDL_Renderer* screen) {
    LifeObject* gbarLife = new LifeObject;
    gbarLife->loadImage(ADDRESS_GBAR_LIFE, screen);
    const int LEFT_MARGIN = 15;
    const int TOP_MARGIN = 5;
    gbarLife->setXPos(LEFT_MARGIN);
    gbarLife->setYPos(TOP_MARGIN);
    gbarLife->render(screen);
    std::string strLife = " x " + std::to_string(life.getLife());
    lifeText.setText(strLife);
    lifeText.loadFromRenderText(fontGame, screen);
    lifeText.showText(screen, LEFT_MARGIN + gbarLife->getWidth(), TOP_MARGIN);
    gbarLife->cleanUp();
}

void showRemainRings(LTexture remainRingText, Management &object, SDL_Renderer* screen) {
    const int LEFT_MARGIN = 325;
    const int TOP_MARGIN = 5;
    RingsObject* gbarRing = new RingsObject;
    gbarRing->loadImage(ADDRESS_GBAR_RING, screen);
    gbarRing->setXPos(LEFT_MARGIN);
    gbarRing->setYPos(TOP_MARGIN);
    gbarRing->render(screen);
    std::string strRing = " x " + std::to_string(object.getRemRings());
    remainRingText.setText(strRing);
    remainRingText.loadFromRenderText(fontGame, screen);
    remainRingText.showText(screen, LEFT_MARGIN + gbarRing->getWidth(), TOP_MARGIN);
    if (object.getRemRings() == 0) {
        object.openAllEndpointObject(screen);
    }
    gbarRing->cleanUp();
}

void showGameOver(SDL_Renderer* screen) {
    BaseObject gameOver;
    gameOver.loadImage(ADDRESS_GAMEOVER, screen);
    gameOver.setRectPos((SCREEN_WIDTH - gameOver.getRect().w) / 2, 
                        (SCREEN_HEIGHT - gameOver.getRect().h) / 2);
    gameOver.render(screen);
    SDL_RenderPresent(screen);
}

void displaySettings(InfoPlayer *infoPlayer, SDL_Renderer* screen) {
    BaseObject boardSettings;
    boardSettings.loadImage(ADDRESS_SETTINGS_BOARD, screen);
    boardSettings.setRectPos((SCREEN_WIDTH - boardSettings.getRect().w) / 2,
        (SCREEN_HEIGHT - boardSettings.getRect().h) / 2);
    boardSettings.render(screen);

    bool setSound = infoPlayer->getSound();
    
    const int BOARDSETTINGS_VS_SOUNDBUTTON_X = 235;
    const int BOARDSETTINGS_VS_SOUNDBUTTON_Y = 148;

    ButtonObject soundOnButton;
    soundOnButton.loadImage(ADDRESS_SETTINGS_BOARD_SOUND_ON_BUTTON, screen);
    soundOnButton.setXPos(boardSettings.getRect().x + BOARDSETTINGS_VS_SOUNDBUTTON_X);
    soundOnButton.setYPos(boardSettings.getRect().y + BOARDSETTINGS_VS_SOUNDBUTTON_Y);
    soundOnButton.setRectPos(soundOnButton.getXPos(), soundOnButton.getYPos());

    ButtonObject soundOnButtonClick;
    soundOnButtonClick.loadImage(ADDRESS_SETTINGS_BOARD_SOUND_ON_BUTTON_CLICK, screen);
    soundOnButtonClick.setXPos(boardSettings.getRect().x + BOARDSETTINGS_VS_SOUNDBUTTON_X);
    soundOnButtonClick.setYPos(boardSettings.getRect().y + BOARDSETTINGS_VS_SOUNDBUTTON_Y);
    soundOnButtonClick.setRectPos(soundOnButtonClick.getXPos(), soundOnButtonClick.getYPos());

    ButtonObject soundOffButton;
    soundOffButton.loadImage(ADDRESS_SETTINGS_BOARD_SOUND_OFF_BUTTON, screen);
    soundOffButton.setXPos(boardSettings.getRect().x + BOARDSETTINGS_VS_SOUNDBUTTON_X);
    soundOffButton.setYPos(boardSettings.getRect().y + BOARDSETTINGS_VS_SOUNDBUTTON_Y);
    soundOffButton.setRectPos(soundOffButton.getXPos(), soundOffButton.getYPos());

    ButtonObject soundOffButtonClick;
    soundOffButtonClick.loadImage(ADDRESS_SETTINGS_BOARD_SOUND_OFF_BUTTON_CLICK, screen);
    soundOffButtonClick.setXPos(boardSettings.getRect().x + BOARDSETTINGS_VS_SOUNDBUTTON_X);
    soundOffButtonClick.setYPos(boardSettings.getRect().y + BOARDSETTINGS_VS_SOUNDBUTTON_Y);
    soundOffButtonClick.setRectPos(soundOffButtonClick.getXPos(), soundOffButtonClick.getYPos());

    const int BOARDSETTINGS_VS_SAVEBUTTON_Y = 210;

    ButtonObject saveButton;
    saveButton.loadImage(ADDRESS_SETTINGS_BOARD_SAVE_BUTTON, screen);
    saveButton.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    saveButton.setYPos(boardSettings.getRect().y + BOARDSETTINGS_VS_SAVEBUTTON_Y);
    saveButton.setRectPos(saveButton.getXPos(), saveButton.getYPos());

    ButtonObject saveButtonClick;
    saveButtonClick.loadImage(ADDRESS_SETTINGS_BOARD_SAVE_BUTTON_CLICK, screen);
    saveButtonClick.setXPos((SCREEN_WIDTH - saveButtonClick.getRect().w) / 2);
    saveButtonClick.setYPos(boardSettings.getRect().y + BOARDSETTINGS_VS_SAVEBUTTON_Y);
    saveButtonClick.setRectPos(saveButtonClick.getXPos(), saveButtonClick.getYPos());

    const int FUNCTIONBUTTON_VS_FUNCTIONBUTTON_Y = 20;

    ButtonObject restoreButton;
    restoreButton.loadImage(ADDRESS_SETTINGS_BOARD_RESTORE_BUTTON, screen);
    restoreButton.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    restoreButton.setYPos(saveButton.getRect().y + saveButton.getRect().h 
                            + FUNCTIONBUTTON_VS_FUNCTIONBUTTON_Y);
    restoreButton.setRectPos(restoreButton.getXPos(), restoreButton.getYPos());

    ButtonObject restoreButtonClick;
    restoreButtonClick.loadImage(ADDRESS_SETTINGS_BOARD_RESTORE_BUTTON_CLICK, screen);
    restoreButtonClick.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    restoreButtonClick.setYPos(saveButton.getRect().y + saveButton.getRect().h
        + FUNCTIONBUTTON_VS_FUNCTIONBUTTON_Y);
    restoreButtonClick.setRectPos(restoreButtonClick.getXPos(), restoreButtonClick.getYPos());

    ButtonObject backButton;
    backButton.loadImage(ADDRESS_SETTINGS_BOARD_BACK_BUTTON, screen);
    backButton.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    backButton.setYPos(restoreButton.getRect().y + restoreButton.getRect().h 
                            + FUNCTIONBUTTON_VS_FUNCTIONBUTTON_Y);
    backButton.setRectPos(backButton.getXPos(), backButton.getYPos());

    ButtonObject backButtonClick;
    backButtonClick.loadImage(ADDRESS_SETTINGS_BOARD_BACK_BUTTON_CLICK, screen);
    backButtonClick.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    backButtonClick.setYPos(restoreButton.getRect().y + restoreButton.getRect().h
        + FUNCTIONBUTTON_VS_FUNCTIONBUTTON_Y);
    backButtonClick.setRectPos(backButtonClick.getXPos(), backButtonClick.getYPos());

    ButtonObject exitButton;
    exitButton.loadImage(ADDRESS_SETTINGS_BOARD_EXIT_BUTTON, screen);
    exitButton.setXPos(boardSettings.getRect().x + boardSettings.getRect().w 
                        - exitButton.getRect().w);
    exitButton.setYPos(boardSettings.getRect().y);
    exitButton.setRectPos(exitButton.getXPos(), exitButton.getYPos());

    ButtonObject exitButtonClick;
    exitButtonClick.loadImage(ADDRESS_SETTINGS_BOARD_EXIT_BUTTON_CLICK, screen);
    exitButtonClick.setXPos(boardSettings.getRect().x + boardSettings.getRect().w - exitButtonClick.getRect().w);
    exitButtonClick.setYPos(boardSettings.getRect().y);
    exitButtonClick.setRectPos(exitButtonClick.getXPos(), exitButtonClick.getYPos());

    SDL_RenderPresent(screen);
    bool quit = false;
    bool sound = infoPlayer->getSound();
    while (!quit) {
        Mouse mouse;
        mouse.mouseHandleEvent();
        bool selectSoundOnButton = bool(mouse.checkMouseInButton(&soundOnButton));
        bool selectSoundOffButton = bool(mouse.checkMouseInButton(&soundOffButton));
        bool selectBackButton = bool(mouse.checkMouseInButton(&backButton));
        bool selectSaveButton = bool(mouse.checkMouseInButton(&saveButton));
        bool selectRestoreButton = bool(mouse.checkMouseInButton(&restoreButton));
        bool selectExitButton = bool(mouse.checkMouseInButton(&exitButton));
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
        if (setSound == true) {
            if (selectSoundOnButton == false) soundOnButton.render(screen);
            else soundOnButtonClick.render(screen);
        }
        else {
            if (selectSoundOffButton == false) soundOffButton.render(screen);
            else soundOffButtonClick.render(screen);
        }
        if (selectSaveButton == false) saveButton.render(screen);
        else saveButtonClick.render(screen);
        if (selectRestoreButton == false) restoreButton.render(screen);
        else restoreButtonClick.render(screen);
        if (selectBackButton == false) backButton.render(screen);
        else backButtonClick.render(screen);
        if (selectExitButton == false) exitButton.render(screen);
        else exitButtonClick.render(screen);
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
    Management object;
    ScoreObject score;
    LifeObject life;
    LTexture scoreText;
    LTexture yourHighScoreText;
    LTexture lifeText;
    LTexture remainRingText;
    Mouse mouse;

    score.setScore(infoPlayer->getScore());
    score.setYourHighScore(infoPlayer->getYourHighScore());
    life.SetLife(infoPlayer->getLife());

    Cryptosystem tmp;
    string addressBackground = ADDRESS_BACKGROUND;
    addressBackground += tmp.convertNumberToString(infoPlayer->getLevel() % MAX_BACKGROUND);
    //addressBackground += tmp.convertNumberToString(rand() % MAX_BACKGROUND);
    addressBackground += ".jpg";
    background.loadImage(addressBackground, screen);

    if (TTF_Init() == -1) return BounceBall::levelType::ERROR_GAME;

    fontGame = TTF_OpenFont(ADDRESS_FONT_GAME.c_str(), FONT_SIZE);
    if (fontGame == NULL) {
        return BounceBall::levelType::ERROR_GAME;
    }

    gamemap.loadMap(nameFileMap);
    gamemap.loadIMGBlock(screen);

    player.loadImage(ADDRESS_BALL, screen);
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
    
    ButtonObject backButton;
    backButton.loadImage(ADDRESS_MENU_BACK_BUTTON, screen);
    backButton.setXPos(0);
    backButton.setYPos(SCREEN_HEIGHT - backButton.getRect().h);
    backButton.setRectPos(backButton.getXPos(), backButton.getYPos());
    backButton.render(screen);

    ButtonObject backButtonClick;
    backButtonClick.loadImage(ADDRESS_MENU_BACK_BUTTON_CLICK, screen);
    backButtonClick.setXPos(0);
    backButtonClick.setYPos(SCREEN_HEIGHT - backButtonClick.getRect().h);
    backButtonClick.setRectPos(backButtonClick.getXPos(), backButtonClick.getYPos());

    ButtonObject settingsButton;
    settingsButton.loadImage(ADDRESS_SETTINGS_BUTTON, screen);
    settingsButton.setXPos(SCREEN_WIDTH - settingsButton.getRect().w);
    settingsButton.setYPos(SCREEN_HEIGHT - settingsButton.getRect().h);
    settingsButton.setRectPos(settingsButton.getXPos(), settingsButton.getYPos());
    settingsButton.render(screen);

    ButtonObject settingsButtonClick;
    settingsButtonClick.loadImage(ADDRESS_SETTINGS_BUTTON_CLICK, screen);
    settingsButtonClick.setXPos(SCREEN_WIDTH - settingsButtonClick.getRect().w);
    settingsButtonClick.setYPos(SCREEN_HEIGHT - settingsButtonClick.getRect().h);
    settingsButtonClick.setRectPos(settingsButtonClick.getXPos(), settingsButtonClick.getYPos());

    while (!isQuit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool selectBackButton = bool(mouse.checkMouseInButton(&backButton));
        bool selectSettingsButton = bool(mouse.checkMouseInButton(&settingsButton));
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && selectBackButton) {
                isQuit = true;
                infoPlayer->setScore(0);
                infoPlayer->setYourHighScore(score.getYourHighScore());
                return BounceBall::levelType::QUIT_GAME;
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
            string address = ADDRESS_MAP_ROOT;
            /* Conver x to 0x*/
            if (infoPlayer->getLevel() <= MAX_ONE_DIGIT) address += "0";
            address += addressLevel.convertNumberToString(infoPlayer->getLevel());
            address += ".map";
            return BounceBall::levelType::NEXT_LEVEL;
        }

        if (object.getIsIntersectBallVsThreats()) {
            //infoPlayer->setLevel(infoPlayer->getLevel() + 1);
            //infoPlayer->setYourHighScore(score.getYourHighScore());
            //return BounceBall::levelType::NEXT_LEVEL;
            player.loadImage(ADDRESS_BALL_POP, screen);
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
                return BounceBall::levelType::GAME_OVER;
            }
            
            showLife(lifeText, life, screen);
            
            SDL_RenderPresent(screen);
            SDL_Delay(TIME_DELAY_POPBALL);
            object.setIsIntersectBallVsThreats(false);
            player.loadImage(ADDRESS_BALL, screen);
            player.render(screen);
            player.setRectPos(player.getXPosCheckpoint(), player.getYPosCheckpoint());
            SDL_RenderPresent(screen);
        }
        
        showLife(lifeText, life, screen);

        if (selectBackButton == false) backButton.render(screen);
        else backButtonClick.render(screen);
        if (selectSettingsButton == false) settingsButton.render(screen);
        else settingsButtonClick.render(screen);

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