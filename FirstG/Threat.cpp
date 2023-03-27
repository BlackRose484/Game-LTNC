#include"Common.h"
#include"Base.h"
#include"Threat.h"
#include"Bullet.h"


Threat::Threat()
{
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;

	frame = 0;
	n_frame = 0;
	frame_attack = 0;
	n_frame_attack = 0;

	T_w = 0;
	T_h = 0;

	is_move = 0;

	T_cb_time = 0;

	Lim_Left = 0;
	Lim_Right = 0;

	T_input_move.left = 0;
	T_flip = SDL_FLIP_HORIZONTAL;
	T_dir_bullet = 0;

	Lim_Area_Left = 0;
	Lim_Area_Right = 0;

	hp_threat = 0;
	is_attack = 0;
}
Threat::~Threat()
{

}

bool Threat::LoadImage(std::string path, SDL_Renderer* render)
{
	int ret = Base::LoadImage(path, render);
	if (ret)
	{
		T_w = O_Rect.w / (n_frame+n_frame_attack);
		T_h = O_Rect.h;
	}
	return ret;
}

void Threat::Set_CLip_T()
{
	if (T_h > 0 && T_w > 0)
	{
		for (int i = 0; i < n_frame+n_frame_attack; i++)
		{
			T_clip[i].x = i * T_w;
			T_clip[i].y = 0;
			T_clip[i].w = T_w;
			T_clip[i].h = T_h;
		}
	}
}

void Threat::show(SDL_Renderer* render)
{
	if(hp_threat>0)
	{
		if(!is_attack)
		{
			O_Rect.x = x_pos - T_map_x;
			O_Rect.y = y_pos - T_map_y;

			frame++;
			frame = (frame >= n_frame * 16) ? 0 : frame;
			SDL_Rect renderQ{ O_Rect.x,O_Rect.y,T_w,T_h };
			SDL_RenderCopyEx(render, OBJ, &T_clip[frame / 16], &renderQ, 0.0, NULL, T_flip);
		}
		else
		{
			O_Rect.x = x_pos - T_map_x;
			O_Rect.y = y_pos - T_map_y;

			frame_attack++;
			frame_attack = (frame_attack >= (n_frame + n_frame_attack) * 16) ? n_frame*16 : frame_attack;
			SDL_Rect renderQ{ O_Rect.x,O_Rect.y,T_w,T_h };
			SDL_RenderCopyEx(render, OBJ, &T_clip[frame_attack / 16], &renderQ, 0.0, NULL, T_flip);
		}
	}
}

void Threat::Do_Threat(Map& map_data,SDL_Renderer*render)
{
	if (hp_threat > 0)
	{
		x_val = 0;
		y_val = 0;
		if (T_input_move.left == 1)
		{
			x_val -= T_SPEED;
		}
		else if (T_input_move.right == 1)
		{
			x_val += T_SPEED;
		}
		if (T_input_move.up == 1)
		{
			y_val -= T_SPEED;
		}
		else if (T_input_move.down == 1)
		{
			y_val += T_SPEED;
		}
		CheckMap(map_data);
	}
	else
	{
		//T_cb_time--;
		//Die_Threat("img//threat//vanish.png", render);
	}
}

void Threat::CheckMap(Map& data_map)
{
	int x1(0), x2(0), y1(0), y2(0);
	//check x
	int hMin = (T_h > TILE_SIZE) ? TILE_SIZE : T_h;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + T_w + x_val - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + hMin - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val > 0)
		{
			int val1 = data_map.tile[y1][x2];
			int val2 = data_map.tile[y2][x2];
			if ((val1 != 2 && val1 != 5) || (val2 != 2 && val2 != 5))
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= T_w + 1;
				x_val = 0;
				T_input_move.left = 1;
				T_input_move.right = 0;
				T_flip = SDL_FLIP_HORIZONTAL;

			}
		}
		else if (x_val < 0)
		{
			int val1 = data_map.tile[y1][x1];
			int val2 = data_map.tile[y2][x1];
			if ((val1 != 2 && val1 != 5) || (val2 != 2 && val2 != 5))
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
				T_input_move.left = 0;
				T_input_move.right = 1;
				T_flip = SDL_FLIP_NONE;
			}
		}
	}
	//check y
	int wMin = (T_w > TILE_SIZE) ? TILE_SIZE : T_w;

	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + wMin) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + T_h - 1) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val > 0)
		{
			int val1 = data_map.tile[y2][x1];
			int val2 = data_map.tile[y2][x2];
			if ((val1 != 2 && val1 != 5) || (val2 != 2 && val2 != 5))
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= T_h + 1;
				y_val = 0;
			}
		}
		else if (y_val < 0)
		{
			int val1 = data_map.tile[y1][x1];
			int val2 = data_map.tile[y1][x2];
			if ((val1 != 2 && val1 != 5) || (val2 != 2 && val2 != 5))
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
	}
	if (x_val < 0 && x_pos < Lim_Area_Left+10)
	{
		x_val = 0;
		//T_flip = SDL_FLIP_HORIZONTAL;
	
	}
	else if (x_val > 0 && x_pos > Lim_Area_Right-10)
	{
		x_val = 0;		
		//T_flip = SDL_FLIP_NONE;
	}
	if (y_val < 0 && y_pos < Lim_Area_Up-10)
	{
		y_val = 0;
		//T_flip = SDL_FLIP_HORIZONTAL;

	}
	else if (y_val > 0 && y_pos > Lim_Area_Down+10)
	{
		y_val = 0;
		//T_flip = SDL_FLIP_NONE;
	}
	x_pos += x_val;
	y_pos += y_val;
}

