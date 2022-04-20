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
    databaseGame.setAddressFileImportDatabase(ADDRESS_IMPORT_DATABASE);
    databaseGame.setAddressFileExportDatabase(ADDRESS_EXPORT_DATABASE);
    databaseGame.importDatabase();
    if (display == typeDisplay::MENU) {
        if (!initSDL())
                return -1;
        //displayLogo();
    }

    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

    BaseObject logo;
    logo.loadImage("img//logo//logo_small.png", gScreen);
    logo.setRectSize(210, 159);
    //logo.setRectSize(192, 145);
    logo.setRectPos((SCREEN_WIDTH - logo.getRect().w) / 2, 5);
    logo.render(gScreen);
    logo.cleanUp();

    ButtonObject* playButton = new ButtonObject;
    playButton->loadImage("img//button//menu_button_play.png", gScreen);
    playButton->setClips();
    playButton->setRectPos(SCREEN_WIDTH / 2 - playButton->getRect().w - 32, 175);
    playButton->render(gScreen);

    ButtonObject* leaderboardButton = new ButtonObject;
    leaderboardButton->loadImage("img//button//menu_button_leaderboard.png", gScreen);
    leaderboardButton->setClips();
    leaderboardButton->setRectPos(SCREEN_WIDTH / 2 + 32, 175);
    leaderboardButton->render(gScreen);

    ButtonObject* howToPlayButton = new ButtonObject;
    howToPlayButton->loadImage("img//button//menu_button_howtoplay.png", gScreen);
    howToPlayButton->setClips();
    howToPlayButton->setRectPos(SCREEN_WIDTH / 2 - howToPlayButton->getRect().w - 32, 275);
    howToPlayButton->render(gScreen);

    ButtonObject* settingsButton = new ButtonObject;
    settingsButton->loadImage("img//button//menu_button_settings.png", gScreen);
    settingsButton->setClips();
    settingsButton->setRectPos(SCREEN_WIDTH / 2 + 32, 275);
    settingsButton->render(gScreen);

    ButtonObject* registerButton = new ButtonObject;
    registerButton->loadImage("img//button//menu_button_register.png", gScreen);
    registerButton->setClips();
    registerButton->setRectPos(SCREEN_WIDTH / 2 + 32, 375);
    registerButton->render(gScreen);

    ButtonObject* loginButton = new ButtonObject;
    ButtonObject* logoutButton = new ButtonObject;
    if (infoPlayer->getUsername() == "") {
        loginButton->loadImage("img//button//menu_button_login.png", gScreen);
        loginButton->setClips();
        loginButton->setRectPos(SCREEN_WIDTH / 2 - playButton->getRect().w - 32, 375);
        loginButton->render(gScreen);
    }
    else {
        logoutButton->loadImage("img//button//menu_button_logout.png", gScreen);
        logoutButton->setClips();
        logoutButton->setRectPos(SCREEN_WIDTH / 2 - playButton->getRect().w - 32, 375);
        logoutButton->render(gScreen);
    }

    SDL_RenderPresent(gScreen);

    bool quit = false;
    MouseEvents* mouse = new MouseEvents;

    display = typeDisplay::MENU;
    cerr << sound << '\n';
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
                bool typeLoginButton = bool(mouse->checkMouseInButton(loginButton));
                bool typeLogoutButton = bool(mouse->checkMouseInButton(logoutButton));
                bool typeHowToPlayButton = bool(mouse->checkMouseInButton(howToPlayButton));
                bool typeSettingsButton = bool(mouse->checkMouseInButton(settingsButton));
                bool typeRegisterButton = bool(mouse->checkMouseInButton(registerButton));
                if (typePlayButton) {
                    display = typeDisplay::PLAY;
                    if (infoPlayer->getUsername() == "") display = typeDisplay::LOGIN;
                } 
                if (typeLeaderboardButton) {
                    display = typeDisplay::LEADERBOARD;
                }
                if (typeLoginButton) {
                    display = typeDisplay::LOGIN;
                }
                if (typeLogoutButton) {
                    display = typeDisplay::LOGOUT;
                }
                if (typeSettingsButton) {
                    display = typeDisplay::SETTINGS;
                }
                if (typeHowToPlayButton) {
                    display = typeDisplay::HOW_TO_PLAY;
                }
                if (typeRegisterButton) {
                    display = typeDisplay::REGISTER;
                }
            }
        }  
        switch (display) {
            case typeDisplay::RE_MENU:
                startGame();
                break;
            case typeDisplay::PLAY:
                displayPlay();
                break;
            case typeDisplay::LEADERBOARD:
                displayLeaderboard();
                break;
            case typeDisplay::LOGIN:
                displayLogin();
                break;
            case typeDisplay::LOGOUT:
                displayLogout();
                break;
            case typeDisplay::REGISTER:
                displayRegister();
                break;
            case typeDisplay::SETTINGS:
                displaySettings();
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

    BaseObject logo;
    logo.loadImage("img//logo//logo_small.png", gScreen);
    logo.setRectSize(192, 145);
    logo.setRectPos((SCREEN_WIDTH - logo.getRect().w) / 2, 5);
    logo.render(gScreen);
    logo.cleanUp();

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", gScreen);
    backButton->setClips();
    backButton->setXPos(0);
    backButton->setYPos(SCREEN_HEIGHT - backButton->getRect().h);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());
    backButton->render(gScreen);

    const int UPPER_BOUNDARY = 100;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 10; ++j) {
            ++level;
            if (infoPlayer->getUnlockLevel(level)) {
                selectLevelButton[i][j].loadImage("img//level//select_level.png", gScreen);
                selectLevelButton[i][j].setIsUnlock(1);
            }
            else {
                selectLevelButton[i][j].loadImage("img//level//select_level_locked.png", gScreen);
                selectLevelButton[i][j].setIsUnlock(0);
            }
            selectLevelButton[i][j].setRectPos(64 * j, UPPER_BOUNDARY + 64 * i);
            selectLevelButton[i][j].setClips();
            selectLevelButton[i][j].render(gScreen);
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
        mouse->mouseHandleEvent();
        bool selectBackButton = bool(mouse->checkMouseInButton(backButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                SDL_RenderPresent(gScreen);
                break;
            }
            int level = 0;
            for (int i = 1; i <= 5; ++i) {
                for (int j = 1; j <= 10; ++j) {
                    if (selectLevelButton[i][j].getIsUnlock() == 0) continue;
                    mouse->mouseHandleEvent();
                    bool typeLeaderboardButton = bool(mouse->checkMouseInButton(&selectLevelButton[i][j]));
                    ++level;
                    if (gEvent.type == SDL_MOUSEBUTTONDOWN && typeLeaderboardButton) {
                        infoPlayer->setLevel(level);
                        infoPlayer->setSound(sound);
                        Cryptosystem addressLevel;
                        string address = "map//level";
                        if (level < 10) address += "0";
                        address += addressLevel.convertNumberToString(level);
                        address += ".map";
                        LevelGame levelGame;
                        int nextAction = levelGame.loadLevelGame(address.c_str(), gScreen, gEvent, infoPlayer);
                        while (nextAction == typeLevel::NEXT_LEVEL && level < 50) {
                            ++level;
                            infoPlayer->setUnlockLevel(level, 1);
                            infoPlayer->setSound(sound);
                            databaseGame.updateDatabaseUsername(*infoPlayer);
                            databaseGame.exportDatabase();  
                            address = "map//level";
                            if (level < 10) address += "0";
                            address += addressLevel.convertNumberToString(level);
                            address += ".map";
                            nextAction = levelGame.loadLevelGame(address.c_str(), gScreen, gEvent, infoPlayer);
                        }
                        return;
                    }
                }
            }
        }
    }
    backGround.cleanUp();
}

