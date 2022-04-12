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
#include "Cryptosystem.h"

using namespace std;

BounceBall::BounceBall() {

}

BounceBall::~BounceBall() {

}

InfoPlayer* infoPlayer = new InfoPlayer;

int BounceBall::startGame() {
    if (display == showDisplay::MENU) {
        if (!initSDL())
                return -1;
        displayLogo();
    }

    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

    ButtonObject* playButton = new ButtonObject;
    playButton->loadImage("img//button//menu_button_play.png", gScreen);
    playButton->setRectPos(450, 100);
    playButton->setClips();
    playButton->render(gScreen);

    ButtonObject* leaderboardButton = new ButtonObject;
    leaderboardButton->loadImage("img//button//menu_button_leaderboard.png", gScreen);
    leaderboardButton->setRectPos(450, 200);
    leaderboardButton->setClips();
    leaderboardButton->render(gScreen);

    ButtonObject* loginButton = new ButtonObject;
    if (display != showDisplay::HIDE_LOGIN) {
        loginButton->loadImage("img//button//menu_button_login.png", gScreen);
        loginButton->setRectPos(450, 300);
        loginButton->setClips();
        loginButton->render(gScreen);
    }
    SDL_RenderPresent(gScreen);

    bool quit = false;
    MouseEvents* mouse = new MouseEvents;

    display = 0;

    while (!quit) {
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                exit(0);
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                mouse->mouseHandleEvent();
                bool typePlayButton = bool(mouse->checkMouseInButton(playButton));
                bool typeLeaderboardButton = bool(mouse->checkMouseInButton(leaderboardButton));
                bool typeloginButton = bool(mouse->checkMouseInButton(loginButton));
                if (typePlayButton)
                    display = showDisplay::PLAY;
                if (typeLeaderboardButton)
                    display = showDisplay::LEADERBOARD;
                if (typeloginButton)
                    display = showDisplay::LOGIN;
            }
        }  
        switch (display) {
            case showDisplay::RE_MENU:
                startGame();
                break;
            case showDisplay::PLAY:
                displayPlay();
                break;
            case showDisplay::LEADERBOARD:
                displayLeaderboard();
                break;
            case showDisplay::LOGIN:
                displayLogin();
                break;
            case showDisplay::HIDE_LOGIN:
                startGame();
                break;
        }
    }
    backGround.cleanUp();
    playButton->cleanUp();
    leaderboardButton->cleanUp();
    loginButton->cleanUp();
    cleanUp();
}

void BounceBall::displayLogo() {
    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);
    backGround.cleanUp();

    BaseObject logo; 
    logo.loadImage("img//logo//logo.png", gScreen);
    logo.setRectSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    logo.render(gScreen);
    logo.cleanUp();
    SDL_RenderPresent(gScreen);
    SDL_Delay(1000);
}

void BounceBall::displayPlay() {
    MouseEvents* mouse = new MouseEvents;
    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

    TTF_Font* fontGame;
    LTexture LevelText;

    if (TTF_Init() == -1) return;
    fontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (fontGame == NULL) {
        return;
    }

    int level = 0;
    ButtonObject selectLevelButton[6][11];

    const int UPPER_BOUNDARY = 100;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 10; ++j) {
            selectLevelButton[i][j].loadImage("img//level//select_level.png", gScreen);
            selectLevelButton[i][j].setRectPos(64 * j, UPPER_BOUNDARY + 64 * i);
            selectLevelButton[i][j].setClips();
            selectLevelButton[i][j].render(gScreen);
            ++level;
            std::string strLevel = "";
            if (level < 10) strLevel += "0";
            strLevel += std::to_string(level);
            LevelText.setText(strLevel);
            LevelText.loadFromRenderText(fontGame, gScreen);
            LevelText.showText(gScreen, 64 * j + 17, UPPER_BOUNDARY + 64 * i + 17);
        } 
    }

    SDL_RenderPresent(gScreen); 
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                display = showDisplay::RE_MENU;
                SDL_RenderPresent(gScreen);
                break;
            }
            int level = 0;
            for (int i = 1; i <= 5; ++i) {
                for (int j = 1; j <= 10; ++j) {
                    mouse->mouseHandleEvent();
                    bool typeLeaderboardButton = bool(mouse->checkMouseInButton(&selectLevelButton[i][j]));
                    ++level;
                    if (gEvent.type == SDL_MOUSEBUTTONDOWN && typeLeaderboardButton) {
                        infoPlayer->setLevel(level);
                        Cryptosystem addressLevel;
                        string address = "map//level";
                        if (level < 10) address += "0";
                        address += addressLevel.convertNumberToString(level);
                        address += ".map";
                        LevelGame::loadLevelGame(address.c_str(), gScreen, gEvent, infoPlayer);
                        return;
                    }
                }
            }
        }
    }
    backGround.cleanUp();
}

void BounceBall::displayLeaderboard() {
    display = 0;
}

