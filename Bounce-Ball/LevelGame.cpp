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
#include "RSACryptoSystem.h"

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
TextObject RemRingText;

void ShowScore(SDL_Renderer* Screen) {
    std::string str_Score = "Score: " + std::to_string(Score.GetScore());
    ScoreText.SetText(str_Score);
    ScoreText.LoadFromRenderText(FontGame, Screen);
    ScoreText.ShowText(Screen, SCREEN_WIDTH - 200, 5);
}

void ShowLife(SDL_Renderer* Screen) {
    LifeObject* gbar_life = new LifeObject;
    gbar_life->LoadImage("img//life//gbar_life.png", Screen);
    gbar_life->SetClips();
    gbar_life->Set_x_pos(15);
    gbar_life->Set_y_pos(5);
    gbar_life->ShowImage(Screen);
    gbar_life->CleanUp();
    std::string str_Life = " x " + std::to_string(Life.GetLife());
    LifeText.SetText(str_Life);
    LifeText.LoadFromRenderText(FontGame, Screen);
    LifeText.ShowText(Screen, 15 + gbar_life->Get_width_frame(), 5);
}

void ShowRemRings(SDL_Renderer* Screen) {
    RingsObject* gbar_ring = new RingsObject;
    gbar_ring->LoadImage("img//rings//gbar_ring.png", Screen);
    gbar_ring->SetClips();
    gbar_ring->Set_x_pos(325);
    gbar_ring->Set_y_pos(5);
    gbar_ring->ShowImage(Screen);
    gbar_ring->CleanUp();
    std::string str_Ring = " x " + std::to_string(Object.Get_rem_Rings());
    RemRingText.SetText(str_Ring);
    RemRingText.LoadFromRenderText(FontGame, Screen);
    RemRingText.ShowText(Screen, 325 + gbar_ring->Get_width_frame(), 5);
    //Object.Set_rem_Rings(0);
    if (Object.Get_rem_Rings() == 0) {
        Object.OpenAllEndpointObject(Screen);
    }
}

void LevelGame::LoadLevelGame(const char* NameFileMap, SDL_Renderer* Screen, 
                                SDL_Event Event, InfoPlayer* infoPlayer) {
    Score.setScore(infoPlayer->getScore());
    Life.SetLife(infoPlayer->getlife());
    Background.LoadImage("img//Background.jpg", Screen);

    if (TTF_Init() == -1) return;
    FontGame = TTF_OpenFont("font//no_continue.ttf", 30);
    if (FontGame == NULL) {
        return;
    }

    gamemap.LoadMap(NameFileMap);
    gamemap.LoadIMGBlock(Screen);

    Player.LoadImage("img//ball//ball.png", Screen);
    Player.Set_Clips();
    Player.Set_pos(gamemap.Get_start_x_player(), gamemap.Get_start_y_player());

    ScoreText.SetColor(TextObject::WHITE_COLOR);
    LifeText.SetColor(TextObject::WHITE_COLOR);
    RemRingText.SetColor(TextObject::WHITE_COLOR);
    
    Object.setAllObject(&gamemap, &Player, &Score, &Life, infoPlayer);
    Object.LoadALLObject(infoPlayer, Screen);

    gamemap.FixMap();

    bool is_quit = false;
    while (!is_quit) {
        fps_timer.start();
        while (SDL_PollEvent(&Event) != 0) {
            if (Event.type == SDL_QUIT) {
                is_quit = true;
                break;
            }
            Player.InputAction(Event, Screen);
        }
        SDL_SetRenderDrawColor(Screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(Screen);

        Background.Render(Screen, NULL);

        Map map_data = gamemap.getMap();

        Player.SetMapXY(map_data.start_x_, map_data.start_y_);
        Player.DoPlayer(map_data);
        Player.ShowImage(Screen);

        gamemap.SetMap(map_data);
        gamemap.DrawMap(Screen);

        Object.setAllObject(&gamemap, &Player, &Score, &Life, infoPlayer);
        Object.checkIntersectALLObject(Screen);
        Object.setAllObject(&gamemap, &Player, &Score, &Life, infoPlayer);

        ShowScore(Screen);
        ShowRemRings(Screen);

        if (Object.Get_is_IntersectBallVsEndpoint_()) {
            Object.Set_is_IntersectBallVsEndpoint_(0);
            infoPlayer->setlife(Life.GetLife()); 
            infoPlayer->setScore(Score.GetScore());
            infoPlayer->setLevel(infoPlayer->getLevel() + 1);
            RSACryptoSystem AddressLevel;
            string address = "map//level";
            if (infoPlayer->getLevel() < 10) address += "0";
            address += AddressLevel.ConvertNumberToString(infoPlayer->getLevel());
            address += ".map";
            LevelGame::LoadLevelGame(address.c_str(), Screen, Event, infoPlayer);
            return;
        }

        if (Object.Get_is_IntersectBallVsThreats()) {
            Player.LoadImage("img//ball//ball_pop.png", Screen);
            Player.Set_Clips();
            Player.ShowImage(Screen);

            Life.IncreaseLife(-1);

            if (Life.GetLife() == 0) {
                ShowLife(Screen);

                SDL_RenderPresent(Screen);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                    "GameOver!!!",
                    "GameOver!!!",
                    NULL);
                return;
            }
            
            ShowLife(Screen);
            
            SDL_RenderPresent(Screen);
            SDL_Delay(1000);
            Object.Set_is_IntersectBallVsThreats(0);
            Player.LoadImage("img//ball//ball.png", Screen);
            Player.Set_Clips();
            Player.ShowImage(Screen);
            Player.Set_pos(Player.Get_x_pos_checkpoint(), Player.Get_y_pos_checkpoint());
            SDL_RenderPresent(Screen);
        }
        
        ShowLife(Screen);

        SDL_RenderPresent(Screen);

        int real_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_time < time_one_frame) {
            int delay_time = time_one_frame - real_time;
            if (delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }
}