void BounceBall::displayLeaderboard() {
    MouseEvents* mouse = new MouseEvents;
    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

    BaseObject leaderboard;
    leaderboard.loadImage("img//leaderboard//leaderboard.png", gScreen);
    leaderboard.setRectSize(612, 512);
    leaderboard.setRectPos((SCREEN_WIDTH - leaderboard.getRect().w) / 2,
        (SCREEN_HEIGHT - leaderboard.getRect().h) / 2);
    leaderboard.render(gScreen);
    
    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", gScreen);
    backButton->setClips();
    backButton->setXPos(0);
    backButton->setYPos(SCREEN_HEIGHT - backButton->getRect().h);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());
    backButton->render(gScreen);

    databaseGame.sortAllDataInfoPlayer();
    vector <InfoPlayer> dataInfoPlayer = databaseGame.getDataInfoPlayer();
    
    TTF_Font* fontGame;
    LTexture usernameText;
    LTexture yourHighScoreText;

    if (TTF_Init() == -1) return;
    fontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (fontGame == NULL) {
        return;
    }

    int xPosUsername = leaderboard.getRect().x + 150;
    int yPosUsername = leaderboard.getRect().y + 168;

    int xPosYourHighScore = leaderboard.getRect().x + leaderboard.getRect().w - 95;
    int yPosYourHighScore = leaderboard.getRect().y + 168;

    for (int i = 0; i < 5; ++i) {
        string strUsernameText = "";
        string strYourHighScoreText = "";
        if (i < dataInfoPlayer.size()) {
            strUsernameText = dataInfoPlayer[i].getUsername();
            Cryptosystem cryptosystemYourHighScore;
            strYourHighScoreText = cryptosystemYourHighScore.convertNumberToString(dataInfoPlayer[i].getYourHighScore());
        }
        else {
            strUsernameText = "???";
            strYourHighScoreText = "0";
        }
        usernameText.setText(strUsernameText);
        usernameText.loadFromRenderText(fontGame, gScreen);
        usernameText.showText(gScreen, xPosUsername, yPosUsername);
        
        yourHighScoreText.setText(strYourHighScoreText);
        yourHighScoreText.loadFromRenderText(fontGame, gScreen);
        yourHighScoreText.showText(gScreen, xPosYourHighScore - yourHighScoreText.getWidth(), yPosYourHighScore);
        yPosUsername += 64;
        yPosYourHighScore += 64;
    }
    SDL_RenderPresent(gScreen);

    bool quit = 0;
    while (!quit) {
        mouse->mouseHandleEvent();
        bool selectBackButton = bool(mouse->checkMouseInButton(backButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                SDL_RenderPresent(gScreen);
                break;
            }
        }
    }
}