SDL_Rect Threat::T_getRect()
{
	SDL_Rect temp;
	temp.x = O_Rect.x;
	temp.y = O_Rect.y;
	temp.w = T_w;
	temp.h = T_h;
	return temp;
}

void Threat::T_Load_Bullet(Bullet* _bullet, SDL_Renderer* render)
{
	if (hp_threat > 0)
	{
		if (_bullet != NULL)
		{
			_bullet->set_Bullet_Pos(x_pos, y_pos);
			_bullet->set_x_val(T_BULLET_SPEED);
			_bullet->set_y_val(T_BULLET_SPEED);
			_bullet->set_dir_bullet(Bullet::b_left);
			_bullet->set_move(1);
			T_list_bullet.push_back(_bullet);
		}
	}
}

void Threat::T_Make_Bullet(SDL_Renderer* render)
{
	if (hp_threat > 0)
	{
		if (!is_move)
		{
			if (T_list_bullet.size() > 0)
			{
				for (int i = 0; i < T_list_bullet.size(); i++)
				{
					Bullet* _bullet = T_list_bullet[i];
					if (_bullet != NULL)
					{
						if (_bullet->get_move())
						{
							_bullet->shot_for_T(x_pos - LIM_DIS_BULLET_T, x_pos + LIM_DIS_BULLET_T, y_pos - LIM_DIS_BULLET_T, y_pos + LIM_DIS_BULLET_T, render);
							_bullet->RenderBullet(render);
						}
						else
						{
							_bullet->set_move(1);
							_bullet->set_Bullet_Pos(x_pos, y_pos);
						}
					}
					else delete _bullet;
				}
			}
		}
	}
}

void Threat::T_move(SDL_Renderer* render, const int& x, const int& y)
{
	if (hp_threat > 0)
	{
		if (is_move)
		{
			if(!is_attack)
			{
				if (x_pos < Lim_Left)
				{
					T_input_move.left = 0;
					T_input_move.right = 1;
					T_flip = SDL_FLIP_NONE;
				}
				else if (x_pos > Lim_Right)
				{
					T_input_move.left = 1;
					T_input_move.right = 0;
					T_flip = SDL_FLIP_HORIZONTAL;
				}
			}
			else
			{
				if (x_pos>Lim_Area_Left+10&&x_pos>x+10)
				{
					T_flip = SDL_FLIP_HORIZONTAL;
				}
				else if (x_pos<Lim_Area_Right-10 && x_pos<x-10)
				{
					T_flip = SDL_FLIP_NONE;
				}
			}
		}
	}
}

bool Threat::Die_Threat(std::string path, SDL_Renderer* render)
{
	int ret = Base::LoadImage(path, render);
	if (ret)
	{
		T_w = O_Rect.w / T_Frame;
		T_h = O_Rect.h;
	}

	O_Rect.x = x_pos - T_map_x;
	O_Rect.y = y_pos - T_map_y;

	frame++;
	frame = (frame >= 64) ? 0 : frame;
	SDL_Rect renderQ{ O_Rect.x,O_Rect.y,T_w,T_h };
	SDL_RenderCopyEx(render, OBJ, &T_clip[frame / 8], &renderQ, 0.0, NULL, T_flip);
	return ret;
}

void Threat::Act_Threat(const int &x, const int &y,Map& map_data, SDL_Renderer* render)
{
	if(is_move)
	{
		if (x_pos > x && x_pos > Lim_Area_Left+10)
		{
			T_input_move.left = 1;
			T_input_move.right = 0;
			Do_Threat(map_data, render);
		}
		else if (x_pos < x && x_pos < Lim_Area_Right-10)
		{
			T_input_move.left = 0;
			T_input_move.right = 1;
			Do_Threat(map_data, render);
		}
		else
		{
			T_input_move.left = 0;
			T_input_move.right = 0;
		}

		if (y_pos < y && y_pos < Lim_Area_Down-10)
		{
			T_input_move.up = 0;
			T_input_move.down = 1;
			Do_Threat(map_data, render);
		}
		else if (y_pos > y && y_pos > Lim_Area_Up+10)
		{
			T_input_move.up = 1;
			T_input_move.down = 0;
			Do_Threat(map_data, render);
		}
		else
		{
			T_input_move.up = 0;
			T_input_move.down = 0;
		}
	}
}