#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../Header/CommonFunc.h"
#include "../Header/BaseObject.h"
#include "../Header/GameMap.h"
#include "../Header/MainObject.h"
#include "../Header/FPS.h"
#include "../Header/GameComponents.h"
#include "../Header/LevelGame.h"
#include "../Header/Utils.h"
#include "../Header/Management.h"
#include "../Header/BounceBall.h"
#include "../Header/Cryptosystem.h"

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

    BaseObject background;
    background.loadImage("Resources/Image/background/background.jpg", gScreen);
    background.render(gScreen);

    const int LOGO_OBJECT_WIDTH = 210;
    const int LOGO_OBJECT_HEIGHT = 159;
    const int LOGO_OBJECT_Y_POS = 5;
    
    BaseObject logo;
    logo.loadImage("Resources/Image/logo/logo_small.png", gScreen);
    logo.setRectSize(LOGO_OBJECT_WIDTH, LOGO_OBJECT_HEIGHT);
    logo.setRectPos((SCREEN_WIDTH - logo.getRect().w) / 2, LOGO_OBJECT_Y_POS);
    logo.render(gScreen);

    const int BACK_MID = 32;
    const int FIRST_HEIGH_Y = 175;
    const int DISTANCE_BUTTONS_Y = 100;

    ButtonObject playButton;
    playButton.loadImage("Resources/Image/button/menu_button_play.png", gScreen);
    playButton.setRectPos(MID_POS_WIDTH - playButton.getRect().w - BACK_MID, FIRST_HEIGH_Y);
    playButton.render(gScreen);

    ButtonObject playButtonClick;
    playButtonClick.loadImage("Resources/Image/button/menu_button_play_click.png", gScreen);
    playButtonClick.setRectPos(MID_POS_WIDTH - playButtonClick.getRect().w - BACK_MID, FIRST_HEIGH_Y);

    ButtonObject leaderboardButton;
    leaderboardButton.loadImage("Resources/Image/button/menu_button_leaderboard.png", gScreen);
    leaderboardButton.setRectPos(MID_POS_WIDTH + BACK_MID, FIRST_HEIGH_Y);
    leaderboardButton.render(gScreen);

    ButtonObject leaderboardButtonClick;
    leaderboardButtonClick.loadImage("Resources/Image/button/menu_button_leaderboard_click.png", gScreen);
    leaderboardButtonClick.setRectPos(MID_POS_WIDTH + BACK_MID, FIRST_HEIGH_Y);

    ButtonObject howToPlayButton;
    howToPlayButton.loadImage("Resources/Image/button/menu_button_howtoplay.png", gScreen);
    howToPlayButton.setRectPos(MID_POS_WIDTH - howToPlayButton.getRect().w - BACK_MID, 
                                playButton.getYPos() + DISTANCE_BUTTONS_Y);
    howToPlayButton.render(gScreen);

    ButtonObject howToPlayButtonClick;
    howToPlayButtonClick.loadImage("Resources/Image/button/menu_button_howtoplay_click.png", gScreen);
    howToPlayButtonClick.setRectPos(MID_POS_WIDTH - howToPlayButtonClick.getRect().w - BACK_MID,
        playButton.getYPos() + DISTANCE_BUTTONS_Y);

    ButtonObject settingsButton;
    settingsButton.loadImage("Resources/Image/button/menu_button_settings.png", gScreen);
    settingsButton.setRectPos(MID_POS_WIDTH + BACK_MID, 
                                leaderboardButton.getYPos() + DISTANCE_BUTTONS_Y);
    settingsButton.render(gScreen);

    ButtonObject settingsButtonClick;
    settingsButtonClick.loadImage("Resources/Image/button/menu_button_settings_click.png", gScreen);
    settingsButtonClick.setRectPos(MID_POS_WIDTH + BACK_MID,
        leaderboardButton.getYPos() + DISTANCE_BUTTONS_Y);

    ButtonObject registerButton;
    registerButton.loadImage("Resources/Image/button/menu_button_register.png", gScreen);
    registerButton.setRectPos(MID_POS_WIDTH + BACK_MID, settingsButton.getYPos() + DISTANCE_BUTTONS_Y);
    registerButton.render(gScreen);

    ButtonObject registerButtonClick;
    registerButtonClick.loadImage("Resources/Image/button/menu_button_register_click.png", gScreen);
    registerButtonClick.setRectPos(MID_POS_WIDTH + BACK_MID, 
                        settingsButton.getYPos() + DISTANCE_BUTTONS_Y);

    ButtonObject loginButton;
    loginButton.loadImage("Resources/Image/button/menu_button_login.png", gScreen);
    loginButton.setRectPos(MID_POS_WIDTH - playButton.getRect().w - BACK_MID,
        howToPlayButton.getYPos() + DISTANCE_BUTTONS_Y);

    ButtonObject loginButtonClick;
    loginButtonClick.loadImage("Resources/Image/button/menu_button_login_click.png", gScreen);
    loginButtonClick.setRectPos(MID_POS_WIDTH - playButton.getRect().w - BACK_MID,
        howToPlayButton.getYPos() + DISTANCE_BUTTONS_Y);

    ButtonObject logoutButton;
    logoutButton.loadImage("Resources/Image/button/menu_button_logout.png", gScreen);
    logoutButton.setRectPos(MID_POS_WIDTH - playButton.getRect().w - BACK_MID, 
                            howToPlayButton.getYPos() + DISTANCE_BUTTONS_Y);

    ButtonObject logoutButtonClick;
    logoutButtonClick.loadImage("Resources/Image/button/menu_button_logout_click.png", gScreen);
    logoutButtonClick.setRectPos(MID_POS_WIDTH - playButton.getRect().w - BACK_MID,
        howToPlayButton.getYPos() + DISTANCE_BUTTONS_Y);

    SDL_RenderPresent(gScreen);

    bool quit = false;
    MouseEvents mouse;

    display = typeDisplay::MENU;

    FPS fpsTimer;
    
    while (!quit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool clickPlayButton = bool(mouse.checkMouseInButton(&playButton));
        bool clickLeaderboardButton = bool(mouse.checkMouseInButton(&leaderboardButton));
        bool clickLoginButton = bool(mouse.checkMouseInButton(&loginButton));
        bool clickLogoutButton = bool(mouse.checkMouseInButton(&logoutButton));
        bool clickLogoutButtonClick = bool(mouse.checkMouseInButton(&logoutButtonClick));
        bool clickHowToPlayButton = bool(mouse.checkMouseInButton(&howToPlayButton));
        bool clickSettingsButton = bool(mouse.checkMouseInButton(&settingsButton));
        bool clickRegisterButton = bool(mouse.checkMouseInButton(&registerButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) {
                quit = true;
                exit(0);
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
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
                if (clickLogoutButton && infoPlayer->getUsername() != "") {
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

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        background.render(gScreen);
        logo.render(gScreen);
        if (clickPlayButton == false) playButton.render(gScreen);
        else playButtonClick.render(gScreen);

        if (clickLeaderboardButton == false) leaderboardButton.render(gScreen);
        else leaderboardButtonClick.render(gScreen);

        if (clickHowToPlayButton == false) howToPlayButton.render(gScreen);
        else howToPlayButtonClick.render(gScreen);

        if (clickSettingsButton == false) settingsButton.render(gScreen);
        else settingsButtonClick.render(gScreen);

        if (infoPlayer->getUsername() == "") {
            if (clickLoginButton == false) loginButton.render(gScreen);
            else loginButtonClick.render(gScreen);
        }
        else {
            if (clickLogoutButton == false) logoutButton.render(gScreen);
            else logoutButtonClick.render(gScreen);
        }
        if (clickRegisterButton == false) registerButton.render(gScreen);
        else registerButtonClick.render(gScreen);

        if (display != typeDisplay::MENU) {
            background.cleanUp();
            logo.cleanUp();
            playButton.cleanUp();
            playButtonClick.cleanUp();
            leaderboardButton.cleanUp();
            leaderboardButtonClick.cleanUp();
            howToPlayButton.cleanUp();
            howToPlayButtonClick.cleanUp();
            loginButton.cleanUp();
            loginButtonClick.cleanUp();
            logoutButton.cleanUp();
            logoutButtonClick.cleanUp();
            settingsButton.cleanUp();
            settingsButtonClick.cleanUp();
            registerButton.cleanUp();
            registerButtonClick.cleanUp();
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
            case typeDisplay::HOW_TO_PLAY:
                displayHowToPlayButton();
                break;
        }

        SDL_RenderPresent(gScreen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = MS_ONE_SECOND / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
    cleanUp();
}

void BounceBall::displayLogo() {
    BaseObject background;
    background.loadImage("Resources/Image/background/background.jpg", gScreen);
    background.render(gScreen);
    
    BaseObject logo; 
    logo.loadImage("Resources/Image/logo/logo.png", gScreen);
    logo.setRectSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    logo.render(gScreen);
    
    SDL_RenderPresent(gScreen);
    SDL_Delay(MS_ONE_SECOND);

    background.cleanUp();
    logo.cleanUp();
}

void BounceBall::displayPlay() {
    MouseEvents mouse;
    BaseObject background;
    background.loadImage("Resources/Image/background/background.jpg", gScreen);

    LTexture LevelText;
    int level = 0;

    const int LOGO_OBJECT_WIDTH = 192;
    const int LOGO_OBJECT_HEIGHT = 145;
    const int LOGO_OBJECT_Y_POS = 5;

    BaseObject logo;
    logo.loadImage("Resources/Image/logo/logo_small.png", gScreen);
    logo.setRectSize(LOGO_OBJECT_WIDTH, LOGO_OBJECT_HEIGHT);
    logo.setRectPos((SCREEN_WIDTH - logo.getRect().w) / 2, LOGO_OBJECT_Y_POS);
    logo.render(gScreen);

    ButtonObject backButton;
    backButton.loadImage("Resources/Image/button/back_button.png", gScreen);
    backButton.setXPos(0);
    backButton.setYPos(SCREEN_HEIGHT - backButton.getRect().h);
    backButton.setRectPos(backButton.getXPos(), backButton.getYPos());
    backButton.render(gScreen);

    ButtonObject backButtonClick;
    backButtonClick.loadImage("Resources/Image/button/back_button_click.png", gScreen);
    backButtonClick.setXPos(0);
    backButtonClick.setYPos(SCREEN_HEIGHT - backButtonClick.getRect().h);
    backButtonClick.setRectPos(backButtonClick.getXPos(), backButtonClick.getYPos());

    FPS fpsTimer;
    bool quit = false;
    while (!quit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool selectBackButton = bool(mouse.checkMouseInButton(&backButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                SDL_RenderPresent(gScreen);
                break;
            }
            int level = 0;
            for (int i = 1; i <= MAX_ROW_SHOW; ++i) {
                for (int j = 1; j <= MAX_COL_SHOW; ++j) {
                    if (selectLevelButton[i][j].getIsUnlock() == lockType::LOCK) continue;
                    mouse.mouseHandleEvent();
                    bool clickLevelButton = bool(mouse.checkMouseInButton(&selectLevelButton[i][j]));
                    ++level;
                    if (gEvent.type == SDL_MOUSEBUTTONDOWN && clickLevelButton) {
                        infoPlayer->setlife(ORIGINAL_LIFE);
                        infoPlayer->setLevel(level);
                        infoPlayer->setSound(sound);
                        Cryptosystem addressLevel;
                        string address = "Resources/Map/level";
                        if (level <= MAX_ONE_DIGIT) address += "0";
                        address += addressLevel.convertNumberToString(level);
                        address += ".map";
                        LevelGame levelGame;
                        int nextAction = levelGame.loadLevelGame(address.c_str(), gScreen, 
                                                                    gEvent, infoPlayer);
                        while (nextAction == levelType::NEXT_LEVEL && level < MAX_LEVEL) {
                            ++level;
                            infoPlayer->setUnlockLevel(level, lockType::UNLOCK);
                            infoPlayer->setSound(sound);
                            databaseGame.updateDatabaseUsername(*infoPlayer);
                            databaseGame.exportDatabase();  
                            address = "Resources/Map/level";
                            if (level <= MAX_ONE_DIGIT) address += "0";
                            address += addressLevel.convertNumberToString(level);
                            address += ".map";
                            nextAction = levelGame.loadLevelGame(address.c_str(), gScreen, gEvent, infoPlayer);
                        }
                        infoPlayer->setUnlockLevel(level, lockType::UNLOCK);
                        infoPlayer->setSound(sound);
                        databaseGame.updateDatabaseUsername(*infoPlayer);
                        databaseGame.exportDatabase();
                        display = typeDisplay::RE_MENU;
                        if (level == MAX_LEVEL && nextAction == levelType::NEXT_LEVEL) {
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                "Bounce Ball",
                                "Congratulations! You've completed all the levels",
                                NULL);
                        }
                        quit = true;
                        break;
                    }
                }
            }
        }
        if (quit == true) break;

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        background.render(gScreen);
        logo.render(gScreen);
        if (selectBackButton == false) backButton.render(gScreen);
        else backButtonClick.render(gScreen);

        const int UPPER_BOUNDARY = 100;
        level = 0;
        for (int i = 1; i <= MAX_ROW_SHOW; ++i) {
            for (int j = 1; j <= MAX_COL_SHOW; ++j) {
                ++level;
                if (infoPlayer->getUnlockLevel(level)) {
                    selectLevelButton[i][j].loadImage("Resources/Image/level/select_level.png", gScreen);
                    selectLevelButton[i][j].setIsUnlock(true);
                }
                else {
                    selectLevelButton[i][j].loadImage("Resources/Image/level/select_level_locked.png", gScreen);
                    selectLevelButton[i][j].setIsUnlock(false);
                }
                selectLevelButton[i][j].setRectPos(TILE_SIZE * j, UPPER_BOUNDARY + TILE_SIZE * i);
                selectLevelButton[i][j].render(gScreen);
                std::string strLevel = "";
                if (level <= MAX_ONE_DIGIT) strLevel += "0";
                strLevel += std::to_string(level);
                bool clickLevelButton = bool(mouse.checkMouseInButton(&selectLevelButton[i][j]));
                LevelText.setText(strLevel);
                if (clickLevelButton == false) LevelText.setColor(LTexture::COLOR::WHITE_COLOR);
                else LevelText.setColor(LTexture::COLOR::YELLOW_COLOR);
                LevelText.loadFromRenderText(fontGame, gScreen);
                LevelText.showText(gScreen, TILE_SIZE * j +
                    (selectLevelButton[i][j].getWidth() - LevelText.getWidth()) / 2,
                    UPPER_BOUNDARY + TILE_SIZE * i
                    + (selectLevelButton[i][j].getHeight() - LevelText.getHeight()) / 2);
            }
        }

        SDL_RenderPresent(gScreen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = MS_ONE_SECOND / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
    
    background.cleanUp();
    logo.cleanUp();
    backButton.cleanUp();
    for (int i = 1; i <= MAX_ROW_SHOW; ++i)
        for (int j = 1; j <= MAX_COL_SHOW; ++j)
            selectLevelButton[i][j].cleanUp();
    LevelText.cleanUp();
}

void BounceBall::displayLeaderboard() {
    MouseEvents mouse;
    BaseObject background;
    background.loadImage("Resources/Image/background/background.jpg", gScreen);

    const int LEADERBOARD_OBJECT_WIDTH = 612;
    const int LEADERBOARD_OBJECT_HEIGHT = 512;

    BaseObject leaderboard;
    leaderboard.loadImage("Resources/Image/leaderboard/leaderboard.png", gScreen);
    leaderboard.setRectSize(LEADERBOARD_OBJECT_WIDTH, LEADERBOARD_OBJECT_HEIGHT);
    leaderboard.setRectPos((SCREEN_WIDTH - leaderboard.getRect().w) / 2,
        (SCREEN_HEIGHT - leaderboard.getRect().h) / 2);
    
    ButtonObject backButton;
    backButton.loadImage("Resources/Image/button/back_button.png", gScreen);
    backButton.setXPos(0);
    backButton.setYPos(SCREEN_HEIGHT - backButton.getRect().h);
    backButton.setRectPos(backButton.getXPos(), backButton.getYPos());
    backButton.render(gScreen);

    ButtonObject backButtonClick;
    backButtonClick.loadImage("Resources/Image/button/back_button_click.png", gScreen);
    backButtonClick.setXPos(0);
    backButtonClick.setYPos(SCREEN_HEIGHT - backButtonClick.getRect().h);
    backButtonClick.setRectPos(backButtonClick.getXPos(), backButtonClick.getYPos());

    databaseGame.sortAllDataInfoPlayer();
    vector <InfoPlayer> dataInfoPlayer = databaseGame.getDataInfoPlayer();
    LTexture usernameText;
    LTexture yourHighScoreText;
    FPS fpsTimer;
    bool quit = false;
    while (!quit) {
        fpsTimer.start();            
        mouse.mouseHandleEvent();
        bool selectBackButton = bool(mouse.checkMouseInButton(&backButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                SDL_RenderPresent(gScreen);
                break;
            }
        }
        if (quit == true) break;
        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        background.render(gScreen);
        leaderboard.render(gScreen);

        if (selectBackButton == false) backButton.render(gScreen);
        else backButtonClick.render(gScreen);

        const int LEFT_MARGIN_OBJECT = 150;
        const int TOP_MARGIN_OBJECT = 168;
        const int OFFSET_RIGHT = 95;
        const int DISTANCE_FLOORS = 64;

        int xPosUsername = leaderboard.getRect().x + LEFT_MARGIN_OBJECT;
        int yPosUsername = leaderboard.getRect().y + TOP_MARGIN_OBJECT;

        int xPosYourHighScore = leaderboard.getRect().x + leaderboard.getRect().w - OFFSET_RIGHT;
        int yPosYourHighScore = leaderboard.getRect().y + TOP_MARGIN_OBJECT;

        for (int i = 0; i < MAX_SHOW_LEADERBOARD; ++i) {
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
            yPosUsername += DISTANCE_FLOORS;
            yPosYourHighScore += DISTANCE_FLOORS;
        }
        SDL_RenderPresent(gScreen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = MS_ONE_SECOND / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
    background.cleanUp();
    leaderboard.cleanUp();
    backButton.cleanUp();
    usernameText.cleanUp();
    yourHighScoreText.cleanUp();
}

bool BounceBall::checkInfoLogin(string usernameText, string passwordText, InfoPlayer *infoPlayer) {
    for (int i = 0; i < usernameText.size(); ++i)
        if (usernameText[i] >= 'a' && usernameText[i] <= 'z')
            usernameText[i] -= DISTANCE_UPPERCASE_VS_LOWERCASE;

    for (int i = 0; i < passwordText.size(); ++i)
        if (passwordText[i] >= 'a' && passwordText[i] <= 'z')
            passwordText[i] -= DISTANCE_UPPERCASE_VS_LOWERCASE;
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
    BaseObject background;
    background.loadImage("Resources/Image/background/background.jpg", gScreen);
    background.render(gScreen);

    BaseObject boardLogin;
    boardLogin.loadImage("Resources/Image/board/boardLogin.png", gScreen);
    boardLogin.setRectPos((SCREEN_WIDTH - boardLogin.getRect().w) / 2,
        (SCREEN_HEIGHT - boardLogin.getRect().h) / 2);
    boardLogin.render(gScreen);

    const int REGISTER_BUTTON_WIDTH = 175;
    const int REGISTER_BUTTON_HEIGHT = 64;

    ButtonObject registerButton;
    registerButton.loadImage("Resources/Image/button/menu_button_register.png", gScreen);
    registerButton.setRectSize(REGISTER_BUTTON_WIDTH, REGISTER_BUTTON_HEIGHT);
    registerButton.setRectPos(SCREEN_WIDTH - registerButton.getRect().w, 
                                SCREEN_HEIGHT - registerButton.getRect().h);

    ButtonObject registerButtonClick;
    registerButtonClick.loadImage("Resources/Image/button/menu_button_register_click.png", gScreen);
    registerButtonClick.setRectSize(REGISTER_BUTTON_WIDTH, REGISTER_BUTTON_HEIGHT);
    registerButtonClick.setRectPos(SCREEN_WIDTH - registerButton.getRect().w,
        SCREEN_HEIGHT - registerButton.getRect().h);

    const int TOP_MARGIN_OBJECT = 150;
    const int DISTANCE_BUTTONS_Y = 100;

    ButtonObject usernameButton;
    usernameButton.loadImage("Resources/Image/button/login_button_username.png", gScreen);
    usernameButton.setXPos((SCREEN_WIDTH - usernameButton.getWidth()) / 2);
    usernameButton.setYPos(TOP_MARGIN_OBJECT);
    usernameButton.setRectPos(usernameButton.getXPos(), usernameButton.getYPos());
    usernameButton.render(gScreen);

    ButtonObject passwordButton;
    passwordButton.loadImage("Resources/Image/button/login_button_password.png", gScreen);
    passwordButton.setXPos((SCREEN_WIDTH - passwordButton.getWidth()) / 2);
    passwordButton.setYPos(usernameButton.getYPos() + DISTANCE_BUTTONS_Y);
    passwordButton.setRectPos(passwordButton.getXPos(), passwordButton.getYPos());
    passwordButton.render(gScreen); 

    ButtonObject loginButton;
    loginButton.loadImage("Resources/Image/button/login_button_login.png", gScreen);
    loginButton.setXPos((SCREEN_WIDTH - loginButton.getWidth()) / 2);
    loginButton.setYPos(passwordButton.getYPos() + DISTANCE_BUTTONS_Y);
    loginButton.setRectPos(loginButton.getXPos(), loginButton.getYPos());
    loginButton.render(gScreen);

    ButtonObject loginButtonClick;
    loginButtonClick.loadImage("Resources/Image/button/login_button_login_click.png", gScreen);
    loginButtonClick.setXPos((SCREEN_WIDTH - loginButtonClick.getWidth()) / 2);
    loginButtonClick.setYPos(passwordButton.getYPos() + DISTANCE_BUTTONS_Y);
    loginButtonClick.setRectPos(loginButton.getXPos(), loginButton.getYPos());

    ButtonObject backButton;
    backButton.loadImage("Resources/Image/button/back_button.png", gScreen);
    backButton.setXPos(0);
    backButton.setYPos(SCREEN_HEIGHT - backButton.getRect().h);
    backButton.setRectPos(backButton.getXPos(), backButton.getYPos());
    backButton.render(gScreen);

    ButtonObject backButtonClick;
    backButtonClick.loadImage("Resources/Image/button/back_button_click.png", gScreen);
    backButtonClick.setXPos(0);
    backButtonClick.setYPos(SCREEN_HEIGHT - backButtonClick.getRect().h);
    backButtonClick.setRectPos(backButtonClick.getXPos(), backButtonClick.getYPos());

    SDL_RenderPresent(gScreen);

    LTexture* gInputTextTexture = nullptr;
    
    const int LTEXTURE_VS_BUTTON_X = 20;
    const int LTEXTURE_VS_BUTTON_Y = 15;

    LTexture usernameTextTexture;
    usernameTextTexture.setPosX(usernameButton.getXPos() + LTEXTURE_VS_BUTTON_X);
    usernameTextTexture.setPosY(usernameButton.getYPos() + LTEXTURE_VS_BUTTON_Y);

    LTexture passwordTextTexture;
    passwordTextTexture.setPosX(passwordButton.getXPos() + LTEXTURE_VS_BUTTON_X);
    passwordTextTexture.setPosY(passwordButton.getYPos() + LTEXTURE_VS_BUTTON_Y);

    string usernameText = "username"; 
    string passwordText = "password";    
    //string usernameText = "buiminhhoat"; 
    //string passwordText = "buiminhhoat";

    gInputTextTexture = &usernameTextTexture;

    BaseObject iteratorMouse;
    iteratorMouse.loadImage("Resources/Image/button/iteratorMouse.png", gScreen);
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
        bool selectUsernameButton = bool(mouse.checkMouseInButton(&usernameButton));
        bool selectPasswordButton = bool(mouse.checkMouseInButton(&passwordButton));
        bool selectLoginButton = bool(mouse.checkMouseInButton(&loginButton));
        bool selectBackButton = bool(mouse.checkMouseInButton(&backButton));
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
                        quit = true;
                        break;
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
                    break;
                }
                if (selectRegisterButton) {
                    quit = true;
                    display = typeDisplay::REGISTER;
                    break;
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

            if (gEvent.type == SDL_KEYDOWN) {
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
                        quit = true;
                        break;
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

        if (quit == true) break;

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, 
                                        RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        background.render(gScreen);
        boardLogin.render(gScreen);
        usernameButton.render(gScreen);
        passwordButton.render(gScreen);
        if (selectLoginButton == false) loginButton.render(gScreen);
        else loginButtonClick.render(gScreen);
        if (selectBackButton == false) backButton.render(gScreen);
        else backButtonClick.render(gScreen);
        if (selectRegisterButton == false) registerButton.render(gScreen);
        else registerButtonClick.render(gScreen);
    
        if (usernameText == "" && deletedAccount == false) usernameText = "username";
        if (passwordText == "" && deletedPassword == false) passwordText = "password";
        string showUsername = "";
        const int LTEXTURE_VS_BOARDLOGIN_X = 85;
        for (int i = max(0, (int) usernameText.size() - MAX_SIZE_SHOW_INFO); 
                        i < usernameText.size(); ++i) {
            showUsername += usernameText[i];
        }
        if (showUsername.size() > 0) {
            usernameTextTexture.setText(showUsername);
            usernameTextTexture.loadFromRenderText(fontGame, gScreen);
            usernameTextTexture.showText(gScreen, usernameTextTexture.getPosX(), 
                                         usernameTextTexture.getPosY());
        }
        else {
            gInputTextTexture->setPosX(boardLogin.getRect().x + LTEXTURE_VS_BOARDLOGIN_X);
            gInputTextTexture->setWidth(0);
        }
        

        string encodePassword = "";
        for (int i = 0; i < min(MAX_SIZE_SHOW_INFO, passwordText.size()); ++i) encodePassword += "*";
        if (passwordText == "password") encodePassword = passwordText;
        if (encodePassword.size() > 0) {
            passwordTextTexture.setText(encodePassword);
            passwordTextTexture.loadFromRenderText(fontGame, gScreen);
            passwordTextTexture.showText(gScreen, passwordTextTexture.getPosX(), 
                                            passwordTextTexture.getPosY());
        }
        else {
            gInputTextTexture->setPosX(boardLogin.getRect().x + LTEXTURE_VS_BOARDLOGIN_X);
            gInputTextTexture->setWidth(0);
        }

        const int LTEXTURE_VS_ITERATORMOUSE_X = 2;
        const int LTEXTURE_VS_ITERATORMOUSE_Y = 4;
        iteratorMouse.setRectPos(gInputTextTexture->getPosX()
                                + gInputTextTexture->getWidth() + LTEXTURE_VS_ITERATORMOUSE_X,
                                    gInputTextTexture->getPosY() + LTEXTURE_VS_ITERATORMOUSE_Y);
        
        const int TIME_START_FLICKERTIMER = 400;
        const int TIME_END_FLICKERTIMER = 800;
        if (flickerTimer.getTicks() >= TIME_START_FLICKERTIMER 
                && flickerTimer.getTicks() <= TIME_END_FLICKERTIMER) {
            iteratorMouse.render(gScreen);
        }
        if (flickerTimer.getTicks() > TIME_END_FLICKERTIMER) flickerTimer.start();

        SDL_RenderPresent(gScreen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = MS_ONE_SECOND / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }

    background.cleanUp();
    boardLogin.cleanUp();
    registerButton.cleanUp();
    registerButtonClick.cleanUp();
    usernameButton.cleanUp();
    passwordButton.cleanUp();
    loginButton.cleanUp();
    loginButtonClick.cleanUp();
    backButton.cleanUp();
    backButtonClick.cleanUp();
    gInputTextTexture->cleanUp();
    usernameTextTexture.cleanUp();
    passwordTextTexture.cleanUp();
    iteratorMouse.cleanUp();
}

void BounceBall::displayLogout() {
    infoPlayer->setUsername("");
    display = typeDisplay::RE_MENU;
}

bool BounceBall::notificationStatusRegister(string usernameText, string passwordText) {
    for (int i = 0; i < usernameText.size(); ++i)
        if (usernameText[i] >= 'a' && usernameText[i] <= 'z')
            usernameText[i] -= DISTANCE_UPPERCASE_VS_LOWERCASE;

    for (int i = 0; i < passwordText.size(); ++i)
        if (passwordText[i] >= 'a' && passwordText[i] <= 'z')
            passwordText[i] -= DISTANCE_UPPERCASE_VS_LOWERCASE;

    InfoPlayer infoRegister;
    infoRegister.setUsername(usernameText);
    infoRegister.setPassword(passwordText);
    infoRegister.setYourHighScore(0);
    infoRegister.setUnlockLevel(1, lockType::UNLOCK);
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
    BaseObject background;
    background.loadImage("Resources/Image/background/background.jpg", gScreen);
    background.render(gScreen);

    BaseObject boardRegister;
    boardRegister.loadImage("Resources/Image/board/boardRegister.png", gScreen);
    boardRegister.setRectPos((SCREEN_WIDTH - boardRegister.getRect().w) / 2,
        (SCREEN_HEIGHT - boardRegister.getRect().h) / 2);
    boardRegister.render(gScreen);

    const int TOP_MARGIN_OBJECT = 150;
    const int DISTANCE_BUTTONS_Y = 100;

    ButtonObject usernameButton;
    usernameButton.loadImage("Resources/Image/button/register_button_username.png", gScreen);
    usernameButton.setXPos((SCREEN_WIDTH - usernameButton.getWidth()) / 2);
    usernameButton.setYPos(TOP_MARGIN_OBJECT);
    usernameButton.setRectPos(usernameButton.getXPos(), usernameButton.getYPos());
    usernameButton.render(gScreen);

    ButtonObject passwordButton;
    passwordButton.loadImage("Resources/Image/button/register_button_password.png", gScreen);
    passwordButton.setXPos((SCREEN_WIDTH - passwordButton.getWidth()) / 2);
    passwordButton.setYPos(usernameButton.getYPos() + DISTANCE_BUTTONS_Y);
    passwordButton.setRectPos(passwordButton.getXPos(), passwordButton.getYPos());
    passwordButton.render(gScreen);

    ButtonObject registerButton;
    registerButton.loadImage("Resources/Image/button/register_button_register.png", gScreen);
    registerButton.setXPos((SCREEN_WIDTH - registerButton.getWidth()) / 2);
    registerButton.setYPos(passwordButton.getYPos() + DISTANCE_BUTTONS_Y);
    registerButton.setRectPos(registerButton.getXPos(), registerButton.getYPos());
    registerButton.render(gScreen);

    ButtonObject registerButtonClick;
    registerButtonClick.loadImage("Resources/Image/button/register_button_register_click.png", gScreen);
    registerButtonClick.setXPos((SCREEN_WIDTH - registerButtonClick.getWidth()) / 2);
    registerButtonClick.setYPos(passwordButton.getYPos() + DISTANCE_BUTTONS_Y);
    registerButtonClick.setRectPos(registerButtonClick.getXPos(), registerButtonClick.getYPos());

    ButtonObject backButton;
    backButton.loadImage("Resources/Image/button/back_button.png", gScreen);
    backButton.setXPos(0);
    backButton.setYPos(SCREEN_HEIGHT - backButton.getRect().h);
    backButton.setRectPos(backButton.getXPos(), backButton.getYPos());
    backButton.render(gScreen);

    ButtonObject backButtonClick;
    backButtonClick.loadImage("Resources/Image/button/back_button_click.png", gScreen);
    backButtonClick.setXPos(0);
    backButtonClick.setYPos(SCREEN_HEIGHT - backButtonClick.getRect().h);
    backButtonClick.setRectPos(backButtonClick.getXPos(), backButtonClick.getYPos());

    const int LOGIN_BUTTON_WIDTH = 175;
    const int LOGIN_BUTTON_HEIGHT = 64;

    ButtonObject loginButton;
    if (infoPlayer->getUsername() == "") {
        loginButton.loadImage("Resources/Image/button/menu_button_login.png", gScreen);
        loginButton.setRectSize(LOGIN_BUTTON_WIDTH, LOGIN_BUTTON_HEIGHT);
        loginButton.setRectPos(SCREEN_WIDTH - loginButton.getRect().w,
                        SCREEN_HEIGHT - loginButton.getRect().h);
        loginButton.render(gScreen);
    }

    ButtonObject loginButtonClick;
    loginButtonClick.loadImage("Resources/Image/button/menu_button_login_click.png", gScreen);
    loginButtonClick.setRectSize(LOGIN_BUTTON_WIDTH, LOGIN_BUTTON_HEIGHT);
    loginButtonClick.setRectPos(SCREEN_WIDTH - loginButtonClick.getRect().w,
        SCREEN_HEIGHT - loginButtonClick.getRect().h);

    SDL_RenderPresent(gScreen);

    LTexture* gInputTextTexture = nullptr;

    const int LTEXTURE_VS_BUTTON_X = 20;
    const int LTEXTURE_VS_BUTTON_Y = 15;

    LTexture usernameTextTexture;
    usernameTextTexture.setPosX(usernameButton.getXPos() + LTEXTURE_VS_BUTTON_X);
    usernameTextTexture.setPosY(usernameButton.getYPos() + LTEXTURE_VS_BUTTON_Y);
    usernameTextTexture.setColor(LTexture::COLOR::PURPLE_COLOR);

    LTexture passwordTextTexture;
    passwordTextTexture.setPosX(passwordButton.getXPos() + LTEXTURE_VS_BUTTON_X);
    passwordTextTexture.setPosY(passwordButton.getYPos() + LTEXTURE_VS_BUTTON_Y);
    passwordTextTexture.setColor(LTexture::COLOR::PURPLE_COLOR);

    string usernameText = "username"; 
    string passwordText = "password";    
    //string usernameText = "buiminhhoat";
    //string passwordText = "buiminhhoat";

    gInputTextTexture = &usernameTextTexture;

    BaseObject iteratorMouse;
    iteratorMouse.loadImage("Resources/Image/button/iteratorMouse.png", gScreen);
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

    MouseEvents mouse;
    while (!quit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool selectUsernameButton = bool(mouse.checkMouseInButton(&usernameButton));
        bool selectPasswordButton = bool(mouse.checkMouseInButton(&passwordButton));
        bool selectRegisterButton = bool(mouse.checkMouseInButton(&registerButton));
        bool selectBackButton = bool(mouse.checkMouseInButton(&backButton));
        bool selectLoginButton = bool(mouse.checkMouseInButton(&loginButton));
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN && selectBackButton)) {
                quit = true;
                display = typeDisplay::RE_MENU;
                break;
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (selectUsernameButton)
                    selectText = selectInput::ACCOUNT;
                if (selectPasswordButton)
                    selectText = selectInput::PASSWORD;
                if (selectRegisterButton) {
                    if (notificationStatusRegister(usernameText, passwordText) == true) {
                        quit = true;
                        display = typeDisplay::RE_MENU;
                        break;
                    }
                }
                if (selectLoginButton) {
                    quit = true;
                    display = typeDisplay::LOGIN;
                    break;
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

            if (gEvent.type == SDL_KEYDOWN) {
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
                        quit = true;
                        display = typeDisplay::RE_MENU;
                        break;
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

        if (quit == true) break;

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, 
                                    RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        background.render(gScreen);
        boardRegister.render(gScreen);
        usernameButton.render(gScreen);
        passwordButton.render(gScreen);
        if (selectLoginButton == false) loginButton.render(gScreen);
        else loginButtonClick.render(gScreen);
        if (selectBackButton == false) backButton.render(gScreen);
        else backButtonClick.render(gScreen);
        if (selectRegisterButton == false) registerButton.render(gScreen);
        else registerButtonClick.render(gScreen);

        if (usernameText == "" && deletedAccount == false) usernameText = "username";
        if (passwordText == "" && deletedPassword == false) passwordText = "password";

        string showUsername = "";
        for (int i = max(0, (int) usernameText.size() - MAX_SIZE_SHOW_INFO); i < usernameText.size(); ++i) {
            showUsername += usernameText[i];
        }

        const int LTEXTURE_VS_BOARDREGISTER_X = 85;

        if (showUsername.size() > 0) {
            usernameTextTexture.setText(showUsername);
            usernameTextTexture.loadFromRenderText(fontGame, gScreen);
            usernameTextTexture.showText(gScreen, usernameTextTexture.getPosX(), 
                                            usernameTextTexture.getPosY());
        }
        else {
            gInputTextTexture->setPosX(boardRegister.getRect().x + LTEXTURE_VS_BOARDREGISTER_X);
            gInputTextTexture->setWidth(0);
        }

        string encodePassword = "";
        for (int i = 0; i < min(MAX_SIZE_SHOW_INFO, passwordText.size()); ++i) encodePassword += "*";
        if (passwordText == "password") encodePassword = passwordText;
        if (encodePassword.size() > 0) {
            passwordTextTexture.setText(encodePassword);
            passwordTextTexture.loadFromRenderText(fontGame, gScreen);
            passwordTextTexture.showText(gScreen, passwordTextTexture.getPosX(), 
                                            passwordTextTexture.getPosY());
        }
        else {
            gInputTextTexture->setPosX(boardRegister.getRect().x + LTEXTURE_VS_BOARDREGISTER_X);
            gInputTextTexture->setWidth(0);
        }

        const int LTEXTURE_VS_ITERATORMOUSE_X = 2;
        const int LTEXTURE_VS_ITERATORMOUSE_Y = 4;

        iteratorMouse.setRectPos(gInputTextTexture->getPosX()
            + gInputTextTexture->getWidth() + LTEXTURE_VS_ITERATORMOUSE_X,
            gInputTextTexture->getPosY() + LTEXTURE_VS_ITERATORMOUSE_Y);

        const int TIME_START_FLICKERTIMER = 400;
        const int TIME_END_FLICKERTIMER = 800;
        if (flickerTimer.getTicks() >= TIME_START_FLICKERTIMER 
                && flickerTimer.getTicks() <= TIME_END_FLICKERTIMER) {
            iteratorMouse.render(gScreen);
        }
        if (flickerTimer.getTicks() > TIME_END_FLICKERTIMER) flickerTimer.start();

        SDL_RenderPresent(gScreen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = MS_ONE_SECOND / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
    background.cleanUp();
    boardRegister.cleanUp();
    registerButton.cleanUp();
    registerButtonClick.cleanUp();
    usernameButton.cleanUp();
    passwordButton.cleanUp();
    loginButton.cleanUp();
    loginButtonClick.cleanUp();
    backButton.cleanUp();
    backButtonClick.cleanUp();
    gInputTextTexture->cleanUp();
    usernameTextTexture.cleanUp();
    passwordTextTexture.cleanUp();
    iteratorMouse.cleanUp();
}

void BounceBall::displaySettings() {
    BaseObject background;
    background.loadImage("Resources/Image/background/background.jpg", gScreen);

    BaseObject boardSettings;
    boardSettings.loadImage("Resources/Image/settingsBoard/settingsBoard.png", gScreen);
    boardSettings.setRectPos((SCREEN_WIDTH - boardSettings.getRect().w) / 2,
        (SCREEN_HEIGHT - boardSettings.getRect().h) / 2);

    const int BUTTON_VS_BOARDREGISTER_X = 235;
    const int BUTTON_VS_BOARDREGISTER_Y = 148;

    int setSound = sound;
    ButtonObject soundOnButton;
    soundOnButton.loadImage("Resources/Image/settingsBoard/settingsBoard_OnButton.png", gScreen);
    soundOnButton.setXPos(boardSettings.getRect().x + BUTTON_VS_BOARDREGISTER_X);
    soundOnButton.setYPos(boardSettings.getRect().y + BUTTON_VS_BOARDREGISTER_Y);
    soundOnButton.setRectPos(soundOnButton.getXPos(), soundOnButton.getYPos());

    ButtonObject soundOnButtonClick;
    soundOnButtonClick.loadImage("Resources/Image/settingsBoard/settingsBoard_OnButton_Click.png", gScreen);
    soundOnButtonClick.setXPos(boardSettings.getRect().x + BUTTON_VS_BOARDREGISTER_X);
    soundOnButtonClick.setYPos(boardSettings.getRect().y + BUTTON_VS_BOARDREGISTER_Y);
    soundOnButtonClick.setRectPos(soundOnButtonClick.getXPos(), soundOnButtonClick.getYPos());

    ButtonObject soundOffButton;
    soundOffButton.loadImage("Resources/Image/settingsBoard/settingsBoard_OffButton.png", gScreen);
    soundOffButton.setXPos(boardSettings.getRect().x + BUTTON_VS_BOARDREGISTER_X);
    soundOffButton.setYPos(boardSettings.getRect().y + BUTTON_VS_BOARDREGISTER_Y);
    soundOffButton.setRectPos(soundOffButton.getXPos(), soundOffButton.getYPos());

    ButtonObject soundOffButtonClick;
    soundOffButtonClick.loadImage("Resources/Image/settingsBoard/settingsBoard_OffButton_Click.png", gScreen);
    soundOffButtonClick.setXPos(boardSettings.getRect().x + BUTTON_VS_BOARDREGISTER_X);
    soundOffButtonClick.setYPos(boardSettings.getRect().y + BUTTON_VS_BOARDREGISTER_Y);
    soundOffButtonClick.setRectPos(soundOffButtonClick.getXPos(), soundOffButtonClick.getYPos());

    const int SAVEBUTTON_VS_BOARDREGISTER_Y = 210;
    ButtonObject saveButton;
    saveButton.loadImage("Resources/Image/settingsBoard/settingsBoard_SaveButton.png", gScreen);
    saveButton.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    saveButton.setYPos(boardSettings.getRect().y + SAVEBUTTON_VS_BOARDREGISTER_Y);
    saveButton.setRectPos(saveButton.getXPos(), saveButton.getYPos());

    ButtonObject saveButtonClick;
    saveButtonClick.loadImage("Resources/Image/settingsBoard/settingsBoard_SaveButton_Click.png", gScreen);
    saveButtonClick.setXPos((SCREEN_WIDTH - saveButtonClick.getRect().w) / 2);
    saveButtonClick.setYPos(boardSettings.getRect().y + SAVEBUTTON_VS_BOARDREGISTER_Y);
    saveButtonClick.setRectPos(saveButtonClick.getXPos(), saveButtonClick.getYPos());

    const int BUTTON_VS_BUTTON_Y = 20;

    ButtonObject restoreButton;
    restoreButton.loadImage("Resources/Image/settingsBoard/settingsBoard_RestoreButton.png", gScreen);
    restoreButton.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    restoreButton.setYPos(saveButton.getRect().y + saveButton.getRect().h + BUTTON_VS_BUTTON_Y);
    restoreButton.setRectPos(restoreButton.getXPos(), restoreButton.getYPos());

    ButtonObject restoreButtonClick;
    restoreButtonClick.loadImage("Resources/Image/settingsBoard/settingsBoard_RestoreButton_click.png", gScreen);
    restoreButtonClick.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    restoreButtonClick.setYPos(saveButton.getRect().y + saveButton.getRect().h + BUTTON_VS_BUTTON_Y);
    restoreButtonClick.setRectPos(restoreButtonClick.getXPos(), restoreButtonClick.getYPos());

    ButtonObject backButton;
    backButton.loadImage("Resources/Image/settingsBoard/settingsBoard_BackButton.png", gScreen);
    backButton.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    backButton.setYPos(restoreButton.getRect().y + restoreButton.getRect().h + BUTTON_VS_BUTTON_Y);
    backButton.setRectPos(backButton.getXPos(), backButton.getYPos());

    ButtonObject backButtonClick;
    backButtonClick.loadImage("Resources/Image/settingsBoard/settingsBoard_BackButton_click.png", gScreen);
    backButtonClick.setXPos((SCREEN_WIDTH - saveButton.getRect().w) / 2);
    backButtonClick.setYPos(restoreButton.getRect().y + restoreButton.getRect().h + BUTTON_VS_BUTTON_Y);
    backButtonClick.setRectPos(backButtonClick.getXPos(), backButtonClick.getYPos());

    ButtonObject exitButton;
    exitButton.loadImage("Resources/Image/settingsBoard/settingsBoard_exitButton.png", gScreen);
    exitButton.setXPos(boardSettings.getRect().x + boardSettings.getRect().w - exitButton.getRect().w);
    exitButton.setYPos(boardSettings.getRect().y);
    exitButton.setRectPos(exitButton.getXPos(), exitButton.getYPos());

    ButtonObject exitButtonClick;
    exitButtonClick.loadImage("Resources/Image/settingsBoard/settingsBoard_exitButton_Click.png", gScreen);
    exitButtonClick.setXPos(boardSettings.getRect().x + boardSettings.getRect().w - exitButtonClick.getRect().w);
    exitButtonClick.setYPos(boardSettings.getRect().y);
    exitButtonClick.setRectPos(exitButtonClick.getXPos(), exitButtonClick.getYPos());

    SDL_RenderPresent(gScreen);
    FPS fpsTimer;
    MouseEvents mouse;
    bool quit = false;
    while (!quit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool selectSoundOnButton = bool(mouse.checkMouseInButton(&soundOnButton));
        bool selectSoundOffButton = bool(mouse.checkMouseInButton(&soundOffButton));
        bool selectBackButton = bool(mouse.checkMouseInButton(&backButton));
        bool selectSaveButton = bool(mouse.checkMouseInButton(&saveButton));
        bool selectRestoreButton = bool(mouse.checkMouseInButton(&restoreButton));
        bool selectExitButton = bool(mouse.checkMouseInButton(&exitButton));
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN 
                    && (selectBackButton || selectExitButton))) {
                quit = true;
                display = typeDisplay::RE_MENU;
                break;
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
                    break;
                }
            }
        }

        if (quit == true) break;

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, 
                                RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        background.render(gScreen);
        boardSettings.render(gScreen);
        if (setSound == true) {
            if (selectSoundOnButton == false) soundOnButton.render(gScreen);
            else soundOnButtonClick.render(gScreen);
        }
        else {
            if (selectSoundOffButton == false) soundOffButton.render(gScreen);
            else soundOffButtonClick.render(gScreen);
        }
        if (selectSaveButton == false) saveButton.render(gScreen);
        else saveButtonClick.render(gScreen);
        if (selectRestoreButton == false) restoreButton.render(gScreen);
        else restoreButtonClick.render(gScreen);
        if (selectBackButton == false) backButton.render(gScreen);
        else backButtonClick.render(gScreen);
        if (selectExitButton == false) exitButton.render(gScreen);
        else exitButtonClick.render(gScreen);
        SDL_RenderPresent(gScreen);

        int realTime = fpsTimer.getTicks();
        int timeOneFrame = MS_ONE_SECOND / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
        }
    }
    background.cleanUp();
    boardSettings.cleanUp();
    soundOnButton.cleanUp();
    soundOffButton.cleanUp();
    saveButton.cleanUp();
    restoreButton.cleanUp();
    backButton.cleanUp();
    exitButton.cleanUp();
}

void BounceBall::displayHowToPlayButton() {
    BaseObject background;
    background.loadImage("Resources/Image/background/background.jpg", gScreen);

    BaseObject howToPlay;
    howToPlay.loadImage("Resources/Image/HowToPlay/HowToPlay.png", gScreen);
    howToPlay.setRectPos((SCREEN_WIDTH - howToPlay.getRect().w) / 2,
        (SCREEN_HEIGHT - howToPlay.getRect().h) / 2);

    ButtonObject backButton;
    backButton.loadImage("Resources/Image/button/back_button.png", gScreen);
    backButton.setXPos(0);
    backButton.setYPos(SCREEN_HEIGHT - backButton.getRect().h);
    backButton.setRectPos(backButton.getXPos(), backButton.getYPos());

    ButtonObject backButtonClick;
    backButtonClick.loadImage("Resources/Image/button/back_button_click.png", gScreen);
    backButtonClick.setXPos(0);
    backButtonClick.setYPos(SCREEN_HEIGHT - backButtonClick.getRect().h);
    backButtonClick.setRectPos(backButtonClick.getXPos(), backButtonClick.getYPos());

    const int PLAY_BUTTON_WIDTH = 192;
    const int PLAY_BUTTON_HEIGHT = 64;

    ButtonObject playButton;
    playButton.loadImage("Resources/Image/button/menu_button_play.png", gScreen);
    playButton.setRectSize(PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT);
    playButton.setRectPos(SCREEN_WIDTH - playButton.getRect().w, SCREEN_HEIGHT - playButton.getRect().h);

    ButtonObject playButtonClick;
    playButtonClick.loadImage("Resources/Image/button/menu_button_play_click.png", gScreen);
    playButtonClick.setRectSize(PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT);
    playButtonClick.setRectPos(SCREEN_WIDTH - playButton.getRect().w, SCREEN_HEIGHT - playButton.getRect().h);

    SDL_RenderPresent(gScreen);

    MouseEvents mouse;
    FPS fpsTimer;
    bool quit = 0;
    while (!quit) {
        fpsTimer.start();
        mouse.mouseHandleEvent();
        bool clickBackButton = bool(mouse.checkMouseInButton(&backButton));
        bool clickPlayButton = bool(mouse.checkMouseInButton(&playButton));
        while (SDL_PollEvent(&gEvent)) {
            if (gEvent.type == SDL_QUIT) exit(0);
            if ((gEvent.type == SDL_MOUSEBUTTONDOWN)) {
                if (clickBackButton || clickPlayButton) {
                    background.cleanUp();
                    howToPlay.cleanUp();
                    backButton.cleanUp();
                    backButtonClick.cleanUp();
                    playButton.cleanUp();
                    playButtonClick.cleanUp();
                }
                if (clickBackButton) {
                    quit = true;
                    display = typeDisplay::RE_MENU;
                    return;
                }
                if (clickPlayButton) {
                    display = typeDisplay::PLAY;
                    if (infoPlayer->getUsername() == "") display = typeDisplay::LOGIN;
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
        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
            RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);
        background.render(gScreen);
        howToPlay.render(gScreen);
        if (clickBackButton == false) backButton.render(gScreen);
        else backButtonClick.render(gScreen);
        if (clickPlayButton == false) playButton.render(gScreen);
        else playButtonClick.render(gScreen);
        SDL_RenderPresent(gScreen);
        int realTime = fpsTimer.getTicks();
        int timeOneFrame = MS_ONE_SECOND / FRAME_PER_SECOND;
        if (realTime < timeOneFrame) {
            int delayTime = timeOneFrame - realTime;
            if (delayTime >= 0)
                SDL_Delay(delayTime);
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

    if (TTF_Init() == -1) return false;
    fontGame = TTF_OpenFont("Resources/Font/no_continue.ttf", FONT_SIZE);
    if (fontGame == NULL) {
        return false;
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