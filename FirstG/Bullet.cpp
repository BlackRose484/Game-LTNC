#include"Common.h"
#include"Base.h"
#include"Bullet.h"

#define BULLET_SPEED 12

Bullet::Bullet()
{
	x_pos = 0;
	y_pos = 0;

	x_val = 0;
	y_val = 0;

	is_move = 0;

	map_x = 0;
	map_y = 0;

	dir_bullet = 0;


}

Bullet::~Bullet()
{

}

void Bullet::shot_for_P(const int& x_left,const int&x_right, const int& y_top,const int&y_bot,SDL_Renderer*render)

{
	if(is_move)
	{
		if (dir_bullet == b_right)
		{
			LoadImage("img//Bullet//shot_right.png", render);
			x_pos += x_val;
			if (x_pos > x_right)
				is_move = 0;
		}
		else if (dir_bullet == b_left)
		{
			LoadImage("img//Bullet//shot_left.png", render);
			x_pos-= x_val;
			if (x_pos < x_left)
				is_move = 0;
		}
		if (dir_bullet == b_up)
		{
			LoadImage("img//Bullet//shot_up.png", render);
			y_pos -= y_val;
			if (y_pos < y_top)
				is_move = 0;
		}
		if (dir_bullet == b_down)
		{
			LoadImage("img//Bullet//shot_down.png", render);
			y_pos += y_val;
			if (y_pos > y_bot)
				is_move = 0;
		}
	}
}

void Bullet::RenderBullet(SDL_Renderer* render)
{
	O_Rect.x = x_pos - map_x;
	O_Rect.y = y_pos - map_y;
	SDL_Rect renderQ{ O_Rect.x,O_Rect.y,O_Rect.w,O_Rect.h };
	SDL_RenderCopy(render, OBJ, NULL, &renderQ);
}

void Bullet::shot_for_T(const int& x_left, const int& x_right, const int& y_top, const int& y_bot, SDL_Renderer* render)
{
	if (is_move)
	{
		if (dir_bullet == b_right)
		{
			x_pos += x_val;
			if (x_pos > x_right)
				is_move = 0;
		}
		else if (dir_bullet == b_left)
		{
			x_pos -= x_val;
			if (x_pos < x_left)
				is_move = 0;
		}
		if (dir_bullet == b_up)
		{
			y_pos -= y_val;
			if (y_pos < y_top)
				is_move = 0;
		}
		if (dir_bullet == b_down)
		{
			y_pos += y_val;
			if (y_pos > y_bot)
				is_move = 0;
		}
	}

}
void Bullet::SetVel(double angle, int PoNx, int PoNy)
{
	x_val = cos(angle * M_PI/180) * BULLET_SPEED*PoNx;
	y_val = sin(angle * M_PI/180) * BULLET_SPEED*PoNy;
}

void Bullet::ShotForPet(const int& x_left, const int& x_right, const int& y_top, const int& y_bot, SDL_Renderer* render)
{
	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < x_left || x_pos>x_right||y_pos<y_top||y_pos>y_bot)
	{
		is_move = 0;
	}
}