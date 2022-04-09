#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "FPS.h"
#include "GameComponents.h"
#include "LevelGame.h"
#include "Utils.h"

#include "ManagementObject.h"
#include "BounceBall.h"
#include "RSACryptoSystem.h"

using namespace std;

BounceBall::BounceBall() {

}

BounceBall::~BounceBall() {

}

InfoPlayer* infoPlayer = new InfoPlayer;

int BounceBall::startGame() {
    if (!initSDL())
        return -1;

    displayLogo();

    bool quit = false;
    
    while (!quit) {
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                break;
            }

            switch (display) {
            case 0:
                displayMenu();
                break;
            case 1:
                displayPlay();
                break;
            case 2:
                displayleaderboard();
                break;
            }
        }
    }
    CleanUp();
}

void BounceBall::displayLogo() {
    BaseObject backGround;
    backGround.LoadImage("img//Background//Background.jpg", gScreen);
    backGround.Render(gScreen);
    backGround.CleanUp();

    BaseObject logo; 
    logo.LoadImage("img//logo//logo.png", gScreen);
    logo.setRectSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    logo.Render(gScreen);
    logo.CleanUp();
    SDL_RenderPresent(gScreen);
    SDL_Delay(1000);
}

void BounceBall::displayMenu() {
    MouseEvents* mouse = new MouseEvents;
    mouse->mouseHandleEvent();

    BaseObject backGround;
    backGround.LoadImage("img//Background//Background.jpg", gScreen);
    backGround.Render(gScreen);

    ButtonObject* playButton = new ButtonObject;
    playButton->LoadImage("img//button//menu_button_play.png", gScreen);
    playButton->setRectPos(450, 100);
    playButton->SetClips();
    playButton->Render(gScreen);
    bool typePlayButton = bool(mouse->CheckMouseInButton(playButton));

    ButtonObject* leaderboardButton = new ButtonObject;
    leaderboardButton->LoadImage("img//button//menu_button_leaderboard.png", gScreen);
    leaderboardButton->setRectPos(450, 200);
    leaderboardButton->SetClips();
    leaderboardButton->Render(gScreen);
    bool typeleaderboardButton = bool(mouse->CheckMouseInButton(leaderboardButton));

    SDL_RenderPresent(gScreen);

    if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
        if (typePlayButton) 
            display = 1;
        if (typeleaderboardButton)
            display = 2;
    }
    backGround.CleanUp();
    playButton->CleanUp();
    leaderboardButton->CleanUp();
}

void BounceBall::displayPlay() {
    MouseEvents* mouse = new MouseEvents;
    mouse->mouseHandleEvent();

    BaseObject backGround;
    backGround.LoadImage("img//Background//Background.jpg", gScreen);
    backGround.Render(gScreen);

    TTF_Font* FontGame;
    TextObject LevelText;

    if (TTF_Init() == -1) return;
    FontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (FontGame == NULL) {
        return;
    }

    int level = 0;
    ButtonObject* selectLevelButton = new ButtonObject;
    const int UPPER_BOUNDARY = 100;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 10; ++j) {
            selectLevelButton->LoadImage("img//level//select_level.png", gScreen);
            selectLevelButton->setRectPos(64 * j, UPPER_BOUNDARY + 64 * i);
            selectLevelButton->SetClips();
            selectLevelButton->Render(gScreen);
            bool typeleaderboardButton = bool(mouse->CheckMouseInButton(selectLevelButton));
            ++level;
            std::string strLevel = "";
            if (level < 10) strLevel += "0";
            strLevel += std::to_string(level);
            LevelText.SetText(strLevel);
            LevelText.LoadFromRenderText(FontGame, gScreen);
            LevelText.ShowText(gScreen, 64 * j + 17, UPPER_BOUNDARY + 64 * i + 17);
            if (gEvent.type == SDL_MOUSEBUTTONDOWN && typeleaderboardButton) {
                infoPlayer->setLevel(level);
                RSACryptoSystem AddressLevel;
                string address = "map//level";
                if (level < 10) address += "0";
                address += AddressLevel.ConvertNumberToString(level);
                address += ".map";
                LevelGame::LoadLevelGame(address.c_str(), gScreen, gEvent, infoPlayer);
            }
            selectLevelButton->CleanUp();
        } 
    }
    SDL_RenderPresent(gScreen); 
}

void BounceBall::displayleaderboard() {
    display = 0;
}

bool BounceBall::initSDL() {
    int init = SDL_Init(SDL_INIT_VIDEO);
    if (init < 0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (gWindow == NULL) {
        return false;
    }
    else {
        gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gScreen == NULL) return false;
        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) && imgFlags)) return false;
    }
    return true;
}

void BounceBall::CleanUp() {
    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}