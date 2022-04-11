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
    if (!initSDL())
        return -1;

    //displayLogo();

    display = 3;

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
                displayLeaderboard();
                break;
            case 3:
                displayLogin();
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

    ButtonObject* loginButton = new ButtonObject;
    loginButton->LoadImage("img//button//menu_button_login.png", gScreen);
    loginButton->setRectPos(450, 300);
    loginButton->SetClips();
    loginButton->Render(gScreen);
    bool typeloginButton = bool(mouse->CheckMouseInButton(loginButton));

    SDL_RenderPresent(gScreen);

    if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
        if (typePlayButton) 
            display = 1;
        if (typeleaderboardButton)
            display = 2;
        if (typeloginButton)
            display = 3;
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

    TTF_Font* fontGame;
    LTexture LevelText;

    if (TTF_Init() == -1) return;
    fontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (fontGame == NULL) {
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
            LevelText.LoadFromRenderText(fontGame, gScreen);
            LevelText.ShowText(gScreen, 64 * j + 17, UPPER_BOUNDARY + 64 * i + 17);
            if (gEvent.type == SDL_MOUSEBUTTONDOWN && typeleaderboardButton) {
                infoPlayer->setLevel(level);
                Cryptosystem AddressLevel;
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

void BounceBall::displayLeaderboard() {
    display = 0;
}

void BounceBall::displayLogin() {
    BaseObject backGround;
    backGround.LoadImage("img//Background//Background.jpg", gScreen);
    backGround.Render(gScreen);
    SDL_RenderPresent(gScreen);
    bool quit = false;

    TTF_Font* fontGame;
    if (TTF_Init() == -1) return;
    fontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (fontGame == NULL) {
        return;
    }

    ButtonObject* usernameButton = new ButtonObject;
    usernameButton->LoadImage("img//button//login_button_username.png", gScreen);
    usernameButton->SetClips();
    usernameButton->Set_x_pos((SCREEN_WIDTH - usernameButton->getWidthButton()) / 2);
    usernameButton->Set_y_pos(150);
    usernameButton->setRectPos(usernameButton->Get_x_pos(), usernameButton->Get_y_pos());
    usernameButton->Render(gScreen);

    ButtonObject* passwordButton = new ButtonObject;
    passwordButton->LoadImage("img//button//login_button_password.png", gScreen);
    passwordButton->SetClips();
    passwordButton->Set_x_pos((SCREEN_WIDTH - passwordButton->getWidthButton()) / 2);
    passwordButton->Set_y_pos(250);
    passwordButton->setRectPos(passwordButton->Get_x_pos(), passwordButton->Get_y_pos());
    passwordButton->Render(gScreen); 

    ButtonObject* loginButton = new ButtonObject;
    loginButton->LoadImage("img//button//login_button_login.png", gScreen);
    loginButton->SetClips();
    loginButton->Set_x_pos((SCREEN_WIDTH - loginButton->getWidthButton()) / 2);
    loginButton->Set_y_pos(350);
    loginButton->setRectPos(loginButton->Get_x_pos(), loginButton->Get_y_pos());
    loginButton->Render(gScreen);

    SDL_RenderPresent(gScreen);

    LTexture* gInputTextTexture;
    
    LTexture usernameTextTexture;
    usernameTextTexture.setPosX(usernameButton->Get_x_pos() + 20);
    usernameTextTexture.setPosY(usernameButton->Get_y_pos() + 15);

    LTexture passwordTextTexture;
    passwordTextTexture.setPosX(passwordButton->Get_x_pos() + 20);
    passwordTextTexture.setPosY(passwordButton->Get_y_pos() + 15);

    string usernameText = "username";
    string passwordText = "password";

    int selectText = selectInput::ACCOUNT;
    string *inputText;
    inputText = &usernameText;

    SDL_StartTextInput();
    while (!quit) {
        MouseEvents* mouse = new MouseEvents;
        mouse->mouseHandleEvent();
        bool selectUsernameButton = bool(mouse->CheckMouseInButton(usernameButton));
        bool selectPasswordButton = bool(mouse->CheckMouseInButton(passwordButton));
        bool selectLoginButton = bool(mouse->CheckMouseInButton(loginButton));
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectUsernameButton)
                    selectText = selectInput::ACCOUNT;
                if (selectPasswordButton)
                    selectText = selectInput::PASSWORD;
                if (selectLoginButton) {
                    if (checkInfoLogin(usernameText, passwordText)) {
                        display = 0;
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
                while ((*inputText).size() > 15) {
                    (*inputText).erase(0, 1);
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

        backGround.Render(gScreen, NULL);
        usernameButton->Render(gScreen, NULL);
        passwordButton->Render(gScreen, NULL);
        loginButton->Render(gScreen, NULL);

        if (usernameText == "") usernameText = "username";
        if (passwordText == "") passwordText = "password";

        usernameTextTexture.SetText(usernameText);
        usernameTextTexture.LoadFromRenderText(fontGame, gScreen);
        usernameTextTexture.ShowText(gScreen, usernameTextTexture.getPosX(), usernameTextTexture.getPosY());

        string encodePassword = "";
        for (int i = 0; i < passwordText.size(); ++i) encodePassword += "*";
        if (passwordText == "password") encodePassword = passwordText;
        passwordTextTexture.SetText(encodePassword);
        passwordTextTexture.LoadFromRenderText(fontGame, gScreen);
        passwordTextTexture.ShowText(gScreen, passwordTextTexture.getPosX(), passwordTextTexture.getPosY());

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

void BounceBall::CleanUp() {
    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}