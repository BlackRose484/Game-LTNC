#pragma once

#include"Common.h"
#include"Base.h"
#include"Bullet.h"

#define T_Frame 32

class Threat :public Base
{
protected:
	int x_pos;
	int y_pos;
	
	int x_val;
	int y_val;

	int T_w;
	int T_h;

	bool is_move;

	int frame;
	int n_frame;
	int frame_attack;
	int n_frame_attack;
	SDL_Rect T_clip[T_Frame];

	int T_map_x;
	int T_map_y;
	SDL_RendererFlip T_flip;

	int T_cb_time;

	int T_dir_bullet;
	std::vector<Bullet*> T_list_bullet;

	int Lim_Left;
	int Lim_Right;

	int Lim_Area_Left;
	int Lim_Area_Right;
	int Lim_Area_Up;
	int Lim_Area_Down;

	input T_input_move;

	bool is_attack;

	int hp_threat;


public:

	enum t_dir_move
	{
		t_none = 50,
		t_left,
		t_right,
		t_up,
		t_down
	};

	Threat();
	~Threat();

	void Set_T_pos(const int& x, const int& y) { x_pos = x; y_pos = y; };

	virtual void Set_CLip_T();

	void Set_Map_T(const int& x, const int& y) { T_map_x = x; T_map_y = y; };

	void Set_T_move(const bool& x) { is_move = x; };

	void Set_T_Dis_move(const int& x, const int& y) { Lim_Left = x; Lim_Right = y; };

	void Set_T_dir_move(const int& x) { T_input_move.left = x; };

	void Set_T_cb_time(const int& x) { T_cb_time = x; };

	void set_Area(const int& x, const int& y, const int& z, const int& t) { Lim_Area_Left = x; Lim_Area_Right = y; Lim_Area_Up = z; Lim_Area_Down = t; };

	void set_Attack(const bool& x) { is_attack = x; };

	void Set_N_frame(const int& x) { n_frame = x; };

	void Set_N_frame_attack(const int& x) { n_frame_attack = x; frame_attack = n_frame*16; };

	int get_T_w()const { return T_w; };

	int get_T_h()const { return T_h; };

	int get_T_x_pos()const { return x_pos; };

	int get_T_y_pos()const { return y_pos; };

	bool get_T_move()const { return is_move; };

	SDL_Rect T_getRect();

	virtual bool LoadImage(std::string path, SDL_Renderer* render);

	void Do_Threat(Map& map_data,SDL_Renderer*render);

	void CheckMap(Map& map_data);

	virtual void show(SDL_Renderer* render);

	void T_Load_Bullet(Bullet* _bullet, SDL_Renderer* render);

	void T_Make_Bullet(SDL_Renderer* render);

	std::vector<Bullet*> get_T_bullet()const { return T_list_bullet; };

	void T_move(SDL_Renderer* render,const int&x,const int&y);

	bool Die_Threat(std::string path, SDL_Renderer* render);

	void Act_Threat(const int &x, const int &y, Map& map_data, SDL_Renderer* render);

	void Set_Hp_Threat(const int& x) { hp_threat = x; }

	void Decresae_HP(const int& x) { hp_threat -= x; };

	int Get_Hp_Threat() { return hp_threat; };
};