void BounceBall::displayLogin() {
    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);
    bool quit = false;

    TTF_Font* fontGame;
    if (TTF_Init() == -1) return;
    fontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (fontGame == NULL) {
        return;
    }

    ButtonObject* usernameButton = new ButtonObject;
    usernameButton->loadImage("img//button//login_button_username.png", gScreen);
    usernameButton->setClips();
    usernameButton->setXPos((SCREEN_WIDTH - usernameButton->getWidthButton()) / 2);
    usernameButton->setYPos(150);
    usernameButton->setRectPos(usernameButton->getXPos(), usernameButton->getYPos());
    usernameButton->render(gScreen);

    ButtonObject* passwordButton = new ButtonObject;
    passwordButton->loadImage("img//button//login_button_password.png", gScreen);
    passwordButton->setClips();
    passwordButton->setXPos((SCREEN_WIDTH - passwordButton->getWidthButton()) / 2);
    passwordButton->setYPos(250);
    passwordButton->setRectPos(passwordButton->getXPos(), passwordButton->getYPos());
    passwordButton->render(gScreen); 

    ButtonObject* loginButton = new ButtonObject;
    loginButton->loadImage("img//button//login_button_login.png", gScreen);
    loginButton->setClips();
    loginButton->setXPos((SCREEN_WIDTH - loginButton->getWidthButton()) / 2);
    loginButton->setYPos(350);
    loginButton->setRectPos(loginButton->getXPos(), loginButton->getYPos());
    loginButton->render(gScreen);

    SDL_RenderPresent(gScreen);

    LTexture* gInputTextTexture;
    
    LTexture usernameTextTexture;
    usernameTextTexture.setPosX(usernameButton->getXPos() + 20);
    usernameTextTexture.setPosY(usernameButton->getYPos() + 15);

    LTexture passwordTextTexture;
    passwordTextTexture.setPosX(passwordButton->getXPos() + 20);
    passwordTextTexture.setPosY(passwordButton->getYPos() + 15);

    string usernameText = "username"; 
    string passwordText = "password";

    int selectText = selectInput::ACCOUNT;
    string *inputText;
    inputText = &usernameText;

    SDL_StartTextInput();
    while (!quit) {
        MouseEvents* mouse = new MouseEvents;
        mouse->mouseHandleEvent();
        bool selectUsernameButton = bool(mouse->checkMouseInButton(usernameButton));
        bool selectPasswordButton = bool(mouse->checkMouseInButton(passwordButton));
        bool selectLoginButton = bool(mouse->checkMouseInButton(loginButton));
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                display = showDisplay::RE_MENU;
                return;
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectUsernameButton)
                    selectText = selectInput::ACCOUNT;
                if (selectPasswordButton)
                    selectText = selectInput::PASSWORD;
                if (selectLoginButton) {
                    if (checkInfoLogin(usernameText, passwordText)) {
                        display = 4;
                        infoPlayer->setUsername(usernameText);
                        return;
                    }
                }
            }

            if (selectText == selectInput::ACCOUNT) {
                inputText = &usernameText;
                gInputTextTexture = &usernameTextTexture;
            }
            else {
                inputText = &passwordText;
                gInputTextTexture = &passwordTextTexture;
            }

            if (gEvent.type == SDL_QUIT) {
                quit = true;
                display = 0;
                return;
            }
            else if (gEvent.type == SDL_KEYDOWN) {
                if (selectText == selectInput::ACCOUNT && *inputText == "username") {
                    *inputText = "";
                }
                else if (selectText == selectInput::PASSWORD && *inputText == "password") {
                    *inputText = "";
                }
                else if (*inputText == "") {
                    if (selectText == selectInput::ACCOUNT) {
                        *inputText = "username";
                    }
                    else {
                        *inputText = "password";
                    }
                }
                if (gEvent.key.keysym.sym == SDLK_BACKSPACE &&  (* inputText).size() > 0) {
                    (* inputText).pop_back();
                }
                else if (gEvent.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                    SDL_SetClipboardText((* inputText).c_str());
                }
                else if (gEvent.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                    (*inputText) = SDL_GetClipboardText();
                }
                else if (gEvent.key.keysym.sym == SDLK_KP_ENTER 
                    || gEvent.key.keysym.sym == SDLK_RETURN) {
                    if (selectText == selectInput::ACCOUNT) {
                        selectText = selectInput::PASSWORD;
                        inputText = &passwordText;
                        gInputTextTexture = &passwordTextTexture;
                    }
                    else {
                        selectText = selectInput::ACCOUNT;
                        inputText = &passwordText;
                        gInputTextTexture = &passwordTextTexture;
                    }
                }
            }
            else if (gEvent.type == SDL_TEXTINPUT) {
                if (!(SDL_GetModState() & KMOD_CTRL 
                    && (gEvent.text.text[0] == 'c' || gEvent.text.text[0] == 'C' 
                        || gEvent.text.text[0] == 'v' || gEvent.text.text[0] == 'V'))) {
                    *inputText += gEvent.text.text;
                }
            }
        }

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        backGround.render(gScreen, NULL);
        usernameButton->render(gScreen, NULL);
        passwordButton->render(gScreen, NULL);
        loginButton->render(gScreen, NULL);
    
        if (usernameText == "") usernameText = "username";
        if (passwordText == "") passwordText = "password";
        string showUsername = "";
        for (int i = max(0, (int) usernameText.size() - 15); i < usernameText.size(); ++i) {
            showUsername += usernameText[i];
        }
        usernameTextTexture.setText(showUsername);
        usernameTextTexture.loadFromRenderText(fontGame, gScreen);
        usernameTextTexture.showText(gScreen, usernameTextTexture.getPosX(), usernameTextTexture.getPosY());

        string encodePassword = "";
        for (int i = 0; i < min(15, passwordText.size()); ++i) encodePassword += "*";
        if (passwordText == "password") encodePassword = passwordText;
        passwordTextTexture.setText(encodePassword);
        passwordTextTexture.loadFromRenderText(fontGame, gScreen);
        passwordTextTexture.showText(gScreen, passwordTextTexture.getPosX(), passwordTextTexture.getPosY());

        SDL_RenderPresent(gScreen);
    }
}

bool BounceBall::checkInfoLogin(string username, string password) {
    return 1;
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

void BounceBall::cleanUp() {
    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}