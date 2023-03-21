#pragma once

#include"Common.h"
#include"Base.h"
#include"Threat.h"
#include"Map.h"
#include"Player.h"
#include"Text.h"
#include"SP_item.h"
#include"Menu.h"
#include"Time.h"
#include"Boss_AI.h"
#include"Button.h"
#include"Game_Utis.h"


using namespace std;

string convert_to_string(int number);

string convert_to_String(int health);

int get_from_file(const char* path);

void update(const char* path, int& new_value);

std::vector<Threat*> Create_Threat(SDL_Renderer* gRender);

std::vector<Boss*> Create_Boss(SDL_Renderer* gRender);