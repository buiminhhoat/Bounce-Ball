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

int BounceBall::startGame() {
    databaseGame.setAddressFileImportDatabase(ADDRESS_DATABASE);
    databaseGame.setAddressFileExportDatabase(ADDRESS_DATABASE);
    databaseGame.importDatabase();
    if (display == typeDisplay::MENU) {
        if (!initSDL())
                return -1;
        displayLogo();
    }

    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

    BaseObject logo;
    logo.loadImage("img//logo//logo_small.png", gScreen);
    logo.setRectSize(210, 159);
    logo.setRectPos((SCREEN_WIDTH - logo.getRect().w) / 2, 5);
    logo.render(gScreen);
    logo.cleanUp();

    ButtonObject* playButton = new ButtonObject;
    playButton->loadImage("img//button//menu_button_play.png", gScreen);
    playButton->setRectPos(SCREEN_WIDTH / 2 - playButton->getRect().w - 32, 175);
    playButton->render(gScreen);

    ButtonObject* leaderboardButton = new ButtonObject;
    leaderboardButton->loadImage("img//button//menu_button_leaderboard.png", gScreen);
    leaderboardButton->setRectPos(SCREEN_WIDTH / 2 + 32, 175);
    leaderboardButton->render(gScreen);

    ButtonObject* howToPlayButton = new ButtonObject;
    howToPlayButton->loadImage("img//button//menu_button_howtoplay.png", gScreen);
    howToPlayButton->setRectPos(SCREEN_WIDTH / 2 - howToPlayButton->getRect().w - 32, 275);
    howToPlayButton->render(gScreen);

    ButtonObject* settingsButton = new ButtonObject;
    settingsButton->loadImage("img//button//menu_button_settings.png", gScreen);
    settingsButton->setRectPos(SCREEN_WIDTH / 2 + 32, 275);
    settingsButton->render(gScreen);

    ButtonObject* registerButton = new ButtonObject;
    registerButton->loadImage("img//button//menu_button_register.png", gScreen);
    registerButton->setRectPos(SCREEN_WIDTH / 2 + 32, 375);
    registerButton->render(gScreen);

    ButtonObject* loginButton = new ButtonObject;
    ButtonObject* logoutButton = new ButtonObject;
    if (infoPlayer->getUsername() == "") {
        loginButton->loadImage("img//button//menu_button_login.png", gScreen);
        loginButton->setRectPos(SCREEN_WIDTH / 2 - playButton->getRect().w - 32, 375);
        loginButton->render(gScreen);
    }
    else {
        logoutButton->loadImage("img//button//menu_button_logout.png", gScreen);
        logoutButton->setRectPos(SCREEN_WIDTH / 2 - playButton->getRect().w - 32, 375);
        logoutButton->render(gScreen);
    }

    SDL_RenderPresent(gScreen);

    bool quit = false;
    MouseEvents mouse;

    display = typeDisplay::MENU;
    while (!quit) {
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                exit(0);
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                mouse.mouseHandleEvent();
                bool clickPlayButton = bool(mouse.checkMouseInButton(playButton));
                bool clickLeaderboardButton = bool(mouse.checkMouseInButton(leaderboardButton));
                bool clickLoginButton = bool(mouse.checkMouseInButton(loginButton));
                bool clickLogoutButton = bool(mouse.checkMouseInButton(logoutButton));
                bool clickHowToPlayButton = bool(mouse.checkMouseInButton(howToPlayButton));
                bool clickSettingsButton = bool(mouse.checkMouseInButton(settingsButton));
                bool clickRegisterButton = bool(mouse.checkMouseInButton(registerButton));
                if (clickPlayButton) {
                    display = typeDisplay::PLAY;
                    if (infoPlayer->getUsername() == "") display = typeDisplay::LOGIN;
                } 
                if (clickLeaderboardButton) {
                    display = typeDisplay::LEADERBOARD;
                }
                if (clickLoginButton) {
                    display = typeDisplay::LOGIN;
                }
                if (clickLogoutButton) {
                    display = typeDisplay::LOGOUT;
                }
                if (clickSettingsButton) {
                    display = typeDisplay::SETTINGS;
                }
                if (clickHowToPlayButton) {
                    display = typeDisplay::HOW_TO_PLAY;
                }
                if (clickRegisterButton) {
                    display = typeDisplay::REGISTER;
                }
                if (clickHowToPlayButton) {
                    display = typeDisplay::HOW_TO_PLAY;
                }
            }
        }  
        switch (display) {
            case typeDisplay::RE_MENU:
                backGround.cleanUp();
                logo.cleanUp();
                playButton->cleanUp();
                leaderboardButton->cleanUp();
                howToPlayButton->cleanUp();
                loginButton->cleanUp();
                logoutButton->cleanUp();
                settingsButton->cleanUp();
                registerButton->cleanUp();
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
            case typeDisplay::HOW_TO_PLAY:
                displayHowToPlayButton();
                break;
        }
    }
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
    MouseEvents mouse;
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
    
    BaseObject logo;
    logo.loadImage("img//logo//logo_small.png", gScreen);
    logo.setRectSize(192, 145);
    logo.setRectPos((SCREEN_WIDTH - logo.getRect().w) / 2, 5);
    logo.render(gScreen);
    logo.cleanUp();

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", gScreen);
    backButton->setXPos(0);
    backButton->setYPos(SCREEN_HEIGHT - backButton->getRect().h);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());
    backButton->render(gScreen);

    const int UPPER_BOUNDARY = 100;
    
    for (int i = 1; i <= MAX_ROW_SHOW; ++i) {
        for (int j = 1; j <= MAX_COL_SHOW; ++j) {
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
        mouse.mouseHandleEvent();
        bool selectBackButton = bool(mouse.checkMouseInButton(backButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                SDL_RenderPresent(gScreen);
                return;
            }
            int level = 0;
            for (int i = 1; i <= MAX_ROW_SHOW; ++i) {
                for (int j = 1; j <= MAX_COL_SHOW; ++j) {
                    if (selectLevelButton[i][j].getIsUnlock() == 0) continue;
                    mouse.mouseHandleEvent();
                    bool clickLeaderboardButton = bool(mouse.checkMouseInButton(&selectLevelButton[i][j]));
                    ++level;
                    if (gEvent.type == SDL_MOUSEBUTTONDOWN && clickLeaderboardButton) {
                        infoPlayer->setlife(ORIGINAL_LIFE);
                        infoPlayer->setLevel(level);
                        infoPlayer->setSound(sound);
                        Cryptosystem addressLevel;
                        string address = "map//level";
                        if (level < 10) address += "0";
                        address += addressLevel.convertNumberToString(level);
                        address += ".map";
                        LevelGame levelGame;
                        int nextAction = levelGame.loadLevelGame(address.c_str(), gScreen, gEvent, infoPlayer);
                        while (nextAction == typeLevel::NEXT_LEVEL && level < MAX_LEVEL) {
                            ++level;
                            infoPlayer->setUnlockLevel(level, TypeLevel::UNLOCK);
                            infoPlayer->setSound(sound);
                            databaseGame.updateDatabaseUsername(*infoPlayer);
                            databaseGame.exportDatabase();  
                            address = "map//level";
                            if (level < 10) address += "0";
                            address += addressLevel.convertNumberToString(level);
                            address += ".map";
                            nextAction = levelGame.loadLevelGame(address.c_str(), gScreen, gEvent, infoPlayer);
                        }
                        infoPlayer->setUnlockLevel(level, TypeLevel::UNLOCK);
                        infoPlayer->setSound(sound);
                        databaseGame.updateDatabaseUsername(*infoPlayer);
                        databaseGame.exportDatabase();
                        display = typeDisplay::RE_MENU;
                        return;
                    }
                }
            }
        }
    }
    backGround.cleanUp();
}

