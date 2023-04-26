#pragma once

#include"Common.h"
#include"Base.h"

class Bullet :public Base
{
private:
	int x_val;
	int y_val;

	int x_pos;
	int y_pos;

	bool is_move;

	int dir_bullet;

	int map_x;
	int map_y;

	

public:
	Bullet();
	~Bullet();
	enum dir_bullet
	{
		b_left=0,
		b_right,
		b_up,
		b_down
	};

	void set_x_val(const int& x) { x_val = x; };

	void set_y_val(const int& y) { y_val = y; };

	void set_Bullet_Pos(const int& x, const int& y) { x_pos = x; y_pos = y; };

	void set_move(const bool& m) { is_move = m; };

	void set_dir_bullet(const int& d) { dir_bullet = d; };

	void set_Map_Bullet(const int& x, const int& y) { map_x = x; map_y = y; };

	bool get_move()const { return is_move; };
	
	//bool LoadImage(std::string path, SDL_Renderer* render);
	void shot_for_P(const int& x_left, const int& x_right, const int& y_top, const int& y_bot, SDL_Renderer* render);

	void shot_for_T(const int& x_left, const int& x_right, const int& y_top, const int& y_bot, SDL_Renderer* render);

	void RenderBullet(SDL_Renderer* render);

	void SetVel(double angle,int PoNx,int PoNy);

	void ShotForPet(const int& x_left, const int& x_right, const int& y_top, const int& y_bot, SDL_Renderer* render);

};