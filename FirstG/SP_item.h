#pragma once

#include"Common.h"
#include"Base.h"

#define N_HP 7
#define N_Clock 8
#define N_Fire 7
class HP :public Base
{
private:
	int hp_w;
	int hp_h;

	int lv_HP;

	SDL_Rect HP_clip[N_HP];

public:
	HP();
	~HP();
	bool LoadHP(std::string path, SDL_Renderer* render);
	void Set_HP_clip();
	void HP_Show(SDL_Renderer* render);
	void set_Lv_HP(const int& x) { lv_HP = x; };
};

class Clock :public Base
{
private:
	int clock_w;
	int clock_h;

	int frame;
	SDL_Rect Clock_clip[N_Clock];
public:
	Clock();
	~Clock();

	int get_clock_w()const { return clock_w; };
	int get_clock_h()const { return clock_h; };

	bool Load_Clock(std::string path, SDL_Renderer* render);
	void Set_Clock_Clip();
	void Clock_Show(SDL_Renderer* render);
};

class Fire :public Base
{
private:
	int fire_w;
	int fire_h;

	int x_pos;
	int y_pos;

	int map_x;
	int map_y;

	int frame;
	SDL_Rect Fire_clip[N_Fire];
public:
	Fire();
	~Fire();
	void set_fire_pos(const int& x, const int& y) { x_pos = x; y_pos = y; };
	void set_fire_map(const int& x, const int& y) { map_x = x; map_y = y; };
	void set_fire_frame(const int& x) { frame = x; };
	bool Load_Fire(std::string path, SDL_Renderer* render);
	void set_Fire_Clip();
	void Fire_Show(SDL_Renderer* render);

};