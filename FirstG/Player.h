#pragma once

#include"Common.h"
#include"Base.h"
#include"Bullet.h"
#include"Menu.h"
#define N_Frame 8

class Player :public Base
{
private:
	float x_pos;
	float y_pos;

	int x_val;
	int y_val;

	float map_x;
	float map_y;

	int f_w;
	int f_h;

	SDL_Rect f_clip[N_Frame];
	int frame;
	int status;
	bool attack;
	int dir_atk;

	input move;

	std::vector<Bullet*> list_bullet;

	int score;

	int revive_time;

	bool is_win;

public:

	Player();
	~Player();

	enum dir
	{
		none =9,
		left,
		right,
		down,
		up
	};

	enum atk_dir
	{
		atk_right=20,
		atk_left,
		atk_up,
		atk_down
	};
	void setPos(const int& x, const int& y) { x_pos = x; y_pos = y; };

	void set_x_val(const int& x) { x_val = x; };
	void set_y_val(const int& y) { y_val = y; };
	void set_status(const int& x) { status = x; };
	void set_default_move()
	{
		move.up = 0;
		move.down = 0;
		move.left = 0;
		move.right = 0;
	}

	float get_x_pos()const { return x_pos; };
	float get_y_pos()const { return y_pos; };

	bool get_win() { return is_win; };

	SDL_Rect P_getRect();

	std::vector<Bullet*> getBullet()const { return list_bullet; };

	bool LoadImage(std::string path, SDL_Renderer* render);

	void SetClip();

	void SetMapXY(const int& x, const int& y) { map_x = x; map_y = y; };

	void HandleKey(SDL_Event e_,SDL_Renderer* render,Time& _time_game);

	void Up(SDL_Renderer* render);

	void Move(Map& data_map,SDL_Renderer*render,Time&_time,bool &win,bool&play);

	void CheckMap(Map& data_map, SDL_Renderer* render, Time& _time, bool& win, bool& play);

	void CenterOnPlayer(Map& data_map);

	void P_Shot(SDL_Renderer* render,Map&data_map);

	void Show(SDL_Renderer* render);

	void set_Score() { score = 0; }

	void Increase_Score() { score++; }

	int get_Score()const { return score; };

	void Remove_Bullet(const int& idx);

	void set_revive_time(const int& x) { revive_time = x; };

};