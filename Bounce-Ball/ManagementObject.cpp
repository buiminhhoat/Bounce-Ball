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
#include "CheckpointObject.h"

#include "LevelGame.h"

#include "ManagementObject.h"

using namespace std;

ManagementObject::ManagementObject() {

}

ManagementObject::~ManagementObject() {

}

typedef struct CircleObject {
    float cx;
    float cy;
    float radius;
};

typedef struct RectObject {
    float x1;
    float y1;
    float x2;
    float y2;
};

void ManagementObject::LoadThreatsObject(GameMap &gamemap, SDL_Renderer* Screen) {
    Map c_map = gamemap.GetMap();
    for (int i = 0; i < c_map.max_y_ / TILE_SIZE; ++i) {
        for (int j = 0; j < c_map.max_x_ / TILE_SIZE; ++j) {
            if (c_map.block[i][j] == DYN_THORN) {
                ThreatsObject* dyn_threats = new ThreatsObject;
                if (dyn_threats != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    dyn_threats->LoadImage("img//threats//dyn_thorn.png", Screen);
                    dyn_threats->SetClips();
                    dyn_threats->Set_x_pos(x);
                    dyn_threats->Set_y_pos(y);

                    int pos1 = dyn_threats->Get_y_pos() - SCREEN_HEIGHT;
                    int pos2 = dyn_threats->Get_y_pos() + SCREEN_HEIGHT;

                    dyn_threats->SetAnimationPos(pos1, pos2);
                    dyn_threats->Set_input_up(1);
                    dyn_threats->Set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
                    threats_list.push_back(dyn_threats);
                }
            }
        }
    }

    for (int i = 0; i < c_map.max_y_ / TILE_SIZE; ++i) {
        for (int j = 0; j < c_map.max_x_ / TILE_SIZE; ++j) {
            if (c_map.block[i][j] == THORN) {
                ThreatsObject* thorn_object = new ThreatsObject;
                if (thorn_object != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    thorn_object->LoadImage("img//threats//thorn.png", Screen);
                    thorn_object->SetClips();
                    thorn_object->Set_x_pos(x);
                    thorn_object->Set_y_pos(y);
                    thorn_object->Set_type_move(ThreatsObject::STATIC_THREAT);
                    thorn_object->Set_input_up(0);
                    threats_list.push_back(thorn_object);
                }
            }
        }
    }
}

int checkIntersectBallVsObject(const CircleObject &circle_player, const RectObject &rect_object) {
    float px = circle_player.cx;
    float py = circle_player.cy;

    if (px < rect_object.x1)
        px = rect_object.x1;
    else if (px > rect_object.x2)
        px = rect_object.x2;

    if (py < rect_object.y1)
        py = rect_object.y1;
    else if (py > rect_object.y2)
        py = rect_object.y2;

    float dx = circle_player.cx - px;
    float dy = circle_player.cy - py;

    return (dx * dx + dy * dy) <= circle_player.radius * circle_player.radius;
}

void ManagementObject::checkIntersectThreatsObject(MainObject &Player, Map &map_data, SDL_Renderer* Screen) {
    for (int i = 0; i < threats_list.size(); ++i) {
        ThreatsObject* threats = threats_list.at(i);
        if (threats != NULL) {
            threats->SetMapXY(map_data.start_x_, map_data.start_y_);
            threats->ImpMoveType(Screen);
            threats->DoPlayer(map_data);
            threats->ShowImage(Screen);

            float x1_threats = threats->Get_x_pos();
            float y1_threats = threats->Get_y_pos();
            float x2_threats = x1_threats + threats->Get_width_frame();
            float y2_threats = y1_threats + threats->Get_height_frame();

            float cx_player = Player.Get_x_pos() + Player.Get_width_frame() / 2;
            float cy_player = Player.Get_y_pos() + Player.Get_height_frame() / 2;
            float r_player = min(Player.Get_width_frame(), Player.Get_height_frame()) / 2 - 1;
            RectObject rect_threat = { x1_threats, y1_threats, x2_threats, y2_threats };
            CircleObject circle_player = { cx_player, cy_player, r_player };
            if (checkIntersectBallVsObject(circle_player, rect_threat)) {
                is_IntersectBallVsThreats_ = 1;
            }

        }
    }
}

