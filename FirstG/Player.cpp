#pragma once

#include"Common.h"
#include"Player.h"
#include"Menu.h"



Player::Player()
{
	x_val = 0;
	y_val = 0;

	x_pos = 0;
	y_pos = 0;

	map_x = 0;
	map_y = 0;

	f_w = 0;
	f_h = 0;

	frame = 0;
	move.left = 0;
	move.right = 0;

	status = -1;
	attack = 0;
	dir_atk = atk_right;

	score = 0;
	revive_time = 0;
	
	is_win = 0;
}

Player::~Player()
{

}

bool Player::LoadImage(std::string path, SDL_Renderer* render)
{
	int ret = Base::LoadImage(path.c_str(), render);
	if (ret)
	{
		f_w = O_Rect.w / N_Frame;
		f_h = O_Rect.h;
	}
	return ret;
}

void Player::SetClip()
{
	if (f_w > 0 && f_h > 0)
	{
		for (int i = 0; i < N_Frame; i++)
		{
			f_clip[i].x = i * f_w;
			f_clip[i].y = 0;
			f_clip[i].w = f_w;
			f_clip[i].h = f_h;
		}
	}
}

SDL_Rect Player::P_getRect()
{
	SDL_Rect temp;
	temp.x = O_Rect.x;
	temp.y = O_Rect.y;
	temp.w = f_w;
	temp.h = f_h;
	return temp;
}

void Player::HandleKey(SDL_Event e_,SDL_Renderer*render,Time&_time_game)
{
	if (e_.type == SDL_KEYDOWN)
	{
		switch (e_.key.keysym.sym)
		{
		case SDLK_a:
		{
			status = left;
			move.left = 1;
			move.right = 0;
			dir_atk = atk_left;
			attack = 0;
			break;
		}
		case SDLK_d:
		{
			status = right;
			move.left = 0;
			move.right = 1;
			dir_atk = atk_right;
			attack = 0;
			break;
		case SDLK_s:
			status = down;
			move.down = 1;
			move.up = 0;
			dir_atk = atk_down;
			attack = 0;
			break;
		case SDLK_w:
			status = up;
			move.up = 1;
			move.down = 0;
			dir_atk = atk_up;
			attack = 0;
			break;
		case SDLK_p:
		{
			Pause_game p_g;
			/*if (_time_game.get_Pause())
			{
				_time_game.Un_Pause()
			}
			else
			{
				_time_game.Pause();
			}*/
			p_g.setPause(render,_time_game);
			break;
		}
		}
		}
	}
	else if (e_.type == SDL_KEYUP)
	{
		switch (e_.key.keysym.sym)
		{
		case SDLK_a:
			move.left = 0;
			status = none;
			break;
		case SDLK_d:
			move.right = 0;
			status = none;
			break;
		case SDLK_s:
			move.down = 0;
			status = none;
			break;
		case SDLK_w:
			move.up = 0;
			status = none;
			break;
		}
	}
	if (e_.type == SDL_MOUSEBUTTONDOWN)
	{
		switch (e_.button.button)
		{
		case SDL_BUTTON_RIGHT:
		{
			Bullet* p_bull = new Bullet;
			if (p_bull != NULL)
			{
				//p_bull->LoadImage("img/shot.png", render);
				{
					if(dir_atk==atk_right)
					{
						p_bull->set_Bullet_Pos(x_pos+ f_w - 50, y_pos+f_h*0.1);
						p_bull->set_dir_bullet(Bullet::b_right);
					}
					else if (dir_atk == atk_left)
					{
						p_bull->set_Bullet_Pos(x_pos- 10, y_pos+f_h*0.1);
						p_bull->set_dir_bullet(Bullet::b_left);
					}
					else if (dir_atk == atk_up)
					{
						p_bull->set_Bullet_Pos(x_pos + 10, y_pos-10);
						p_bull->set_dir_bullet(Bullet::b_up);
					}
					else if (dir_atk == atk_down)
					{
						p_bull->set_Bullet_Pos(x_pos, y_pos+f_h-20);
						p_bull->set_dir_bullet(Bullet::b_down);
					}
					p_bull->set_x_val(BULLET_SPEED);
					p_bull->set_y_val(BULLET_SPEED);
					p_bull->set_move(1);
					list_bullet.push_back(p_bull);
				}
			}
			attack = 1;
			break;
		}
		}

	}
}