bool BounceBall::checkInfoLogin(string username, string password, InfoPlayer *infoPlayer) {
    InfoPlayer info = databaseGame.getDatabaseUsername(username);
    infoPlayer->setUsername(info.getUsername());
    infoPlayer->setPassword(info.getPassword());
    infoPlayer->setYourHighScore(info.getYourHighScore());
    for (int level = 1; level <= MAX_LEVEL; ++level)
        infoPlayer->setUnlockLevel(level, info.getUnlockLevel(level));
    if (info.getPassword() == password)
        return true;
    else
        return false;
}

void BounceBall::displayLogin() {
    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

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

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", gScreen);
    backButton->setClips();
    backButton->setXPos(0);
    backButton->setYPos(SCREEN_HEIGHT - backButton->getRect().h);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());
    backButton->render(gScreen);

    SDL_RenderPresent(gScreen);

    LTexture* gInputTextTexture = nullptr;
    
    LTexture usernameTextTexture;
    usernameTextTexture.setPosX(usernameButton->getXPos() + 20);
    usernameTextTexture.setPosY(usernameButton->getYPos() + 15);

    LTexture passwordTextTexture;
    passwordTextTexture.setPosX(passwordButton->getXPos() + 20);
    passwordTextTexture.setPosY(passwordButton->getYPos() + 15);

    //string usernameText = "username"; 
    //string passwordText = "password";    
    string usernameText = "buiminhhoat"; 
    string passwordText = "buiminhhoat";

    gInputTextTexture = &usernameTextTexture;

    BaseObject iteratorMouse;
    iteratorMouse.loadImage("img//button//iteratorMouse.png", gScreen);
    int selectText = selectInput::ACCOUNT;
    string *inputText;
    inputText = &usernameText;

    FPS fpsTimer;
    FPS flickerTimer;
    flickerTimer.start();
    SDL_StartTextInput();
    bool quit = false;
    while (!quit) {
        fpsTimer.start();
        MouseEvents* mouse = new MouseEvents;
        mouse->mouseHandleEvent();
        bool selectUsernameButton = bool(mouse->checkMouseInButton(usernameButton));
        bool selectPasswordButton = bool(mouse->checkMouseInButton(passwordButton));
        bool selectLoginButton = bool(mouse->checkMouseInButton(loginButton));
        bool selectBackButton = bool(mouse->checkMouseInButton(backButton));
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectUsernameButton) 
                    selectText = selectInput::ACCOUNT;
                if (selectPasswordButton)
                    selectText = selectInput::PASSWORD;
                if (selectLoginButton) {
                    if (checkInfoLogin(usernameText, passwordText, infoPlayer)) {
                        display = typeDisplay::RE_MENU;
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                            "Login successfully",
                            "Dang nhap thanh cong",
                            NULL);
                        return;
                    }
                    else {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                            "Failed to Login",
                            "Wrong account or password",
                            NULL);
                    }
                }
                if (selectBackButton) {
                    quit = true;
                    display = typeDisplay::RE_MENU;
                    return;
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
                display = typeDisplay::MENU;
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
                else if (gEvent.key.keysym.sym == SDLK_TAB) {
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
                else if (gEvent.key.keysym.sym == SDLK_RETURN) {
                    if (checkInfoLogin(usernameText, passwordText, infoPlayer)) {
                        display = typeDisplay::RE_MENU;
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                            "Login successfully",
                            "Dang nhap thanh cong",
                            NULL);
                        return;
                    }
                    else {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                            "Failed to Login",
                            "Wrong account or password",
                            NULL);
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
        backButton->render(gScreen, NULL);
    
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

        iteratorMouse.setRectPos(gInputTextTexture->getPosX()
                                + gInputTextTexture->getWidth() + 2,
                                    gInputTextTexture->getPosY() + 4);
        
        if (flickerTimer.getTicks() > 400 && flickerTimer.getTicks() < 800) {
            iteratorMouse.render(gScreen);
        }
        if (flickerTimer.getTicks() > 800) flickerTimer.start();

        SDL_RenderPresent(gScreen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = 1000 / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
}

void BounceBall::displayLogout() {
    infoPlayer->setUsername("");
    display = typeDisplay::RE_MENU;
}

bool BounceBall::notificationStatusRegister(string usernameText, string passwordText) {
    InfoPlayer infoRegister;
    infoRegister.setUsername(usernameText);
    infoRegister.setPassword(passwordText);
    infoRegister.setYourHighScore(0);
    infoRegister.setUnlockLevel(1, 1);
    pair <string, bool> statusRegister = databaseGame.registerAccount(infoRegister);
    if (statusRegister.second == true) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
            "Register successfully",
            statusRegister.first.c_str(),
            NULL);
        return true;
    }
    else {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
            "Failed to Register",
            statusRegister.first.c_str(),
            NULL);
        return false;
    }
}