void ManagementObject::LoadRingsObject(GameMap& gamemap, SDL_Renderer* Screen) {
    Map c_map = gamemap.GetMap();
    for (int i = 0; i < c_map.max_y_ / TILE_SIZE; ++i) {
        for (int j = 0; j < c_map.max_x_ / TILE_SIZE; ++j) {
            if (c_map.block[i][j] == RING_HORIZONTAL) {
                RingsObject* ring_object = new RingsObject;
                if (ring_object != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    ring_object->LoadImage("img//rings//RING_HORIZONTAL.png", Screen);
                    ring_object->SetClips();
                    ring_object->Set_x_pos(x);
                    ring_object->Set_y_pos(y);
                    ring_object->Set_ScoreRing(SCORE_RING_HORIZONTAL);
                    ring_object->Set_is_Vertical(0);
                    rings_list.push_back(ring_object);
                }
            }
            else if (c_map.block[i][j] == RING_VERTICAL)  {
                RingsObject* ring_object = new RingsObject;
                if (ring_object != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    ring_object->LoadImage("img//rings//RING_VERTICAL.png", Screen);
                    ring_object->SetClips();
                    ring_object->Set_x_pos(x);
                    ring_object->Set_y_pos(y);
                    ring_object->Set_ScoreRing(SCORE_RING_VERTICAL);
                    ring_object->Set_is_Vertical(1);
                    rings_list.push_back(ring_object);
                }
            }
        }
    }
}

void ManagementObject::checkIntersectRingsObject(ScoreObject &Score, 
                                                    MainObject &Player, 
                                                    Map& map_data, 
                                                    SDL_Renderer* Screen) {
    for (int i = 0; i < rings_list.size(); ++i) {
        RingsObject* ring_object = rings_list.at(i);
        if (ring_object != NULL) {
            ring_object->SetMapXY(map_data.start_x_, map_data.start_y_);
            ring_object->ShowImage(Screen);

            float x1_ring = ring_object->Get_x_pos();
            float y1_ring = ring_object->Get_y_pos();
            float x2_ring = x1_ring + ring_object->Get_width_frame();
            float y2_ring = y1_ring + ring_object->Get_height_frame();

            float cx_player = Player.Get_x_pos() + Player.Get_width_frame() / 2;
            float cy_player = Player.Get_y_pos() + Player.Get_height_frame() / 2;
            float r_player = min(Player.Get_width_frame(), Player.Get_height_frame()) / 2 - 1;

            RectObject rect_ring = { x1_ring, y1_ring, x2_ring, y2_ring };
            CircleObject circle_player = { cx_player, cy_player, r_player };
            if (checkIntersectBallVsObject(circle_player, rect_ring)
                && ring_object->Get_is_catched() == 0) {
                is_IntersectBallVsRing_ = 1;
                Score.IncreaseScore(ring_object->Get_ScoreRing());
                ring_object->Set_ScoreRing(0);
                ring_object->Set_is_catched(1);
                if (ring_object->Get_is_Vertical()) {
                    ring_object->LoadImage("img//rings//RING_VERTICAL_catched.png", Screen);
                    ring_object->SetClips();
                }
                    
                else {
                    ring_object->LoadImage("img//rings//RING_HORIZONTAL_catched.png", Screen);
                    ring_object->SetClips();
                }
                    
            }
        }
    }
}

