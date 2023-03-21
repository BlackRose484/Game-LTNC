#pragma once

#include"Common.h"
#include"Base.h"
#include"Text.h"
#include"Time.h"

class Menu :public Base
{
public:
	int create_menu(std::string path, SDL_Renderer* render,Time &_time_game);
};

class Pause_game :public Base
{
private: 
	bool is_pause;
public:
	Pause_game();
	~Pause_game();
	int setPause(SDL_Renderer* render,Time& _time_game);
	int create_pause(SDL_Renderer* render);

};

class Result_game:public Base
{
public:
	int create_result(std::string path, SDL_Renderer* render, Time& _time_game);
};