void Player::P_Shot(SDL_Renderer* render,Map&data_map)
{
	for (int i = 0; i < list_bullet.size(); i++)
	{
		Bullet* p_bull = list_bullet[i];
		if (p_bull != NULL)
		{
			if (p_bull->get_move())
			{
				p_bull->set_Map_Bullet(data_map.start_x, data_map.start_y);
				p_bull->shot_for_P(x_pos- LIM_DIS_BULLET,x_pos+ LIM_DIS_BULLET,y_pos- LIM_DIS_BULLET,y_pos+ LIM_DIS_BULLET, render);
				p_bull->RenderBullet(render);
			}
			else
			{
				list_bullet.erase(list_bullet.begin() + i);
				if (p_bull != NULL);
				{
					delete p_bull;
					p_bull = NULL;
				}
			}
		}
	}
}

void Player::Remove_Bullet(const int& idx)
{
	int s = list_bullet.size();
	if (s > 0 && s >idx)
	{
		Bullet* bull_temp = list_bullet[idx];
		if (bull_temp != NULL)
		{
			list_bullet.erase(list_bullet.begin() + idx);
			delete bull_temp;
		}
	}
}

void Player::Move(Map& data_map, SDL_Renderer* render, Time& _time, bool& win, bool& play)
{
	if(revive_time==0)
	{
		x_val = 0;
		y_val = 0;
		if (move.left == 1)
		{
			x_val -= SPEED;
		}
		else if (move.right == 1)
		{
			x_val += SPEED;
		}
		if (move.up == 1)
		{
			y_val -= SPEED;
		}
		else if (move.down == 1)
		{
			y_val += SPEED;
		}
		CheckMap(data_map,render,_time,win,play);
		CenterOnPlayer(data_map);
	}
	if(revive_time>0)
	{
		revive_time--;
		if (revive_time == 0)
		{
			x_val = 0;
			y_val = 0;
			if(dir_atk==atk_left)
			{
				x_pos += 150;
			}
			else if(dir_atk==atk_right)
			{
				x_pos -= 150;
			}
			else if (dir_atk == atk_up)
			{
				y_pos += 150;
			}
			else if (dir_atk == atk_down)
			{
				y_pos -= 150;
			}
		}
	}
}