void ManagementObject::LoadCheckpointObject(MainObject& Player, GameMap& gamemap, SDL_Renderer* Screen) {
    Map c_map = gamemap.GetMap();
    for (int i = 0; i < c_map.max_y_ / TILE_SIZE; ++i) {
        for (int j = 0; j < c_map.max_x_ / TILE_SIZE; ++j) {
            if (c_map.block[i][j] == START_POINT) {
                Player.Set_pos_checkpoint(j * TILE_SIZE, i * TILE_SIZE);
            }
            else if (c_map.block[i][j] == CHECKPOINT) {
                CheckpointObject* checkpoint_object = new CheckpointObject;
                if (checkpoint_object != NULL) {
                    int x = j * TILE_SIZE;
                    int y = i * TILE_SIZE;
                    checkpoint_object->LoadImage("img//checkpoint//checkpoint.png", Screen);
                    checkpoint_object->SetClips();
                    checkpoint_object->Set_x_pos(x);
                    checkpoint_object->Set_y_pos(y);
                    checkpoint_object->Set_ScoreRing(SCORE_CHECKPOINT);
                    checkpoints_list.push_back(checkpoint_object);
                }
            }
        }
    }
}

void ManagementObject::checkIntersectCheckpointObject(ScoreObject& Score, 
                                                        MainObject& Player, 
                                                        Map& map_data, 
                                                        SDL_Renderer* Screen) {
    for (int i = 0; i < checkpoints_list.size(); ++i) {
        CheckpointObject* checkpoint_object = checkpoints_list.at(i);
        if (checkpoint_object != NULL) {
            checkpoint_object->SetMapXY(map_data.start_x_, map_data.start_y_);
            checkpoint_object->ShowImage(Screen);

            float x1_checkpoint = checkpoint_object->Get_x_pos();
            float y1_checkpoint = checkpoint_object->Get_y_pos();
            float x2_checkpoint = x1_checkpoint + checkpoint_object->Get_width_frame();
            float y2_checkpoint = y1_checkpoint + checkpoint_object->Get_height_frame();

            float cx_player = Player.Get_x_pos() + Player.Get_width_frame() / 2;
            float cy_player = Player.Get_y_pos() + Player.Get_height_frame() / 2;
            float r_player = min(Player.Get_width_frame(), Player.Get_height_frame()) / 2 - 1;

            RectObject rect_checkpoint = { x1_checkpoint, y1_checkpoint, x2_checkpoint, y2_checkpoint };
            CircleObject circle_player = { cx_player, cy_player, r_player };
            if (checkIntersectBallVsObject(circle_player, rect_checkpoint)
                && checkpoint_object->Get_is_catched() == 0) {
                is_IntersectBallVsRing_ = 1;
                Score.IncreaseScore(checkpoint_object->Get_ScoreRing());
                checkpoint_object->Set_ScoreRing(0);
                
                int id_checkpoint = Player.Get_id_checkpoint();
                if (id_checkpoint != -1) {
                    CheckpointObject* last_checkpoint = checkpoints_list.at(id_checkpoint);
                    last_checkpoint->LoadImage("img//checkpoint//checkpoint_clear.png", Screen);
                    last_checkpoint->SetClips();
                }
                checkpoint_object->Set_is_catched(1);
                Player.Set_pos_checkpoint(x1_checkpoint, y1_checkpoint);
                Player.Set_id_checkpoint(i);
                checkpoint_object->LoadImage("img//checkpoint//checkpoint_catched.png", Screen);
                checkpoint_object->SetClips();
            }
        }
    }
}

void ManagementObject::LoadALLObject(MainObject& Player, GameMap& gamemap, SDL_Renderer* Screen) {
    LoadThreatsObject(gamemap, Screen);
    LoadRingsObject(gamemap, Screen);
    LoadCheckpointObject(Player, gamemap, Screen);
}

void ManagementObject::checkIntersectALLObject(ScoreObject& Score, 
                                                MainObject& Player, 
                                                Map& map_data, 
                                                SDL_Renderer* Screen) {
    checkIntersectThreatsObject(Player, map_data, Screen);
    checkIntersectRingsObject(Score, Player, map_data, Screen);
    checkIntersectCheckpointObject(Score, Player, map_data, Screen);
}