void BounceBall::displayLeaderboard() {
    MouseEvents mouse;
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
    fontGame = TTF_OpenFont("font//no_continue.ttf", FONT_SIZE);
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
        mouse.mouseHandleEvent();
        bool selectBackButton = bool(mouse.checkMouseInButton(backButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                SDL_RenderPresent(gScreen);
                backGround.cleanUp();
                leaderboard.cleanUp();
                backButton->cleanUp();
                usernameText.cleanUp();
                yourHighScoreText.cleanUp();
                return;
            }
        }
    }
}

bool BounceBall::checkInfoLogin(string usernameText, string passwordText, InfoPlayer *infoPlayer) {
    for (int i = 0; i < usernameText.size(); ++i)
        if (usernameText[i] >= 'a' && usernameText[i] <= 'z')
            usernameText[i] -= 32;

    for (int i = 0; i < passwordText.size(); ++i)
        if (passwordText[i] >= 'a' && passwordText[i] <= 'z')
            passwordText[i] -= 32;
    InfoPlayer info = databaseGame.getDatabaseUsername(usernameText);
    infoPlayer->setUsername(info.getUsername());
    infoPlayer->setPassword(info.getPassword());
    infoPlayer->setYourHighScore(info.getYourHighScore());
    for (int level = 1; level <= MAX_LEVEL; ++level)
        infoPlayer->setUnlockLevel(level, info.getUnlockLevel(level));
    if (info.getPassword() == passwordText)
        return true;
    else
        return false;
}