void Player:: CheckMap(Map& data_map, SDL_Renderer* render, Time& _time, bool& win, bool& play)
{
	int x1(0), x2(0), y1(0), y2(0);
	//check x
	int hMin = (f_h > TILE_SIZE) ? TILE_SIZE : f_h;

	x1 = (x_pos+x_val) / TILE_SIZE;
	x2 = (x_pos + f_w + x_val - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + hMin-1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
	{
		if (x_val > 0)
		{
			int val1 = data_map.tile[y1][x2];
			int val2 = data_map.tile[y2][x2];
			if ((val1 != 2 && val1 != 5) || (val2 != 2 && val2 != 5))
			{
				if ((val1==166) || (val2==166))
				{
					Increase_Score();
					Increase_Score();
					Increase_Score();
					data_map.tile[y1][x2] = 2;
					data_map.tile[y2][x2] = 2;
				}
				else if ((val1 == 167) || (val2 == 167))
				{
					/*SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
						"Congratulate",
						"You Win",
						NULL);
					SDL_Quit();*/
					/*Result_game win;
					is_win = win.create_result("img//Menu//win.jpg", render, _time);
					setPos(200, 300);
					set_default_move();
					set_status(none);
					set_Score();*/
					win = 1;
					play = 0;
					setPos(200, 300);
					set_default_move();
					set_status(none);
					//set_Score();
				}
				else
				{
					x_pos = x2 * TILE_SIZE;
					x_pos -= f_w + 1;
					x_val = 0;
				}
			}
		}
		else if (x_val < 0)
		{
			int val1 = data_map.tile[y1][x1];
			int val2 = data_map.tile[y2][x1];
			if ((val1 != 2 && val1 != 5) || (val2 != 2 && val2 != 5))
			{
				if ((val1 == 166) || (val2 == 166))
				{
					Increase_Score();
					Increase_Score();
					Increase_Score();
					data_map.tile[y1][x1] = 2;
					data_map.tile[y2][x1] = 2;
				}
				else if ((val1 == 167) || (val2 == 167))
				{
					win = 1;
					play = 0;
					setPos(200, 300);
					set_default_move();
					set_status(none);
					//set_Score();
				}
				else
				{
					x_pos = (x1 + 1) * TILE_SIZE;
					x_val = 0;
				}
			}
		}
	}
	//check y
	int wMin = (f_w > TILE_SIZE) ? TILE_SIZE : f_w;

	x1 = (x_pos ) / TILE_SIZE;
	x2 = (x_pos + wMin) / TILE_SIZE;

	y1 = (y_pos+y_val) / TILE_SIZE;
	y2 = (y_pos + y_val+f_h-1) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
	{
		if (y_val > 0)
		{
			int val1 = data_map.tile[y2][x1];
			int val2 = data_map.tile[y2][x2];
			if ((val1 != 2 && val1 != 5) || (val2 != 2 && val2 != 5))
			{
				if ((val1 == 166) || (val2 == 166))
				{
					Increase_Score();
					Increase_Score();
					Increase_Score();
					data_map.tile[y1][x2] = 2;
					data_map.tile[y2][x2] = 2;
				}
				else if ((val1 == 167) || (val2 == 167))
				{
					win = 1;
					play = 0;
					setPos(200, 300);
					set_default_move();
					set_status(none);
					set_Score();
				}
				else
				{
					y_pos = y2 * TILE_SIZE;
					y_pos -= (f_h + 1);
					y_val = 0;
				}
			}
		}
		else if (y_val < 0)
		{
			int val1 = data_map.tile[y1][x1];
			int val2 = data_map.tile[y1][x2];
			if ((val1 != 2 && val1 != 5) || (val2 != 2 && val2 != 5))
			{
				if ((val1 == 166) || (val2 == 166))
				{
					Increase_Score();
					Increase_Score();
					Increase_Score();
					data_map.tile[y1][x1] = 2;
					data_map.tile[y1][x2] = 2;
				}
				else if ((val1 == 167) || (val2 == 167))
				{
					win = 1;
					play = 0;
					setPos(200, 300);
					set_default_move();
					set_status(none);
					set_Score();
				}
				else
				{
					y_pos = (y1 + 1) * TILE_SIZE;
					y_val = 0;
				}
			}
		}
	}

	x_pos += x_val;
	y_pos += y_val;
}
void Player::CenterOnPlayer(Map& data_map)
{
	data_map.start_x = x_pos - WIDTH / 2;
	if (data_map.start_x < 0)
	{
		data_map.start_x = 0;
	}
	else if (data_map.start_x > data_map.max_x - WIDTH)
	{
		data_map.start_x = data_map.max_x - WIDTH;
	}
	data_map.start_y = y_pos - HEIGHT/ 2;
	if (data_map.start_y < 0)
	{
		data_map.start_y = 0;
	}
	else if (data_map.start_y >= data_map.max_y - HEIGHT)
	{
		data_map.start_y = data_map.max_y - HEIGHT;
	}
}

void Player::Show(SDL_Renderer* render)
{
	if(revive_time==0)
	{
		Up(render);
		O_Rect.x = x_pos - map_x;
		O_Rect.y = y_pos - map_y;

		if (move.right == 1 || move.left == 1 || move.down == 1 || move.up == 1 || attack)
		{
			frame++;
		}
		else frame = 0;
		if (attack && frame >= 24)attack = 0;
		frame = (frame >= 24) ? 0 : frame;
		SDL_Rect RenderQ{ O_Rect.x,O_Rect.y,f_w,f_h };
		SDL_RenderCopy(render, OBJ, &f_clip[frame / 3], &RenderQ);
	}
}

void  Player:: Up(SDL_Renderer*render)
{
	if(attack==0)
	{
		if (status == left)
		{
			LoadImage("img//Player//left1.png", render);
		}
		else if (status == right)
		{
			LoadImage("img//Player//right1.png", render);
		}
		else if (status == down)
		{
			LoadImage("img//Player//down1.png", render);
		}
		else if (status == up)
		{
			LoadImage("img//Player//up1.png", render);
		}
	}
	else if (attack==1)
	{
		if (dir_atk == atk_right)
		{
			LoadImage("img//Player//attack_right1.png", render);
		}
		if (dir_atk == atk_down)
		{
			LoadImage("img//Player//attack_down1.png", render);
		}
		if (dir_atk == atk_up)
		{
			LoadImage("img//Player//attack_up1.png", render);
		}
		if (dir_atk == atk_left)
		{
			LoadImage("img//Player//attack_left1.png", render);
		}
	}
}