void BounceBall::displayRegister() {
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
    usernameButton->loadImage("img//button//register_button_username.png", gScreen);
    usernameButton->setClips();
    usernameButton->setXPos((SCREEN_WIDTH - usernameButton->getWidthButton()) / 2);
    usernameButton->setYPos(150);
    usernameButton->setRectPos(usernameButton->getXPos(), usernameButton->getYPos());
    usernameButton->render(gScreen);

    ButtonObject* passwordButton = new ButtonObject;
    passwordButton->loadImage("img//button//register_button_password.png", gScreen);
    passwordButton->setClips();
    passwordButton->setXPos((SCREEN_WIDTH - passwordButton->getWidthButton()) / 2);
    passwordButton->setYPos(250);
    passwordButton->setRectPos(passwordButton->getXPos(), passwordButton->getYPos());
    passwordButton->render(gScreen);

    ButtonObject* loginButton = new ButtonObject;
    loginButton->loadImage("img//button//register_button_register.png", gScreen);
    loginButton->setClips();
    loginButton->setXPos((SCREEN_WIDTH - loginButton->getWidthButton()) / 2);
    loginButton->setYPos(350);
    loginButton->setRectPos(loginButton->getXPos(), loginButton->getYPos());
    loginButton->render(gScreen);

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", gScreen);
    backButton->setClips();
    backButton->setXPos(0);
    backButton->setYPos(SCREEN_HEIGHT - backButton->getRect().h);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());
    backButton->render(gScreen);

    SDL_RenderPresent(gScreen);

    LTexture* gInputTextTexture = nullptr;

    LTexture usernameTextTexture;
    usernameTextTexture.setPosX(usernameButton->getXPos() + 20);
    usernameTextTexture.setPosY(usernameButton->getYPos() + 15);
    usernameTextTexture.setColor(LTexture::COLOR::PURPLE_COLOR);

    LTexture passwordTextTexture;
    passwordTextTexture.setPosX(passwordButton->getXPos() + 20);
    passwordTextTexture.setPosY(passwordButton->getYPos() + 15);
    passwordTextTexture.setColor(LTexture::COLOR::PURPLE_COLOR);

    //string usernameText = "username"; 
    //string passwordText = "password";    
    string usernameText = "buiminhhoat";
    string passwordText = "buiminhhoat";

    gInputTextTexture = &usernameTextTexture;

    BaseObject iteratorMouse;
    iteratorMouse.loadImage("img//button//iteratorMouse.png", gScreen);
    int selectText = selectInput::ACCOUNT;
    string* inputText;
    inputText = &usernameText;

    FPS fpsTimer;
    FPS flickerTimer;
    flickerTimer.start();
    SDL_StartTextInput();
    while (!quit) {
        fpsTimer.start();
        MouseEvents* mouse = new MouseEvents;
        mouse->mouseHandleEvent();
        bool selectUsernameButton = bool(mouse->checkMouseInButton(usernameButton));
        bool selectPasswordButton = bool(mouse->checkMouseInButton(passwordButton));
        bool selectRegisterButton = bool(mouse->checkMouseInButton(loginButton));
        bool selectBackButton = bool(mouse->checkMouseInButton(backButton));
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                return;
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectUsernameButton)
                    selectText = selectInput::ACCOUNT;
                if (selectPasswordButton)
                    selectText = selectInput::PASSWORD;
                if (selectRegisterButton) {
                    if (notificationStatusRegister(usernameText, passwordText) == true) {
                        display = typeDisplay::RE_MENU;
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
                display = typeDisplay::MENU;
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
                if (gEvent.key.keysym.sym == SDLK_BACKSPACE && (*inputText).size() > 0) {
                    (*inputText).pop_back();
                }
                else if (gEvent.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                    SDL_SetClipboardText((*inputText).c_str());
                }
                else if (gEvent.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                    (*inputText) = SDL_GetClipboardText();
                }
                else if (gEvent.key.keysym.sym == SDLK_TAB) {
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
                else if (gEvent.key.keysym.sym == SDLK_RETURN) {
                    if (notificationStatusRegister(usernameText, passwordText) == true) {
                        display = typeDisplay::RE_MENU;
                        return;
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
        backButton->render(gScreen, NULL);

        if (usernameText == "") usernameText = "username";
        if (passwordText == "") passwordText = "password";
        string showUsername = "";
        for (int i = max(0, (int)usernameText.size() - 15); i < usernameText.size(); ++i) {
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

        iteratorMouse.setRectPos(gInputTextTexture->getPosX()
            + gInputTextTexture->getWidth() + 2,
            gInputTextTexture->getPosY() + 4);

        if (flickerTimer.getTicks() > 400 && flickerTimer.getTicks() < 800) {
            iteratorMouse.render(gScreen);
        }
        if (flickerTimer.getTicks() > 800) flickerTimer.start();

        SDL_RenderPresent(gScreen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = 1000 / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
}

void BounceBall::displaySettings() {
    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

    BaseObject boardSettings;
    boardSettings.loadImage("img//settingsBoard//settingsBoard.png", gScreen);
    boardSettings.setRectPos((SCREEN_WIDTH - boardSettings.getRect().w) / 2,
        (SCREEN_HEIGHT - boardSettings.getRect().h) / 2);
    boardSettings.render(gScreen);

    int setSound = sound;
    ButtonObject* soundOnButton = new ButtonObject;
    soundOnButton->loadImage("img//settingsBoard//settingsBoard_OnButton.png", gScreen);
    soundOnButton->setClips();
    soundOnButton->setXPos(boardSettings.getRect().x + 235);
    soundOnButton->setYPos(boardSettings.getRect().y + 148);
    soundOnButton->setRectPos(soundOnButton->getXPos(), soundOnButton->getYPos());

    ButtonObject* soundOffButton = new ButtonObject;
    soundOffButton->loadImage("img//settingsBoard//settingsBoard_OffButton.png", gScreen);
    soundOffButton->setClips();
    soundOffButton->setXPos(boardSettings.getRect().x + 235);
    soundOffButton->setYPos(boardSettings.getRect().y + 148);
    soundOffButton->setRectPos(soundOffButton->getXPos(), soundOffButton->getYPos());

    ButtonObject* saveButton = new ButtonObject;
    saveButton->loadImage("img//settingsBoard//settingsBoard_SaveButton.png", gScreen);
    saveButton->setClips();
    saveButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    saveButton->setYPos(boardSettings.getRect().y + 210);
    saveButton->setRectPos(saveButton->getXPos(), saveButton->getYPos());

    ButtonObject* restoreButton = new ButtonObject;
    restoreButton->loadImage("img//settingsBoard//settingsBoard_RestoreButton.png", gScreen);
    restoreButton->setClips();
    restoreButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    restoreButton->setYPos(saveButton->getRect().y + saveButton->getRect().h + 20);
    restoreButton->setRectPos(restoreButton->getXPos(), restoreButton->getYPos());

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//settingsBoard//settingsBoard_BackButton.png", gScreen);
    backButton->setClips();
    backButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    backButton->setYPos(restoreButton->getRect().y + restoreButton->getRect().h + 20);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());

    SDL_RenderPresent(gScreen);
    bool quit = false;
    while (!quit) {
        MouseEvents* mouse = new MouseEvents;
        mouse->mouseHandleEvent();
        bool selectSoundOnButton = bool(mouse->checkMouseInButton(soundOnButton));
        bool selectSoundOffButton = bool(mouse->checkMouseInButton(soundOffButton));
        bool selectBackButton = bool(mouse->checkMouseInButton(backButton));
        bool selectSaveButton = bool(mouse->checkMouseInButton(saveButton));
        bool selectRestoreButton = bool(mouse->checkMouseInButton(restoreButton));
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                return;
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectSoundOnButton || selectSoundOffButton) {
                    if (setSound == typeSound::ON) setSound = typeSound::OFF;
                    else setSound = typeSound::ON;
                }
                if (selectRestoreButton)
                    setSound = typeSound::ON;
                if (selectSaveButton) {
                    sound = setSound;
                }
            }
        }

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        backGround.render(gScreen, NULL);
        boardSettings.render(gScreen, NULL);
        if (setSound == true)
            soundOnButton->render(gScreen, NULL);
        else
            soundOffButton->render(gScreen, NULL);
        saveButton->render(gScreen);
        restoreButton->render(gScreen);
        backButton->render(gScreen);
        SDL_RenderPresent(gScreen);
    }
}

bool BounceBall::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
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
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            return false;
        }
    }
    return true;
}

void BounceBall::cleanUp() {
    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}