void BounceBall::displayLogin() {
    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

    BaseObject boardLogin;
    boardLogin.loadImage("img//board//boardLogin.png", gScreen);
    boardLogin.setRectPos((SCREEN_WIDTH - boardLogin.getRect().w) / 2,
        (SCREEN_HEIGHT - boardLogin.getRect().h) / 2);
    boardLogin.render(gScreen);

    TTF_Font* fontGame;
    if (TTF_Init() == -1) return;
    fontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (fontGame == NULL) {
        return;
    }

    ButtonObject* registerButton = new ButtonObject;
    registerButton->loadImage("img//button//menu_button_register.png", gScreen);
    registerButton->setRectSize(175, 64);
    registerButton->setRectPos(SCREEN_WIDTH - registerButton->getRect().w, SCREEN_HEIGHT - registerButton->getRect().h);

    //ButtonObject registerButton;
    //registerButton.loadImage("img//button//menu_button_register.png", gScreen);
    //registerButton.setRectSize(175, 64);
    //registerButton.setRectPos(SCREEN_WIDTH - registerButton.getRect().w, 
    //                            SCREEN_HEIGHT - registerButton.getRect().h);

    ButtonObject* usernameButton = new ButtonObject;
    usernameButton->loadImage("img//button//login_button_username.png", gScreen);
    usernameButton->setXPos((SCREEN_WIDTH - usernameButton->getWidth()) / 2);
    usernameButton->setYPos(150);
    usernameButton->setRectPos(usernameButton->getXPos(), usernameButton->getYPos());
    usernameButton->render(gScreen);

    ButtonObject* passwordButton = new ButtonObject;
    passwordButton->loadImage("img//button//login_button_password.png", gScreen);
    passwordButton->setXPos((SCREEN_WIDTH - passwordButton->getWidth()) / 2);
    passwordButton->setYPos(250);
    passwordButton->setRectPos(passwordButton->getXPos(), passwordButton->getYPos());
    passwordButton->render(gScreen); 

    ButtonObject* loginButton = new ButtonObject;
    loginButton->loadImage("img//button//login_button_login.png", gScreen);
    loginButton->setXPos((SCREEN_WIDTH - loginButton->getWidth()) / 2);
    loginButton->setYPos(350);
    loginButton->setRectPos(loginButton->getXPos(), loginButton->getYPos());
    loginButton->render(gScreen);

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", gScreen);
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

    /*string usernameText = "username"; 
    string passwordText = "password"; */   
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
    bool deletedAccount = false;
    bool deletedPassword = false;
    while (!quit) {
        fpsTimer.start();
        MouseEvents mouse;
        mouse.mouseHandleEvent();
        bool selectUsernameButton = bool(mouse.checkMouseInButton(usernameButton));
        bool selectPasswordButton = bool(mouse.checkMouseInButton(passwordButton));
        bool selectLoginButton = bool(mouse.checkMouseInButton(loginButton));
        bool selectBackButton = bool(mouse.checkMouseInButton(backButton));
        bool selectRegisterButton = bool(mouse.checkMouseInButton(&registerButton));
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
                            "Bounce Ball",
                            "Login successfully",
                            NULL);
                        return;
                    }
                    else {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                            "Bounce Ball",
                            "Wrong account or password",
                            NULL);
                    }
                }
                if (selectBackButton) {
                    quit = true;
                    display = typeDisplay::RE_MENU;
                    return;
                }
                if (selectRegisterButton) {
                    backGround.cleanUp();
                    boardLogin.cleanUp();
                    registerButton.cleanUp();
                    usernameButton->cleanUp();
                    passwordButton->cleanUp();
                    loginButton->cleanUp();
                    backButton->cleanUp();
                    gInputTextTexture->cleanUp();
                    usernameTextTexture.cleanUp();
                    passwordTextTexture.cleanUp();
                    iteratorMouse.cleanUp();
                    display = typeDisplay::REGISTER;
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
                    if (selectText == selectInput::ACCOUNT && deletedAccount == false) {
                        *inputText = "username";
                    }
                    else if (selectText == selectInput::PASSWORD && deletedPassword == false) {
                        *inputText = "password";
                    }
                }
                if (gEvent.key.keysym.sym == SDLK_BACKSPACE) {
                    if ((*inputText).size() > 0) (* inputText).pop_back();
                    if (inputText == &usernameText) deletedAccount = true;
                    else deletedPassword = true;
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
                            "Bounce Ball",
                            "Login successfully",
                            NULL);
                        return;
                    }
                    else {
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                            "Bounce Ball",
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

        backGround.render(gScreen);
        boardLogin.render(gScreen);
        usernameButton->render(gScreen);
        passwordButton->render(gScreen);
        loginButton->render(gScreen);
        backButton->render(gScreen);
        registerButton.render(gScreen);
    
        if (usernameText == "" && deletedAccount == false) usernameText = "username";
        if (passwordText == "" && deletedPassword == false) passwordText = "password";
        string showUsername = "";
        for (int i = max(0, (int) usernameText.size() - 15); i < usernameText.size(); ++i) {
            showUsername += usernameText[i];
        }
        if (showUsername.size() > 0) {
            usernameTextTexture.setText(showUsername);
            usernameTextTexture.loadFromRenderText(fontGame, gScreen);
            usernameTextTexture.showText(gScreen, usernameTextTexture.getPosX(), usernameTextTexture.getPosY());
        }
        else {
            gInputTextTexture->setPosX(boardLogin.getRect().x + 85);
            gInputTextTexture->setWidth(0);
        }
        

        string encodePassword = "";
        for (int i = 0; i < min(15, passwordText.size()); ++i) encodePassword += "*";
        if (passwordText == "password") encodePassword = passwordText;
        if (encodePassword.size() > 0) {
            passwordTextTexture.setText(encodePassword);
            passwordTextTexture.loadFromRenderText(fontGame, gScreen);
            passwordTextTexture.showText(gScreen, passwordTextTexture.getPosX(), passwordTextTexture.getPosY());
        }
        else {
            gInputTextTexture->setPosX(boardLogin.getRect().x + 85);
            gInputTextTexture->setWidth(0);
        }
        
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
    for (int i = 0; i < usernameText.size(); ++i)
        if (usernameText[i] >= 'a' && usernameText[i] <= 'z')
            usernameText[i] -= 32;

    for (int i = 0; i < passwordText.size(); ++i)
        if (passwordText[i] >= 'a' && passwordText[i] <= 'z')
            passwordText[i] -= 32;

    InfoPlayer infoRegister;
    infoRegister.setUsername(usernameText);
    infoRegister.setPassword(passwordText);
    infoRegister.setYourHighScore(0);
    infoRegister.setUnlockLevel(1, TypeLevel::UNLOCK);
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

    BaseObject boardRegister;
    boardRegister.loadImage("img//board//boardRegister.png", gScreen);
    boardRegister.setRectPos((SCREEN_WIDTH - boardRegister.getRect().w) / 2,
        (SCREEN_HEIGHT - boardRegister.getRect().h) / 2);
    boardRegister.render(gScreen);

    TTF_Font* fontGame;
    if (TTF_Init() == -1) return;
    fontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (fontGame == NULL) {
        return;
    }

    ButtonObject* usernameButton = new ButtonObject;
    usernameButton->loadImage("img//button//register_button_username.png", gScreen);
    usernameButton->setXPos((SCREEN_WIDTH - usernameButton->getWidth()) / 2);
    usernameButton->setYPos(150);
    usernameButton->setRectPos(usernameButton->getXPos(), usernameButton->getYPos());
    usernameButton->render(gScreen);

    ButtonObject* passwordButton = new ButtonObject;
    passwordButton->loadImage("img//button//register_button_password.png", gScreen);
    passwordButton->setXPos((SCREEN_WIDTH - passwordButton->getWidth()) / 2);
    passwordButton->setYPos(250);
    passwordButton->setRectPos(passwordButton->getXPos(), passwordButton->getYPos());
    passwordButton->render(gScreen);

    ButtonObject* registerButton = new ButtonObject;
    registerButton->loadImage("img//button//register_button_register.png", gScreen);
    registerButton->setXPos((SCREEN_WIDTH - registerButton->getWidth()) / 2);
    registerButton->setYPos(350);
    registerButton->setRectPos(registerButton->getXPos(), registerButton->getYPos());
    registerButton->render(gScreen);

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", gScreen);
    backButton->setXPos(0);
    backButton->setYPos(SCREEN_HEIGHT - backButton->getRect().h);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());
    backButton->render(gScreen);

    ButtonObject* loginButton = new ButtonObject;
    if (infoPlayer->getUsername() == "") {
        loginButton->loadImage("img//button//menu_button_login.png", gScreen);
        loginButton->setRectSize(175, 64);
        loginButton->setRectPos(SCREEN_WIDTH - loginButton->getRect().w,
                        SCREEN_HEIGHT - loginButton->getRect().h);
        loginButton->render(gScreen);
    }

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

    string usernameText = "username"; 
    string passwordText = "password";    
    //string usernameText = "buiminhhoat";
    //string passwordText = "buiminhhoat";

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
    bool deletedAccount = false;
    bool deletedPassword = false;
    bool quit = false;
    while (!quit) {
        fpsTimer.start();
        MouseEvents mouse;
        mouse.mouseHandleEvent();
        bool selectUsernameButton = bool(mouse.checkMouseInButton(usernameButton));
        bool selectPasswordButton = bool(mouse.checkMouseInButton(passwordButton));
        bool selectRegisterButton = bool(mouse.checkMouseInButton(registerButton));
        bool selectBackButton = bool(mouse.checkMouseInButton(backButton));
        bool selectLoginButton = bool(mouse.checkMouseInButton(loginButton));
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
                if (selectLoginButton) {
                    backGround.cleanUp();
                    boardRegister.cleanUp();
                    registerButton->cleanUp();
                    usernameButton->cleanUp();
                    passwordButton->cleanUp();
                    loginButton->cleanUp();
                    backButton->cleanUp();
                    gInputTextTexture->cleanUp();
                    usernameTextTexture.cleanUp();
                    passwordTextTexture.cleanUp();
                    iteratorMouse.cleanUp();
                    display = typeDisplay::LOGIN;
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
                    if (selectText == selectInput::ACCOUNT && deletedAccount == false) {
                        *inputText = "username";
                    }
                    else if (selectText == selectInput::PASSWORD && deletedPassword == false) {
                        *inputText = "password";
                    }
                }
                if (gEvent.key.keysym.sym == SDLK_BACKSPACE) {
                    if ((*inputText).size() > 0) (*inputText).pop_back();
                    if (inputText == &usernameText) deletedAccount = true;
                    else deletedPassword = true;
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

        backGround.render(gScreen);
        boardRegister.render(gScreen);
        usernameButton->render(gScreen);
        passwordButton->render(gScreen);
        loginButton->render(gScreen);
        backButton->render(gScreen);
        registerButton->render(gScreen);

        if (usernameText == "" && deletedAccount == false) usernameText = "username";
        if (passwordText == "" && deletedPassword == false) passwordText = "password";

        string showUsername = "";
        for (int i = max(0, (int)usernameText.size() - 15); i < usernameText.size(); ++i) {
            showUsername += usernameText[i];
        }

        if (showUsername.size() > 0) {
            usernameTextTexture.setText(showUsername);
            usernameTextTexture.loadFromRenderText(fontGame, gScreen);
            usernameTextTexture.showText(gScreen, usernameTextTexture.getPosX(), usernameTextTexture.getPosY());
        }
        else {
            gInputTextTexture->setPosX(boardRegister.getRect().x + 85);
            gInputTextTexture->setWidth(0);
        }

        string encodePassword = "";
        for (int i = 0; i < min(15, passwordText.size()); ++i) encodePassword += "*";
        if (passwordText == "password") encodePassword = passwordText;
        if (encodePassword.size() > 0) {
            passwordTextTexture.setText(encodePassword);
            passwordTextTexture.loadFromRenderText(fontGame, gScreen);
            passwordTextTexture.showText(gScreen, passwordTextTexture.getPosX(), passwordTextTexture.getPosY());
        }
        else {
            gInputTextTexture->setPosX(boardRegister.getRect().x + 85);
            gInputTextTexture->setWidth(0);
        }

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
    soundOnButton->setXPos(boardSettings.getRect().x + 235);
    soundOnButton->setYPos(boardSettings.getRect().y + 148);
    soundOnButton->setRectPos(soundOnButton->getXPos(), soundOnButton->getYPos());

    ButtonObject* soundOffButton = new ButtonObject;
    soundOffButton->loadImage("img//settingsBoard//settingsBoard_OffButton.png", gScreen);
    soundOffButton->setXPos(boardSettings.getRect().x + 235);
    soundOffButton->setYPos(boardSettings.getRect().y + 148);
    soundOffButton->setRectPos(soundOffButton->getXPos(), soundOffButton->getYPos());

    ButtonObject* saveButton = new ButtonObject;
    saveButton->loadImage("img//settingsBoard//settingsBoard_SaveButton.png", gScreen);
    saveButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    saveButton->setYPos(boardSettings.getRect().y + 210);
    saveButton->setRectPos(saveButton->getXPos(), saveButton->getYPos());

    ButtonObject* restoreButton = new ButtonObject;
    restoreButton->loadImage("img//settingsBoard//settingsBoard_RestoreButton.png", gScreen);
    restoreButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    restoreButton->setYPos(saveButton->getRect().y + saveButton->getRect().h + 20);
    restoreButton->setRectPos(restoreButton->getXPos(), restoreButton->getYPos());

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//settingsBoard//settingsBoard_BackButton.png", gScreen);

    backButton->setXPos((SCREEN_WIDTH - saveButton->getRect().w) / 2);
    backButton->setYPos(restoreButton->getRect().y + restoreButton->getRect().h + 20);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());

    ButtonObject* exitButton = new ButtonObject;
    exitButton->loadImage("img//settingsBoard//settingsBoard_exitButton.png", gScreen);
    exitButton->setXPos(boardSettings.getRect().x + boardSettings.getRect().w - exitButton->getRect().w);
    exitButton->setYPos(boardSettings.getRect().y);
    exitButton->setRectPos(exitButton->getXPos(), exitButton->getYPos());

    SDL_RenderPresent(gScreen);
    bool quit = false;
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
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN 
                    && (selectBackButton || selectExitButton))) {
                quit = true;
                display = typeDisplay::RE_MENU;
                backGround.cleanUp();
                boardSettings.cleanUp();
                soundOnButton->cleanUp();
                soundOffButton->cleanUp();
                saveButton->cleanUp();
                restoreButton->cleanUp();
                backButton->cleanUp();
                exitButton->cleanUp();
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
                    quit = true;
                    display = typeDisplay::RE_MENU;
                    return;
                }
            }
        }

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        backGround.render(gScreen);
        boardSettings.render(gScreen);
        if (setSound == true)
            soundOnButton->render(gScreen);
        else
            soundOffButton->render(gScreen);
        saveButton->render(gScreen);
        restoreButton->render(gScreen);
        backButton->render(gScreen);
        exitButton->render(gScreen);
        SDL_RenderPresent(gScreen);
    }
}

