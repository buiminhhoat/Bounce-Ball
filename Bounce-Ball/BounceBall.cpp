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
#include "Utils.h"

#include "ManagementObject.h"
#include "BounceBall.h"

using namespace std;

BounceBall::BounceBall() {

}

BounceBall::~BounceBall() {

}

InfoPlayer* infoPlayer = new InfoPlayer;

int BounceBall::startGame() {
    if (!initSDL())
        return -1;

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

void BounceBall::displayMenu() {
    MouseEvents* mouse = new MouseEvents;
    mouse->mouseHandleEvent();

    BaseObject backGround;
    backGround.LoadImage("img//Background.jpg", gScreen);
    backGround.Render(gScreen);

    ButtonObject* playButton = new ButtonObject;
    playButton->LoadImage("img//button//menu_button_play.png", gScreen);
    playButton->SetRectSize(450, 100);
    playButton->SetClips();
    playButton->Render(gScreen);
    bool typePlayButton = bool(mouse->CheckMouseInButton(playButton));

    ButtonObject* leaderboardButton = new ButtonObject;
    leaderboardButton->LoadImage("img//button//menu_button_leaderboard.png", gScreen);
    leaderboardButton->SetRectSize(450, 200);
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
}

void BounceBall::displayPlay() {
    LevelGame::LoadLevelGame("map//level02.map", gScreen, gEvent, infoPlayer);
    display = 0;
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