#include <vector>
#include <string>
#include <fstream>

#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "FPS.h"

#include "ThreatsObject.h"
#include "RingsObject.h"
#include "ScoreObject.h"
#include "LifeObject.h"
#include "CheckpointObject.h"
#include "TextObject.h"

#include "LevelGame.h"

#include "ManagementObject.h"

using namespace std;

LevelGame::LevelGame() {

}

LevelGame::~LevelGame() {

}

BaseObject Background;
GameMap gamemap;
FPS fps_timer;
MainObject Player;
ManagementObject Object;
ScoreObject Score;
LifeObject Life;
TTF_Font *FontGame;
TextObject ScoreText;
TextObject LifeText;

void ShowScore(SDL_Renderer* Screen) {
    std::string str_Score = "Score: " + std::to_string(Score.GetScore());
    ScoreText.SetText(str_Score);
    ScoreText.LoadFromRenderText(FontGame, gScreen);
    ScoreText.ShowText(gScreen, SCREEN_WIDTH - 250, 15);
}

void ShowLife(SDL_Renderer* Screen) {
    std::string str_Life = "Life: " + std::to_string(Life.GetLife());
    LifeText.SetText(str_Life);
    LifeText.LoadFromRenderText(FontGame, Screen);
    LifeText.ShowText(Screen, 15, 15);
}

void LevelGame::LoadLevelGame() {
    Life.SetLife(ORIGINAL_LIFE);

    gamemap.LoadMap("map//map02.dat");
    gamemap.LoadIMGBlock(gScreen);

    Player.LoadImage("img//ball//ball.png", gScreen);
    Player.Set_Clips();
    Player.Set_pos(gamemap.Get_start_x_player(), gamemap.Get_start_y_player());
    //Player.Set_pos(7200, 1216);

    ScoreText.SetColor(TextObject::WHITE_COLOR);
    LifeText.SetColor(TextObject::WHITE_COLOR);

    Object.LoadALLObject(Player, gamemap, gScreen);

    gamemap.FixMap();

    bool is_quit = false;
    while (!is_quit) {
        fps_timer.start();
        while (SDL_PollEvent(&gEvent) != 0) {
            if (gEvent.type == SDL_QUIT) {
                is_quit = true;
            }
            Player.InputAction(gEvent, gScreen);
        }

        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);

        Background.Render(gScreen, NULL);

        Map map_data = gamemap.getMap();

        Player.SetMapXY(map_data.start_x_, map_data.start_y_);
        Player.DoPlayer(map_data);
        Player.ShowImage(gScreen);

        gamemap.SetMap(map_data);
        gamemap.DrawMap(gScreen);
        
        Object.checkIntersectALLObject(Life, Score, Player, map_data, gScreen);

        ShowScore(gScreen);

        // //SDL_RenderPresent(gScreen);

        if (Object.Get_is_IntersectBallVsThreats()) {
            Player.LoadImage("img//ball//ball_pop.png", gScreen);
            Player.Set_Clips();
            Player.ShowImage(gScreen);

            Life.IncreaseLife(-1);

            if (Life.GetLife() == 0) {
                ShowLife(gScreen);

                SDL_RenderPresent(gScreen);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                    "GameOver!!!",
                    "GameOver!!!",
                    NULL);
                return;
            }
            
            ShowLife(gScreen);

            SDL_RenderPresent(gScreen);
            SDL_Delay(1000);
            Object.Set_is_IntersectBallVsThreats(0);
            Player.LoadImage("img//ball//ball.png", gScreen);
            Player.Set_Clips();
            Player.ShowImage(gScreen);
            Player.Set_pos(Player.Get_x_pos_checkpoint(), Player.Get_y_pos_checkpoint());
            SDL_RenderPresent(gScreen);
        }

        ShowLife(gScreen);

        SDL_RenderPresent(gScreen);

        int real_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_time < time_one_frame) {
            int delay_time = time_one_frame - real_time;
            if (delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }
}

bool initSDL() {
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
        if (TTF_Init() == -1) return false;
        FontGame = TTF_OpenFont("font//no_continue.ttf", 45);
        if (FontGame == NULL) {
            return false;   
        }
    }
    return true;
}

bool LoadBackground() {
    return Background.LoadImage("img//Background.jpg", gScreen);
}

void CleanUp() {
    Background.CleanUp();

    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}