void BounceBall::displayHowToPlayButton() {
    BaseObject backGround;
    backGround.loadImage("img//background//background.jpg", gScreen);
    backGround.render(gScreen);

    BaseObject howToPlay;
    howToPlay.loadImage("img//HowToPlay//HowToPlay.png", gScreen);
    howToPlay.setRectPos((SCREEN_WIDTH - howToPlay.getRect().w) / 2,
        (SCREEN_HEIGHT - howToPlay.getRect().h) / 2);
    howToPlay.render(gScreen);

    ButtonObject* backButton = new ButtonObject;
    backButton->loadImage("img//button//back_button.png", gScreen);

    backButton->setXPos(0);
    backButton->setYPos(SCREEN_HEIGHT - backButton->getRect().h);
    backButton->setRectPos(backButton->getXPos(), backButton->getYPos());
    backButton->render(gScreen);

    ButtonObject* playButton = new ButtonObject;
    playButton->loadImage("img//button//menu_button_play.png", gScreen);
    playButton->setRectSize(192, 64);
    playButton->setRectPos(SCREEN_WIDTH - playButton->getRect().w, SCREEN_HEIGHT - playButton->getRect().h);
    playButton->render(gScreen);

    SDL_RenderPresent(gScreen);

    MouseEvents mouse;

    bool quit = 0;
    while (!quit) {
        mouse.mouseHandleEvent();
        bool clickBackButton = bool(mouse.checkMouseInButton(backButton));
        bool clickPlayButton = bool(mouse.checkMouseInButton(playButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN)) {
                if (clickBackButton) {
                    quit = true;
                    display = typeDisplay::RE_MENU;
                    backGround.cleanUp();
                    howToPlay.cleanUp();
                    backButton->cleanUp();
                    playButton->cleanUp();
                    return;
                }
                if (clickPlayButton) {
                    display = typeDisplay::PLAY;
                    if (infoPlayer->getUsername() == "") display = typeDisplay::LOGIN;
                    backGround.cleanUp();
                    howToPlay.cleanUp();
                    backButton->cleanUp();
                    playButton->cleanUp();
                    return;
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
        case typeDisplay::LOGIN:
            displayLogin();
            break;
        }
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