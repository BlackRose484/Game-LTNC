#include"Pet.h"

Pet::Pet()
{
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;

	CurrentTime = 0;
	LastTime = 0;
	pet_frame = 0;
	bool is_attack = 0;

	pet_frame = 0;
	n_frame = 0;
	pet_frame_attack = 0;
	n_frame_attack = 0;

	pet_flip = SDL_FLIP_NONE;

	rolate_angle = 0;

}

Pet::~Pet()
{

}

bool Pet:: LoadImage(std::string path, SDL_Renderer* render)
{
	bool ret = Base::LoadImage(path.c_str(), render);
	if (ret)
	{
		pet_w = O_Rect.w / (n_frame+n_frame_attack);
		pet_h = O_Rect.h;
	}
	return ret;
}

void Pet::SetClip()
{
	for (int i = 0; i < n_frame + n_frame_attack; i++)
	{
		pet_clip[i].x = pet_w*i;
		pet_clip[i].y = 0;
		pet_clip[i].w = pet_w;
		pet_clip[i].h = pet_h;
	}
}


void Pet::Show(SDL_Renderer*render)
{
	O_Rect.x = x_pos - x_map;
	O_Rect.y = y_pos - y_map;

	if(!is_attack)
	{
		pet_frame++;
		pet_frame = (pet_frame >= n_frame * 8) ? 0 : pet_frame;
		SDL_Rect RenderQ = { O_Rect.x,O_Rect.y,pet_w,pet_h };
		SDL_RenderCopyEx(render, OBJ, &pet_clip[pet_frame / 8], &RenderQ, 0.0, NULL, pet_flip);
	}
	else
	{
		pet_frame_attack++;
		pet_frame_attack = (pet_frame_attack >= (n_frame + n_frame_attack) * 8) ? n_frame*8 : pet_frame_attack;
		SDL_Rect RenderQ = { O_Rect.x,O_Rect.y,pet_w,pet_h };
		SDL_RenderCopyEx(render, OBJ, &pet_clip[pet_frame_attack / 8], &RenderQ, 0.0, NULL, pet_flip);
	}

}

void Pet::PetMove(const int& x, const int& y)
{
	x_val = 0;
	y_val = 0;
	if (x_pos < x - 100)
	{
		x_val += Pet_Speed;
	}
	else if (x_pos > x + 100)
	{
		x_val -= Pet_Speed;
	}
	if (y_pos < y - 100)
	{
		y_val += Pet_Speed;
	}
	else if (y_pos > y + 100)
	{
		y_val -= Pet_Speed;
	}
	x_pos += x_val;
	y_pos += y_val;

}

void Pet::LoadBullet(SDL_Renderer* render, int PoNx, int PoNy)
{
	CurrentTime = SDL_GetTicks();
	if(CurrentTime>LastTime +1200)
	{
		Bullet* tmp = new Bullet;
		if (tmp)
		{
			tmp->LoadImage("img//Bullet//shot_left.png", render);
			tmp->set_Bullet_Pos(x_pos, y_pos);
			tmp->set_move(1);
			tmp->SetVel(rolate_angle,PoNx,PoNy);
			list_bullet.push_back(tmp);
		}
		LastTime = CurrentTime;
	}
}

void Pet::PetShot(SDL_Renderer* render, Map& map_)
{
	if(list_bullet.size() > 0)
	{
		for (int i = 0; i < list_bullet.size(); i++)
		{
			Bullet* _bullet = list_bullet[i];
			if (_bullet != NULL)
			{
				if (_bullet->get_move())
				{
					_bullet->set_Map_Bullet(map_.start_x, map_.start_y);
					_bullet->ShotForPet(x_pos - LIM_DIS_BULLET, x_pos + LIM_DIS_BULLET, y_pos - LIM_DIS_BULLET, y_pos + LIM_DIS_BULLET, render);
					_bullet->RenderBullet(render);
				}
				else
				{

					list_bullet.erase(list_bullet.begin() + i);
					if (_bullet != NULL);
					{
						delete _bullet;
						_bullet = NULL;
					}
					
				}
			}
			else delete _bullet;
		}
	}
}

void Pet::Remove_Bullet(const int& idx)
{
	int s = list_bullet.size();
	if (s > 0 && s > idx)
	{
		Bullet* bull_temp = list_bullet[idx];
		if (bull_temp != NULL)
		{
			list_bullet.erase(list_bullet.begin() + idx);
			delete bull_temp;
		}
	}
}